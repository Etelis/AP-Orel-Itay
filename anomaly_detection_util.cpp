/*
 * animaly_detection_util.cpp
 *
 * Author: Itay Etelis - 209041474.
 *         Orel Ben Shamay - 318869658.
 */

#include <math.h>
#include "anomaly_detection_util.h"

float var(float* x, int size) {
    // obtain the average of the values
    float xAverage = avg(x, size);
    float sum = 0;
    // iterate on the values and compute the sum
    for(int i = 0; i < size; i++) {
       sum += (*x - xAverage)*(*x - xAverage);
       x++;
    }
    return ((float)1.0/(float)size) * sum;
}

float avg(const float* x, int size) {
    float sum = 0;
    // compute the sum of the values
    for(int i = 0; i < size; i++) {
        sum += *x;
        x++;
    }
    return sum / (float)size;
}

float multiplyAvg(const float* x, const float* y, int size) {
    float multiXY[size];
    // compute the sum of the multiplied values
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


float pearson(float* x, float* y, int size) {
    float c = cov(x, y, size);
    return c / ((float)(sqrt(var(x, size)) * (float)sqrt(var(y, size))));
}

Line linear_reg(Point** points, int size) {
    float X[size], Y[size];
    // obtain the x and y values of each point and store them in the array
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

float dev(Point p,Point** points, int size){
    Line l = linear_reg(points, size);
    return dev(p, l);
}

float dev(Point p,Line l){
    float functionOutput = l.f(p.x);
    return abs(p.y - functionOutput);
}
