/**
 * Autogenerated by Thrift Compiler (1.0.0-dev)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "message_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace com { namespace codinginfinity { namespace benchmark { namespace management { namespace thrift { namespace messages {

int _kMeasurementTypeValues[] = {
  MeasurementType::CPU,
  MeasurementType::MEM,
  MeasurementType::TIME
};
const char* _kMeasurementTypeNames[] = {
  "CPU",
  "MEM",
  "TIME"
};
const std::map<int, const char*> _MeasurementType_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(3, _kMeasurementTypeValues, _kMeasurementTypeNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));

int _kLanguageTypeValues[] = {
  LanguageType::JAVA
};
const char* _kLanguageTypeNames[] = {
  "JAVA"
};
const std::map<int, const char*> _LanguageType_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(1, _kLanguageTypeValues, _kLanguageTypeNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));


JobSpecificationMessage::~JobSpecificationMessage() throw() {
}


void JobSpecificationMessage::__set_experimentId(const int32_t val) {
  this->experimentId = val;
}

void JobSpecificationMessage::__set_jobId(const int32_t val) {
  this->jobId = val;
}

void JobSpecificationMessage::__set_languageType(const LanguageType::type val) {
  this->languageType = val;
}

void JobSpecificationMessage::__set_measurementType(const MeasurementType::type val) {
  this->measurementType = val;
}

void JobSpecificationMessage::__set_dataset(const std::string& val) {
  this->dataset = val;
}

void JobSpecificationMessage::__set_algorithm(const std::string& val) {
  this->algorithm = val;
}

void JobSpecificationMessage::__set_timeout(const int32_t val) {
  this->timeout = val;
}

void JobSpecificationMessage::__set_probeInterval(const int32_t val) {
  this->probeInterval = val;
}

uint32_t JobSpecificationMessage::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->experimentId);
          this->__isset.experimentId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->jobId);
          this->__isset.jobId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast0;
          xfer += iprot->readI32(ecast0);
          this->languageType = (LanguageType::type)ecast0;
          this->__isset.languageType = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast1;
          xfer += iprot->readI32(ecast1);
          this->measurementType = (MeasurementType::type)ecast1;
          this->__isset.measurementType = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->dataset);
          this->__isset.dataset = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->algorithm);
          this->__isset.algorithm = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 7:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->timeout);
          this->__isset.timeout = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 8:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->probeInterval);
          this->__isset.probeInterval = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t JobSpecificationMessage::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("JobSpecificationMessage");

  xfer += oprot->writeFieldBegin("experimentId", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->experimentId);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("jobId", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->jobId);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("languageType", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32((int32_t)this->languageType);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("measurementType", ::apache::thrift::protocol::T_I32, 4);
  xfer += oprot->writeI32((int32_t)this->measurementType);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("dataset", ::apache::thrift::protocol::T_STRING, 5);
  xfer += oprot->writeBinary(this->dataset);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("algorithm", ::apache::thrift::protocol::T_STRING, 6);
  xfer += oprot->writeBinary(this->algorithm);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("timeout", ::apache::thrift::protocol::T_I32, 7);
  xfer += oprot->writeI32(this->timeout);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("probeInterval", ::apache::thrift::protocol::T_I32, 8);
  xfer += oprot->writeI32(this->probeInterval);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(JobSpecificationMessage &a, JobSpecificationMessage &b) {
  using ::std::swap;
  swap(a.experimentId, b.experimentId);
  swap(a.jobId, b.jobId);
  swap(a.languageType, b.languageType);
  swap(a.measurementType, b.measurementType);
  swap(a.dataset, b.dataset);
  swap(a.algorithm, b.algorithm);
  swap(a.timeout, b.timeout);
  swap(a.probeInterval, b.probeInterval);
  swap(a.__isset, b.__isset);
}

JobSpecificationMessage::JobSpecificationMessage(const JobSpecificationMessage& other2) {
  experimentId = other2.experimentId;
  jobId = other2.jobId;
  languageType = other2.languageType;
  measurementType = other2.measurementType;
  dataset = other2.dataset;
  algorithm = other2.algorithm;
  timeout = other2.timeout;
  probeInterval = other2.probeInterval;
  __isset = other2.__isset;
}
JobSpecificationMessage& JobSpecificationMessage::operator=(const JobSpecificationMessage& other3) {
  experimentId = other3.experimentId;
  jobId = other3.jobId;
  languageType = other3.languageType;
  measurementType = other3.measurementType;
  dataset = other3.dataset;
  algorithm = other3.algorithm;
  timeout = other3.timeout;
  probeInterval = other3.probeInterval;
  __isset = other3.__isset;
  return *this;
}
void JobSpecificationMessage::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "JobSpecificationMessage(";
  out << "experimentId=" << to_string(experimentId);
  out << ", " << "jobId=" << to_string(jobId);
  out << ", " << "languageType=" << to_string(languageType);
  out << ", " << "measurementType=" << to_string(measurementType);
  out << ", " << "dataset=" << to_string(dataset);
  out << ", " << "algorithm=" << to_string(algorithm);
  out << ", " << "timeout=" << to_string(timeout);
  out << ", " << "probeInterval=" << to_string(probeInterval);
  out << ")";
}


ResultMessage::~ResultMessage() throw() {
}


void ResultMessage::__set_experimentId(const int32_t val) {
  this->experimentId = val;
}

void ResultMessage::__set_jobId(const int32_t val) {
  this->jobId = val;
}

void ResultMessage::__set_measurements(const std::vector<Measurement> & val) {
  this->measurements = val;
}

uint32_t ResultMessage::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->experimentId);
          this->__isset.experimentId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->jobId);
          this->__isset.jobId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->measurements.clear();
            uint32_t _size4;
            ::apache::thrift::protocol::TType _etype7;
            xfer += iprot->readListBegin(_etype7, _size4);
            this->measurements.resize(_size4);
            uint32_t _i8;
            for (_i8 = 0; _i8 < _size4; ++_i8)
            {
              xfer += this->measurements[_i8].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.measurements = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t ResultMessage::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("ResultMessage");

  xfer += oprot->writeFieldBegin("experimentId", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->experimentId);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("jobId", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->jobId);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("measurements", ::apache::thrift::protocol::T_LIST, 3);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->measurements.size()));
    std::vector<Measurement> ::const_iterator _iter9;
    for (_iter9 = this->measurements.begin(); _iter9 != this->measurements.end(); ++_iter9)
    {
      xfer += (*_iter9).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(ResultMessage &a, ResultMessage &b) {
  using ::std::swap;
  swap(a.experimentId, b.experimentId);
  swap(a.jobId, b.jobId);
  swap(a.measurements, b.measurements);
  swap(a.__isset, b.__isset);
}

ResultMessage::ResultMessage(const ResultMessage& other10) {
  experimentId = other10.experimentId;
  jobId = other10.jobId;
  measurements = other10.measurements;
  __isset = other10.__isset;
}
ResultMessage& ResultMessage::operator=(const ResultMessage& other11) {
  experimentId = other11.experimentId;
  jobId = other11.jobId;
  measurements = other11.measurements;
  __isset = other11.__isset;
  return *this;
}
void ResultMessage::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "ResultMessage(";
  out << "experimentId=" << to_string(experimentId);
  out << ", " << "jobId=" << to_string(jobId);
  out << ", " << "measurements=" << to_string(measurements);
  out << ")";
}


Measurement::~Measurement() throw() {
}


void Measurement::__set_timestamp(const int64_t val) {
  this->timestamp = val;
}

void Measurement::__set_value(const int32_t val) {
  this->value = val;
}

uint32_t Measurement::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->timestamp);
          this->__isset.timestamp = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->value);
          this->__isset.value = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Measurement::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Measurement");

  xfer += oprot->writeFieldBegin("timestamp", ::apache::thrift::protocol::T_I64, 1);
  xfer += oprot->writeI64(this->timestamp);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("value", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->value);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Measurement &a, Measurement &b) {
  using ::std::swap;
  swap(a.timestamp, b.timestamp);
  swap(a.value, b.value);
  swap(a.__isset, b.__isset);
}

Measurement::Measurement(const Measurement& other12) {
  timestamp = other12.timestamp;
  value = other12.value;
  __isset = other12.__isset;
}
Measurement& Measurement::operator=(const Measurement& other13) {
  timestamp = other13.timestamp;
  value = other13.value;
  __isset = other13.__isset;
  return *this;
}
void Measurement::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "Measurement(";
  out << "timestamp=" << to_string(timestamp);
  out << ", " << "value=" << to_string(value);
  out << ")";
}

}}}}}} // namespace
