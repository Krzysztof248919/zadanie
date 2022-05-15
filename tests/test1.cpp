//
// Created by k on 11.05.2022.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#warning "doctest 2.4.7 required - 2.4.8 incompatible (TEST_CASE_CLASS broken) !!!"

#include "point.h"
#include "group.h"

using namespace std;

TEST_SUITE_BEGIN("point class tests");
/// friend class to bypass encapsulation
class Point_Test: public Point {
public:
    TEST_CASE_CLASS("valid input") {
        SUBCASE("operator ==") {
            Point point = {100, 50};
            REQUIRE(point.x == 100);
            REQUIRE(point.y == 50);
            REQUIRE(point == Point({100, 50}));
            REQUIRE_FALSE(point == Point({50, 100}));
        }
        SUBCASE("operator *") {
            SUBCASE("case 1") {
                array<double, 2> l_arr({0.5, 0.5});
                Point r_point({100, 50});
                CHECK(l_arr*r_point == Point({50, 25}));
            }
            SUBCASE("case 2") {
                Point l_point({100, 50});
                array<double, 2> r_arr({0.5, 0.5});
                CHECK(r_arr*l_point == Point({50, 25}));
            }
        }
        SUBCASE("operator *=") {
            SUBCASE("case 1") {
                Point point({100, 100});
                array<double, 2> arr({1.5, 1.0});
                point*=arr;
                CHECK(point == Point({150, 100}));
            }
            SUBCASE("case 2") {
                Point point({100, 100});
                array<double, 2> arr({0.1, 1.1});
                point*=arr;
                CHECK(point == Point({10, 110}));
            }
        }
    }
    TEST_CASE_CLASS("exception handling") {
        // not needed
    }
};
TEST_SUITE_END;

TEST_SUITE_BEGIN("group class tests");
/// friend class to bypass encapsulation
class Group_Test {
public:

