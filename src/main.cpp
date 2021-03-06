#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <unistd.h>
#include <fstream>
#include <string>


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

#include "message_constants.h"
#include <MeasurementType.h>
#include <WallClockMeasurementType.h>
#include <CPUMeasurementType.h>
#include <MemoryMeasurementType.h>
#include <stdlib.h>
#include <SignalHandler.h>
#include "untar.h"

char datasetSpec[] = "dataset.spec";

/**
 * Create connection to message broker to start retrieving jobs
 */
std::string broker;
std::string address;
std::string results;
std::string heartbeatQueue;


qpid::messaging::Session session;
qpid::messaging::Connection connection;
qpid::messaging::Receiver receiver;
qpid::messaging::Sender sender;
qpid::messaging::Sender heartbeat;

/**
 * Create Heartbeat messege to be sent
 */
com::codinginfinity::benchmark::management::thrift::messages::Heartbeat heartbeatMessage;
/**
 * Extract all information form the YAML file
 */
YAML::Node config = YAML::LoadFile("/etc/instrumentation/config.yaml");
YAML::Node general = config["general"];
YAML::Node technical = config["technical"];
YAML::Node distro = technical["distro"];
YAML::Node administrative = config["administrative"];
YAML::Node server = config["server"];
YAML::Node queues = server["queues"];

