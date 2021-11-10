

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#define CORRELATION_THRESHOLD 0.9
#define DEVIATION_THRESHOLD float(1.1)

struct correlatedFeatures {
	string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
	float threshold;
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector {
	vector<correlatedFeatures> cf;
public:
	SimpleAnomalyDetector() {

    }
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    void freePoints(Point** points, size_t size);
    void createPoints(Point** points, float* x, float* y, size_t size);
    void detector(vector<AnomalyReport>& reports, Point** points, const correlatedFeatures&  cf, size_t size);
    void createCorrelatedPair(const string &firstFeature, const string &secondFeature, map<string, vector<float>> &data,
                              float max);
};



#endif /* SIMPLEANOMALYDETECTOR_H_ */
