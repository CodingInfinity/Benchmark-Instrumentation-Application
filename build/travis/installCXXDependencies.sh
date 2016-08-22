#!/bin/sh

# Mainly aiming Travis CI's Ubuntu machines for now
# General dependencies
sudo apt-add-repository "deb http://archive.ubuntu.com/ubuntu/ trusty main restricted" -y
sudo apt-get update -qq

sudo apt-get install -qq libboost-dev libboost-test-dev libboost-program-options-dev libboost-system-dev libboost-filesystem-dev libboost-thread-dev libevent-dev automake libtool flex bison pkg-config g++ libssl-dev make cmake git libuuid1 uuid-dev uuid-runtime
dpkg -S /usr/include/boost/version.hpp
