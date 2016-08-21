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
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TBufferTransports.h>


#include "message_constants.h"
#include <libltdl/lt_system.h>
#include <MeasurementType.h>
#include <WallClockMeasurementType.h>
#include <CPUMeasurementType.h>
#include <MemoryMeasurementType.h>
#include "untar.h"

const int BACKLOG_SIZE = 1;
const unsigned short PORT = 5555;

int main(int argc, char** argv) {

	/**
	 * First ensure we can bind to a socket to allow the client to use pass Benchmark API calls us
	 */
	boost::asio::ip::address address1 = boost::asio::ip::address_v4::loopback();
	boost::asio::ip::tcp::endpoint endpoint(address1, PORT);

	boost::asio::io_service ios;
	boost::asio::ip::tcp::acceptor acceptor(ios, endpoint.protocol());
	boost::system::error_code ec;
	acceptor.bind(endpoint,  ec);

	if (ec.value() != 0) {
		std::cout
		<< "Failed to open acceptor socket! "
		<< "Error code = "
		<< ec.value() << ". Message: " << ec.message();
		return ec.value();
	}

	acceptor.listen(BACKLOG_SIZE);

	/**
	 * Open connection to message broker to start retrieving jobs
	 */
	std::string broker = argc > 1 ? argv[1] : "localhost:5672";
	std::string address = argc > 2 ? argv[2] : "jobs";

	qpid::messaging::Connection connection(broker);

	try {
		connection.open();
		qpid::messaging::Session session = connection.createSession();
		qpid::messaging::Receiver receiver = session.createReceiver(address);
        qpid::messaging::Sender sender = session.createSender(address);
		while (true) {
            try {
                std::cout<<"Pulling message off the queue..."<<std::endl;
                qpid::messaging::Message message = receiver.fetch(qpid::messaging::Duration::SECOND * 1); // 1s timeout
                std::cout<<"Message received"<<std::endl;
                session.acknowledge();

                std::string content = message.getContent();

                uint8_t *buffer = new uint8_t[message.getContentSize()];
                for (size_t i = 0; i < message.getContentSize(); i++) {
                    buffer[i] = message.getContent().at(i);
                }

                /**
                 * Deserialize message using Apache Thrift binary protocol
                 */
                boost::shared_ptr<apache::thrift::transport::TMemoryBuffer> tMemoryBuffer(
                        new apache::thrift::transport::TMemoryBuffer(buffer, uint32_t(message.getContentSize())));
                boost::shared_ptr<apache::thrift::protocol::TBinaryProtocol> protocol(
                        new apache::thrift::protocol::TBinaryProtocol(tMemoryBuffer));
                std::cout<<"Converting message into Thrift Object"<<std::endl;
                com::codinginfinity::benchmark::management::thrift::messages::JobSpecificationMessage job;
                job.read(protocol.get());

                //Define location on monitor node where code and dataset is to be sotred
                std::string location = "/home/fabio/Desktop/tmp/";

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
                    std::string command;
                    while (getline(infile, command)){
                        if(command == "run:") {
                            getline(infile, command);
                            command.erase(0, 1);
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
                std::vector<com::codinginfinity::benchmark::management::thrift::messages::Measurement> listOfMeasurements = measurementType->measure(job, command);
                com::codinginfinity::benchmark::management::thrift::messages::ResultMessage *resultMessage = new com::codinginfinity::benchmark::management::thrift::messages::ResultMessage;
                resultMessage->experimentId = job.experimentId;
                resultMessage->jobId = job.jobId;
                resultMessage->measurements = listOfMeasurements;

                /**
                 * Serialize message using Apache Thrift binary protocol
                 */

                uint32_t bufferSize = listOfMeasurements.capacity()*sizeof(com::codinginfinity::benchmark::management::thrift::messages::Measurement)
                                      + sizeof(com::codinginfinity::benchmark::management::thrift::messages::Measurement)
                                      + sizeof(com::codinginfinity::benchmark::management::thrift::messages::ResultMessage);
                bufferSize *= 1.2;
                boost::shared_ptr<apache::thrift::transport::TMemoryBuffer> bufferOut = new apache::thrift::transport::TMemoryBuffer(bufferSize);
                boost::shared_ptr<apache::thrift::protocol::TBinaryProtocol> protocolOut = new apache::thrift::protocol::TBinaryProtocol(bufferOut);
                resultMessage->write(protocolOut.get());


                /**
                 * Place the serialized object back on the Queue
                 */
                qpid::messaging::Message* message1 = new qpid::messaging::Message(bufferOut.get()->getBufferAsString());
                sender.send(*message1);




                /*
                 * Deallocate memory(Because C++ is fun)
                 */
                delete(listOfMeasurements);
                listOfMeasurements = NULL;

                delete(resultMessage);
                resultMessage = NULL;

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
