add_library(gui src/gui.cpp inc/gui.h)

target_include_directories(gui PUBLIC inc/)

target_link_libraries(gui
        PUBLIC
        point_group
        Qt5::Widgets
        Qt5::Core
        )