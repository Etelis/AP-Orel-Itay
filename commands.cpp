//
// Created by Itay on 12/14/2021.
//

struct sharedContent{
    HybridAnomalyDetector hd;
    float desiredThreshHold;
};

// implement here your command classes
class detect_anomalies : public Command{
    string description = "3. detect anomalies\n";
    const char* trainCSV = "anomalyTrain.csv";
    const char* testCSV = "anomalyTrain.csv";
    const char* detectionCompleteMSG = "anomaly detection complete\n";
    vector<AnomalyReport> ar;

public:
    detect_anomalies(DefaultIO* dio, sharedContent sc): Command(dio){}
    void execute() override{
        HybridAnomalyDetector hd;
        TimeSeries testTimeSeries(testCSV);
        TimeSeries trainTimeSeries(trainCSV);

        hd.learnNormal(trainTimeSeries);
        ar = hd.detect(testTimeSeries);
        dio->write(detectionCompleteMSG);
    }

};

class display_results : public Command{
    string description = "4. display results\n";
    const char* trainCSV = "anomalyTrain.csv";
    const char* testCSV = "anomalyTrain.csv";
    const char* detectionCompleteMSG = "anomaly detection complete\n";
    vector<AnomalyReport> ar;

public:
    display_results(DefaultIO* dio): Command(dio){}
    void execute() override{
        HybridAnomalyDetector hd;
        TimeSeries testTimeSeries(testCSV);
        TimeSeries trainTimeSeries(trainCSV);

        hd.learnNormal(trainTimeSeries);
        ar = hd.detect(testTimeSeries);
        dio->write(detectionCompleteMSG);
    }

};