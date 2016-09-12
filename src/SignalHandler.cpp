//
// Created by fabio on 2016/09/12.
//

#include "SignalHandler.h"

extern qpid::messaging::Connection connection;
extern com::codinginfinity::benchmark::management::thrift::messages::Heartbeat heartbeatMessage;
extern qpid::messaging::Sender heartbeat;

void signal_exit(int signum){
    printf("Caught signal %d\n",signum);
    printf("Closing Connection\n");
    connection.close();
    exit(signum);
}

void signal_alarm(int signum){
    unsigned long milliseconds_since_epoch =
            std::chrono::duration_cast<std::chrono::seconds>
                    (std::chrono::system_clock::now().time_since_epoch()).count();
    heartbeatMessage.__set_current(milliseconds_since_epoch);
    heartbeatMessage.__set_heartbeat(30);
    heartbeatMessage.__set_busy(false);

    boost::shared_ptr<apache::thrift::transport::TMemoryBuffer> memoryBuffer(
            new apache::thrift::transport::TMemoryBuffer);
    boost::shared_ptr<apache::thrift::protocol::TJSONProtocol> protocol(
            new apache::thrift::protocol::TJSONProtocol(memoryBuffer));

    memoryBuffer->resetBuffer();
    heartbeatMessage.write(protocol.get());
    qpid::messaging::Message heartbeatAMQPMessage(memoryBuffer->getBufferAsString());
    heartbeat.send(heartbeatAMQPMessage);
    std::cout<<"Heartbeat sent"<<std::endl;
    alarm(30);
}
