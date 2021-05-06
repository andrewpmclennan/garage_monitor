/*
 * serverConnection.cpp
 *
 *  Created on: 5 May 2021
 *      Author: andrew.mclennan
 */

#include "serverConnection.h"
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <netinet/in.h>


ServerConnection::ServerConnection() :
	portno(23345)
{

}
ServerConnection::~ServerConnection()
{

}

void ServerConnection::init(std::string &data)
{
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
       std::cout << "ERROR opening socket" << std::endl;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
    		std::cout << "ERROR on binding" << std::endl;
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
}
void ServerConnection::startListening()
{
	newsockfd = accept(sockfd,
			 (struct sockaddr *) &cli_addr,
			 &clilen);
	if (newsockfd < 0)
	 std::cout << "ERROR on accept" << std::endl;
}

void ServerConnection::closeListener()
{
	close(newsockfd);
}

bool ServerConnection::getData(MessageStructure &msg)
{
	bool retval = true;
    char buffer[256];
    int n;
	bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	if (n <= 0)
	{
		 std::cout << "ERROR reading from socket" << std::endl;
		 retval = false;
	}
	else
	{
		std::string object(buffer);
		msg.deserialise(object);
	}
	printf("Here is the message: %s\n",buffer);
	std::string response = "I got your message: " + std::string(buffer);
	n = write(newsockfd, response.c_str(), response.length());
	if (n <= 0)
	{
		std::cout << "ERROR writing to socket" << std::endl;
		retval = false;
	}
	return retval;
}
void ServerConnection::closeConnection()
{
    close(sockfd);
}








