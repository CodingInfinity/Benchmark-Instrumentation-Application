#!/bin/sh

SCRIPTPATH=$( cd $(dirname $0) ; pwd -P )

# Mainly aiming Travis CI's Ubuntu machines for now

# General dependencies
sh ${SCRIPTPATH}/installCXXDependencies.sh

# Setup Apache qpid Proton
PROTON_TEMP_DIRECTORY="$(mktemp -d)"
cd ${PROTON_TEMP_DIRECTORY}
git clone git://git.apache.org/qpid-proton.git
cd qpid
mkdir cmake-build
cd cmake build
cmake ..
make all
make install

# Setup Apache qpid CPP
QPID_TEMP_DIRECTORY="$(mktemp -d)"
cd ${QPID_TEMP_DIRECTORY}
git clone git://git.apache.org/qpid-cpp.git
cd qpid-cpp
mkdir cmake-build
cd cmake build
make ..
make all
make install

# Setup Apache Thrift
THRIFT_TEMP_DIRECTORY="$(mktemp -d)"
cd ${THRIFT_TEMP_DIRECTORY}
git clone git://git.apache.org/thrift.git
cd thrift
mkdir cmake-build
cd cmake build
cmake ..
make
make install

# Setup Hyperic SIGAR
SIGAR_TEMP_DIRECTORY="$(mktemp -d)"
cd ${SIGAR_TEMP_DIRECTORY}
git clone https://github.com/hyperic/sigar.git
cd siger
mkdir cmake-build
cd cmake build
cmake ..
make
make install

# Setup libarchive
LIBARCHIVE_TEMP_DIRECTORY="$(mktemp -d)"
cd ${LIBARCHIVE_TEMP_DIRECTORY}
git clone https://github.com/libarchive/libarchive.git
cd libarchive
mkdir cmake-build
cd cmake build
cmake ..
make
make install