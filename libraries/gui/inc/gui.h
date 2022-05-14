//
// Created by k on 13.05.2022.
//

#pragma once

#include <QtWidgets>
#include "group.h"


class Canvas : public QWidget {
    Q_OBJECT
public:
    Canvas() {
        setMinimumSize(200, 200);
    }
    explicit Canvas(Group* group_): group(group_) {
        setMinimumSize(200, 200);
    }
    Group* group = nullptr;
    QBrush background = QBrush(Qt::black);
    QBrush circleBrush = QBrush(Qt::darkGray);
    QPen circlePen = QPen(Qt::white, 0);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    void paint(QPainter *painter, QPaintEvent *event);
};