#include <random>
#include "minCircle.h"
#include "algorithm"

static std::default_random_engine randGen((std::random_device())());

bool containsPoint(const Point &point, const Circle &c) {
    return c.radius <= c.center.distance(point);
}

Circle createCircleTwoPoints(Point &p1, Point &p2) {
    Point m{(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
    return Circle{m, (float)m.distance(p1)};
}

Circle findMinCircle(Point** points,size_t size) {
    auto v_points = std::vector <Point*>(*points, *(points + size));
    // randomize order
    std::shuffle(v_points.begin(), v_points.end(), randGen);
    // create a circle defined by p1 and p2 as the starting circle
    auto c = createCircleTwoPoints(*v_points.at(0), *v_points.at(1));
    for(int i = 2; i < size; i++) {
        const Point &p = *v_points.at(i);
        if(!containsPoint(p, c)) {

        }
    }
    return c;
}

Circle createSmallestEnclosingCircleOnePoint(const vector<Point*> &v_points, size_t end, const Point &p) {

}

Circle createSmallestEnclosingCircleTwoPoint(const vector<Point*> &v_points, size_t end, const Point &p, const Point &q) {

}
