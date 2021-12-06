/*
 * HybridAnomalyDetector.cpp
 *
 * Author: Itay Etelis - 209041474.
 *         Orel Ben Shamay - 318869658.
 */
#include "HybridAnomalyDetector.h"

bool HybridAnomalyDetector::correlationTest(const float &p, const float &max) {
    return (p > max) && (p >= CORRELATION_THRESHOLD || p >= CORRELATION_THRESHOLD_2);
}

bool HybridAnomalyDetector::checkPoint(Point p, const correlatedFeatures &features) {
    if (features.circle.radius != -1) {
       return !features.circle.containsPoint(p);
    } else {
        return (dev(p, features.lin_reg) > features.threshold);
    }
}

/**
 * createCorrelatedPair - create correlated pair from two correlated features.
 * @param firstFeature - first feature's name.
 * @param secondFeature - second feature's name.
 * @param data - data table.
 * @param max - max correlation found.
 */
void HybridAnomalyDetector::createCorrelatedPair(const string& firstFeature, const string& secondFeature, size_t size,
                                                 Point** points, float max) {
    struct correlatedFeatures c;
    if (max >= CORRELATION_THRESHOLD) {
        Line reg = linear_reg(points, size);
        float threshold = maxDev(points, reg, size);
        c = *new correlatedFeatures{firstFeature, secondFeature, max, reg, threshold * DEVIATION_THRESHOLD};
    } else if (max >= CORRELATION_THRESHOLD_2){
        Circle min = findMinCircle(points, size);
        Circle circ = Circle(min.center, min.radius * DEVIATION_THRESHOLD);
        c = *new correlatedFeatures{firstFeature, secondFeature, max, Line(), 0, circ};
    }
    cf.push_back(c);
}

