/*
 * StudentDB.h
 *
 *  Created on: Dec 21, 2024
 *      Author: Admin
 *
 *  @file StudentDB.h
 *  @brief Defines the StudentDB class, which manages students, courses,
 *         and their enrollments.
 */

#ifndef STUDENTDB_H_
#define STUDENTDB_H_
#include "Student.h"
#include "Course.h"
#include "BlockCourse.h"
#include "WeeklyCourse.h"
#include <memory>
#include <fstream>

#include <iostream>
#include <boost/asio.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/json.hpp>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>

/**
 * @class StudentDB
 * @brief Represents a database for storing students, courses, and enrollments.
 *
 * The StudentDB class manages the enrollment of students in courses, keeps
 * track of students and courses, and provides functionality to add, remove,
 * and update student information and enrollments.
 */
class StudentDB
{
private:
    std::map <int, Student> students; ///<Map of students, indexed by matrikel number
    std::map <int, std::unique_ptr<const Course>> courses; ///< Map of courses.

public:
    /**
     * @brief Constructs an empty StudentDB.
     *
     * Initializes the database with no students or courses.
     */
	StudentDB();

    /**
     * @brief Retrieves all the courses in the database.
     *
     * @return A constant reference to the map of courses.
     */
	const std::map <int, std::unique_ptr<const Course>>& getCourses() const {
		return courses;};

    /**
     * @brief Retrieves all the students in the database.
     *
     * @return A constant reference to the map of students.
     */
	const std::map <int, Student>& getStudents() const {return students;};

    /**
     * @brief Adds a course to the database.
     *
     * @param coursePtr A unique pointer to a course to be added.
     */
	void addCourse(std::unique_ptr<Course> coursePtr);

    /**
     * @brief Adds a student to the database.
     *
     * @param newStudent A reference to the student to be added.
     */
	void addStudent(Student& newStudent);

    /**
     * @brief Checks if a student with the given matrikel number exists.
     *
     * @param matrikel The matrikel number of the student.
     * @return true if the student exists, false otherwise.
     */
	bool studentExists(int matrikel) const;

    /**
     * @brief Checks if a course with the given course ID exists.
     *
     * @param courseID The ID of the course.
     * @return true if the course exists, false otherwise.
     */
	bool courseExists(int courseID) const;

    /**
     * @brief Checks if an enrollment already exists for the given student
     *        and course.
     *
     * @param courseKey The course key.
     * @param matrikel The matrikel number of the student.
     * @return true if the enrollment exists, false otherwise.
     */
	bool enrollmentAlreadyExists(int courseKey, int matrikel) const;

    /**
     * @brief Adds an enrollment for a student in a course.
     *
     * @param matrikel The matrikel number of the student.
     * @param enroll The enrollment to be added.
     */
	void addEnrollment(int matrikel, Enrollment& enroll);

    /**
     * @brief Updates the grade for a student in a course.
     *
     * @param grade The new grade.
     * @param courseKey The course key.
     * @param matrikel The matrikel number of the student.
     */
	void updateGrade(float grade, unsigned int courseKey, unsigned int matrikel);

    /**
     * @brief Removes an enrollment for a student from a course.
     *
     * @param courseKey The course key.
     * @param matrikel The matrikel number of the student.
     */
	void removeEnrollment(unsigned int courseKey, unsigned int matrikel);

    /**
     * @brief Updates the address of a student.
     *
     * @param newAddress The new address to be set.
     * @param matrikel The matrikel number of the student.
     */
	void updateAddress(Address newAddress, unsigned int matrikel);

    /**
     * @brief Updates the name of a student.
     *
     * @param first The new first name.
     * @param last The new last name.
     * @param matrikel The matrikel number of the student.
     */
	void updateName(std::string first, std::string last, unsigned int matrikel);

    /**
     * @brief Updates the date of birth of a student.
     *
     * @param dob The new date of birth.
     * @param matrikel The matrikel number of the student.
     */
	void updateDOB(Poco::Data::Date dob, unsigned int matrikel);

    /**
     * @brief Writes the database contents to an output stream.
     *
     * Serializes the student and course data to an output stream.
     *
     * @param out The output stream to write to.
     */
	void write(std::ostream& out) const;

    /**
     * @brief Reads the database contents from an input stream.
     *
     * Deserializes the student and course data from an input stream.
     *
     * @param in The input stream to read from.
     */
	void read(std::istream &in);

    /**
     * @brief Deletes the entire student database.
     *
     * Clears all students and courses from the database.
     */
	void deleteDatabase();

    /**
     * @brief Fetches students from the server.
     *
     * Retrieves the specified number of students from a remote server.
     *
     * @param numStudents The number of students to retrieve.
     */
	void getStudentsFromServer(int numStudents);
};

#endif /* STUDENTDB_H_ */
