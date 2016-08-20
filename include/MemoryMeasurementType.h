//
// Created by reinhardt on 2016/08/17.
//

#ifndef BENCHMARK_INSTRUMENTATION_APPLICATION_MEMORYMEASUREMENTTYPE_H
#define BENCHMARK_INSTRUMENTATION_APPLICATION_MEMORYMEASUREMENTTYPE_H

#include "MeasurementType.h"

class MemoryMeasurementType : public MeasurementType{
    std::vector<com::codinginfinity::benchmark::management::thrift::messages::Measurement> measure(
            com::codinginfinity::benchmark::management::thrift::messages::JobSpecificationMessage,
            std::string location);
};

#endif //BENCHMARK_INSTRUMENTATION_APPLICATION_MEMORYMEASUREMENTTYPE_H
