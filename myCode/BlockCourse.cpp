/*
 * BlockCourse.cpp
 *
 *  Created on: Jan 8, 2025
 *      Author: Admin
 */

#include "BlockCourse.h"
#include <iostream>

BlockCourse::BlockCourse
(unsigned int courseKey, std::string title, std::string major,
		float creditPoints, Poco::Data::Date startDate,
		Poco::Data::Date endDate, Poco::Data::Time startTime,
		Poco::Data::Time endTime):Course(courseKey, title, major, creditPoints)
{
	this->startDate = startDate;
	this->endDate = endDate;
	this->startTime = startTime;
	this->endTime = endTime;
}

BlockCourse::~BlockCourse()
{
}

void BlockCourse::write(std::ostream &out) const
{
	out << "B;";
	Course::write(out);
	std::string startDay = std::to_string(
			startDate.day()) + "." + std::to_string(startDate.month() )+
					"." + std::to_string(startDate.year());
	std::string endDay = std::to_string(endDate.day()) + "." +
			std::to_string(endDate.month() )+ "." + std::to_string(endDate.year());
	std::string blockStartTime = std::to_string(startTime.hour()) +
			":" + std::to_string(startTime.minute());
	std::string blockEndTime = std::to_string(endTime.hour()) + ":" +
			std::to_string(endTime.minute() );
	out << startDay << ";" << endDay << ";" << blockStartTime
			<< ";" << blockEndTime << std::endl;
}

void BlockCourse::read(std::istream &in)
{
	Course::read(in);

	//Update start date
	std::string day, month, year;
	std::getline(in, day, '.');
	std::getline(in, month, '.');
	std::getline(in, year, ';');
	this->startDate = Poco::Data::Date{
		std::stoi(year), std::stoi(month), std::stoi(day)};

	//Update end date
	std::getline(in, day, '.');
	std::getline(in, month, '.');
	std::getline(in, year, ';');
	this->endDate = Poco::Data::Date{
		std::stoi(year), std::stoi(month), std::stoi(day)};

	//Update starttime
	std::string hour, min;
	std::getline(in, hour, ':');
	std::getline(in, min, ';');
	this->startTime = Poco::Data::Time {
		std::stoi(hour), std::stoi(min), 0};

	//Update endtime
	std::getline(in, hour, ':');
	std::getline(in, min);
	this->endTime = Poco::Data::Time {
		std::stoi(hour), std::stoi(min), 0};
}
