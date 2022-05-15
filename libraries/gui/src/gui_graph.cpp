//
// Created by k on 13.05.2022.
//
#include "gui_graph.h"

#include <iostream>

Graph::Graph(Group *group_, QWidget *parent): QWidget(parent), group(group_),
background(Qt::black), circleBrush(Qt::darkGray), circlePen(Qt::white, 0) {
    setMinimumSize(200, 200);
    setSizeIncrement(50, 50);
    resize(200, 200);
}

void Graph::paint(QPainter *painter, QPaintEvent *event) {
    painter->fillRect(event->rect(), background);
    painter->setBrush(circleBrush);
    painter->setPen(circlePen);
    painter->save();

    painter->restore();
    for(auto point_it = group->points_begin(); point_it < group->points_end(); ++point_it) {
        painter->save();
        painter->drawEllipse(point_it->x-group->point_radius_range, point_it->y-group->point_radius_range,
                             2*group->point_radius_range, 2*group->point_radius_range);
        painter->restore();
    }
}

void Graph::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    paint(&painter, event);
    painter.end();
}

void Graph::resizeEvent(QResizeEvent *event) {
    uint32_t new_scope_x = event->size().width();
    uint32_t new_scope_y = event->size().height();
    group->rescale({new_scope_x, new_scope_y});
}
