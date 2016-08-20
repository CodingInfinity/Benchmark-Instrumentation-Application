//
// Created by reinhardt on 2016/08/17.
//

#include "MemoryMeasurementType.h"

std::vector<com::codinginfinity::benchmark::management::thrift::messages::Measurement>
MemoryMeasurementType::measure(com::codinginfinity::benchmark::management::thrift::messages::JobSpecificationMessage,
                               std::string command) {
    // Every specified interval, probe for measurement and add to results structure, while also monitoring if user
    // process is still active.
    // When user process exits, push result structure onto queue
    return NULL;
}
