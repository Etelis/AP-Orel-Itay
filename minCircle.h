#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "anomaly_detection_util.h"

using namespace std;

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){};
    bool containsPoint(const Point &point) const;
};
Circle createCircleTwoPoints(const Point &a, const Point &b);
Circle createCircleThreePoints (const Point &p1, const Point &p2, const Point &p3);
Circle findMinCircle(Point** points, size_t size);
Circle findMinCircleRecursion(vector<Point> &v_points, size_t size, vector<Point> boundary);

#endif /* MINCIRCLE_H_ */
