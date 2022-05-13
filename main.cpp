#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.resize(320, 240);
    QLabel label("my label");
    label.show();
    window.show();
    window.setWindowTitle(
            QApplication::translate("toplevel", "Top-level widget"));
    return QApplication::exec();
}