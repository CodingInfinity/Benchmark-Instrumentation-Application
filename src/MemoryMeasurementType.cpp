//
// Created by reinhardt on 2016/08/17.
//

#include <chrono>
#include <sigar.h>
#include "MemoryMeasurementType.h"

void MemoryMeasurementType::measure(com::codinginfinity::benchmark::management::thrift::messages::JobSpecificationMessage jobSpecification,
                                    std::string command,
                                    std::vector<com::codinginfinity::benchmark::management::thrift::messages::Measurement*>* measurements) {
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
        system(command.c_str());
    } else {
        unsigned long milliseconds_since_epoch =
                std::chrono::duration_cast<std::chrono::seconds>
                        (std::chrono::system_clock::now().time_since_epoch()).count();

        int probeInterval = jobSpecification.probeInterval;
        int timeout = jobSpecification.timeout;

        sigar_t *sigar;
        sigar_open(&sigar);

        for (int i = 0; i < timeout; i += probeInterval) {
            com::codinginfinity::benchmark::management::thrift::messages::Measurement *measurement = new com::codinginfinity::benchmark::management::thrift::messages::Measurement();
            sigar_proc_mem_t mem;
            sigar_proc_mem_get(sigar, child_process_id, &mem);
            measurement->value = mem.resident;
            measurement->timestamp = std::chrono::duration_cast<std::chrono::seconds>
                    (std::chrono::system_clock::now().time_since_epoch()).count();
            measurements->push_back(measurement);
            sleep(probeInterval);
        }
        sigar_close(sigar);
    }

    }
}
