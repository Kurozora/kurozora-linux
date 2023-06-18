# Multi Threading
## _Implement long task triggered via UI elements_

When building a GUI app using GTK the main thread is used by GTK itself to render elements, stalling this thread by running long tasks (fetching data online, loading resources via the filesystem, etc) means that the app will become unresponsive.

Aside from avoiding lengthy tasks before the actual application is run (slow startup) you should also avoid lengthy tasks in functions called by UI elements triggered by the user, since those will be execute synchronously in the main thread.

In order to avoid freezes, lengthy tasks should be run on another, detatched thread, meaning that the main thread will only invoke the new thread and return, in the meantime this same function can decide to spawn elements like spinners to show to the user that _something is happening in the background_.

When the new thread completes it's task, it should invoke a callback connected to a `Glib::Dispatcher`, which is a utility function that stored a function pointer, one the `emit()` method of the dispatcher is called the connected function is execute **on the main thread**.
This is extremely important, **GTK element should only be modified by the main thread**, this is because internally GTK might be freeing, allocating, or modifying buffers, and *sometimes* the secondary thread may get caught up in a data race and corrupt something, which would make GTK **crash** when trying to read said resource.

## Graphical Representation

```
┌────────────────────────────────┐
│                                │
│                                │
│     Main Thread                │
│                                │
│                                │
└───┬────────────────────────────┘
    │
    │
    │
    │
    │
    │    ┌──────────────────────┐
    │    │                      │
    ├────┤ UI Element Triggered │
    │    │                      │
    │    └──────────┬───────────┘
    │               │
    │               │
    │    ┌──────────▼───────────┐               ┌─────────────────────┐
    │    │                      │               │                     │
    │    │ Show Loading Widgets ├───────────────►  Secondary Thread   │
    │    │                      │               │                     │
    │    └──────────────────────┘               └───────────────────┬─┘
    │                                                               │
    │                                                               │
    │    ┌───────────────────┐                   ┌──────────────┐   │
    │    │                   │                   │              │   │
    ├────┤ GTK keeps working │                   │ Lengthy Task ├───┤
    │    │                   │                   │              │   │
    │    └───────────────────┘                   └──────┬───────┘   │
    │                                                   │           │
    │    ┌───────────────────┐                   ┌──────▼───────┐   │
    │    │                   │                   │              │   │
    │    │ Display result or │                   │ Dispatcher   │   │
    ├────┤ error             ◄───────────────────┤ Emit()       ├───┤
    │    │                   │                   │              │   │
    │    └───────────────────┘                   └──────────────┘   │
    │                                                               │
    │                                                               │
    ▼                                                        ┌──────▼──────────┐
                                                             │                 │
                                                             │ Thread returns  │
                                                             │                 │
                                                             └─────────────────┘
```

## Code Sample
_Taken from the `PrivacyLabel` widget_

**Step 1: define the dispatcher _(CallBack function)_**

``` cpp
popup_callback = std::shared_ptr<Glib::Dispatcher>(new Glib::Dispatcher());
popup_callback->connect([this]() {
    // The only modifications to a GTK widget happen here, in the main thread
    this->popup_text->get_buffer()->set_text(this->policy_text);
});
```

**Step 2: bind a function to a button that invokes a new thread**
``` cpp
gesture_click = Gtk::GestureClick::create();
// Connect function to a button (executed on the main thread)
gesture_click->signal_released().connect([this](const int&, const double&, const double&) {
    // Retrieve policy
    std::cout << "Clicked Button" << std::endl;
    // Here you could show a spinner, for example
    this->popup_window->show();
    // Next is the lengthy task, spawn a new thread for it
    std::thread retrieve_privacy_notice([this]() {
        std::cout << "Thread running..." << std::endl;
        try
        {
            if (!cached)
            {
                cpr::Response response = cpr::Get(
                    cpr::Url("https://api.kurozora.app/v1/legal/privacy-policy")
                );
                if (response.status_code != 200) { throw std::runtime_error("Error: Couldn't retrieve privacy policy"); }
                nlohmann::json response_object = nlohmann::json::parse(response.text);
                if (!response_object["data"]["attributes"]["text"].is_string()) { throw std::runtime_error("Error: malformed response"); }
                this->policy_text = response_object["data"]["attributes"]["text"];
                this->cached = true;
                // You got what you needed, execute the callback function in the main thread
                this->popup_callback->emit();
            }
        }
        catch (std::exception& e)
        {
            // An error Occurred
        }
    });
    // Detathc the thread, otherwise the main thread would be waiting for it and get locked
    retrieve_privacy_notice.detach();
});

label->add_controller(gesture_click);
```

_In this example I used lambdas for cleaner and simpler code, it's not required, but highly suggested._
