/*
 * clientConnection.h
 *
 *  Created on: 5 May 2021
 *      Author: andrew.mclennan
 */

#ifndef INC_CLIENTCONNECTION_H_
#define INC_CLIENTCONNECTION_H_

#include <netinet/in.h>
#include <string>

class ClientConnection
{
	public:
		ClientConnection();
		~ClientConnection();

		void init(std::string &data);
		void startConnection();
		void closeConnection();
		void sendMessage(std::string &data);

	private:
	    int sockfd;
	    int portno;
	    int n;
	    struct sockaddr_in serv_addr;
	    struct hostent *server;

};



#endif /* INC_CLIENTCONNECTION_H_ */

