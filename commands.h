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
	virtual ~DefaultIO(){}

	// you may add additional methods here
};

struct sharedContent{
public:
    HybridAnomalyDetector hd;
    float desiredThreshHold = 0.9;
    vector<AnomalyReport> ar;
};



// you may edit this class
class Command{
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

// implement here your command classes
class detect_anomalies : public Command{
    string description = "3. detect anomalies\n";
    const char* trainCSV = "anomalyTrain.csv";
    const char* testCSV = "anomalyTrain.csv";
    const char* detectionCompleteMSG = "anomaly detection complete\n";
    sharedContent *sc;

public:
    detect_anomalies(DefaultIO* dio, sharedContent *sc): Command(dio), sc(sc){}
    void execute() override{
        TimeSeries testTimeSeries(testCSV);
        TimeSeries trainTimeSeries(trainCSV);

        sc->hd.learnNormal(trainTimeSeries);
        sc->ar = sc->hd.detect(testTimeSeries);
        dio->write(detectionCompleteMSG);
    }

};

class display_results : public Command{
    string description = "4. display results\n";
    sharedContent *sc;

public:
    display_results(DefaultIO* dio, sharedContent *sc): Command(dio), sc(sc){}
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
    sharedContent *sc;

public:
    analyze_result(DefaultIO* dio, sharedContent *sc): Command(dio), sc(sc){
        this->description = "5. upload anomalies and analyze results\n";}

    void execute() override{
        unsigned int splitLocation, startTime, endTime;
        string input;
        auto reportVec = reportVector();
        auto reportVec_iter = reportVec.begin();
        dio->write(uploadComment);
        input = dio->read();

        // while the read line is not "done"
        while(input != "done") {
            splitLocation = input.find(',');
            startTime = stoi(input.substr(0,splitLocation));
            endTime = stoi(input.substr(splitLocation + 1));

            input = dio->read();
        }


    }
};


#endif /* COMMANDS_H_ */
