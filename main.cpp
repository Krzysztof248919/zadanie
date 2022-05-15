#include <QtWidgets>

#include "gui_main_window.h"
#include "gui_graph.h"
#include "group.h"


//#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Group group;
    group.random_init();
    Graph test(&group);
    test.show();
    return QApplication::exec();
}

//QApplication app(argc, argv);
//QWidget window;
//
//auto *n_pointsLabel = new QLabel(
//        QApplication::translate("nestedlayouts", "Number of points: "));
//n_pointsLabel->setFixedHeight(10);
//
//auto *clearButton = new QPushButton("Clear");
//auto *closeButton = new QPushButton("Close");
//clearButton->setFixedWidth(50);
//closeButton->setFixedWidth(50);
//
//auto *topLayout = new QHBoxLayout();
//topLayout->addWidget(n_pointsLabel, Qt::AlignLeft);
//
//auto *bottomLayout = new QHBoxLayout();
//bottomLayout->addWidget(clearButton, Qt::AlignRight);
//bottomLayout->addWidget(closeButton, Qt::AlignRight);
//
//auto *mainLayout = new QVBoxLayout();
//mainLayout->addLayout(topLayout);
//
//Group group(10, Point({200, 200}));
//group.random_init();
//Graph canvas(&group);
//mainLayout->addWidget(&canvas);
//mainLayout->addLayout(bottomLayout);
//window.setLayout(mainLayout);
//
//window.setWindowTitle(
//        QApplication::translate("nestedlayouts", "Points"));
//
//n_pointsLabel->setText("Test");
//window.show();
//
//return QApplication::exec();