FROM ubuntu:trusty

MAINTAINER Andrew Broekman

RUN apt-get update && apt-get install -y git python3 python-dev python3-dev ruby software-properties-common libboost-dev libboost-test-dev libboost-program-options-dev libboost-system-dev libboost-filesystem-dev libboost-thread-dev libevent-dev automake libtool flex bison pkg-config g++ libssl-dev make cmake git libuuid1 uuid-dev uuid-runtime

RUN cd /tmp && \
    git clone git://git.apache.org/qpid-proton.git && \
    mkdir /tmp/qpid-proton/cmake_build && \
    cd /tmp/qpid-proton/cmake_build && \
    cmake .. && \
    make all && \
    make install

RUN cd /tmp && \
    git clone git://git.apache.org/qpid-cpp.git && \
    mkdir /tmp/qpid-cpp/cmake_build && \
    cd /tmp/qpid-cpp/cmake_build && \
    cmake .. && \
    make all && \
    make install

RUN cd /tmp && \
    git clone git://git.apache.org/thrift.git && \
    mkdir /tmp/thrift/cmake_build && \
    cd /tmp/thrift/cmake_build && \
    cmake .. && \
    make all && \
    make install

RUN cd /tmp && \
    git clone git://github.com/hyperic/sigar.git && \
    mkdir /tmp/sigar/cmake_build && \
    cd /tmp/sigar/cmake_build && \
    cmake .. && \
    make all && \
    make install

RUN cd /tmp && \
    git clone git://github.com/jbeder/yaml-cpp.git && \
    mkdir /tmp/yaml-cpp/cmake_build && \
    cd /tmp/yaml-cpp/cmake_build && \
    cmake .. && \
    make all && \
    make install

RUN cd /tmp && \
    git clone https://github.com/CodingInfinity/Benchmark-Instrumentation-Application && \
    mkdir /tmp/Benchmark-Instrumentation-Application/x`cmake_build && \
    cd /tmp/Benchmark-Instrumentation-Application/cmake_build && \
    cmake .. && \
    make all && \
    mv /tmp/Benchmark-Instrumentation-Application/cmake_build/Instrumentation /usr/bin && \
    mkdir /etc/instrumentation

VOLUME ["/etc/instrumentation"]
