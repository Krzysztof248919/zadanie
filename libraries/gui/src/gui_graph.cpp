//
// Created by k on 13.05.2022.
//
#include "gui_graph.h"

//#include <iostream> // for debug

Graph::Graph(Group *group_, QWidget *parent): QWidget(parent), group(group_), left_clicked_point(group_->points_end()),
                                              background(Qt::black), circleBrush(Qt::darkGray), circlePen(Qt::white, 0) {
    setMinimumSize(200, 200);
    setSizeIncrement(50, 50);
    resize(200, 200);
}

void Graph::paint(QPainter *painter, QPaintEvent *event) {
    // draw background
    painter->fillRect(event->rect(), background);
    painter->setBrush(circleBrush);

    // draw lines
    painter->setPen(linePen);
    for(auto point_it = group->points_begin(); point_it < group->points_end()-1; ++point_it) {
        painter->save();
        painter->drawLine(point_it->x, point_it->y, (point_it+1)->x, (point_it+1)->y);
        painter->restore();
    }
    // draw circles
    painter->setPen(circlePen);
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

void Graph::clear() {
    group->clear();
}

void Graph::mousePressEvent(QMouseEvent *event) {
//    cout << __func__ << endl; // for debug (event tracking)
    if (event->button() == Qt::LeftButton) {
        if (group->find_in_extended_range(Point(event->x(), event->y())) == group->points_end()) {
            // outside of point
            group->add_point(Point({uint32_t(event->x()), uint32_t(event->y())}));
            update();
        }
        left_clicked_point = group->find_in_range(Point(event->x(), event->y()));
    }
    if (event->button() == Qt::RightButton) {
        auto iter = group->find_in_range(Point(event->x(), event->y()));
        if (iter != group->points_end()) {
            group->remove_point(iter);
            update();
        }
    }

}

void Graph::mouseMoveEvent(QMouseEvent *event) {
//    cout << __func__ << endl; // for debug (event tracking)
    if (left_clicked_point != group->points_end()) {
        auto event_point = Point(event->x(), event->y());
        if (group->in_scope(event_point)) {
            auto found_point_iter = group->find_in_extended_range(event_point, left_clicked_point);
            if (found_point_iter == group->points_end()) {
                // if not in extended range of ant point beside itself
                group->move(left_clicked_point, event_point);
                // update left_clicked_point after rearrangement
                left_clicked_point = group->find_in_range(event_point);
                update();
            }
        }

    }
}

void Graph::mouseReleaseEvent(QMouseEvent *event) {
//    cout << __func__ << endl; // for debug (event tracking)
    if (event->button() == Qt::LeftButton) {
        left_clicked_point = group->points_end();
    }
}
