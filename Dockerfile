FROM ubuntu:trusty

MAINTAINER Andrew Broekman

RUN apt-get update && apt-get install -y git

COPY ./build/travis/installCXXDependencies.sh /tmp
COPY ./build/travis/installDependencies.sh /tmp

RUN /tmp/installDependencies.sh && /tmp/installCXXDependencies.sh

RUN git clone https://github.com/CodingInfinity/Benchmark-Instrumentation-Application && \
    cd Benchmark-Instrumentation-Application && \
    mkdir cmake_build && \
    cd cmake_build && \
    cmake .. && \
    make all && \
    mv cmake_build/Instrumentation /usr/bin && \
    mkdir /etc/instrumentation

VOLUME ["/etc/instrumentation"]

ENTRYPOINT ["Instrumentation"]

