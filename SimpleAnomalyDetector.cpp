
#include "SimpleAnomalyDetector.h"

void createPoints(Point** points, float* x, float* y, size_t size) {
    for(int i = 0; i < size; i++) {
        points[i] = new Point(x[i], y[i]);
    }
}

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    auto data = ts.getData();
    map<string, vector<float>>::iterator it1;
    map<string, vector<float>>::iterator it2;
    it1 = data.begin();
    float max, p, *firstVector, *secondVector;
    string firstFeature, secondFeature;
    Point* points[it1->second.size()];
    while(it1 != data.end()) {
        max = 0;
        firstFeature = it1->first;
        secondFeature = nullptr;
        it2 = it1++;
        while(it2 != data.end()) {
            firstVector = &it1->second[0];
            secondVector = &it2->second[0];
            p = fabs(pearson(firstVector,secondVector, it1->second.size()));
            if (p > max && p >= 0.9){
                secondFeature = it2->first;
                max = p;
            }
            it2++;
        }
        if (!secondFeature.empty()) {
            createPoints(points, firstVector, secondVector, it1->second.size());
            Line reg = linear_reg(points, it1->second.size());
            correlatedFeatures c = {firstFeature, secondFeature, p, reg, maxDev(points, reg, it1->second.size()) * 1.1};
            cf.push_back(c);
        }
        it1++;
    }
    //TODO free allocated points
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
}

