/*
 * WeeklyCourse.h
 *
 *  Created on: Jan 9, 2025
 *      Author: Admin
 *
 *  @file WeeklyCourse.h
 *  @brief Defines the WeeklyCourse class, which represents a weekly recurring
 *         course with a specific day, start time, and end time.
 */

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_

#include "Course.h"
#include <Poco/DateTime.h>
#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>
#include <string>

/**
 * @class WeeklyCourse
 * @brief Represents a weekly recurring course with a specific day and time.
 *
 * The WeeklyCourse class extends the Course class and adds additional
 * information for courses that meet on a specific day of the week at a
 * designated time. It provides methods to retrieve and manipulate day and time
 * details for weekly courses.
 */
class WeeklyCourse: public Course
{
private:
    Poco::DateTime::DaysOfWeek dayOfWeek; ///< The day of the week the course meets.
    Poco::Data::Time startTime; ///< The start time of the weekly course.
    Poco::Data::Time endTime; ///< The end time of the weekly course.
public:

    /**
     * @brief Constructs a WeeklyCourse object with the specified details.
     *
     * Initializes a weekly course with the given course key, title, major,
     * credit points, day of the week, start time, and end time.
     *
     * @param courseKey The unique identifier for the course.
     * @param title The title of the weekly course.
     * @param major The major associated with the course.
     * @param creditPoints The number of credit points the course is worth.
     * @param dayOfWeek The day of the week the course meets.
     * @param startTime The start time of the weekly course.
     * @param endTime The end time of the weekly course.
     */
	WeeklyCourse(unsigned int courseKey, std::string title, std::string major,
			float creditPoints, Poco::DateTime::DaysOfWeek dayOfWeek,
			Poco::Data::Time startTime, Poco::Data::Time endTime);

    /**
     * @brief Destructor for the WeeklyCourse class.
     *
     * Ensures proper cleanup of resources used by the weekly course.
     */
	~WeeklyCourse();

    /**
     * @brief Retrieves the start time of the weekly course.
     *
     * @return The start time of the course.
     */
	Poco::Data::Time getStartTime() const{ return startTime;};

    /**
     * @brief Retrieves the end time of the weekly course.
     *
     * @return The end time of the course.
     */
	Poco::Data::Time getEndTime() const{ return endTime;} ;

    /**
     * @brief Retrieves the day of the week the course meets.
     *
     * @return The day of the week as an enumerated value (e.g., Monday).
     */
	Poco::DateTime::DaysOfWeek getDayOfWeek() const {return dayOfWeek;};

    /**
     * @brief Writes the weekly course's details to an output stream.
     *
     * Serializes the weekly course information, including the day and time,
     * to an output stream.
     *
     * @param out The output stream to write to.
     */
	void write(std::ostream& out) const;

    /**
     * @brief Reads the weekly course's details from an input stream.
     *
     * Deserializes the weekly course information from an input stream.
     *
     * @param in The input stream to read from.
     */
	void read(std::istream &in);

    /**
     * @brief Retrieves the name of the day based on the day of the week.
     *
     * Converts the enumerated day value (e.g., Monday, Tuesday) to a string.
     *
     * @param dayOfWeek The enumerated day of the week.
     * @return The name of the day as a string (e.g., "Monday").
     */
	std::string getDayName(const Poco::DateTime::DaysOfWeek& dayOfWeek) const;

    /**
     * @brief Converts a day index to the corresponding enumerated day of the week.
     *
     * @param dayIndex The index representing the day of the week (1 = Monday, 0 = Sunday).
     * @return The corresponding enumerated day of the week.
     */
	Poco::DateTime::DaysOfWeek getDayOfWeekFromInt(int dayIndex) const;
};

#endif /* WEEKLYCOURSE_H_ */
