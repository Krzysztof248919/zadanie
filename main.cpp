#include <QtWidgets>

#include "gui_main_window.h"
#include "gui_graph.h"
#include "group.h"


//#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Group group;
    group.random_init();
    MainWindow test(&group);
    test.show();
    return QApplication::exec();
}