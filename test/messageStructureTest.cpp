/*
 * messageStructureTest.cpp
 *
 *  Created on: 5 May 2021
 *      Author: andrew.mclennan
 */

#include "messageStructure.h"
#include <iostream>

int main()
{
	MessageStructure msg(MessageStructure::senderId::CLIENT);
	msg.GetHumid();
	std::cout << msg.serialise() << std::endl;
	return 0;
}


