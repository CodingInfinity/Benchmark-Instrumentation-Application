cmake_minimum_required(VERSION 3.5)
project(Benchmark_Instrumentation_Application)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp message_constants.cpp message_types.cpp)
add_executable(Benchmark_Instrumentation_Application ${SOURCE_FILES})

target_link_libraries(Benchmark_Instrumentation_Application /usr/local/lib/libqpidmessaging.so /usr/local/lib/libqpidtypes.so thrift)
