//
// Created by reinhardt on 2016/08/17.
//

#include <chrono>
#include "WallClockMeasurementType.h"
#include <string.h>
#include <cstring>
#include <iostream>
#include <wait.h>

extern char datasetSpec[];

void WallClockMeasurementType::measure(com::codinginfinity::benchmark::management::thrift::messages::JobSpecificationMessage jobSpecification,
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

    auto start_HighResolution = std::chrono::high_resolution_clock::now();
    auto start_Steady = std::chrono::steady_clock::now();

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

        int intVal;

        if(std::chrono::high_resolution_clock::is_steady){
            //if high_resolution_clock is steady use it
            auto start = std::chrono::steady_clock::now();
            auto start_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(start);

            auto end = std::chrono::steady_clock::now();
            auto end_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(end);

            std::chrono::duration<int, std::milli> durationAsIntergerMilliseconds = end_ms - start_ms;

            int startMinusEnd = durationAsIntergerMilliseconds.count();

            int keepGoing = true;

            while(startMinusEnd < (1000*timeout) && keepGoing) {
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

            auto end_HighResolution = std::chrono::high_resolution_clock::now();

            auto start_ms_HighResolution = std::chrono::time_point_cast<std::chrono::milliseconds>(start_HighResolution);
            auto end_ms_HighResolution = std::chrono::time_point_cast<std::chrono::milliseconds>(end_HighResolution);

            std::chrono::duration<int, std::milli> durationAsIntergerMilliseconds_HighResolution = end_ms_HighResolution - start_ms_HighResolution;

            intVal = durationAsIntergerMilliseconds_HighResolution.count();

            if(startMinusEnd > probeInterval && keepGoing){
                kill(child_process_id, SIGKILL);
                com::codinginfinity::benchmark::management::thrift::messages::Measurement *measurement = new com::codinginfinity::benchmark::management::thrift::messages::Measurement();
                long milliseconds_since_epoch =
                        std::chrono::duration_cast<std::chrono::seconds>
                                (std::chrono::system_clock::now().time_since_epoch()).count();
                measurement->timestamp = (int) milliseconds_since_epoch;
                measurement->value = -1;

                measurements->push_back(measurement);
            }else{
                com::codinginfinity::benchmark::management::thrift::messages::Measurement *measurement = new com::codinginfinity::benchmark::management::thrift::messages::Measurement();
                long milliseconds_since_epoch =
                        std::chrono::duration_cast<std::chrono::seconds>
                                (std::chrono::system_clock::now().time_since_epoch()).count();
                measurement->timestamp = (int) milliseconds_since_epoch;
                measurement->value = intVal;

                measurements->push_back(measurement);
            }

        }else{
            //if high_resolution_clock is not steady use steady_clock
            auto start = std::chrono::steady_clock::now();
            auto start_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(start);

            auto end = std::chrono::steady_clock::now();
            auto end_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(end);

            std::chrono::duration<int, std::milli> durationAsIntergerMilliseconds = end_ms - start_ms;

            int startMinusEnd = durationAsIntergerMilliseconds.count();

            int keepGoing = true;

            while(startMinusEnd < (1000*timeout) && keepGoing) {
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

            auto end_Steady = std::chrono::steady_clock::now();

            auto start_ms_Steady = std::chrono::time_point_cast<std::chrono::milliseconds>(start_Steady);
            auto end_ms_Steady = std::chrono::time_point_cast<std::chrono::milliseconds>(end_Steady);

            std::chrono::duration<int, std::milli> durationAsIntergerMilliseconds_Steady = end_ms_Steady - start_ms_Steady;

            intVal = durationAsIntergerMilliseconds_Steady.count();

            std::cout<<( (keepGoing)? "True" : "False") << std::endl;

            if(startMinusEnd > (1000*timeout) && keepGoing){
                kill(child_process_id, SIGKILL);
                com::codinginfinity::benchmark::management::thrift::messages::Measurement *measurement = new com::codinginfinity::benchmark::management::thrift::messages::Measurement();
                long milliseconds_since_epoch =
                        std::chrono::duration_cast<std::chrono::seconds>
                                (std::chrono::system_clock::now().time_since_epoch()).count();
                measurement->timestamp = (int) milliseconds_since_epoch;
                measurement->value = -1;

                measurements->push_back(measurement);
            }else{
                com::codinginfinity::benchmark::management::thrift::messages::Measurement *measurement = new com::codinginfinity::benchmark::management::thrift::messages::Measurement();
                long milliseconds_since_epoch =
                        std::chrono::duration_cast<std::chrono::seconds>
                                (std::chrono::system_clock::now().time_since_epoch()).count();
                measurement->timestamp = (int) milliseconds_since_epoch;
                measurement->value = intVal;

                measurements->push_back(measurement);
            }
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

