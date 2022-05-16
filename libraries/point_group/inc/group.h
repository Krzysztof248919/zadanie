//
// Created by k on 12.05.2022.
//

#pragma once

#include "point.h"

#include <cstdint>
#include <vector>
using namespace std;


class Group {
private:
    vector<Point> points;           // group of points, in x based order

    [[nodiscard]] bool in_range(const Point& point, vector<Point>::iterator center) const;
    [[nodiscard]] bool in_extended_range(const Point& point, vector<Point>::iterator center) const;
    void update_relative_position(Point& point);

public:
    Group(): point_radius_range(10), points_scope({200, 200}) {};
    Group(uint32_t r, Point scope): point_radius_range(r), points_scope(scope) {};
    Group(Group&) = default;
    ~Group() = default;

    uint32_t point_radius_range;    // radius of point representation
    Point points_scope;             // acceptable scope of point representation

    vector<Point>::iterator points_begin() { return points.begin(); }
    vector<Point>::iterator points_end() { return points.end(); }
    [[nodiscard]] size_t size() const { return points.size(); }
    void clear() { points.clear(); }

    void random_init(const size_t& n_points = 10);              // initialize Group with n random points
    void add_point(Point point);                                // add new point, rearrange
    void remove_point(vector<Point>::iterator point_iter);      // remove point, rearrange
    void move(vector<Point>::iterator point_iter, Point destination);
    void rescale(const Point& new_scope);

    vector<Point>::iterator find_in_range(const Point& point);
    vector<Point>::iterator find_in_extended_range(const Point &point);

    friend class Group_Test;
};