#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->sc = new sharedContent{HybridAnomalyDetector(), 0.9, vector<AnomalyReport>()};
    this->commands[0] = new uploadCommand(dio);
    this->commands[1] = new algoSettingCommand(dio, this->sc);
    this->commands[2] = new detect_anomalies(dio, this->sc);
    this->commands[3] = new display_results(dio, this->sc);
    //TODO
    this->commands[5] = new finishCommand(dio);
}

void CLI::start(){
    int input = 0;
    while(input != 6) {
        printMenu();
        input = stoi(this->dio->read());
        if(input >= 1 && input <= 6) {
            this->commands[input - 1]->execute();
        }
    }
}

void CLI::printMenu() {
    for(auto & command : this->commands) {
        this->dio->write(command->description);
    }
}

CLI::~CLI() {
    for(auto & command : this->commands) {
        delete command;
    }
    delete sc;
}

