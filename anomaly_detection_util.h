#include "Line.h"
#include "Point.h"
#ifndef ANOMALYDETECTORUTIL_H_
#define ANOMALYDETECTORUTIL_H_

// returns the average of a float array.
float avg(float* x, int size);

// returns the variance of X and Y.
float var(float* x, int size);

// returns the covariance of X and Y.
float cov(float* x,  float* y, int size);

// returns the average of both arrays x and y when multiplying each value.
float multiplyAvg(float* x, float* y, int size);

// returns the Pearson correlation coefficient of X and Y.
float pearson(float* x, float* y, int size);

// performs a linear regression and returns the line equation.
Line linear_reg(Point** points, int size);

// returns the deviation between point p and the line equation of the points.
float dev(Point p,Point** points, int size);

// returns the deviation between point p and the line.
float dev(Point p,Line l);

#endif
