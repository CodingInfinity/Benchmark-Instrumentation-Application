//
// Created by reinhardt on 2016/08/17.
//

#ifndef BENCHMARK_INSTRUMENTATION_APPLICATION_MEASUREMENTTYPE_H
#define BENCHMARK_INSTRUMENTATION_APPLICATION_MEASUREMENTTYPE_H


#include "message_types.h"

class MeasurementType {
    public:
        virtual std::vector<com::codinginfinity::benchmark::management::thrift::messages::Measurement> measure(
                com::codinginfinity::benchmark::management::thrift::messages::JobSpecificationMessage,
                std::string command) = 0;
};


#endif //BENCHMARK_INSTRUMENTATION_APPLICATION_MEASUREMENTTYPE_H
