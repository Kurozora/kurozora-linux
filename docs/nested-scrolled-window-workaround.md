# Nested `GtkScrolledWindow` workaround

When you nest multiple `GtkScrolledWindow` objects and they happen to be of different orientations (one vertical and one horizontal) and unfortunate _"bug"_ will occurr where the scrolling will lock the moment the user cursor is above the nested `GtkScrolledWindow` widget.

This happens due to the `GtkEventControllerScroll` of type `bubble`, which will unnecessarily capture the event and will prevent the top level widget from reacting to it.

_In GTK, event are processed from the inner most widget to the top._

In order to fix this issue, you need to change the `flags` property of the correct `GtkEventControllerScroll` and remove the flag `vertical` or `horizontal` (the opposite of what that nested `GtkEventControllerScroll` orientation is).

Unfortunately, there is no way _(as far as I know)_ to do this directly from a UI file or from a simple `GtkScrolledWindow` property, instead you need to get the list of controllers for the `GtkScrolledWindow`, filter the ones you need and then apply the correct flags.

In order to do this, an helper utility function has been implemented (`kurozora::utils::gtk::fix_nested_scroll(Gtk::Builder* builder)`), which takes the builder where the `GtkScrolledWindow` widgets are defined, it then looks for widgets with the name _`scrolled-window-workaround-*`_ where `*` starts from `0` and increments by one for every `GtkScrolledWindow` that needs the fix.

You can look at the file _source/kurozora/src/utils/gtk/nested-scroll-workaround.cpp_)_ to see the actual implementation, it has been used in _source/kurozora/src/explore-view/explore-view.cpp_ and _resources/ui/widgets/explore-view/explore-view.ui_.
