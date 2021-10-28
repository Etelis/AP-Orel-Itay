
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

void x(vector<AnomalyReport>& reports, Point** points,const correlatedFeatures&  cf, size_t size) {
    Line reg = cf.lin_reg;
    float threshold = cf.threshold;
    string f1 = cf.feature1, f2 = cf.feature2;
    for(int i = 0; i < size; i++) {
        if(dev(*points[i], reg) > threshold) {
            string description;
            auto* r = new AnomalyReport(description.append(f1).append("-").append(f2), i);
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
    Point* points[size];
    while(it1 != data.end()) {
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
            if (p > max && p >= 0.9){
                secondFeature = it2->first;
                max = p;
            }
            it2++;
        }
        if (!secondFeature.empty()) {
            createPoints(points, firstVector, secondVector, size);
            Line reg = linear_reg(points, it1->second.size());
            //TODO free allocated names

            struct correlatedFeatures c = {firstFeature, secondFeature, p, reg, maxDev(points, reg, size) * (float)1.1};
            freePoints(points, size);
            cf.push_back(c);
        }
        it1++;
    }
    //TODO free allocated points
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    auto data = ts.getData();
    string feature1, feature2;
    float *v1, *v2;
    size_t size;
    Point* points[size];
    vector<AnomalyReport> reports;
    for(int i = 0; i < size; i++) {
        feature1 = cf[i].feature1;
        feature2 = cf[i].feature2;
        size = data.find(feature1)->second.size();
        v1 = &data.find(feature1)->second[0];
        v2 = &data.find(feature2)->second[0];
        createPoints(points, v1, v2, size);
        x(reports, points, cf[i] ,size);
        freePoints(points, size);
    }
    return reports;
}