    TEST_CASE_CLASS("default init") {
        Group group;
        REQUIRE(group.point_radius_range == 10);
        REQUIRE(group.points_scope == Point({200, 200}));
    }
    TEST_CASE_CLASS("valid input") {
        SUBCASE("basic init") {
            Group group(10, Point(200, 300));
            REQUIRE(group.point_radius_range == 10);
            REQUIRE(group.points_scope == Point({200, 300}));
        }
        SUBCASE("random_init") {
            SUBCASE("number of points") {
                SUBCASE("default") {
                    Group group;
                    group.random_init();
                    CHECK(group.points.size() == 10);
                }
                SUBCASE("specified size") {
                    Group group;
                    group.random_init(5);
                    CHECK(group.points.size() == 5);
                }
            }
            SUBCASE("location") {
                SUBCASE("case 1") {
                    Group group;
                    group.random_init();
                    bool failure(false);
                    for (auto &point: group.points) {
                        if (point.x > group.points_scope.x - group.point_radius_range) failure = true;
                        if (point.x < group.point_radius_range) failure = true;
                        if (point.y > group.points_scope.y - group.point_radius_range) failure = true;
                        if (point.y < group.point_radius_range) failure = true;
                    }
                    CHECK_FALSE(failure);
                }
                SUBCASE("case 2") {
                    Group group(3, {30, 30});
                    group.random_init();
                    bool failure(false);
                    for (auto &point: group.points) {
                        if (point.x > group.points_scope.x - group.point_radius_range) failure = true;
                        if (point.x < group.point_radius_range) failure = true;
                        if (point.y > group.points_scope.y - group.point_radius_range) failure = true;
                        if (point.y < group.point_radius_range) failure = true;
                    }
                    CHECK_FALSE(failure);
                }
            }
            SUBCASE("different outputs") {
                Group group1(10, {200, 200});
                group1.random_init(10);
                Group group2(10, {200, 200});
                group2.random_init(10);
                bool failure(false);
                for (size_t i(0); i < 10; ++i) {
                    if (group1.points[i] == group2.points[i]) failure = true;
                }
                CHECK_FALSE(failure);
           }
        }
        SUBCASE("rearrange") {
            Group group(5, {100, 100});
            group.points = {{20, 45}, {10, 55}, {30, 15}, {50, 45}, {40, 70}};
            vector<Point> expected = {{10, 55}, {20, 45}, {30, 15}, {40, 70}, {50, 45}};
            group.rearrange();
            CHECK(group.points == expected);
        }
        SUBCASE("add_point") {
            Group group(5, {100, 100});
            group.points = {{10, 55}, {20, 45}, {30, 15}, {40, 70}, {50, 45}};
            Point new_point({15, 55});
            vector<Point> expected = {
                    {10, 55}, {15, 55}, {20, 45}, {30, 15}, {40, 70}, {50, 45}
            };
            group.add_point(new_point);
            CHECK(group.points == expected);
        }
        SUBCASE("remove_point") {
            Group group(5, {100, 100});
            group.points = {{10, 55}, {20, 45}, {30, 15}, {40, 70}, {50, 45}};
            group.remove_point(group.points.begin()+1);
            vector<Point> expected = {{10, 55}, {30, 15}, {40, 70}, {50, 45}};
            CHECK(group.points == expected);
        }
        SUBCASE("move") {
            Group group(5, {100, 100});
            group.points = {{10, 55}, {20, 45}, {30, 15}, {40, 70}, {50, 45}};
            group.move(group.points.begin()+2, {60, 55});
            vector<Point> expected = {{10, 55}, {20, 45}, {40, 70}, {50, 45}, {60, 55}};
            CHECK(group.points == expected);
        }
        SUBCASE("rescale") {
            SUBCASE("enlarge") {
                Group group(5, {100, 100});
                group.points = {{10, 55}, {20, 45}, {30, 15}, {40, 70}, {50, 45}};
                group.update_relative_positions(); /// !!!
                Point new_scope({200, 200});
                group.rescale(new_scope);
                vector<Point> expected = {
                        {20, 110}, {40, 90}, {60, 30}, {80, 140}, {100, 90}
                };
                CHECK(group.points == expected);
                CHECK(group.points_scope == new_scope);
            }
            SUBCASE("shrink") {
                Group group(5, {200, 200});
                group.points = {{10, 20}, {20, 40}, {30, 60}, {40, 80}, {50, 100}};
                group.update_relative_positions(); /// !!!
                Point new_scope({100, 100});
                group.rescale(new_scope);
                vector<Point> expected = {
                        {5, 10}, {10, 20}, {15, 30}, {20, 40}, {25, 50}
                };
                CHECK(group.points == expected);
                CHECK(group.points_scope == new_scope);
            }
        }
        SUBCASE("in_range") {
            SUBCASE("inside") {
                Group group(5, {100, 100});
                group.points = {{10, 55}, {20, 45}, {30, 15}, {40, 70}, {50, 45}};
                CHECK(group.in_range({12, 57}, group.points.begin()));
            }
            SUBCASE("edge") {
                Group group(5, {100, 100});
                group.points = {{10, 55}, {20, 45}, {30, 15}, {40, 70}, {50, 45}};
                CHECK(group.in_range({15, 55}, group.points.begin()));
            }
            SUBCASE("outside") {
                Group group(5, {100, 100});
                group.points = {{10, 55}, {20, 45}, {30, 15}, {40, 70}, {50, 45}};
                CHECK_FALSE(group.in_range({10, 62}, group.points.begin()));
            }
        }
        SUBCASE("find_in_range") {
            SUBCASE("in range") {
                Group group(5, {100, 100});
                group.points = {{10, 55}, {20, 45}, {30, 15}, {40, 70}, {50, 45}};
                CHECK(group.find_in_range({31,17}) == group.points.begin()+2);
            }
            SUBCASE("out of range") {
                Group group(5, {100, 100});
                group.points = {{10, 55}, {20, 45}, {30, 15}, {40, 70}, {50, 45}};
                CHECK(group.find_in_range({80,50}) == group.points.end());
            }
        }
        SUBCASE("size") {
            Group group(5, {100, 100});
            group.points = {{10, 55}, {20, 45}, {30, 15}, {40, 70}, {50, 45}};
            CHECK(group.size() == 5);
        }
        SUBCASE("clear") {
            Group group(5, {100, 100});
            group.points = {{10, 55}, {20, 45}, {30, 15}, {40, 70}, {50, 45}};
            group.clear();
            CHECK(group.points.size() == 0);
        }
    }
    TEST_CASE_CLASS("exception handling") {
        SUBCASE("add_point") {
            Group group(5, {100, 100});
            CHECK_THROWS_AS(group.add_point({120, 100}), domain_error);
        }
        SUBCASE("move") {
            Group group(5, {100, 100});
            group.points = {{10, 55}, {20, 45}, {30, 15}, {40, 70}, {50, 45}};
            CHECK_THROWS_AS(group.move(group.points.begin(), {120, 0}), domain_error);
        }
        SUBCASE("find_in_range") {
            Group group(5, {100, 100});
            group.points = {{10, 55}, {20, 45}, {30, 15}, {40, 70}, {50, 45}};
            CHECK_THROWS_AS(group.find_in_range({200, 200}), domain_error);
        }
    }
};

TEST_SUITE_END;