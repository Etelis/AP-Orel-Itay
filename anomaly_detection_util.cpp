/*
 * anomaly_detection_util.cpp
 *
 * Author: Itay Etelis - 209041474.
 *         Orel Ben Shamay - 318869658.
 */

#include "anomaly_detection_util.h"


float var(float* x, size_t size) {
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

float avg(float* x, size_t size) {
    float sum = 0;
    // compute the sum of the values
    for(int i = 0; i < size; i++) {
        sum += *x;
        x++;
    }
    return sum / (float)size;
}

float multiplyAvg(float* x,float* y, size_t size) {
    float multiXY[size];
    // compute the sum of the multiplied values
    for (int i = 0; i < size; i++){
        multiXY[i] = *x * *y;
        x++, y++;
    }
    return avg(multiXY, size);
}

float cov(float* x, float* y, size_t size) {
    float eXY = multiplyAvg(x,y,size);
    float eX = avg(x,size);
    float eY = avg(y,size);
    return (eXY - (eX*eY));
}

//TODO check division by zero
float pearson(float* x, float* y, size_t size) {
    float c = cov(x, y, size);
    return c / ((sqrtf(var(x, size)) * sqrtf(var(y, size))));
}

Line linear_reg(Point** points, size_t size) {
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


float dev(Point p,Point** points, size_t size){
    Line l = linear_reg(points, size);
    return dev(p, l);
}

float dev(Point p,Line l){
    float functionOutput = l.f(p.x);
    return fabs(p.y - functionOutput);
}

float maxDev(Point** points, Line reg, size_t size) {
    float max = 0, temp = 0;
    for(int i = 0; i < size; i++) {
        temp = dev(*points[i], reg);
        max = max < temp ? temp : max;
    }
    return max;
}

