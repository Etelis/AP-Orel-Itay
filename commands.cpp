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
