//
// Created by k on 12.05.2022.
//

#include "group.h"

#include <random>
#include <chrono>
#include <algorithm>

void Group::random_init(const size_t &n_points) {
    auto sqr = [](auto val) {
        return val*val;
    };

    using namespace chrono;
    // counter makes sure, that generated output is pseudo random even if function is called two times between period of
    // time that is too short for high_resolution_clock
    static uint32_t counter(0);

    // pseudo random generator
    default_random_engine generator(high_resolution_clock::to_time_t(high_resolution_clock::now()) + (counter++));
    // distributions
    uniform_int_distribution<uint32_t> dist_x(point_radius_range, points_scope.x - point_radius_range);
    uniform_int_distribution<uint32_t> dist_y(point_radius_range, points_scope.y - point_radius_range);

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
        if (not collision) points.push_back(new_point);
    }
    rearrange();
}

void Group::rearrange() {
    sort(points.begin(), points.end(), [](const Point& a, const Point& b)->bool {
        return a.x < b.x;
    });
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
    const array<double, 2> scale_vec({
        static_cast<double>(new_scope.x / points_scope.x),
        static_cast<double>(new_scope.y / points_scope.y)
    });
    for (auto& point : points) {
        point *= scale_vec;
    }
    points_scope = new_scope;
}

bool Group::in_range(const Point &point, vector<Point>::iterator center) const {
    return pow(point.x - center->x, 2) + pow(point.y - center->y, 2) <= pow(point_radius_range, 2);
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
