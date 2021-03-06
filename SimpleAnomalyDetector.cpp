/*
 * SimpleAnomalyDetector.cpp
 *
 * Author: Itay Etelis - 209041474.
 *         Orel Ben Shamay - 318869658.
 */
#include "SimpleAnomalyDetector.h"

#include <utility>

/**
 * freePoints - free created points.
 * @param points - points array.
 * @param size - size of the array.
 */
void SimpleAnomalyDetector:: freePoints(Point** points, size_t size){
    for (int i = 0; i < size; i++){
        delete(points[i]);
    }
}

/**
 * createPoints - create new points from two given arrays.
 * @param points - pointer to the array holding the array.
 * @param x - first array for x coordinates.
 * @param y - second array for y coordinates.
 * @param size - size of both arrays.
 */
void SimpleAnomalyDetector:: createPoints(Point** points, float* x, float* y, size_t size) {
    for(int i = 0; i < size; i++) {
        points[i] = new Point(x[i], y[i]);
    }
}

/**
 * detector - will help detect all deviations and report them.
 * @param reports - current report.
 * @param points - points array.
 * @param feature - correlated pair.
 * @param size - size of points array.
 */
void SimpleAnomalyDetector:: detector(Point** points, const correlatedFeatures&  feature, size_t size) {
    string firstFeature = feature.feature1, secondFeature = feature.feature2;
    for (int i = 0; i < size; i++) {
        if (checkPoint(*points[i], feature)) {
            string description;
            auto r = new AnomalyReport(description.append(firstFeature).append("-").append(secondFeature), i + 1);
            reports.push_back(*r);
            delete(r);
        }
    }
}

/**
 * learnNormal - will learn correlations based on the given test table.
 * @param ts - the test table.
 */
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    // Receive the data table.
    auto data = ts.getData();
    // Create two map iterators.
    auto firstFeature_it = data.begin(), secondFeature_it = data.begin();
    size_t vectorSize = firstFeature_it->second.size();
    float max, p;
    string firstFeature, secondFeature;
    // Run on all features and detect suitable corrlation and insert into the corrlation vector.
    for(; firstFeature_it != data.end(); firstFeature_it++) {
        max = 0;
        firstFeature = firstFeature_it->first;
        secondFeature.clear();
        secondFeature_it = firstFeature_it;
        // Iterate on the rest of the features and detect corrlation.
        for(++secondFeature_it; secondFeature_it != data.end(); secondFeature_it++) {
            // Calculate p from given formula.
            p = fabs(pearson(&firstFeature_it->second[0], &secondFeature_it->second[0], vectorSize));
            // If fitting correlation has been found update max parameters.
            if (correlationTest(p, max)){
                secondFeature = secondFeature_it->first;
                max = p;
            }
        }
        // If correlated feature was found create a new pair by inserting into the corrlation vector.
        if (!secondFeature.empty()) {
            size_t size = data.find(firstFeature)->second.size();
            Point *points[vectorSize];
            createPoints(points, &data.find(firstFeature)->second[0], &data.find(secondFeature)->second[0], size);
            createCorrelatedPair(firstFeature, secondFeature, size, points, max);
            freePoints(points, vectorSize);
        }
    }
}

/**
 * createCorrelatedPair - create correlated pair from two correlated features.
 * @param firstFeature - first feature's name.
 * @param secondFeature - second feature's name.
 * @param data - data table.
 * @param max - max corrlation found.
 */
void SimpleAnomalyDetector::createCorrelatedPair(const string& firstFeature, const string& secondFeature, size_t vectorSize,
                                                  Point** points, float max) {
    Line reg = linear_reg(points, vectorSize);
    float threshold = maxDev(points, reg, vectorSize);
    insertCorrelatedFeatures(firstFeature, secondFeature, max, reg,threshold * DEVIATION_THRESHOLD, DEFAULT_POINT);
}


/**
 * detect - detect and report deviations in realtime.
 * @param ts - data table.
 * @return reports vector containing all exceptions.
 */
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    auto data = ts.getData();
    string feature1, feature2;
    size_t size = cf.size();
    // iterate on every two correlated features in cf
    for(int i = 0; i < size; i++) {
        feature1 = cf[i].feature1;
        feature2 = cf[i].feature2;
        size_t s = data.find(feature1)->second.size();
        Point* points[s];
        // create points from the features values
        createPoints(points, &data.find(feature1)->second[0], &data.find(feature2)->second[0], s);
        detector(points, cf[i] , s);
        freePoints(points, s);
    }
    return reports;
}

/**
 * correlationTest - check if correlation exists according to arguments sent.
 * @param p - pearson.
 * @param max - max pearson achieved so far.
 * @return - if corrlelation was found according to threshold set return true, otherwise false.
 */
bool SimpleAnomalyDetector::correlationTest(const float &p, const float &max) {
    return p > max && p >= correlation;
}

/**
 * checkPoint - check if given point is inside the circle_center.
 * @param p - the point.
 * @param feature - the current correlated feature.
 * @return true - if point is inside the circle_center, otherwise false.
 */
bool SimpleAnomalyDetector::checkPoint(Point p, const correlatedFeatures &feature) {
    return (dev(p, feature.lin_reg) > feature.threshold);
}

/**
 *
 * @param firstFeature - first feature's name
 * @param secondFeature - second feature's name
 * @param max - max pearson.
 * @param reg - line reg
 * @param maxThreshold - maxThreshold for line / circle.
 * @param center - circle center - if non provided will use default.
 */
void SimpleAnomalyDetector::insertCorrelatedFeatures(string firstFeature, string secondFeature, float max, Line reg,
                                                     float maxThreshold, Point center) {
    struct correlatedFeatures c = {std::move(firstFeature), std::move(secondFeature), max, reg, maxThreshold, center};
    cf.push_back(c);
}



