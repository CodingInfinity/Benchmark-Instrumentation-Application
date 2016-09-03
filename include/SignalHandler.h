//
// Created by fabio on 2016/09/03.
//

#ifndef BENCHMARK_INSTRUMENTATION_APPLICATION_SIGNALHANDLER_H
#define BENCHMARK_INSTRUMENTATION_APPLICATION_SIGNALHANDLER_H

#include <cstdio>
#include <stdlib.h>
#include <boost/asio.hpp>
#include <qpid/messaging/Connection.h>
#include <qpid/messaging/FailoverUpdates.h>
#include <qpid/messaging/Message.h>
#include <qpid/messaging/Receiver.h>
#include <qpid/messaging/Sender.h>
#include <qpid/messaging/Session.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>

namespace SignalHandler{
    static std::string broker = "localhost:5672";
}



void signal_exit(int signum);
void signal_alarm(int signum);


#endif //BENCHMARK_INSTRUMENTATION_APPLICATION_SIGNALHANDLER_H
