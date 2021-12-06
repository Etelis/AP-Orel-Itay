#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <iostream>
#include "minCircle.h"

#define CORRELATION_THRESHOLD 0.9
#define DEVIATION_THRESHOLD float(1.1)
#define DEFAULT_CIRCLE Circle{Point{0,0}, -1}

/**
 * a struct for every two correlated features.
 * the struct holds the features name, the correlation value, the linear regression and the threshold.
 */
struct correlatedFeatures {
    string feature1;
    string feature2;
    float corrlation;
    Line lin_reg;
    float threshold;
    Circle circle = DEFAULT_CIRCLE;
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector {
public:
    // stores a struct of every two correlated features
    vector<correlatedFeatures> cf;
    // a vector of reports
    vector<AnomalyReport> reports;
    SimpleAnomalyDetector() = default;
    virtual ~SimpleAnomalyDetector() = default;
    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel(){
        return cf;
    }
protected:
    virtual bool correlationTest(const float &p,const float &max);
    virtual void createCorrelatedPair(const string& firstFeature, const string& secondFeature, size_t size, Point** points, float max);
    void detector(Point** points, const correlatedFeatures&  cf, size_t size);
    void freePoints(Point** points, size_t size);
    void createPoints(Point** points, float* x, float* y, size_t size);
    virtual bool checkPoint(Point p, const correlatedFeatures &features);
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */