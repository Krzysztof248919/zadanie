//
// Created by k on 11.05.2022.
//

#pragma once

#include <cstdint>
#include <array>
using namespace std;

class Point {
public:
    uint32_t x, y;
    double relative_x, relative_y;
    Point() = default;
    Point(uint32_t x_, uint32_t y_): x(x_), y(y_) {};
    Point(uint32_t x_, uint32_t y_, double relative_x_, double relative_y_):
    x(x_), y(y_), relative_x(relative_x_), relative_y(relative_y_) {};

    friend class Point_Test;
};



Point operator * (const array<double, 2>& vec, const Point& point);
Point& operator *= (Point& point, const array<double, 2>& vec);
bool operator == (const Point& point_l, const Point& point_r);