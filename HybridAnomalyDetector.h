
#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_
#define CORRELATION_THRESHOLD_2 0.5

#include "SimpleAnomalyDetector.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector() = default;
    virtual ~HybridAnomalyDetector() = default;
    bool correlationTest(const float &p,const float &max) override;
    void createCorrelatedPair(const string& firstFeature, const string& secondFeature, size_t size,
                                      Point** points, float max) override;
    bool checkPoint(Point p, const correlatedFeatures &feature) override;
};

#endif
