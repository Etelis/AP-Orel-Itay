//
// Created by Itay on 10/14/2021.
//
#include "cmath"
#include "anomaly_detection_util.h"

// returns the variance of X and Y
float var(float* x, int size) {
    float m = average(x, size);
    float sum = 0;
    for(int i = 1; i <= size; i++) {
       sum += (float)pow(*(x + i) - m, 2);
    }
    return (float)(1.0/size) * sum;
}

float average(const float *pDouble, int size) {
    float sum = 0;
    for(int i = 1; i <= size; i++) {
        sum += *(pDouble + i);
    }
    return float (1.0/size) * sum;
}

float cov(float* x, float* y, int size) {
    float multiXY[size];
    for (int i = 0; i < size; i++){
        multiXY[i] = *(x +i) * *(y+i);
    }
    float eXY = average(multiXY, size);
    float eX = average(x,size);
    float eY = average(y,size);
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
    for(int i = 1; i <= size; i++) {
        X[i] = temp->x;
        Y[i] = temp->y;
        temp = temp + i;
    }
    float a = cov(X,Y,size) / var(X, size);
    float avX = average(X, size);
    float avY = average(Y, size);
    float b = avY - (a * avX);
    return {a, b};
}