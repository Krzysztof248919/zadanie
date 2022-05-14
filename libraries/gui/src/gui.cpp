//
// Created by k on 13.05.2022.
//
#include "gui.h"

void Canvas::paint(QPainter *painter, QPaintEvent *event) {
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

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    paint(&painter, event);
    painter.end();
}
