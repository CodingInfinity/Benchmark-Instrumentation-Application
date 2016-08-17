project (Benchmark_Instrumentation_Application)
cmake_minimum_required (VERSION 2.8.12)

# The version number.
set (Instrumentation_VERSION_MAJOR 1)
set (Instrumentation_VERSION_MINOR 0)

# Add local headers to project
include_directories(include)

message (STATUS "** Searching for dependencies")
# Find all required dependencies
# Apache Proton
message (STATUS "** Searching for Apache Proton")
find_package(Proton)
if (NOT Proton_LIBRARIES)
    set(PROTON_FOUND "Not found")
else()
    set(PROTON_FOUND "Found")
endif()

# Apache Qpid
message (STATUS "** Searching for Apache Qpid")
find_package(Qpid)
if (NOT Qpid_LIBRARIES)
    set(QPID_FOUND "Not found")
else()
    set(QPID_FOUND "Found")
endif()

# Apache Thrift
message (STATUS "** Searching for Apache Thrift")
find_library(THRIFT_LIBRARIES thrift)
if (NOT THRIFT_LIBRARIES)
    set(THRIFT_FOUND "Not found")
else()
    set(THRIFT_FOUND "Found")
endif()

# Hyperic Sigar
message (STATUS "** Searching for Hyperic SIGAR")
find_library(SIGAR_LIBRARIES sigar)
if (NOT SIGAR_LIBRARIES)
    set(SIGAR_FOUND "Not found")
else()
    set(SIGAR_FOUND "Found")
endif()

# libarchive
message (STATUS "** Searching for libarchive")
find_package(LibArchive)
if (NOT LibArchive_FOUND )
    set(LIBARCHIVE_FOUND "Not found")
else()
    set(LIBARCHIVE_FOUND "Found")
endif()

# Boost libraries
# DEFINE BOOST_SYSTEM_NO_DEPRECATED as to prevent from using old and deprecated API calls
message (STATUS "** Searching for Boost")
add_definitions(-DBOOST_SYSTEM_NO_DEPRECATED)
find_package (Boost 1.54.0 REQUIRED system)
include_directories (${Boost_INCLUDE_DIRS})
link_directories (${Boost_LIBRARY_DIRS})
message (STATUS "** Finished searching for dependencies")

message(STATUS "")
message (STATUS "----------------------------------------------------------")
message (STATUS "Build configuration Summary")
message (STATUS "  Dependencies")
message (STATUS "    Apache Proton      :     ${PROTON_FOUND}")
message (STATUS "    Apache Qpid        :     ${QPID_FOUND}")
message (STATUS "    Apache Thrift      :     ${THRIFT_FOUND}")
message (STATUS "    Hyperic SIGAR      :     ${SIGAR_FOUND}")
message (STATUS "    libarchive         :     ${LIBARCHIVE_FOUND}")
message (STATUS "    Boost")
message (STATUS "      Root             :     ${BOOST_ROOT}")
message (STATUS "      Include Path     :     ${Boost_INCLUDE_DIR}")
message (STATUS "      Libraries        :     ${Boost_LIBRARY_DIRS}")
message (STATUS "      Linked Libraries :     ${Boost_LIBRARIES}")
message (STATUS "----------------------------------------------------------")
message(STATUS "")


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file (GLOB SOURCE_FILES "src/*.cpp" "include/*.h")
add_executable (Instrumentation ${SOURCE_FILES} include/MeasurementType.h include/WallClockMeasurementType.h src/WallClockMeasurementType.cpp include/CPUMeasurementType.h include/MemoryMeasurementType.h)
target_link_libraries (Instrumentation ${THRIFT_LIBRARIES} ${Qpid_LIBRARIES} ${Proton_LIBRARIES} ${Boost_LIBRARIES} ${SIGAR_LIBRARIES} ${LibArchive_LIBRARIES} )
