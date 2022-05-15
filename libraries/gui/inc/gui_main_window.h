//
// Created by k on 15.05.2022.
//

#pragma once

#include <QtWidgets>
#include "gui_graph.h"

class Button : public QToolButton
{
Q_OBJECT

public:
    explicit Button(const QString &text, QWidget *parent = nullptr);

    QSize sizeHint() const override;
};

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void closeClicked();
    void clearClicked();
//    void setPointCounter();
private:
    // unique pointers?
    Button *createButton(const QString &text, const char *member);
    QLabel *point_counterLabel;
//    Graph *graph;
    Button *clearButton;
    Button *closeButton;
};