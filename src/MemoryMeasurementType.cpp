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

// Fork process and start user's process
    pid_t child_process_id;
    child_process_id = fork();

    if (child_process_id == -1) {
        perror("fork");
        _exit(EXIT_FAILURE);
    } else if (child_process_id == 0) {
        // If the child_process_id == 0, then we are in the child process
        // Load child process
    } else {
        // If the child_process_id is greater than 0, we are then in the parent process
        // User's process ID is in child_process_id

        // Get type of Job
        // Switch on type of job

    }b
    return NULL;
}
