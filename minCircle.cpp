/*
 * minCircle.cpp
 *
 * Author: Itay Etelis - 209041474.
 *         Orel Ben Shamay - 318869658.
 */

#include <random>
#include "minCircle.h"
#include "algorithm"


// check if a given circle contains a points, or if the points lies on the circle's boundaries
bool Circle::containsPoint(const Point& p) const{
    return center.distance(p) <= radius;
}

// create a circle with two given points on its sphere
Circle createCircleTwoPoints(const Point &a, const Point &b) {
    float x = (a.x + b.x) / 2.0;
    float y = (a.y + b.y) / 2.0;
    Point m = Point{x, y};
    return Circle{m, static_cast<float>(m.distance(a))};
}

// creates a circle with three points on its sphere
Circle createCircleThreePoints (const Point &p1, const Point &p2, const Point &p3) {
    float a = p2.x - p1.x;
    float b = p2.y - p1.y;
    float c = p3.x - p1.x;
    float d = p3.y - p1.y;
    float e = a * (p2.x + p1.x) * 0.5 + b * (p2.y + p1.y) * 0.5;
    float f = c * (p3.x + p1.x) * 0.5 + d * (p3.y + p1.y) * 0.5;
    float det = a*d - b*c;
    double cx = (d*e - b*f)/det;
    double cy = (-c*e + a*f)/det;
    return {Point(cx, cy), static_cast<float>(sqrt((p1.x-cx)*(p1.x-cx) + (p1.y-cy)*(p1.y-cy)))};
}

Circle findMinCircleRecursion(vector<Point> &v_points, size_t size, vector<Point> boundary) {
    // terminal cases
    if(boundary.size() == 3) {
        return createCircleThreePoints(boundary.at(0), boundary.at(1), boundary.at(2));
    } else if(size == 1 && boundary.empty()) {
        return {v_points.at(0), 0};
    } else if(size == 0 && boundary.size() == 2) {
        return createCircleTwoPoints(boundary.at(0), boundary.at(1));
    } else if(size == 1 && boundary.size() == 1) {
        return createCircleTwoPoints(v_points.at(0), boundary.at(0));
    } else {
        Point p = v_points.at(size - 1);
        // get the minimum circle without the last point
        Circle c = findMinCircleRecursion(v_points, size - 1, boundary);
        // if the circle contains v_points[i - 1] then return the circle
        if (c.containsPoint(p)) {
            return c;
        }
        // else the point has to be on the boundary of the circle
        boundary.push_back(p);
        // return the minimum circle without the last point in v_points, and with the last point on the boundary points
        return findMinCircleRecursion(v_points, size - 1, boundary);
    }
}

Circle findMinCircle(Point** points, size_t size) {
    // create an empty vector to store the points in
    vector<Point> v_points = {};
    v_points.reserve(size);
    // store the points in a vector
    for(int i = 0; i < size; i++) {
        v_points.push_back(*points[i]);
    }
    // shuffle the points in a random order
    shuffle(v_points.begin(), v_points.end(), std::mt19937(std::random_device()()));
    vector<Point> boundary = {};
    return findMinCircleRecursion(v_points, v_points.size(), {});
}
