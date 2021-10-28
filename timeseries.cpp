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
    getline(myFile, featuresLine);
    stringstream ss(featuresLine);
    string feature;
    while (getline(ss, feature, ',')) {
        data.insert(pair<string, vector<float>>(feature, {}));
    }
    string info;
    while(getline(myFile, info)) {
        it = data.begin();
        stringstream line(info);
        string value;
        while(getline(ss, value, ',')) {
            it->second.push_back(stof(info));
            it++;
        }
    }
    myFile.close();
}

map<string, vector<float>> TimeSeries::getData() const {
    return data;
}

