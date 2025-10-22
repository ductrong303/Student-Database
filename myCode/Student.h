/*
 * Student.h
 *
 *  Created on: Dec 21, 2024
 *      Author: Admin
 *
 *  @file Student.h
 *  @brief Defines the Student class that represents a student's information.
 *         This includes personal details, address, and academic enrollments.
 */

#ifndef STUDENT_H_
#define STUDENT_H_
#include "Address.h"
#include "Enrollment.h"
#include <Poco/Data/Date.h>

/**
 * @class Student
 * @brief Represents a student with personal information and enrollment details.
 *
 * The Student class stores information about a student, including their first
 * and last name, date of birth, address, and enrollment history. It provides
 * methods for managing enrollment, updating personal details, and writing/reading
 * student information.
 */
class Student
{
private:

	static unsigned int nextMatrikelNumber;///< Tracks the next matriculation number.

	unsigned int matrikelNumber; ///< Unique matriculation number for the student.

	std::string firstName; ///< First name of the student.

	std::string lastName; ///< Last name of the student.

	Poco::Data::Date dateOfBirth; ///< The student's date of birth.

	std::vector<Enrollment> enrollments; ///< List of courses the student is enrolled in.

	Address address; ///< Residential address of the student.

public:

    /**
     * @brief Constructs a Student object with the given personal details.
     *
     * Initializes a Student object with the student's first name, last name,
     * date of birth, and address. A unique matriculation number is assigned
     * automatically.
     *
     * @param firstName The first name of the student.
     * @param lastName The last name of the student.
     * @param dateOfBirth The date of birth of the student.
     * @param address The address of the student.
     */
	Student(std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth,
			Address address);

    /**
     * @brief Retrieves the student's matriculation number.
     * @return The student's unique matriculation number.
     */
	unsigned int getMatrikelNumber() const {return matrikelNumber;};

    /**
     * @brief Retrieves the student's first name.
     * @return The first name of the student.
     */
	std::string getFirstName() const {return firstName;};

    /**
     * @brief Retrieves the student's last name.
     * @return The last name of the student.
     */
	std::string getLastName() const {return lastName;};

    /**
     * @brief Retrieves the student's date of birth.
     * @return The date of birth of the student.
     */
	Poco::Data::Date getDateOfBirth() const {return dateOfBirth;};

    /**
     * @brief Retrieves the student's address.
     * @return A reference to the Address object representing the student's address.
     */
	const Address& getAddress() const {return address;};

    /**
     * @brief Retrieves the list of enrollments for the student.
     * @return A constant reference to the vector of enrollments.
     */
	const std::vector<Enrollment>& getEnrollments() const { return enrollments;};

    /**
     * @brief Adds a new enrollment to the student's record.
     *
     * @param enroll The Enrollment object to be added.
     */
	void addEnrollment(Enrollment& enroll);

    /**
     * @brief Updates the student's grade for a specific course.
     *
     * Finds the enrollment by course key and updates the grade.
     *
     * @param grade The new grade to assign.
     * @param courseKey The unique key of the course.
     */
	void updateGrade(float grade, unsigned int courseKey);

    /**
     * @brief Removes an enrollment from the student's record.
     *
     * Deletes the enrollment for the specified course key.
     *
     * @param courseKey The unique key of the course to remove.
     */
	void removeEnrollment(unsigned int courseKey);

    /**
     * @brief Updates the student's name.
     *
     * Changes both the first name and the last name of the student.
     *
     * @param first The new first name.
     * @param last The new last name.
     */
	void updateName(std::string first, std::string last);

    /**
     * @brief Updates the student's date of birth.
     *
     * @param dob The new date of birth.
     */
	void updateDOB(Poco::Data::Date dob);

    /**
     * @brief Updates the student's residential address.
     *
     * @param newAddress The new Address object to set.
     */
	void updateAddress(Address newAddress);

    /**
     * @brief Writes the student's information to an output stream.
     *
     * This method writes the student's information (including name, date of birth,
     * address, and enrollments) to the provided output stream.
     *
     * @param out The output stream to write the student's information to.
     */
	void write(std::ostream& out) const;

    /**
     * @brief Reads the student's information from an input stream and update.
     *
     * This method reads the student's information (including name, date of birth,
     * address, and enrollments) from the provided input stream.
     *
     * @param in The input stream to read the student's information from.
     */
	void read(std::istream &in);

};

#endif /* STUDENT_H_ */
