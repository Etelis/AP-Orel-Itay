#ifndef COMMANDS_H_
#define COMMANDS_H_
#include<iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){};
};

struct sharedContent{
public:
    HybridAnomalyDetector hd;
    float desiredThreshHold;
    vector<AnomalyReport> ar;
};



// you may edit this class
class Command {
protected:
	DefaultIO* dio;
public:
    string description;
	Command(DefaultIO* dio):dio(dio){}
	virtual void execute()=0;
	virtual ~Command(){}
};


class uploadCommand : public Command {
public:
    uploadCommand(DefaultIO* dio):Command(dio) {
        this->description = "1. upload a time series csv file\n";
    }
    void execute() override {
        ofstream train, test;
        train.open("anomalyTrain.csv");
        test.open("anomalyTest.csv");
        dio->write("Please upload your local train csv file.\n");
        string input = dio->read();
        // while the read line is not "done"
        while(input != "done") {
            train << input << endl;
            input = dio->read();
        }
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test csv file.\n");
        input = dio->read();
        // while the read line is not "done"
        while(input != "done") {
            test << input << endl;
            input = dio->read();
        }
        dio->write("Upload complete.\n");
        train.close();
        test.close();
    }
};


class algoSettingCommand : public Command {
    sharedContent* sc;
public:
    algoSettingCommand(DefaultIO* dio, sharedContent* sc): Command(dio) {
        this->description = "2. algorithm settings\n";
        this->sc = sc;
    }
    void execute() override {
        dio->write("The current correlation threshold is" + to_string(sc->desiredThreshHold) + "\n");
        float newThreshold;
        newThreshold = stof(dio->read());
        while(newThreshold <= 0 || newThreshold >= 1) {
            dio->write("please choose a value between 0 and 1.\n");
            newThreshold = stof(dio->read());
        }
        sc->desiredThreshHold = newThreshold;
        sc->hd.correlation = newThreshold;
    }
};


class detect_anomalies : public Command{
    sharedContent *sc;
    const char* trainCSV = "anomalyTrain.csv";
    const char* testCSV = "anomalyTrain.csv";
    const char* detectionCompleteMSG = "anomaly detection complete\n";
public:
    detect_anomalies(DefaultIO* dio, sharedContent *sc): Command(dio), sc(sc){
        this->description = "3. detect anomalies\n";
    }
    void execute() override{
        TimeSeries testTimeSeries(testCSV);
        TimeSeries trainTimeSeries(trainCSV);

        sc->hd.learnNormal(trainTimeSeries);
        sc->ar = sc->hd.detect(testTimeSeries);
        dio->write(detectionCompleteMSG);
    }

};

class display_results : public Command{
    sharedContent *sc;
public:
    display_results(DefaultIO* dio, sharedContent *sc): Command(dio), sc(sc){
        this->description = "4. display results\n";
    }
    void execute() override{
        string format, done = "done\n";
        for (const auto& report : sc->ar){
            format.append((to_string(report.timeStep) + "\t" + report.description + "\n"));
        }
        format.append(done);
        dio->write(format);
    }
};

class analyze_result : public Command{
    string uploadComment = "Please upload your local anomalies file.\n";
    string uploadComplete = "Upload complete.\n";
    string truePositiveComment = "True Positive Rate: ";
    string falsePositiveComment = "False Positive Rate: ";
    sharedContent *sc;
public:
    analyze_result(DefaultIO* dio, sharedContent *sc): Command(dio), sc(sc){
        this->description = "5. upload anomalies and analyze results\n";
    }

    void execute() override{
        int P = 0, N = TimeSeries("anomalyTest.csv").getData().at(0).size(), startTime, endTime;
        int s, t, FP = 0, TP = 0;
        float TPrate, FPrate;
        bool intersecting;
        auto reportVec = reportVector();
        auto anomalyVec = anomalyVector(P, N);
        dio->write(uploadComplete);

        for(const auto& exception_report : anomalyVec) {
            intersecting = false;
            startTime = exception_report.first;
            endTime = exception_report.second;
            for(const auto& report : reportVec){
                s = report.first;
                t = report.second;
                if ((startTime <= s && endTime >= s) || (startTime >= s && startTime <= t)){
                    TP++;
                    intersecting = true;
                }
            }
            if (!intersecting)
                FP++;
        }

        TPrate = (float) floor(TP * 1000 / P) / 1000;
        FPrate = (float) floor(FP * 1000 / N) / 1000;

        dio->write(truePositiveComment + to_string(TPrate) + "\n");
        dio->write(falsePositiveComment + to_string(FPrate) + "\n");
    }

    vector<pair<int,int>> reportVector(){
        int startTime, currentTime;
        string currentDescription;
        vector<pair<int,int>> reportVec;
        startTime = sc->ar.begin()->timeStep;
        currentTime = startTime;
        currentDescription = sc->ar.begin()->description;
        for(const auto& report : sc->ar){
            if (report.description != currentDescription){
                currentDescription = report.description;
                pair<int,int> tempPair(startTime,currentTime);
                reportVec.push_back(tempPair);
                startTime = report.timeStep;
                currentTime = startTime;
            }
            else
                currentTime = report.timeStep;
        }
        return reportVec;
    }

    vector<pair<int, int>> anomalyVector(int &P, int &N) {
        int splitLocation, startTime, endTime;
        vector<pair<int,int>> anomalyVec;
        dio->write(uploadComment);
        string input = dio->read();
        // while the read line is not "done"
        while(input != "done") {
            splitLocation = input.find(',');
            startTime = stoi(input.substr(0,splitLocation));
            endTime = stoi(input.substr(splitLocation + 1));
            pair<int,int> tempPair(startTime,endTime);
            anomalyVec.push_back(tempPair);
            N = N - (endTime - startTime);
            P++;
            input = dio->read();
        }
        return anomalyVec;
    }
};

class finishCommand : public Command{
public:
    finishCommand(DefaultIO* dio) : Command(dio) {}
    void execute() override {}
};


#endif /* COMMANDS_H_ */
