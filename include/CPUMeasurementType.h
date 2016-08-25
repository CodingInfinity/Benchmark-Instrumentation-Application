//
// Created by reinhardt on 2016/08/17.
//

#ifndef BENCHMARK_INSTRUMENTATION_APPLICATION_CPUMEASUREMENTTYPE_H
#define BENCHMARK_INSTRUMENTATION_APPLICATION_CPUMEASUREMENTTYPE_H

#include "MeasurementType.h"

class CPUMeasurementType : public MeasurementType{
    void measure (
            com::codinginfinity::benchmark::management::thrift::messages::JobSpecificationMessage,
            std::string,
            std::vector<com::codinginfinity::benchmark::management::thrift::messages::Measurement*>*);
};

#endif //BENCHMARK_INSTRUMENTATION_APPLICATION_CPUMEASUREMENTTYPE_H
