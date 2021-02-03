/*
 * messageStructure.h
 *
 *  Created on: 3 Feb 2021
 *      Author: andrew.mclennan
 */

#ifndef INC_MESSAGESTRUCTURE_H_
#define INC_MESSAGESTRUCTURE_H_

#include <string>

class MessageStructure
{
	public:
		MessageStructure();
		~MessageStructure();

		enum messageData
		{
			MONITOR_LOCK,
			FREE_LOCK,
			EMPTY_MESSAGE
		};

		std::string serialise();
		void deserialise(const std::string &object);
	private:
		messageData payload;
};



#endif /* INC_MESSAGESTRUCTURE_H_ */