int main(int argc, char** argv) {

    broker = server["host"].as<std::string>() + ":" + server["port"].as<std::string>();
    connection = *(new qpid::messaging::Connection(broker, "{protocol: amqp1.0}"));
    address = queues["jobs"].as<std::string>();
    results = queues["results"].as<std::string>();
    heartbeatQueue = queues["heartbeat"].as<std::string>();

    /**
     * Assign all values execpt time to the heartbeat messege
     */
    heartbeatMessage.__set_id(general["id"].as<std::string>());
    heartbeatMessage.__set_description(general["description"].as<std::string>());

    heartbeatMessage.__set_cpu(technical["cpu"].as<std::string>());
    heartbeatMessage.__set_memory(technical["memory"].as<std::string>());

    heartbeatMessage.__set_os(distro["os"].as<std::string>());
    heartbeatMessage.__set_kernel(distro["kernel"].as<std::string>());

    heartbeatMessage.__set_name(administrative["name"].as<std::string>());
    heartbeatMessage.__set_email(administrative["email"].as<std::string>());
    heartbeatMessage.__set_phone(administrative["phone"].as<std::string>());

    try {
        /**
         * Open connection to message broker to start retrieving jobs
         */
        connection.open();

		session = connection.createSession();
		receiver = session.createReceiver(address);
        sender = session.createSender(results);
        heartbeat = session.createSender(heartbeatQueue);

        signal(SIGINT, signal_exit);
        signal(SIGALRM, signal_alarm);
        alarm(1);


        /**
         * Apache Thrift objects used for serialization and deserialization. The
         * protocol is backed by an in-memory buffer capable managing it's own
         * memory allocations and deallocations.
         */
        boost::shared_ptr<apache::thrift::transport::TMemoryBuffer> memoryBuffer(new apache::thrift::transport::TMemoryBuffer);
        boost::shared_ptr<apache::thrift::protocol::TJSONProtocol> protocol(new apache::thrift::protocol::TJSONProtocol(memoryBuffer));

		while (true) {
            try {
                std::cout<<"Pulling message off the queue..."<<std::endl;
                qpid::messaging::Message message = receiver.fetch(qpid::messaging::Duration::SECOND * 2); // 1s timeout
                std::cout<<"Message received"<<std::endl;
                session.acknowledge();


                /**
                 * Deserialize message using Apache Thrift binary protocol
                 */
                std::cout<<"Converting message into Thrift Object"<<std::endl;
                memoryBuffer->resetBuffer((uint32_t)message.getContentSize());
                memoryBuffer->write((uint8_t*)message.getContent().c_str(), (uint32_t)message.getContentSize());
                com::codinginfinity::benchmark::management::thrift::messages::JobSpecificationMessage job;
                job.read(protocol.get());

                //Define location on monitor node where code and dataset is to be sotred
                std::string location = "/tmp/test301";

                //Remove the directory if it alread exisits
                Archive::removeDirectory(location);
                // Decompress the algorithm
                Archive::extractArchive(location, job.algorithm);
                // Decompress the dataset into the root of the extracted algorithm directory
                Archive::extractDataset(location, job.dataset);


                // Build the user's application
                char pathNameBuffer[MAXPATHLEN];
                char *path = getcwd(pathNameBuffer, MAXPATHLEN);
                std::string command = "ls"; //this is just so that the variable has been defined should
                                            //something go wrong while parsing the makefile

                if(path){
                    std::string CurrentPath;
                    CurrentPath = path;
                    std::cout << "Current path: " << CurrentPath << std::endl;
                }else{
                    std::cout << "error on getcwd" << std::endl;
                }

                if(chdir(location.c_str())){
                    std::cout << "error on chdir" << std::endl;
                }else {
                    //The path has successfully been changed to location
                    path = getcwd(pathNameBuffer, MAXPATHLEN);

                    if (path) {
                        std::string CurrentPath;
                        CurrentPath = path;
                        std::cout << "Path after switch to location" << CurrentPath << std::endl;
                    } else {
                        std::cout << "error on getcwd" << std::endl;
                    }
                    system("make");

                    std::ifstream infile("makefile");
                    while (getline(infile, command)){
                        if(command == "run:") {
                            getline(infile, command);
                            command.erase(0, 1);
                            break;
                        }
                    }
                }

                MeasurementType *measurementType;
                switch (job.measurementType) {
                    case com::codinginfinity::benchmark::management::thrift::messages::MeasurementType::CPU:
                        measurementType = new CPUMeasurementType();
                        break;
                    case com::codinginfinity::benchmark::management::thrift::messages::MeasurementType::MEM:
                        measurementType = new MemoryMeasurementType();
                        break;
                    case com::codinginfinity::benchmark::management::thrift::messages::MeasurementType::TIME:
                        measurementType = new WallClockMeasurementType();
                        break;
                }
                std::cout << "The run command send to measure is : " << command << std::endl;
                /**
                 * The measure() function of MeasurementType class can create new Measurmenet objects, and hence will
                 * pass pointers back to these objects to prevent the use of copy-constructing of objects on vector.
                 */
                std::vector<com::codinginfinity::benchmark::management::thrift::messages::Measurement*> listOfMeasurements;
                //cancel the alarm
                alarm(0);
                unsigned long milliseconds_since_epoch =
                        std::chrono::duration_cast<std::chrono::seconds>
                                (std::chrono::system_clock::now().time_since_epoch()).count();
                heartbeatMessage.__set_current(milliseconds_since_epoch);
                heartbeatMessage.__set_heartbeat(job.timeout);
                heartbeatMessage.__set_busy(true);

                boost::shared_ptr<apache::thrift::transport::TMemoryBuffer> memoryBuffer(
                        new apache::thrift::transport::TMemoryBuffer);
                boost::shared_ptr<apache::thrift::protocol::TJSONProtocol> protocol(
                        new apache::thrift::protocol::TJSONProtocol(memoryBuffer));

                memoryBuffer->resetBuffer();
                heartbeatMessage.write(protocol.get());
                qpid::messaging::Message heartbeatAMQPMessage(memoryBuffer->getBufferAsString());
                heartbeat.send(heartbeatAMQPMessage);
                std::cout<<"Final Heartbeat before doing measurement set"<<std::endl;

                //Do the measurement
                measurementType->measure(job, command, &listOfMeasurements);

                std::cout<<"Reset alarm after doing measurement"<<std::endl;
                alarm(1);

                /**
                 * The Thrift object however requires a vector of Measurement objects, hence we need to create a new
                 * vector to dereference all the objects created by the measure function in the MeasurementType class.
                 */
                std::vector<com::codinginfinity::benchmark::management::thrift::messages::Measurement> resultMeasurements;
                for (std::vector<com::codinginfinity::benchmark::management::thrift::messages::Measurement*>::iterator it = listOfMeasurements.begin() ; it != listOfMeasurements.end(); ++it) {
                    resultMeasurements.push_back(**it);
                }

                com::codinginfinity::benchmark::management::thrift::messages::ResultMessage resultMessage;
                resultMessage.experimentId = job.experimentId;
                resultMessage.jobId = job.jobId;
                resultMessage.measurements = resultMeasurements;

                /**
                 * Serialize message using Apache Thrift binary protocol
                 */
                memoryBuffer->resetBuffer();
                resultMessage.write(protocol.get());

                /**
                 * Remove objects from resultMeasurements which is simply dereferenced pointers.
                 */
                resultMeasurements.clear();
                /**
                 * Cleanup all the objects created by the MeasurementType.
                 */
                while (!listOfMeasurements.empty()) {
                    delete (listOfMeasurements.front());
                    listOfMeasurements.erase(listOfMeasurements.begin());
                }

                /**
                 * Place the serialized object back on the Queue
                 */
                qpid::messaging::Message result(memoryBuffer->getBufferAsString());
                sender.send(result);

                
                /*
                 * Deallocate memory(Because C++ is fun)
                 */
                delete(measurementType);
                measurementType = NULL;

            }catch (const std::exception& error) {
                std::cerr << error.what() << std::endl;
            }
		}
		connection.close();
		return 0;
	} catch (const std::exception& error) {
		std::cerr << error.what() << std::endl;
		connection.close();
		return 1;
	}
}


