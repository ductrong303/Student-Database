/*
 * Course.cpp
 *
 *  Created on: Dec 21, 2024
 *      Author: Admin
 */

#include "Course.h"


std::map<unsigned char, std::string> Course::majorByld;

Course::Course(unsigned int courseKey, std::string title,
		std::string major, float creditPoints)
{
	this->courseKey = courseKey;
	this->title = title;
	this->major = major[0];
	majorByld[this->major] = major;
	this->creditPoints = creditPoints;
}

Course::~Course(){

}

void Course::write(std::ostream &out) const
{
	out << courseKey << ";" << title << ";" << getMajor() <<
			";" << creditPoints << ";";
}

std::string Course::getMajor() const
{
	return majorByld[this->major];
}

void Course::read(std::istream &in)
{
	//Change course ID
	std::string info;
	std::getline(in, info, ';');
	this->courseKey = std::stoi(info);
	//Change title
	std::getline(in, info, ';');
	this->title = info;
	//Change major
	std::getline(in, info, ';');
	this->majorByld.erase('D');
	this->major = info[0];
	majorByld[this->major] = info;
	//Change CP
	std::getline(in, info, ';');
	this->creditPoints = std::stof(info);
}
