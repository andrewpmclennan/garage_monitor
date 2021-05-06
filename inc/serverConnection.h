/*
 * serverConnection.h
 *
 *  Created on: 5 May 2021
 *      Author: andrew.mclennan
 */

#ifndef INC_SERVERCONNECTION_H_
#define INC_SERVERCONNECTION_H_

#include "messageStructure.h"

#include <string>
#include <netinet/in.h>
#include <unistd.h>

class ServerConnection
{
	public:
		ServerConnection();
		~ServerConnection();

		void init(std::string &data);
		void startListening();
		void closeConnection();
		bool getData(MessageStructure &msg);
		void closeListener();

	private:
    	int sockfd, newsockfd, portno;
    	socklen_t clilen;
    	struct sockaddr_in cli_addr;
};


#endif /* INC_SERVERCONNECTION_H_ */
