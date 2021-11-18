#include <random>
#include "minCircle.h"
#include "algorithm"
#include "anomaly_detection_util.h"

constexpr static const double EPSILON = 1e-9;
static std::default_random_engine randGen((std::random_device())());

bool collinear(const Point &a, const Point &b, const Point &c) {
    return fabs((a.y - b.y) * (a.x - c.x) - (a.y - c.y) * (a.x - b.x)) <= EPSILON;
}

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

Circle makeCircleThreePoints (const Point &a, const Point &b, const Point &c) {
    // Mathematical algorithm from:: https://www.xarg.org/2018/02/create-a-circle-out-of-three-points/

    float var_1 = a.x * (b.y - c.y) - a.y * (b.x - c.x) + b.x * c.y - c.y * b.y;

    float var_2 = (a.x * a.x + a.y * a.y) * (c.y - b.y) + (b.x * b.x + b.y * b.y) * (a.y - c.y)
                  + (c.x * c.x + c.y * c.y) * (b.y - a.y);

    float var_3 = (a.x * a.x + a.y * a.y) * (b.x - c.x) + (b.x * b.x + b.y * b.y) * (c.x - a.x)
                  + (c.x * c.x + c.y * c.y) * (a.x - b.x);

    float new_x = -var_2 / (2 * var_1);
    float new_y = -var_3 / (2 * var_1);
    float r = hypot(new_x - a.x, new_y - a.y);
    return {Point(new_x, new_y), r};
}