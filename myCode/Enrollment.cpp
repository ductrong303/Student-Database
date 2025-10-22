/*
 * Enrollment.cpp
 *
 *  Created on: Dec 21, 2024
 *      Author: Admin
 */

#include "Enrollment.h"

Enrollment::Enrollment(const Course* course,
		std::string semester): course{course}, semester{semester}
{
	grade = 0;
}

void Enrollment::updateGrade(float grade)
{
	this->grade = grade;
}

void Enrollment::write(std::ostream &out) const
{
	out << course->getCourseKey() << ";" << semester << ";" << grade << std::endl;
}

void Enrollment::read(std::istream &in)
{
	std::string info;
	std::getline(in, info, ';');
	this->semester = info;
	std::getline(in, info);
	this->grade = std::stof(info);
}
