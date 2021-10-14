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
    float m = avg(x, size);
    float sum = 0;
    for(int i = 0; i < size; i++) {
       sum += (float)pow(*(x + i) - m, 2);
    }
    return (float)(1.0/size) * sum;
}

float avg(float* x, int size) {
    float sum = 0;
    for(int i = 0; i < size; i++) {
        sum += *(x + i);
    }
    return sum / (float)size;
}

float cov(float* x, float* y, int size) {
    float multiXY[size];
    for (int i = 0; i < size; i++){
        multiXY[i] = *(x +i) * *(y+i);
    }
    float eXY = avg(multiXY, size);
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
    Point* temp = *points;
    for(int i = 0; i < size; i++) {
        X[i] = temp->x;
        Y[i] = temp->y;
        temp = temp + i;
    }
    float a = cov(X,Y,size) / var(X, size);
    float avX = avg(X, size);
    float avY = avg(Y, size);
    float b = avY - (a * avX);
    return {a, b};
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    return 0;
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
    return 0;
}
