#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <string>
#include <vector>
#include <map>

using namespace std;

class TimeSeries{
public:
    map<string, vector<float>> data;
    const char *CSVFileName;
    TimeSeries(const char* CSVfileName);
    map<string, vector<float>> getData() const;
private:
    void insertRow(const string& rowInfo);
    void insertFeatureNames(const string& featureNames);
};

#endif /* TIMESERIES_H_ */