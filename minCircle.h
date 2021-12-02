
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

Circle createCircleTwoPoints(const Point &a, const Point &b);
Circle createCircleThreePoints (const Point &p1, const Point &p2, const Point &p3);
Circle findMinCircle(Point** points, size_t size);
Circle findMinCircleRecursion(vector<Point> &v_points, size_t size, vector<Point> boundary);
bool containsPoint(const Circle &c, const Point &point);

#endif /* MINCIRCLE_H_ */
