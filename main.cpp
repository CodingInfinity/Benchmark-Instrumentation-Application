#include <iostream>
#include <memory>

#include <qpid/messaging/Connection.h>
#include <qpid/messaging/FailoverUpdates.h>
#include <qpid/messaging/Message.h>
#include <qpid/messaging/Receiver.h>
#include <qpid/messaging/Sender.h>
#include <qpid/messaging/Session.h>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TBufferTransports.h>

#include "message_constants.h"

int main(int argc, char** argv) {

	std::string broker = argc > 1 ? argv[1] : "localhost:5672";
	std::string address = argc > 2 ? argv[2] : "test";

	qpid::messaging::Connection connection(broker);
	try {
		connection.open();
		qpid::messaging::Session session = connection.createSession();

		// Code here
		qpid::messaging::Receiver receiver = session.createReceiver(address);
		qpid::messaging::Message message = receiver.fetch(qpid::messaging::Duration::SECOND * 1); // 1s timeout
		session.acknowledge();
		receiver.fetch()

		std::string content = message.getContent();

		uint8_t* buffer = new uint8_t[message.getContentSize()];
		for (size_t i = 0; i < message.getContentSize(); i++) {
			buffer[i] = message.getContent().at(i);
		}
		boost::shared_ptr<apache::thrift::transport::TMemoryBuffer> tMemoryBuffer(new apache::thrift::transport::TMemoryBuffer(buffer, uint32_t(message.getContentSize())));
		boost::shared_ptr<apache::thrift::protocol::TBinaryProtocol> protocol(new apache::thrift::protocol::TBinaryProtocol(tMemoryBuffer));
		com::codinginfinity::benchmark::management::messages::Message message1;
		message1.read(protocol.get());


		// Decompress the algorithm
		// Decompress the dataset into the root of the extracted algorithm directory
		// Build the user's application
		// Fork process and start user's process
		// In parent process start socket to listen for client for API ready call from client. Can we bind to socket before
		// we fork, does *nix copy a process bound sockets also in forking? Research needs to be done
		// Get user's processs ID
		// Get type of Job
		// Switch on type of job
		// Every specified interval, probe for measurement and add to results strcuture, while also monitoring if user
		// process is still active,
		// When user process exits, push result strucutre onto queue
		// Go back to start of loop and check if there is more jobs on the queue
		// Rinse and repeat

		message1.printTo(std::cout);

		connection.close();
		return 0;
	} catch (const std::exception& error) {
		std::cerr << error.what() << std::endl;
		connection.close();
		return 1;
	}
}