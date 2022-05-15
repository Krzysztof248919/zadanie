//
// Created by k on 15.05.2022.
//

#include "gui_main_window.h"

Button::Button(const QString &text, QWidget *parent)
        : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    setText(text);
}
QSize Button::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}

MainWindow::MainWindow(Group* group_, QWidget *parent): graph(group_, this), QWidget(parent) {
    clearButton = createButton(tr("Clear"), SLOT(clearClicked()));
    closeButton = createButton(tr("Close"), SLOT(closeClicked()));
    auto *mainLayout = new QGridLayout;

    mainLayout->addWidget(clearButton, 2, 0, Qt::AlignRight);
    mainLayout->addWidget(closeButton, 2, 1, Qt::AlignRight);

    mainLayout->addWidget(&graph, 1, 0);

    point_counterLabel = new QLabel;
    point_counterLabel->setText("Number of points: ");
    point_counterLabel->setAlignment(Qt::AlignLeft);
    mainLayout->addWidget(point_counterLabel, 0, 0);

    setLayout(mainLayout);
    setWindowTitle(tr("Points"));
}

void MainWindow::clearClicked() {
    graph.clear();
    this->update();
}

void MainWindow::closeClicked() {
    QCoreApplication::quit();
}

Button *MainWindow::createButton(const QString &text, const char *member) {
    auto *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}
