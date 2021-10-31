#include "timeseries.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <map>

/*
 * timeseries.cpp
 *
 * Author: Itay Etelis - 209041474.
 *         Orel Ben Shamay - 318869658.
 */

TimeSeries::TimeSeries(const char *CSVFileName):CSVFileName(CSVFileName) {
    ifstream myFile;
    myFile.open(CSVFileName);
    string featuresLine;
    map<string, vector<float>>::iterator it;
    // get the line that represents the features names
    getline(myFile, featuresLine);
    stringstream ss(featuresLine);
    // obtain each feature from the line
    string feature;
    while (getline(ss, feature, ',')) {
        data.insert(pair<string, vector<float>>(feature, {}));
    }
    // iterate on each one of the lines separately
    string info;
    while(getline(myFile, info)) {
        // iterate on the map
        it = data.begin();
        stringstream line(info);
        string value;
        // add to every one of the features their value
        while(getline(line, value, ',')) {
            it->second.push_back(stof(value));
            it++;
        }
    }
    myFile.close();
}

map<string, vector<float>> TimeSeries::getData() const {
    return data;
}

