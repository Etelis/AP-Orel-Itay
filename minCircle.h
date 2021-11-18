
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "../../assignment/anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}

    bool contains(const Point &p) const;

    bool contains(const vector<Point> &ps) const;
};
// --------------------------------------

Circle findMinCircle(Point** points,size_t size);

// you can add here additional methods

#endif /* MINCIRCLE_H_ */
