/*
 * messageStructure.cpp
 *
 *  Created on: 3 Feb 2021
 *      Author: andrew.mclennan
 */

#include "messageStructure.h"
#include <map>
#include <iostream>

MessageStructure::MessageStructure(senderId direction) :
	payload(EMPTY_MESSAGE),
	direction(direction),
	pin_number(0),
	pin_state(false),
	current_temp(-25.0),
	current_humidity(-1.0),
	response_message("")
{

}
MessageStructure::~MessageStructure()
{

}

MessageStructure& MessageStructure::operator=(const MessageStructure &rhs)
{
	this->payload = rhs.payload;
	this->direction = rhs.direction;
	this->pin_number = rhs.pin_number;
	this->pin_state = rhs.pin_state;
	this->current_temp = rhs.current_temp;
	this->current_humidity = rhs.current_humidity;
	this->response_message = rhs.response_message;
	return *this;
}

void MessageStructure::SetArm()
{
	payload = ARM;
}
void MessageStructure::SetDisarm()
{
	payload = DISARM;
}
void MessageStructure::SetShutdown()
{
	payload = SHUTDOWN;
}
void MessageStructure::ReadPin(uint16_t gpio_pin_number)
{
	//TODO: Needs range checking on valid pin numbers;
	payload = READ_PIN;
	pin_number = gpio_pin_number;
}
void MessageStructure::WritePin(uint16_t gpio_pin_number, bool status)
{
	payload = WRITE_PIN;
	pin_number = gpio_pin_number;
	pin_state = status;
}
void MessageStructure::GetTemp()
{
	payload = TEMP;
}
void MessageStructure::GetHumid()
{
	payload = HUMID;
}
void MessageStructure::SetMessageRelay(std::string message_to_relay)
{
	payload = MESSAGE_RELAY;
}
std::string MessageStructure::serialise()
{
	std::string retval;
	retval += getPrefix();
	if (MessageStructure::senderId::SERVER == direction)
	{
		retval += serialiseServer();
	}
	else
	{
		retval += serialiseClient();
	}
	return retval;
}
std::string MessageStructure::serialiseClient()
{
	std::string retval;
	switch(payload)
	{
		case ARM:
			retval += "ARM;";
			break;
		case DISARM:
			retval += "DISARM;";
			break;
		case READ_PIN:
			retval += "READ_PIN;" + std::to_string(pin_number) + ";";
			break;
		case WRITE_PIN:
			retval += "WRITE_PIN;" + std::to_string(pin_number) + ";" + std::to_string(pin_state);
			break;
		case SHUTDOWN:
			retval += "SHUTDOWN;";
			break;
		case TEMP:
			retval += "TEMP;";
			break;
		case HUMID:
			retval += "HUMID;";
			break;
		case MESSAGE_RELAY:
			retval += "MESSAGE_RELAY;";
			break;
		case EMPTY_MESSAGE:
			retval += "EMPTY_MESSAGE;";
			break;
	}
	return retval;
}

// TODO doxygen this so that I can learn this too.
std::string MessageStructure::serialiseServer()
{
	std::string retval;
	switch(payload)
	{
		case ARM:
			retval += "ARMED;";
			break;
		case DISARM:
			retval += "DISARMED;";
			break;
		case READ_PIN:
			retval += "READ_PIN;" + std::to_string(pin_number) + ";" + std::to_string(pin_state);
			break;
		case WRITE_PIN:
			retval += "WRITE_PIN;" + std::to_string(pin_number) + ";";
			break;
		case SHUTDOWN:
			retval += "OK;";
			break;
		case TEMP:
			retval += "TEMP;" + std::to_string(current_temp);
			break;
		case HUMID:
			retval += "HUMID;" + std::to_string(current_humidity);
			break;
		case MESSAGE_RELAY:
			retval += "MESSAGE_RELAY;";
			break;
		case EMPTY_MESSAGE:
			retval += "EMPTY_MESSAGE;";
			break;
	}
	return retval;
}
// TODO: How is this supposed to work?
void MessageStructure::deserialise(const std::string &object)
{
	std::size_t semi_colon_pos = object.find_first_of(";");
	std::size_t string_length = semi_colon_pos - getPrefix().length();
	std::string substring = object.substr(getPrefix().length(), string_length);

	std::map<std::string, messageData> lookupTable
	{
			{"ARM", ARM},
			{"DISARM", DISARM},
			{"READ_PIN", READ_PIN},
			{"WRITE_PIN", WRITE_PIN},
			{"SHUTDOWN", SHUTDOWN},
			{"TEMP", TEMP},
			{"HUMID", HUMID},
			{"MESSAGE_RELAY", MESSAGE_RELAY}
	};
	auto search = lookupTable.find(substring);
	if (search != lookupTable.end())
	{
		payload = search->second;
		switch(payload)
		{
			// TODO: this parsing needs properly fixing
			case READ_PIN:
				pin_number = 15;
				pin_state = true;
				break;
			// TODO: this parsing needs properly fixing
			case WRITE_PIN:
				pin_number = 16;
				pin_state = true;
				break;
			// TODO: this parsing needs properly fixing
			case TEMP:
				break;
			// TODO: this parsing needs properly fixing
			case HUMID:
				break;
			// TODO: this parsing needs properly fixing
			case MESSAGE_RELAY:
				break;
			default:
				break;
		}
	}
	else
	{
		payload = EMPTY_MESSAGE;
	}
}

const MessageStructure::messageData MessageStructure::GetPayload() const
{
	return payload;
}

// Append the prefix depending on which direction the communications are going.
std::string MessageStructure::getPrefix()
{
	if (CLIENT == direction)
	{
		return CLIENT_PREFIX;
	}
	else
	{
		return SERVER_PREFIX;
	}
}
