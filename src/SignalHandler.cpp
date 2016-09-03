//
// Created by fabio on 2016/09/03.
//
#include <iostream>
#include <chrono>
#include <message_types.h>
#include "SignalHandler.h"



void signal_exit(int signum){
    printf("Caught signal %d\n",signum);
    exit(signum);
}

void signal_alarm(int signum){
    qpid::messaging::Connection connection(SignalHandler::broker, "{protocol: amqp1.0}");

    try {
        connection.open();

        qpid::messaging::Session session = connection.createSession();
        qpid::messaging::Sender heartbeat = session.createSender("heartbeat");

        // ToDo Find a way to send the heartbeat messages on regular intervals in cpp
        // ToDo After impl of sending of heartbeats, refactor code to cleanup
        com::codinginfinity::benchmark::management::thrift::messages::Heartbeat heartbeatMessage;

        YAML::Node config = YAML::LoadFile("../config.yaml");
        YAML::Node general = config["general"];
        heartbeatMessage.__set_id(general["id"].as<std::string>());
        heartbeatMessage.__set_description(general["description"].as<std::string>());

        YAML::Node technical = config["technical"];
        heartbeatMessage.__set_cpu(technical["cpu"].as<std::string>());
        heartbeatMessage.__set_memory(technical["memory"].as<std::string>());

        YAML::Node distro = technical["distro"];
        heartbeatMessage.__set_os(distro["os"].as<std::string>());
        heartbeatMessage.__set_kernel(distro["kernel"].as<std::string>());


        YAML::Node administrative = config["administrative"];
        heartbeatMessage.__set_name(administrative["name"].as<std::string>());
        heartbeatMessage.__set_email(administrative["email"].as<std::string>());
        heartbeatMessage.__set_phone(administrative["phone"].as<std::string>());

        unsigned long milliseconds_since_epoch =
                std::chrono::duration_cast<std::chrono::seconds>
                        (std::chrono::system_clock::now().time_since_epoch()).count();
        heartbeatMessage.__set_current(milliseconds_since_epoch);
        heartbeatMessage.__set_heartbeat(0);
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
    }catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;
        connection.close();
    }

}
