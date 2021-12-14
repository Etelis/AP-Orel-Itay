cmake_minimum_required(VERSION 3.20)
project(AP_Orel_Itay)

set(CMAKE_CXX_STANDARD 14)

add_executable(AP_Orel_Itay minCircle.h minCircle.cpp anomaly_detection_util.h anomaly_detection_util.cpp
        AnomalyDetector.h
        SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h timeseries.cpp HybridAnomalyDetector.cpp
        HybridAnomalyDetector.h CLI.h CLI.cpp commands.h Server.cpp Server.h)
