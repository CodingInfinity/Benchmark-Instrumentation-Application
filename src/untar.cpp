
#include "untar.h"

void Archive::extractArchive(std::string location, std::string contents) {
    Archive::createDirectory(location);
    std::cout<<"Extracting Archive into "<< location<<std::endl;
    std::ofstream out(location + "algorithm.tar.gz");
    out << contents;
    out.close();
    std::string command =  "tar -xf "+ location + "algorithm.tar.gz -C "+ location;
    system(command.c_str());
}

void Archive::extractDataset(std::string location, std::string contents){
    std::cout<<"Extracting Dataset into "<< location<<std::endl;
    std::ofstream out(location + "dataset.tar.gz");
    out << contents;
    out.close();
    std::string command = "tar -xf "+ location + "dataset.tar.gz -C "+ location;
    system(command.c_str());
}

void Archive::removeDirectory(std::string location){
    std::cout<<"Removing "<<location<<std::endl;
    std::string command = "rm -rf " + location;
    system(command.c_str());
}
void Archive::createDirectory(std::string location){
    std::cout<<"Creating "<<location<<std::endl;
    std::string command = "mkdir " + location;
    system(command.c_str());
}


