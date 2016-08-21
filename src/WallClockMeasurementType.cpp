//
// Created by reinhardt on 2016/08/17.
//

#include <chrono>
#include "WallClockMeasurementType.h"

std::vector<com::codinginfinity::benchmark::management::thrift::messages::Measurement> 
        WallClockMeasurementType::measure(
                com::codinginfinity::benchmark::management::thrift::messages::JobSpecificationMessage,
                std::string command) {
    // Every specified interval, probe for measurement and add to results structure, while also monitoring if user
    // process is still active.
    // When user process exits, push result structure onto queue



    int intVal;

    if(std::chrono::high_resolution_clock::is_steady){
        //if high_resolution_clock is steady use it

        auto start = std::chrono::high_resolution_clock::now();

        system(command.c_str());

        auto end = std::chrono::high_resolution_clock::now();

        auto start_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(start);
        auto end_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(end);

        std::chrono::duration<int, std::milli> durationAsIntergerMilliseconds = end_ms - start_ms;

        intVal = durationAsIntergerMilliseconds.count();

    }else{
        //if high_resolution_clock is not steady use steady_clock

        auto start = std::chrono::steady_clock::now();

        system(command.c_str());

        auto end = std::chrono::steady_clock::now();

        auto start_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(start);
        auto end_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(end);

        std::chrono::duration<int, std::milli> durationAsIntergerMilliseconds = end_ms - start_ms;

        intVal = durationAsIntergerMilliseconds.count();
    }

    com::codinginfinity::benchmark::management::thrift::messages::Measurement *measurement = new com::codinginfinity::benchmark::management::thrift::messages::Measurement();
    measurement->timestamp = 0;
    measurement->value = intVal;

    std::vector<com::codinginfinity::benchmark::management::thrift::messages::Measurement> *measurements = new std::vector<com::codinginfinity::benchmark::management::thrift::messages::Measurement>();
    measurements->push_back(*measurement);

    return *measurements;
}

