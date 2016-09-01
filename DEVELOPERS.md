# Developers #

## Required Dependencies ##
  * Relative POSIX-compliant *NIX system
  * g++ 4.2
  * boost 1.53.0
  * Runtime libraries for lex and yacc might be needed for the Apache Thrift compiler.

## External Dependencies ##
The following dependencies listed below are advised to be installed from source
and not using the underlying systems package manager
  * Apache Qpid Proton
  * Apache Qpid CPP with AMQP version 1.0 (Requires Apache Qpid Proton)
  * Apache Thrift C++ binding
  * Hyperic SIGAR

**For all dependencies listed below please refer to relevant documentation for building dependency in question such
as required dependencies etc.**

### Apache Qpid Proton
    $ git clone git://git.apache.org/qpid-proton.git
    $ cd qpid-proton
    $ mkdir cmake-build
    $ cd cmake-build
    $ cmake ..
    $ make all
    $ make install
    
#### Dependancies for Apache Qpid Proton can be found at https://github.com/apache/qpid-proton/blob/master/INSTALL.md

### Apache Qpid CPP
    $ git clone git://git.apache.org/qpid-cpp.git
    $ cd qpid-cpp
    $ mkdir cmake-build
    $ cd cmake-build
    $ cmake ..
    $ make all
    $ make install

### Dependancies for Apache Qpid CPP can be found at https://github.com/apache/qpid-cpp/blob/master/INSTALL.txt

### Apache Thrift
    $ git clone git://git.apache.org/thrift.git
    $ cd thrift
    $ mkdir cmake-build
    $ cd cmake-build
    $ cmake ..
    $ make
    $ make install

### Hyperic SIGAR
    $ git clone https://github.com/hyperic/sigar.git
    $ cd siger
    $ mkdir cmake-build
    $ cd cmake-build
    $ cmake ..
    $ make
    $ make install

### YAML CPP
    $ git clone https://github.com/jbeder/yaml-cpp
    $ cd yaml-cpp
    $ mkdir cmake-build
    $ cd cmake-build
    $ cmake ..
    $ make
    $ make install
