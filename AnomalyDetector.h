#ifndef ANOMALYDETECTOR_H_
#define ANOMALYDETECTOR_H_
#include <string>
#include <vector>
#include "timeseries.h"
#include <cmath>
using namespace std;

class AnomalyReport{
public:
    // description of the report
	const string description;
    // the time step of the deviation
	const long timeStep;
	AnomalyReport(string description, long timeStep):description(description),timeStep(timeStep){}
};

class TimeSeriesAnomalyDetector {
public:
	virtual void learnNormal(const TimeSeries& ts)=0;
	virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
	virtual ~TimeSeriesAnomalyDetector() = default;
};

#endif /* ANOMALYDETECTOR_H_ */
