#include <QtWidgets>

#include "gui.h"
#include "group.h"




//#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;

    auto *n_pointsLabel = new QLabel(
            QApplication::translate("nestedlayouts", "Number of points: "));
    n_pointsLabel->setFixedHeight(10);

    auto *clearButton = new QPushButton("Clear");
    auto *closeButton = new QPushButton("Close");

    auto *topLayout = new QHBoxLayout();
    topLayout->addWidget(n_pointsLabel, Qt::AlignLeft);

    auto *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(clearButton);
    bottomLayout->addWidget(closeButton);

    auto *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topLayout);

    Group group(15, Point({200, 200}));
    group.random_init();
    Canvas canvas(&group);
    mainLayout->addWidget(&canvas);
    mainLayout->addLayout(bottomLayout);
    window.setLayout(mainLayout);
    
    window.setWindowTitle(
            QApplication::translate("nestedlayouts", "Points"));

    n_pointsLabel->setText("Test");
    window.show();


//    canvas.background = Qt::darkRed;


    return QApplication::exec();
}