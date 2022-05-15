//
// Created by k on 12.05.2022.
//

#include "group.h"

#include <random>
#include <chrono>
#include <algorithm>

#include <iostream>

class TimeOutError : public std::runtime_error
{
public:
    TimeOutError(const char* what) : runtime_error(what) {}
};

void Group::random_init(const size_t &n_points) {
    auto sqr = [](auto val) {return val*val;};

    if ((points_scope.x*points_scope.y)/(sqr(point_radius_range)) < n_points)
        throw domain_error("Not enough space for non-overlapping points");

    using namespace chrono;
    // counter makes sure, that generated output is pseudo random even if function is called two times between period of
    // time that is too short for high_resolution_clock
    static uint32_t counter(0);

    // pseudo random generator
    default_random_engine generator(high_resolution_clock::to_time_t(high_resolution_clock::now()) + (counter++));
    // distributions
    uniform_int_distribution<uint32_t> dist_x(point_radius_range, points_scope.x - point_radius_range);
    uniform_int_distribution<uint32_t> dist_y(point_radius_range, points_scope.y - point_radius_range);

    auto start = high_resolution_clock::now();
    const uint32_t timeout_ms(1000);

    points.push_back(Point({dist_x(generator), dist_y(generator)}));
    while (points.size() < n_points) {
        Point new_point = Point({dist_x(generator), dist_y(generator)});
        bool collision = false;
        for (auto& point : points) {
            // pow doesn't work here idk why ( even with #pragma optimize("", off) )
            if (sqr(point.x - new_point.x) + sqr(point.y - new_point.y) <= sqr(2 * point_radius_range)) {
                collision = true;
                break;
            }
        }
        if (not collision)
            points.push_back(new_point);
        if (duration_cast<milliseconds>(high_resolution_clock::now() - start).count() > timeout_ms)
            throw TimeOutError("Initialization maximum time exceeded.");
    }
    update_relative_positions();
    rearrange();
}

void Group::rearrange() {
    sort(points.begin(), points.end(), [](const Point& a, const Point& b)->bool {
        return a.x < b.x;
    });
}

void Group::update_relative_position(vector<Point>::iterator point_iter) {
    point_iter->relative_x = double(point_iter->x) / double (points_scope.x);
    point_iter->relative_y = double(point_iter->y) / double (points_scope.y);
}

void Group::update_relative_positions() {
    for (auto iter = points.begin(); iter < points.end(); ++iter) {
        update_relative_position(iter);
    }
}

void Group::add_point(const Point &point) {
    if (not (point.x <= points_scope.x and point.y <= points_scope.y))
        throw domain_error("Point out of scope");
    points.push_back(point);
    rearrange();
//    points.insert(upper_bound(points.begin(), points.end(), point,
//                              [](const Point& a, const Point& b)->bool {return a.x < b.x;}), point);
}

void Group::remove_point(const vector<Point>::iterator point_iter) {
    points.erase(point_iter);
}

void Group::move(const vector<Point>::iterator point_iter, const Point &destination) {
    if (not (destination.x <= points_scope.x and destination.y <= points_scope.y))
        throw domain_error("Point destination out of scope");
    *point_iter = destination;
    rearrange();
}

void Group::rescale(const Point &new_scope) {
    points_scope = new_scope;
    for (auto &point: points) {
        point.x = point.relative_x*points_scope.x;
        point.y = point.relative_y*points_scope.y;
        cout << point.x << " " << point.y << endl;
    }
}

bool Group::in_range(const Point &point, vector<Point>::iterator center) const {
    auto sqr = [](auto val) {return val*val;};
    return sqr(point.x - center->x) + sqr(point.y - center->y) <= sqr(point_radius_range);
}

vector<Point>::iterator Group::find_in_range(const Point &point) {
    if (not (point.x <= points_scope.x and point.y <= points_scope.y))
        throw domain_error("Point out of scope");
    auto iter = points.begin();
    while (iter < points.end()) {
        if (in_range(point, iter)) break;
        ++iter;
    }
    return iter;
}
