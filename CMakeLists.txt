cmake_minimum_required(VERSION 3.20)
project(AP_Orel_Itay)

set(CMAKE_CXX_STANDARD 14)

add_executable(AP_Orel_Itay anomaly_detection_util.h anomaly_detection_util.cpp AnomalyDetector.h SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h timeseries.cpp)
