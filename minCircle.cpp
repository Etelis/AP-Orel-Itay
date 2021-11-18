#include <random>
#include "minCircle.h"
#include "algorithm"


static std::default_random_engine randGen((std::random_device())());
bool containsPoint(const Point* &point, const Circle &c) const {
    return c.radius <= c.center
}
Circle findMinCircle(Point** points,size_t size) {
    auto v_points = std::vector <Point*>(*points, *(points + size));
    // randomize order
    std::shuffle(v_points.begin(), v_points.end(), randGen);
    // create a circle defined by p1 and p2 as the starting circle
    auto c = Circle(new Point(3,3), 5.5);
    for(int i = 2; i < size; i++) {
        const Point* p = v_points.at(i);

    }
}
