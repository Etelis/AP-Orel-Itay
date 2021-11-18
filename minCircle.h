
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

Circle findMinCircle(Point** points,size_t size);
Circle createCircleTwoPoints(Point &p1, Point &p2);
Circle createSmallestEnclosingCircleOnePoint(const vector<Point*> &v_points, size_t end, const Point &p);
Circle createSmallestEnclosingCircleTwoPoint(const vector<Point*> &v_points, size_t end, const Point &p, const Point &q);

#endif /* MINCIRCLE_H_ */
