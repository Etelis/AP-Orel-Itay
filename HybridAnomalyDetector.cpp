/*
 * HybridAnomalyDetector.cpp
 *
 * Author: Itay Etelis - 209041474.
 *         Orel Ben Shamay - 318869658.
 */
#include "HybridAnomalyDetector.h"

/**
 * correlationTest - check if correlation exists according to arguments sent.
 * @param p - pearson.
 * @param max - max pearson achieved so far.
 * @return - if corrlelation was found according to threshold set return true, otherwise false.
 */
bool HybridAnomalyDetector::correlationTest(const float &p, const float &max) {
    return (p > max) && (p >= correlation || p >= CORRELATION_THRESHOLD_2);
}

/**
 * checkPoint - check if given point is inside the circle_center.
 * @param p - the point.
 * @param feature - the current correlated feature.
 * @return true - if point is inside the circle_center, otherwise false.
 */
bool HybridAnomalyDetector::checkPoint(Point p, const correlatedFeatures &feature) {
    // check if the current feature matches the linear correlation.
    if (feature.corrlation >= correlation) {
        // if so, check if point correlated to line.
        return SimpleAnomalyDetector::checkPoint(p,feature);
       // otherwise, confirm point is inside the circle provided by current feature.
    } else {
        return !Circle{feature.circle_center, feature.threshold}.containsPoint(p);
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
    // check if the correlation value is above threshold defined for linear correlation.
    if (max >= correlation) {
        SimpleAnomalyDetector::createCorrelatedPair(firstFeature, secondFeature, size, points, max);
    } else if (max >= CORRELATION_THRESHOLD_2){
        Circle min = findMinCircle(points, size);
        insertCorrelatedFeatures(firstFeature, secondFeature, max, Line(),
                                 min.radius * DEVIATION_THRESHOLD, min.center);
    }
}

