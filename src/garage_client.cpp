#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

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

int main(int argc, char *argv[])
{
	ClientConnection client;

	std::string target = "localhost";
	client.init(target);
	client.startConnection();

    MessageStructure msg(MessageStructure::senderId::CLIENT);
    msg.SetArm();
    std::string data = msg.serialise();

    client.sendMessage(data);
    client.closeConnection();

    return 0;
}
