//
// Created by reinhardt on 2016/08/17.
//

#include <chrono>
#include <sigar.h>
#include "MemoryMeasurementType.h"
#include <string.h>
#include <cstring>
#include <wait.h>


void MemoryMeasurementType::measure(com::codinginfinity::benchmark::management::thrift::messages::JobSpecificationMessage jobSpecification,
                                    std::string command,
                                    std::vector<com::codinginfinity::benchmark::management::thrift::messages::Measurement*>* measurements) {
    // Every specified interval, probe for measurement and add to results structure, while also monitoring if user
    // process is still active.
    // When user process exits, push result structure onto queue

    char  * input = new char[command.length()];
    strcpy(input, command.c_str());
    std::vector<char *> commands;
    char *token = std::strtok(input, " ");
    while (token != NULL) {
        commands.push_back(token);
        token = std::strtok(NULL, " ");
    }
    char ** args = new char *[commands.size()+ 1 + 2];
    int i;
    for(i = 0; i < commands.size(); ++i){
        args[i] = new char[strlen(commands[i])];
        strcpy(args[i],commands[i]);
    }
    args[i] = new char[1];
    args[i][0] = '<';
    args[i+1] = new char[strlen(datasetSpec)];
    strcpy(args[i+1], datasetSpec);
    args[i+2] = (char *)0;

// Fork process and start user's process
    pid_t child_process_id;
    child_process_id = fork();

    if (child_process_id == -1) {
        perror("fork");
        _exit(EXIT_FAILURE);
    } else if (child_process_id == 0) {
        // If the child_process_id == 0, then we are in the child process
        // Load child process

        //system(command.c_str());

        execvp(args[0], args);
    } else {
        int probeInterval = jobSpecification.probeInterval;
        int timeout = jobSpecification.timeout;

        sigar_t *sigar;
        sigar_open(&sigar);

        auto start = std::chrono::steady_clock::now();
        auto start_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(start);

        auto end = std::chrono::steady_clock::now();
        auto end_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(end);

        std::chrono::duration<int, std::milli> durationAsIntergerMilliseconds = end_ms - start_ms;

        int startMinusEnd = durationAsIntergerMilliseconds.count();

        int keepGoing = true;

         while(startMinusEnd < (1000*timeout) && keepGoing) {
            com::codinginfinity::benchmark::management::thrift::messages::Measurement *measurement = new com::codinginfinity::benchmark::management::thrift::messages::Measurement();
            sigar_proc_mem_t mem;
            sigar_proc_mem_get(sigar, child_process_id, &mem);
            //std::cout<< mem.resident << std::endl;
            measurement->value = mem.resident;
            measurement->timestamp = std::chrono::duration_cast<std::chrono::seconds>
                    (std::chrono::system_clock::now().time_since_epoch()).count();
            measurements->push_back(measurement);

            sleep(probeInterval);

             int status;
             pid_t result = waitpid(child_process_id, &status, WNOHANG);
             if(result != 0){
                 //The proccess has finished executing
                 keepGoing = false;
                 break;
             }

             end = std::chrono::steady_clock::now();
             end_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(end);
             durationAsIntergerMilliseconds = end_ms - start_ms;
             startMinusEnd = durationAsIntergerMilliseconds.count();
        }

        sigar_close(sigar);

        if(startMinusEnd > (1000*timeout) && keepGoing){
            kill(child_process_id, SIGKILL);
            while (!measurements->empty()) {
                delete (measurements->front());
                measurements->erase(measurements->begin());
            }
            com::codinginfinity::benchmark::management::thrift::messages::Measurement *measurement = new com::codinginfinity::benchmark::management::thrift::messages::Measurement();
            unsigned long milliseconds_since_epoch =
                    std::chrono::duration_cast<std::chrono::seconds>
                            (std::chrono::system_clock::now().time_since_epoch()).count();
            measurement->timestamp = milliseconds_since_epoch;
            measurement->value = -1;

            measurements->push_back(measurement);
        }
    }
    //delete each part of the args char **
    for(i = 0; i < commands.size(); ++i){
        delete [] (args[i]);
    }
    delete [] args;

    //delete input which is a char array
    delete[] input;
}

