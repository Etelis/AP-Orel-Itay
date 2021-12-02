/*
 * timeseries.cpp
 *
 * Author: Itay Etelis - 209041474.
 *         Orel Ben Shamay - 318869658.
 */
#include "timeseries.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

/**
 * TimeSeries Constructor - use given CSV file to create table for correlation detection.
 * @param CSVFileName - the given CSV file table.
 */
TimeSeries::TimeSeries(const char *CSVFileName):CSVFileName(CSVFileName) {
    ifstream tableFile;
    tableFile.exceptions ( ifstream::badbit );
    try {
        tableFile.open(CSVFileName);
        // The following string will hold all features names for future iterations.
        string featureNames, info;
        // Get the line that represents the features names
        getline(tableFile, featureNames);
        // Insert feature's names into the table.
        insertFeatureNames(featureNames);
        // After inserting all features to the map, insert for each element the corresponding value for each level.
        while (getline(tableFile, info))
            insertRow(info);
    }
    catch (const ifstream::failure& e) {
        cout << "Exception opening/reading file";
    }
    tableFile.close();
}

/**
 * insertRow - receives a row to insert and inserts it into the table.
 * @param rowInfo - a string represents the row information needed to be entered.
 */
void TimeSeries:: insertRow(const string& rowInfo) {
    auto it = data.begin();
    string value;
    stringstream lineStream(rowInfo);
    // Iterate over the row and for each value push it into the vector corresponding to the correct row.
    while (getline(lineStream, value, ',') && it != data.end() ) {
        it->second.push_back(stof(value));
        it++;
    }
}

/**
 * insertFeatureNames - receives a line with features names to insert, inserts it into the table.
 * @param featureNames - a string represents the feature names.
 */
void TimeSeries:: insertFeatureNames(const string& featureNames) {
    stringstream nameStream(featureNames);
    string featureName;
    // Obtain each feature name from given stream.
    while (getline(nameStream, featureName, ',')) {
        // Insert feature name inside the data table with an empty float vector.
        data.insert(pair<string, vector<float>>(featureName, {}));
    }
}

/**
 * getData - as simple as it gets, returns the table created.
 * @return - table created.
 */
map<string, vector<float>> TimeSeries::getData() const {
    return data;
}