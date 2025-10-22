/*
 * WeeklyCourse.cpp
 *
 *  Created on: Jan 9, 2025
 *      Author: Admin
 */

#include "WeeklyCourse.h"

WeeklyCourse::WeeklyCourse
(unsigned int courseKey, std::string title, std::string major,
		float creditPoints, Poco::DateTime::DaysOfWeek dayOfWeek,
		Poco::Data::Time startTime, Poco::Data::Time endTime)
:Course(courseKey, title, major, creditPoints)
{
	this->dayOfWeek = dayOfWeek;
	this->startTime = startTime;
	this->endTime = endTime;
}

WeeklyCourse::~WeeklyCourse()
{
}

Poco::DateTime::DaysOfWeek WeeklyCourse::getDayOfWeekFromInt(int dayIndex) const {
    switch (dayIndex) {
        case 0:
            return Poco::DateTime::DaysOfWeek::SUNDAY;
        case 1:
            return Poco::DateTime::DaysOfWeek::MONDAY;
        case 2:
            return Poco::DateTime::DaysOfWeek::TUESDAY;
        case 3:
            return Poco::DateTime::DaysOfWeek::WEDNESDAY;
        case 4:
            return Poco::DateTime::DaysOfWeek::THURSDAY;
        case 5:
            return Poco::DateTime::DaysOfWeek::FRIDAY;
        case 6:
            return Poco::DateTime::DaysOfWeek::SATURDAY;
        default:
            return Poco::DateTime::DaysOfWeek::SUNDAY;
    }
}

void WeeklyCourse::write(std::ostream &out) const
{
	out << "W;";
	Course::write(out);
	std::string blockStartTime =
			std::to_string(startTime.hour()) + ":" +
			std::to_string(startTime.minute());
	std::string blockEndTime =
			std::to_string(endTime.hour()) + ":" + std::to_string(endTime.minute() );
	out << dayOfWeek << ";" << blockStartTime << ";" << blockEndTime<< std::endl;
}


std::string WeeklyCourse::getDayName(
		const Poco::DateTime::DaysOfWeek& dayOfWeek) const {
    switch (dayOfWeek) {
        case Poco::DateTime::DaysOfWeek::SUNDAY:
            return "Sunday";
        case Poco::DateTime::DaysOfWeek::MONDAY:
            return "Monday";
        case Poco::DateTime::DaysOfWeek::TUESDAY:
            return "Tuesday";
        case Poco::DateTime::DaysOfWeek::WEDNESDAY:
            return "Wednesday";
        case Poco::DateTime::DaysOfWeek::THURSDAY:
            return "Thursday";
        case Poco::DateTime::DaysOfWeek::FRIDAY:
            return "Friday";
        case Poco::DateTime::DaysOfWeek::SATURDAY:
            return "Saturday";
        default:
            return "Invalid day"; // Handle invalid input
    }
}

void WeeklyCourse::read(std::istream &in)
{
	Course::read(in);

	//Update weekday
	std::string info;
	std::getline(in, info, ';');
	this->dayOfWeek = getDayOfWeekFromInt(std::stoi(info));

	//Update starttime
	std::string hour, min;
	std::getline(in, hour, ':');
	std::getline(in, min, ';');
	this->startTime = Poco::Data::Time {std::stoi(hour), std::stoi(min), 0};

	//Update endtime
	std::getline(in, hour, ':');
	std::getline(in, min);
	this->endTime = Poco::Data::Time {std::stoi(hour), std::stoi(min), 0};
}
