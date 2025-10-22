/*
 * Student.cpp
 *
 *  Created on: Dec 21, 2024
 *      Author: Admin
 */

#include "Student.h"

//In C++, static members belong to the class, not to any instance. They must
//be defined and initialized outside of the class definition to avoid issues
//of multiple definitions or ambiguities.
unsigned int Student::nextMatrikelNumber = 100000;

Student::Student(std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth, Address addressPara):
					firstName{firstName},lastName{lastName},
					dateOfBirth{dateOfBirth},address{addressPara}
{
	this->matrikelNumber = nextMatrikelNumber;
	nextMatrikelNumber ++;
}

void Student::addEnrollment(Enrollment &enroll)
{
	enrollments.push_back(enroll);
}

void Student::updateGrade(float grade, unsigned int courseKey)
{
	for(auto& enroll: enrollments){
		if(enroll.getCourse()->getCourseKey() == courseKey){
			enroll.updateGrade(grade);
			break;
		}
	}
}

void Student::removeEnrollment(unsigned int courseKey)
{
	for(auto it = enrollments.begin(); it != enrollments.end(); ++it){
		if(it->getCourse()->getCourseKey() == courseKey){
			enrollments.erase(it);
			break;
		}
	}
}

void Student::updateName(std::string first, std::string last)
{
	this->firstName = first;
	this->lastName = last;
}

void Student::updateDOB(Poco::Data::Date dob)
{
	this->dateOfBirth = dob;
}

void Student::updateAddress(Address newAddress)
{
	address = newAddress;
}

void Student::write(std::ostream &out) const
{
	std::string dob = std::to_string(dateOfBirth.day()) + "." +
			std::to_string(dateOfBirth.month() )+ "."
			+ std::to_string(dateOfBirth.year());
	out << matrikelNumber << ";" << lastName << ";" << firstName << ";" <<
			dob << ";" << address.getStreet() << ";" << address.getPostalCode()
			<< ";"<< address.getCityName() << ";"
			<< address.getAdditionalInfo() << std::endl;
}

void Student::read(std::istream &in)
{
	std::string info;

	//Change matrikel number
	std::getline(in, info, ';');
	this->matrikelNumber = std::stoi(info);

	//Last name
	std::getline(in, info, ';');
	this->lastName = info;

	//First name
	std::getline(in, info, ';');
	this->firstName = info;

	//Update DOB
	std::string day, month, year;
	std::getline(in, day, '.');
	std::getline(in, month, '.');
	std::getline(in, year, ';');
	this->dateOfBirth = Poco::Data::Date{std::stoi(year),
		std::stoi(month), std::stoi(day)};

	//Change address
	std::string street, postal, city, additional;
	std::getline(in, street, ';');
	std::getline(in, postal, ';');
	std::getline(in, city, ';');
	std::getline(in, additional);
	this->address = Address{street, static_cast<short unsigned int>(
			std::stoi(postal)), city, additional};
}
