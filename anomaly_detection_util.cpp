/*
 * animaly_detection_util.cpp
 *
 * Author: Itay Etelis - 209041474
 *         Orel Benshamai - 318869658
 */

#include <math.h>
#include "anomaly_detection_util.h"

// returns the variance of X and Y
float var(float* x, int size) {
    float xAverage = avg(x, size);
    float sum = 0;
    for(int i = 0; i < size; i++) {
       sum += (float)pow(*x - xAverage, 2);
       x++;
    }
    return (float)(1.0/size) * sum;
}

float avg(const float* x, int size) {
    float sum = 0;
    for(int i = 0; i < size; i++) {
        sum += *x;
        x++;
    }
    return sum / (float)size;
}

float multiplyAvg(const float* x, const float* y, int size) {
    float multiXY[size];
    for (int i = 0; i < size; i++){
        multiXY[i] = *x * *y;
        x++, y++;
    }
    return avg(multiXY, size);
}

float cov(float* x, float* y, int size) {
    float eXY = multiplyAvg(x,y,size);
    float eX = avg(x,size);
    float eY = avg(y,size);
    return (eXY - (eX*eY));
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size) {
    float c = cov(x, y, size);
    return c / (float)(sqrt(var(x, size)) * sqrt(var(y, size)));
}

// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size) {
    float X[size], Y[size];
    for(int i = 0; i < size; i++) {
        X[i] = (*points)->x;
        Y[i] = (*points)->y;
        points++;
    }
    float a = cov(X,Y,size) / var(X, size);
    float avX = avg(X, size);
    float avY = avg(Y, size);
    float b = avY - (a * avX);
    return {a, b};
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    Line l = linear_reg(points, size);
    return dev(p, l);
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
    float functionOutput = l.f(p.x);
    return abs(p.y - functionOutput);
}
