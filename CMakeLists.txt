cmake_minimum_required(VERSION 3.22.1)
project(Kurozora VERSION 0.8.2)

add_compile_definitions(APPLICATION_VERSION="0.0.1")

# Set C++ to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

set(CMAKE_CXX_COMPILER "/mingw64/bin/g++.exe")
set(CMAKE_C_COMPILER "/mingw64/bin/gcc.exe")

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0)
pkg_check_modules(GLIB2 glib-2.0)

link_directories(
    ${GTKMM_LIBRARY_DIRS}
)

include_directories(
    "/mingw64/lib/graphene-1.0/include",
    "/mingw64/include/graphene-1.0",
    "/mingw64/include/gtkmm-4.0/gtkmm",
    "/mingw64/include/pangomm-2.48",
    "/mingw64/include/gdk-pixbuf-2.0",
    "/mingw64/include/harfbuzz",
    "/mingw64/include/pango-1.0",
    "/mingw64/include/gtk-4.0",
    "/mingw64/include/freetype2",
    "/mingw64/include/cairo",
    "/mingw64/lib/cairomm-1.16/include",
    "/mingw64/include/cairomm-1.16",
    "/mingw64/lib/pangomm-2.48/include",
    "/mingw64/lib/gtkmm-4.0/include",
    "/mingw64/lib/giomm-2.68/include",
    "/mingw64/include/giomm-2.68",
    "/mingw64/lib/sigc++-3.0/include",
    "/mingw64/include/sigc++-3.0",
    "/mingw64/lib/glib-2.0/include",
    "/mingw64/lib/glibmm-2.4/include",
    "/mingw64/include/gtkmm-4.0",
    "/mingw64/include/glib-2.0",
    "/mingw64/include/glibmm-2.68",
    ${GTKMM_INCLUDE_DIRS},
    ${GLIB2_INCLUDE_DIRS}
)

# Add source files
file(GLOB_RECURSE hnSourceFiles
    "source/*.h"
    "source/*.hpp"
    "source/*.c"
    "source/*.cc"
    "source/*.cpp"
    "config/*" #  Just to be able to browse config files in IDEs
)

add_executable(Kurozora ${hnSourceFiles})

target_compile_options(Kurozora PRIVATE -lstdc++)

# Add and link libraries
target_link_libraries(Kurozora ${GTKMM_LIBRARIES})

# Specify targets output directory
set_target_properties( Kurozora
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug/lib"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug/lib"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release/lib"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release/lib"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/bin/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/bin/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/bin"
    
)

# Copy resources

# Copy configs to binary
file(COPY config DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(COPY ui DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Respect source code folder structure
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# set_property(TARGET Kurozora PROPERTY FOLDER "Kurozora")

# Source Code
file(GLOB_RECURSE hnSource
    "source/*.h"
    "source/*.hpp"
    "source/*.c"
    "source/*.cc"
    "source/*.cpp"
    "source/backend/*.h"
    "source/backend/*.hpp"
    "source/backend/*.c"
    "source/backend/*.cc"
    "source/backend/*.cpp"
    "source/gui/*.h"
    "source/gui/*.hpp"
    "source/gui/*.c"
    "source/gui/*.cc"
    "source/gui/*.cpp"
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/source" PREFIX "Source" FILES ${hnSource})

# Config files
file (GLOB hnConfig
    "config/*"
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/config/" PREFIX "Configuration Files" FILES ${hnConfig})
