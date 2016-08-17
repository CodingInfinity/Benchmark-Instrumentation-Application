//
// Created by fabio on 2016/07/24.
//


#ifndef BENCHMARK_INSTRUMENTATION_APPLICATION_UNTAR_H
#define BENCHMARK_INSTRUMENTATION_APPLICATION_UNTAR_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>



class Archive{
public:
    static void extractArchive(std::string filename, std::string contents);
    static void extractDataset(std::string location, std::string contents);
    static void removeDirectory(std::string location);
    static void createDirectory(std::string location);
};



#endif //BENCHMARK_INSTRUMENTATION_APPLICATION_UNTAR_H
