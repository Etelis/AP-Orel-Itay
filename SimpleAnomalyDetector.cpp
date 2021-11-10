
#include "SimpleAnomalyDetector.h"


void freePoints(Point** points, size_t size){
    for (int i = 0; i < size; i++){
        free(points[i]);
    }
}

void createPoints(Point** points, float* x, float* y, size_t size) {
    for(int i = 0; i < size; i++) {
        points[i] = new Point(x[i], y[i]);
    }
}

void detector(vector<AnomalyReport>& reports, Point** points, const correlatedFeatures&  cf, size_t size) {
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
    auto data = ts.getData();
    map<string, vector<float>>::iterator it1;
    map<string, vector<float>>::iterator it2;
    it1 = data.begin();
    size_t size = it1->second.size();
    float max, p, *firstVector, *secondVector;
    string firstFeature, secondFeature;
    while(it1 != data.end()) {
        Point* points[size];
        max = 0;
        p = 0;
        firstFeature = it1->first;
        secondFeature = "";
        it2 = it1;
        it2++;
        while(it2 != data.end()) {
            firstVector = &it1->second[0];
            secondVector = &it2->second[0];
            p = fabs(pearson(firstVector,secondVector, size));
            if (fabs(p) > max && fabs(p) >= 0.9){
                secondFeature = it2->first;
                max = p;
            }
            it2++;
        }
        // if we found a correlated feature
        if (!secondFeature.empty()) {
            createPoints(points, &data.find(firstFeature)->second[0], &data.find(secondFeature)->second[0], size);
            Line reg = linear_reg(points, size);
            struct correlatedFeatures c = {firstFeature, secondFeature, max, reg, maxDev(points, reg, size) * (float)1.1};
            cf.push_back(c);
            freePoints(points, size);
        }
        it1++;
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