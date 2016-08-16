#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <unistd.h>

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
#include "untar.h"

const int BACKLOG_SIZE = 1;
const unsigned short PORT = 5555;


void measurement_CPU(pid_t);
void measurement_MEMORY(pid_t);
void measurement_TIME(pid_t);

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

                // Fork process and start user's process
                pid_t child_process_id;
                child_process_id = fork();

                if (child_process_id == -1) {
                    perror("fork");
                    _exit(EXIT_FAILURE);
                } else if (child_process_id == 0) {
                    // If the child_process_id == 0, then we are in the child process
                    // Load child process
                } else {
                    // If the child_process_id is greater than 0, we are then in the parent process
                    // User's process ID is in child_process_id

                    // Get type of Job
                    // Switch on type of job
                    switch (job.measurementType) {
                        case com::codinginfinity::benchmark::management::thrift::messages::MeasurementType::CPU:
                            measurement_CPU(child_process_id);
                            break;
                        case com::codinginfinity::benchmark::management::thrift::messages::MeasurementType::MEM:
                            measurement_MEMORY(child_process_id);
                            break;
                        case com::codinginfinity::benchmark::management::thrift::messages::MeasurementType::TIME:
                            measurement_TIME(child_process_id);
                            break;
                    }
                }
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

/**
 * ToDo: Look at using Strategy design pattern to handle the measurement of job
 */
void measurement_CPU(pid_t process_id) {

	// Every specified interval, probe for measurement and add to results structure, while also monitoring if user
	// process is still active.
	// When user process exits, push result structure onto queue
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(30));
        return;
	}

}

void measurement_MEMORY(pid_t process_id) {

	// Every specified interval, probe for measurement and add to results structure, while also monitoring if user
	// process is still active.
	// When user process exits, push result structure onto queue
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(30));
        return;
	}
}

void measurement_TIME(pid_t proccess_id) {

	// Every specified interval, probe for measurement and add to results structure, while also monitoring if user
	// process is still active.
	// When user process exits, push result structure onto queue
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(30));
        return;
	}
}
