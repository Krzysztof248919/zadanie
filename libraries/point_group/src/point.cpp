//
// Created by k on 11.05.2022.
//

#include "point.h"


Point operator * (const array<double, 2>& vec, const Point& point) {
    Point output({
        static_cast<uint32_t>(vec[0]*point.x),
        static_cast<uint32_t>(vec[1]*point.y)
    });
    return output;
}

Point& operator *= (Point& point, const array<double, 2>& vec) {
    point.x = vec[0]*point.x;
    point.y = vec[1]*point.y;
    return point;
}

bool operator == (const Point& point_l, const Point& point_r) {
    return point_l.x == point_r.x and point_l.y == point_r.y;
}
