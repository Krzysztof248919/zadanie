//
// Created by k on 15.05.2022.
//

#pragma once

#include <QtWidgets>
#include "gui_graph.h"
#include "group.h"

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
    MainWindow(Group* group_, QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void closeClicked();
    void clearClicked();
private:
    // unique pointers?
    Group* group;
    Button *createButton(const QString &text, const char *member);
    QLabel *point_counterLabel;
    Graph graph;
    Button *clearButton;
    Button *closeButton;
};