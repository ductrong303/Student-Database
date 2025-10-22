/*
 * Course.h
 *
 *  Created on: Dec 21, 2024
 *      Author: Admin
 *
 *  @file Course.h
 *  @brief Defines the Course class, representing a course in an academic system.
 *         Courses include details such as title, major, and credit points.
 */

#ifndef COURSE_H_
#define COURSE_H_
#include <map>
#include <string>
#include <iostream>

/**
 * @class Course
 * @brief Represents an academic course with its details.
 *
 * The Course class stores information about a course, including its unique
 * course key, title, major, and credit points. It provides methods for reading,
 * writing, and retrieving course data. This is an abstract base class.
 */
class Course
{
private:
	static std::map<unsigned char, std::string> majorByld;///<Maps major names to char
	unsigned int courseKey; ///< Unique identifier for the course.
	std::string title; ///< Title of the course.
	unsigned char major; ///< Code representing the course's major.
	float creditPoints; ///< Number of credit points the course is worth.

public:
    /**
     * @brief Constructs a Course object with the given details.
     *
     * @param courseKey The unique identifier for the course.
     * @param title The title of the course.
     * @param major The name of the course's major.
     * @param creditPoints The number of credit points assigned to the course.
     */
	Course(unsigned int courseKey, std::string title,
			std::string major, float creditPoints);

    /**
     * @brief Virtual destructor for the Course class.
     *
     * Ensures proper cleanup in derived classes.
     */
	virtual ~Course() = 0;

    /**
     * @brief Writes the course's details to an output stream.
     *
     * Outputs the course's information in a serialized format.
     *
     * @param out The output stream to write to.
     */
	virtual void write(std::ostream& out) const;

    /**
     * @brief Retrieves the course's unique key.
     *
     * @return The unique course key.
     */
	unsigned int getCourseKey()const{return courseKey;};

    /**
     * @brief Retrieves the title of the course.
     *
     * @return The course's title as a string.
     */
	std::string getTitle()const{return title;};

    /**
     * @brief Retrieves the name of the course's major.
     *
     * Looks up the major name using the major code.
     *
     * @return The name of the major as a string.
     */
	std::string getMajor()const;

    /**
     * @brief Retrieves the number of credit points assigned to the course.
     *
     * @return The course's credit points as a float.
     */
	float getCreditPoints()const{return creditPoints;};

    /**
     * @brief Reads the course's details from an input stream.
     *
     * Loads course information from a serialized format.
     *
     * @param in The input stream to read from.
     */
	void read(std::istream& in);
};

#endif /* COURSE_H_ */
