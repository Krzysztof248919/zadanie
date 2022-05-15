//
// Created by k on 15.05.2022.
//

#include "gui_main_window.h"

Button::Button(const QString &text, QWidget *parent)
        : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
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
    point_counterLabel = new QLabel;
    point_counterLabel->setText("Number of points: ");
    point_counterLabel->setAlignment(Qt::AlignLeft);
    point_counterLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    clearButton = createButton(tr("Clear"), SLOT(clearClicked()));
    closeButton = createButton(tr("Close"), SLOT(closeClicked()));

    auto *mainLayout = new QVBoxLayout;
    auto *bottomLayout = new QHBoxLayout;
    bottomLayout->setAlignment(Qt::AlignRight);

    bottomLayout->addWidget(clearButton);
    bottomLayout->addWidget(closeButton);

    mainLayout->addWidget(point_counterLabel);
    mainLayout->addWidget(&graph);
    mainLayout->addLayout(bottomLayout);

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
