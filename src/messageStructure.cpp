/*
 * messageStructure.cpp
 *
 *  Created on: 3 Feb 2021
 *      Author: andrew.mclennan
 */

#include "messageStructure.h"

MessageStructure::MessageStructure() : payload(EMPTY_MESSAGE)
{

}
MessageStructure::~MessageStructure()
{

}
std::string MessageStructure::serialise()
{
	std::string retval;
	switch(payload)
	{
		case MONITOR_LOCK:
			retval = "MONITOR_LOCK";
			break;
		case FREE_LOCK:
			retval = "FREE_LOCK";
			break;
		case EMPTY_MESSAGE:
			retval = "EMPTY_MESSAGE";
			break;
	}
	return retval;
}
void MessageStructure::deserialise(const std::string &object)
{

}
