#ifndef ANOMALYDETECTORUTIL_H_
#define ANOMALYDETECTORUTIL_H_
#include <cstddef>
#include <math.h>

class Line{
public:
    float a,b;
    Line():a(0),b(0){}
    Line(float a, float b):a(a),b(b){}
    float f(float x) const{
        return a*x+b;
    }
};

class Point{
public:
    float x,y;
    Point(float x, float y):x(x),y(y){}
    double distance(const Point &p) const{ return sqrt(pow(this->x - p.x, 2) + pow(this->y-p.y, 2)); }
};

// returns the average of a float array.
float avg(float* x, size_t size);

// returns the variance of X and Y.
float var(float* x, size_t size);

// returns the covariance of X and Y.
float cov(float* x,  float* y, size_t size);

// returns the average of both arrays x and y when multiplying each value.
float multiplyAvg(float* x, float* y, size_t size);

// returns the Pearson corrlation coefficient of X and Y.
float pearson(float* x, float* y, size_t size);

// performs a linear regression and returns the line equation.
Line linear_reg(Point** points, size_t size);

// returns the deviation between point p and the line equation of the points.
float dev(Point p,Point** points, size_t size);

// returns the deviation between point p and the line.
float dev(Point p,Line l);

// returns the max deviation between point p and the line
float maxDev(Point** points, Line reg, size_t size);

#endif
