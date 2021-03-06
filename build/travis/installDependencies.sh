#!/bin/sh

SCRIPTPATH=$( cd $(dirname $0) ; pwd -P )

# Mainly aiming Travis CI's Ubuntu machines for now

# General dependencies
sh ${SCRIPTPATH}/installCXXDependencies.sh

# Setup Apache qpid Proton
PROTON_TEMP_DIRECTORY="$(mktemp -d)"
cd ${PROTON_TEMP_DIRECTORY}
git clone git://git.apache.org/qpid-proton.git
cd qpid-proton
mkdir cmake_build
cd cmake_build
cmake ..
make all
sudo make install

# Setup Apache qpid CPP
QPID_TEMP_DIRECTORY="$(mktemp -d)"
cd ${QPID_TEMP_DIRECTORY}
git clone git://git.apache.org/qpid-cpp.git
cd qpid-cpp
mkdir cmake_build
cd cmake_build
cmake ..
make all
sudo make install

# Setup Apache Thrift
THRIFT_TEMP_DIRECTORY="$(mktemp -d)"
cd ${THRIFT_TEMP_DIRECTORY}
git clone git://git.apache.org/thrift.git
cd thrift
mkdir cmake_build
cd cmake_build
cmake ..
make
sudo make install

# Setup Hyperic SIGAR
SIGAR_TEMP_DIRECTORY="$(mktemp -d)"
cd ${SIGAR_TEMP_DIRECTORY}
git clone https://github.com/hyperic/sigar.git
cd sigar
mkdir cmake_build
cd cmake_build
cmake ..
make
sudo make install

# Setup Hyperic SIGAR
YAML_TEMP_DIRECTORY="$(mktemp -d)"
cd ${YAML_TEMP_DIRECTORY}
git clone https://github.com/jbeder/yaml-cpp
cd yaml-cpp
mkdir cmake_build
cd cmake_build
cmake ..
make
sudo make install
