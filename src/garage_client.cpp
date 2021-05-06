#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include <iostream>
#include <map>
#include "messageStructure.h"
#include "clientConnection.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

//TODO: Add a menu so that you can pick what command you want to send.
//TODO: Rewrite server code to be a class
//TODO: Add Handler to the server class for the different commands that can be sent
//TODO: Add command line options for setting the host.

std::string getUserInput();
bool run = true;

int main(int argc, char *argv[])
{
	ClientConnection client;

	std::string target = "localhost";
	client.init(target);
	client.startConnection();
	while (run)
	{
		std::string data = getUserInput();
		if (!data.empty())
			client.sendMessage(data);
		sleep(1);
	}
    client.closeConnection();

    return 0;
}

std::string getUserInput()
{
	std::string user_input;
	std::string retval = "";
	// Get the user input
	std::cin >> user_input;

	std::map<std::string, MessageStructure::messageData> lookupTable
	{
			{"ARM", MessageStructure::ARM},
			{"DISARM", MessageStructure::DISARM},
			{"READ_PIN", MessageStructure::READ_PIN},
			{"WRITE_PIN", MessageStructure::WRITE_PIN},
			{"SHUTDOWN", MessageStructure::SHUTDOWN},
			{"TEMP", MessageStructure::TEMP},
			{"HUMID", MessageStructure::HUMID},
			{"MESSAGE_RELAY", MessageStructure::MESSAGE_RELAY}
	};

	auto search = lookupTable.find(user_input);
    MessageStructure msg(MessageStructure::senderId::CLIENT);
	if (search != lookupTable.end())
	{
		switch(search->second)
		{
			case MessageStructure::ARM:
			    msg.SetArm();
			    break;
			case MessageStructure::DISARM:
				msg.SetDisarm();
				break;
			case MessageStructure::READ_PIN:
				msg.ReadPin(10);
				break;
			case MessageStructure::WRITE_PIN:
				msg.WritePin(11, true);
				break;
			case MessageStructure::SHUTDOWN:
				run = false;
				msg.SetShutdown();
				break;
			case MessageStructure::TEMP:
				msg.GetTemp();
				break;
			case MessageStructure::HUMID:
				msg.GetHumid();
				break;
			case MessageStructure::MESSAGE_RELAY:
				msg.SetMessageRelay("hello world");
				break;
		}
	    retval = msg.serialise();
	}
	return retval;
}
