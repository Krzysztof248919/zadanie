//
// Created by k on 12.05.2022.
//

#include "group.h"

#include <random>
#include <chrono>
#include <algorithm>
#include <stdexcept>

bool Group::in_scope(const Point &point) const {
    if (point.x < point_radius_range or point.x > (points_scope.x - point_radius_range))
        return false;
    if (point.y < point_radius_range or point.y > (points_scope.y - point_radius_range))
        return false;
    return true;
}

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

    // pseudo random generator
    static default_random_engine generator(high_resolution_clock::to_time_t(high_resolution_clock::now()));
    // distributions
    uniform_int_distribution<uint32_t> dist_x(point_radius_range, points_scope.x - point_radius_range);
    uniform_int_distribution<uint32_t> dist_y(point_radius_range, points_scope.y - point_radius_range);

    auto start = high_resolution_clock::now();
    const uint32_t timeout_ms(1000);

    add_point(Point({dist_x(generator), dist_y(generator)}));
    while (points.size() < n_points) {
        Point new_point = Point({dist_x(generator), dist_y(generator)});
        if(find_in_extended_range(new_point) == points_end())
            add_point(new_point);
        if (duration_cast<milliseconds>(high_resolution_clock::now() - start).count() > timeout_ms)
            throw TimeOutError("Initialization maximum time exceeded.");
    }
}

void Group::update_relative_position(Point &point) {
    point.relative_x = double(point.x) / double (points_scope.x);
    point.relative_y = double(point.y) / double (points_scope.y);
}

void Group::add_point(Point point) {
    if (not in_scope(point))
        throw domain_error("Point out of scope");
    update_relative_position(point);
    points.insert(upper_bound(points.begin(), points.end(), point,
                              [](const Point& a, const Point& b)->bool {return a.x < b.x;}), point);
}

void Group::remove_point(const vector<Point>::iterator point_iter) {
    points.erase(point_iter);
}

void Group::move(const vector<Point>::iterator point_iter, Point destination) {
    if (not in_scope(destination))
        throw domain_error("Point destination out of scope");
    update_relative_position(destination);
    remove_point(point_iter);
    add_point(destination);
}

void Group::rescale(const Point &new_scope) {
    points_scope = new_scope;
    for (auto &point: points) {
        point.x = point.relative_x*points_scope.x;
        point.y = point.relative_y*points_scope.y;
    }
}

bool Group::in_range(const Point &point, vector<Point>::iterator center) const {
    auto sqr = [](auto val) {return val*val;};
    return sqr(point.x - center->x) + sqr(point.y - center->y) <= sqr(point_radius_range);
}

vector<Point>::iterator Group::find_in_range(const Point &point) {
    if (not in_scope(point))
        throw domain_error("Point out of scope");
    auto iter = points.begin();
    while (iter < points.end()) {
        if (in_range(point, iter)) break;
        ++iter;
    }
    return iter;
}

bool Group::in_extended_range(const Point &point, vector<Point>::iterator center) const {
    auto sqr = [](auto val) {return val*val;};
    return sqr(point.x - center->x) + sqr(point.y - center->y) <= sqr(2*point_radius_range);
}

vector<Point>::iterator Group::find_in_extended_range(const Point &point) {
    if (not in_scope(point))
        throw domain_error("Point out of scope");
    auto iter = points.begin();
    while (iter < points.end()) {
        if (in_extended_range(point, iter)) break;
        ++iter;
    }
    return iter;
}

vector<Point>::iterator Group::find_in_extended_range(const Point &point, vector<Point>::iterator exclude_iter) {
    if (not in_scope(point))
        throw domain_error("Point out of scope");
    auto iter = points.begin();
    while (iter < points.end()) {
        if (iter != exclude_iter and in_extended_range(point, iter))
            break;
        ++iter;
    }
    return iter;
}

