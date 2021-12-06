#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_
#define CORRELATION_THRESHOLD_2 0.5
#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector() = default;
    virtual ~HybridAnomalyDetector() = default;
    virtual bool correlationTest(const float &p,const float &max);
    virtual void createCorrelatedPair(const string& firstFeature, const string& secondFeature, size_t size,
                                      Point** points, float max);
    virtual bool checkPoint(Point p, const correlatedFeatures &features);
};

#endif
