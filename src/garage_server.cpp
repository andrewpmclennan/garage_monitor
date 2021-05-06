/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include "messageStructure.h"
#include "serverConnection.h"
#include <iostream>

void processMessage(MessageStructure &msg);
bool run = true;

int main(int argc, char *argv[])
{
	MessageStructure msg(MessageStructure::senderId::SERVER);
	ServerConnection server;

	std::string data;
	server.init(data);
	server.startListening();
	while (run)
	{
		if (server.getData(msg))
		{
			processMessage(msg);
		}
		else
		{
			server.closeListener();
			server.startListening();
		}
	}
	server.closeConnection();
    return 0;
}

void processMessage(MessageStructure &msg)
{
	switch(msg.GetPayload())
	{
	case MessageStructure::messageData::ARM:
	{
		std::cout << "ARM" << std::endl;
		break;
	}
	case MessageStructure::messageData::DISARM:
	{
		std::cout << "DISARM" << std::endl;
		break;
	}
	case MessageStructure::messageData::EMPTY_MESSAGE:
	{
		std::cout << "EMPTY" << std::endl;
		break;
	}
	case MessageStructure::messageData::HUMID:
	{
		std::cout << "HUMID" << std::endl;
		break;
	}
	case MessageStructure::messageData::MESSAGE_RELAY:
	{
		std::cout << "RELAY" << std::endl;
		break;
	}
	case MessageStructure::messageData::READ_PIN:
	{
		std::cout << "READPIN" << std::endl;
		break;
	}
	case MessageStructure::messageData::SHUTDOWN:
	{
		std::cout << "SHUTDOWN" << std::endl;
		run = false;
		break;
	}
	case MessageStructure::messageData::TEMP:
	{
		std::cout << "TEMP" << std::endl;
		break;
	}
	case MessageStructure::messageData::WRITE_PIN:
	{
		std::cout << "WRITEPIN" << std::endl;
		break;
	}
	default:
	{
		std::cout << "How did you get here?" << std::endl;
		break;
	}
	}
}
