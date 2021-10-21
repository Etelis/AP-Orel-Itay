

#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <string>
#include <vector>
#include <map>

using namespace std;

class TimeSeries{

public:

    map<string, vector<float>> data;
    const char* CSVFileName;
    vector<string> featuresNames;

	TimeSeries(const char* CSVfileName);

    map<string, vector<float>> getData() const;

    vector<string> getFeaturesNames() const;

};



#endif /* TIMESERIES_H_ */
