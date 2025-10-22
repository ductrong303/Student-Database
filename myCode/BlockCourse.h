/*
 * BlockCourse.h
 *
 *  Created on: Jan 8, 2025
 *      Author: Admin
 *
 *  @file BlockCourse.h
 *  @brief Defines the BlockCourse class, which is a type of course with a
 *         specific start and end date, as well as start and end times.
 */

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_

#include "Course.h"
#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>

/**
 * @class BlockCourse
 * @brief Represents a course that is taught in a block format with specific
 *        start and end dates, along with start and end times.
 *
 * The BlockCourse class inherits from the Course class and adds additional
 * details specific to block courses, including the start and end dates and
 * times for the course.
 */
class BlockCourse: public Course
{
private:
    Poco::Data::Date startDate; ///< The start date of the block course.
    Poco::Data::Date endDate; ///< The end date of the block course.
    Poco::Data::Time startTime; ///< The start time of the block course.
    Poco::Data::Time endTime; ///< The end time of the block course.

public:
    /**
     * @brief Constructs a BlockCourse object with the specified details.
     *
     * Initializes a block course with the given course key, title, major,
     * credit points, start and end dates, and start and end times.
     *
     * @param courseKey The unique identifier for the course.
     * @param title The title of the block course.
     * @param major The major associated with the block course.
     * @param creditPoints The number of credit points the course is worth.
     * @param startDate The start date of the block course.
     * @param endDate The end date of the block course.
     * @param startTime The start time of the block course.
     * @param endTime The end time of the block course.
     */
	BlockCourse(unsigned int courseKey, std::string title, std::string major,
			float creditPoints, Poco::Data::Date startDate,
			Poco::Data::Date endDate, Poco::Data::Time startTime,
			Poco::Data::Time endTime);

    /**
     * @brief Retrieves the start date of the block course.
     *
     * @return The start date of the course.
     */
	Poco::Data::Date getStartDate() const{ return startDate;};

    /**
     * @brief Retrieves the end date of the block course.
     *
     * @return The end date of the course.
     */
	Poco::Data::Date getEndDate() const{ return endDate;} ;

    /**
     * @brief Retrieves the start time of the block course.
     *
     * @return The start time of the course.
     */
	Poco::Data::Time getStartTime() const{ return startTime;};

    /**
     * @brief Retrieves the end time of the block course.
     *
     * @return The end time of the course.
     */
	Poco::Data::Time getEndTime() const{ return endTime;};

    /**
     * @brief Destructor for the BlockCourse class.
     *
     * Ensures proper cleanup of any resources used by the block course.
     */
	~BlockCourse();

    /**
     * @brief Writes the block course's details to an output stream.
     *
     * Serializes the block course information, including start and end dates
     * and times, to an output stream.
     *
     * @param out The output stream to write to.
     */
	void write(std::ostream& out) const;

    /**
     * @brief Reads the block course's details from an input stream.
     *
     * Deserializes the block course information from an input stream.
     *
     * @param in The input stream to read from.
     */
	void read(std::istream &in);
};

#endif /* BLOCKCOURSE_H_ */
