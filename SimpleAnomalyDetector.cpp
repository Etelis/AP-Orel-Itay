
#include "SimpleAnomalyDetector.h"


void SimpleAnomalyDetector:: freePoints(Point** points, size_t size){
    for (int i = 0; i < size; i++){
        free(points[i]);
    }
}

void SimpleAnomalyDetector:: createPoints(Point** points, float* x, float* y, size_t size) {
    for(int i = 0; i < size; i++) {
        points[i] = new Point(x[i], y[i]);
    }
}

void SimpleAnomalyDetector:: detector(vector<AnomalyReport>& reports, Point** points, const correlatedFeatures&  cf,
                                    size_t size) {
    Line reg = cf.lin_reg;
    float threshold = cf.threshold;
    string f1 = cf.feature1, f2 = cf.feature2;
    for(int i = 0; i < size; i++) {
        if(dev(*points[i], reg) > threshold) {
            string description;
            auto* r = new AnomalyReport(description.append(f1).append("-").append(f2), i + 1);
            reports.push_back(*r);
        }
    }
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    // receive the data table.
    auto data = ts.getData();
    auto firstFeature_it = data.begin(), secondFeature_it = data.begin();
    size_t vectorSize = firstFeature_it->second.size();
    Point* points[vectorSize];
    float max, p, *firstVector, *secondVector;
    string firstFeature, secondFeature;
    for(; firstFeature_it != data.end(); firstFeature_it++) {
        max = 0;
        firstFeature = firstFeature_it->first;
        secondFeature.clear();
        secondFeature_it = firstFeature_it;
        for(secondFeature_it++; secondFeature_it != data.end(); secondFeature_it++) {
            firstVector = &firstFeature_it->second[0];
            secondVector = &secondFeature_it->second[0];
            p = fabs(pearson(firstVector, secondVector, vectorSize));
            if (p > max && p >= CORRELATION_THRESHOLD){
                secondFeature = secondFeature_it->first;
                max = p;
            }
        }
        // if we found a correlated feature
        if (!secondFeature.empty()) {
            createPoints(points, &data.find(firstFeature)->second[0], &data.find(secondFeature)->second[0], vectorSize);
            Line reg = linear_reg(points, vectorSize);
            struct correlatedFeatures c = {firstFeature, secondFeature, max, reg, maxDev(points, reg, vectorSize) *
                    DEVIATION_THRESHOLD};
            cf.push_back(c);
            freePoints(points, vectorSize);
        }
    }
}

void SimpleAnomalyDetector:: createCorrelatedPair(const string& firstFeature, const string& secondFeature, map<string,
        vector<float>>& data, float max){
    size_t vectorSize = data.find(firstFeature)->second.size();
    Point* points[vectorSize];
    createPoints(points, &data.find(firstFeature)->second[0], &data.find(secondFeature)->second[0], vectorSize);
    Line reg = linear_reg(points, vectorSize);
    struct correlatedFeatures c = {firstFeature, secondFeature, max, reg, maxDev(points, reg, vectorSize) *
                                                                          DEVIATION_THRESHOLD};
    cf.push_back(c);
    freePoints(points, vectorSize);
}

}


vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    auto data = ts.getData();
    string feature1, feature2;
    float *v1, *v2;
    size_t size = cf.size();
    vector<AnomalyReport> reports;
    // iterate on every two correlated features in cf
    for(int i = 0; i < size; i++) {
        feature1 = cf[i].feature1;
        feature2 = cf[i].feature2;
        size_t s = data.find(feature1)->second.size();
        Point* points[s];
        v1 = &data.find(feature1)->second[0];
        v2 = &data.find(feature2)->second[0];
        createPoints(points, v1, v2, s);
        detector(reports, points, cf[i] , s);
        freePoints(points, s);
    }
    return reports;
}