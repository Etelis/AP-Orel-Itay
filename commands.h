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



#endif /* COMMANDS_H_ */
