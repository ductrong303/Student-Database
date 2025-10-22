/*
 * Address.cpp
 *
 *  Created on: Dec 21, 2024
 *      Author: Admin
 */

#include "Address.h"

Address::Address(std::string street, unsigned short postalCode,
		std::string cityName, std::string additionalInfo)
{
	this->street = street;
	this->additionalInfo = additionalInfo;
	this->postalCode = postalCode;
	this->cityName = cityName;
}

