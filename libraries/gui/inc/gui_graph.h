//
// Created by k on 13.05.2022.
//

#pragma once

#include <QtWidgets>
#include "group.h"


class Graph : public QWidget {
    Q_OBJECT
public:
    Graph(Group* group_, QWidget *parent = nullptr);
    void clear();
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    void paint(QPainter *painter, QPaintEvent *event);
    vector<Point>::iterator left_clicked_point;
    Group* group;
    QBrush background = QBrush(Qt::black);
    QBrush circleBrush = QBrush(Qt::darkGray);
    QPen circlePen = QPen(Qt::white, 0);
    QPen linePen = QPen(Qt::green, 0);
};