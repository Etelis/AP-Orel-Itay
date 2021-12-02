#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <iostream>

#define CORRELATION_THRESHOLD 0.9
#define DEVIATION_THRESHOLD float(1.1)

/**
 * a struct for every two correlated features.
 * the struct holds the features name, the correlation value, the linear regression and the threshold.
 */
struct correlatedFeatures {
    string feature1,feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector {
private:
    // stores a struct of every two correlated features
    vector<correlatedFeatures> cf;
    // a vector of reports
    vector<AnomalyReport> reports;
public:
    SimpleAnomalyDetector() = default;
    virtual ~SimpleAnomalyDetector() = default;
    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    static void freePoints(Point** points, size_t size);
    static void createPoints(Point** points, float* x, float* y, size_t size);
    void detector(Point** points, const correlatedFeatures&  cf, size_t size);
    void createCorrelatedPair(const string &firstFeature, const string &secondFeature, map<string, vector<float>> &data,
                              float max);
    vector<correlatedFeatures> getNormalModel(){
        return cf;
    }
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */