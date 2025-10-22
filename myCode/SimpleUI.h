/*
 * SimpleUI.h
 *
 *  Created on: Dec 21, 2024
 *      Author: Admin
 *
 *  @file SimpleUI.h
 *  @brief Defines the SimpleUI class, which provides a user interface for
 *         interacting with the StudentDB database.
 */

#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_
#include "StudentDB.h"
#include <iostream>
#include <type_traits>

/**
 * @class SimpleUI
 * @brief Provides a simple command-line interface for the StudentDB class.
 *
 * The SimpleUI class allows users to interact with the StudentDB database
 * by adding students and courses, managing enrollments, and viewing or
 * updating data through a command-line interface.
 */
class SimpleUI
{
private:
	StudentDB& db;

    /**
     * @brief Adds a new course to the database.
     *
     * Prompts the user for course details and adds it to the database.
     *
     * @return true if the course was added successfully, false otherwise.
     */
	bool addNewCourse();

    /**
     * @brief Lists all the courses in the database.
     *
     * Displays the details of all courses stored in the database.
     */
    void listCourses() const;

    /**
     * @brief Adds a new student to the database.
     *
     * Prompts the user for student details and adds the student to the
     * database.
     *
     * @return true if the student was added successfully, false otherwise.
     */
    bool addNewStudent();

    /**
     * @brief Adds an enrollment for a student in a course.
     *
     * Prompts the user for student and course details, then creates an
     * enrollment.
     */
    void addEnrollment();

    /**
     * @brief Prints all students in the database.
     *
     * Displays the details of all students stored in the database.
     */
    void printStudents() const;

    /**
     * @brief Searches for a student in the database.
     *
     * Prompts the user for search criteria and displays matching student
     * details.
     */
    void searchStudent() const;

    /**
      * @brief Updates the details of an existing student.
      *
      * Prompts the user for the student's matrikel number and the details to
      * update.
      */
    void updateStudent();

    /**
     * @brief Writes the database contents to a file.
     *
     * Serializes the database and writes it to an output file.
     */
    void write() const;

    /**
     * @brief Reads the database contents from a file.
     *
     * Deserializes the database from an input file.
     */
    void read();

    /**
     * @brief Retrieves students from a remote server.
     *
     * Fetches student data from a server and adds it to the database.
     */
    void obtainFromServer();
public:

    /**
     * @brief Constructs a SimpleUI instance with a reference to a database.
     *
     * @param db A reference to the StudentDB instance.
     */
	SimpleUI(StudentDB& db);

    /**
     * @brief Runs the SimpleUI interface.
     *
     * Displays a menu and processes user input to perform database
     * operations.
     */
	void run();
};

#endif /* SIMPLEUI_H_ */
