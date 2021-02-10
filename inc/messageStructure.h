/*
 * messageStructure.h
 *
 *  Created on: 3 Feb 2021
 *      Author: andrew.mclennan
 */

#ifndef INC_MESSAGESTRUCTURE_H_
#define INC_MESSAGESTRUCTURE_H_

#include <string>
#include <cstdint>

class MessageStructure
{
	public:
		enum senderId
		{
			CLIENT,
			SERVER
		};

		explicit MessageStructure(senderId direction);
		~MessageStructure();

		enum messageData
		{
			ARM,
			DISARM,
			READ_PIN,
			WRITE_PIN,
			SHUTDOWN,
			TEMP,
			HUMID,
			MESSAGE_RELAY,
			EMPTY_MESSAGE
		};

		std::string serialise();
		void deserialise(const std::string &object);
		const messageData GetPayload() const;

		void SetArm();
		void SetDisarm();
		void SetShutdown();
		void ReadPin(uint16_t gpio_pin_number);
		void WritePin(uint16_t gpio_pin_number, bool status);
		void GetTemp();
		void GetHumid();
		void SetMessageRelay(std::string message_to_relay);
	private:
		messageData payload;
		senderId direction;
		const std::string CLIENT_PREFIX = "C_";
		const std::string SERVER_PREFIX = "S_";
		uint16_t pin_number;
		bool pin_state;
		float current_temp;
		float current_humidity;
		std::string response_message;

		std::string getPrefix();
		std::string serialiseClient();
		std::string serialiseServer();
};



#endif /* INC_MESSAGESTRUCTURE_H_ */
