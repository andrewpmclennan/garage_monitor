/*
 * clientConnection.cpp
 *
 *  Created on: 5 May 2021
 *      Author: andrew.mclennan
 */

#include "clientConnection.h"


#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <netdb.h>
#include <unistd.h>


ClientConnection::ClientConnection() :
	sockfd(-1),
	portno(23345)
{

}

ClientConnection::~ClientConnection()
{

}

void ClientConnection::init(std::string &data)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        std::cout << "ERROR opening socket" << std::endl;
    server = gethostbyname(data.c_str());
    if (server == NULL) {
        std::cout << "ERROR, no such host\n" << std::endl;
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
}

void ClientConnection::startConnection()
{
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        std::cout << "ERROR connecting" << std::endl;

}

void ClientConnection::sendMessage(std::string &data)
{
    char buffer[256];
    bzero(buffer,256);
    strcpy(buffer,data.c_str());
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0)
    	std::cout << "ERROR writing to socket" << std::endl;
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0)
    	std::cout << "ERROR reading from socket" << std::endl;
    printf("%s\n",buffer);
}

void ClientConnection::closeConnection()
{
	close(sockfd);
}

