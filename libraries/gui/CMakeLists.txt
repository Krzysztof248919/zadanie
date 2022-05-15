add_library(gui src/gui_graph.cpp inc/gui_graph.h src/gui_main_window.cpp inc/gui_main_window.h)

target_include_directories(gui PUBLIC inc/)

target_link_libraries(gui
        PUBLIC
        point_group
        Qt5::Widgets
        Qt5::Core
        )