/*
 * Enrollment.h
 *
 *  Created on: Dec 21, 2024
 *      Author: Admin
 *
 *  @file Enrollment.h
 *  @brief Defines the Enrollment class that represents a student's enrollment
 *         in a course, including grade and semester details.
 */

#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_
#include "Course.h"

/**
 * @class Enrollment
 * @brief Represents a student's enrollment in a course.
 *
 * The Enrollment class stores information about a student's enrollment in a
 * course, including the course, semester, and grade. It provides methods for
 * updating and retrieving enrollment details, including the grade.
 */
class Enrollment
{
private:
	float grade; ///< The grade the student received in the course.
	const Course* course; ///< Pointer to the course in which the student is enrolled.
	std::string semester; ///< The semester in which the student is enrolled.

public:
    /**
     * @brief Constructs an Enrollment object for a student.
     *
     * Initializes an enrollment for the specified course and semester.
     *
     * @param course The course in which the student is enrolling.
     * @param semester The semester of the enrollment.
     */
	Enrollment(const Course* course, std::string semester);

    /**
     * @brief Retrieves the grade for the enrollment.
     *
     * @return The grade the student received in the course.
     */
	float getGrade() const{ return grade;};

    /**
     * @brief Retrieves the semester of the enrollment.
     *
     * @return The semester as a string (e.g., "WS2025").
     */
	std::string getSemester() const{ return semester;};

    /**
     * @brief Retrieves the course associated with the enrollment.
     *
     * @return A pointer to the course in which the student is enrolled.
     */
	const Course* getCourse() const{ return course;};

    /**
     * @brief Updates the grade for the enrollment.
     *
     * Sets a new grade for the student in the enrolled course.
     *
     * @param grade The new grade to assign.
     */
	void updateGrade(float grade);

    /**
     * @brief Writes the enrollment details to an output stream.
     *
     * Serializes the enrollment information (course, grade, semester) to an
     * output stream.
     *
     * @param out The output stream to write to.
     */
	void write(std::ostream& out) const;

    /**
     * @brief Reads the enrollment details from an input stream.
     *
     * Deserializes the enrollment information from an input stream.
     *
     * @param in The input stream to read from.
     */
	void read(std::istream &in);
};

#endif /* ENROLLMENT_H_ */
