/*
 * StudentDB.cpp
 *
 *  Created on: Dec 21, 2024
 *      Author: Admin
 */

#include "StudentDB.h"

StudentDB::StudentDB()
{
}
using boost::asio::ip::tcp;

void StudentDB::addCourse(std::unique_ptr<Course> coursePtr)
{
	// void StudentDB::addCourse(std::unique_ptr<const Course>& coursePtr)
	// The parameter must be by value, so polymorphism can be applied.
	// If pass the reference, we cant not pass pointer to Weekly or Block Course
	// Const will be automatically added when insert to the map
	courses.insert(std::make_pair(coursePtr->getCourseKey(), std::move(coursePtr)));
}

void StudentDB::addStudent(Student& newStudent)
{
	students.insert(std::make_pair(newStudent.getMatrikelNumber(), newStudent));
}

bool StudentDB::studentExists(int matrikel) const
{
	if(students.find(matrikel) != students.end()){
		return true;
	}
	return false;
}

bool StudentDB::courseExists(int courseID) const
{
	if(courses.find(courseID)!= courses.end()){
		return true;
	}
	return false;
}

bool StudentDB::enrollmentAlreadyExists(int courseKey, int matrikel) const
{
	const std::vector <Enrollment>& enrollments =
			students.at(matrikel).getEnrollments();
	for(const Enrollment& enroll: enrollments){
		if (courseKey == static_cast<int>(
				enroll.getCourse()->getCourseKey())) return true;
	}
	return false;
}

void StudentDB::addEnrollment(int matrikel, Enrollment &enroll)
{
	students.at(matrikel).addEnrollment(enroll);
}

void StudentDB::updateGrade(float grade, unsigned int courseKey,
		unsigned int matrikel)
{
	students.at(static_cast<int>(matrikel)).updateGrade(grade, courseKey);
}

void StudentDB::removeEnrollment(unsigned int courseKey, unsigned int matrikel)
{
	students.at(static_cast<int>(matrikel)).removeEnrollment(courseKey);
}

void StudentDB::updateName(std::string first,
		std::string last, unsigned int matrikel)
{
	students.at(static_cast<int>(matrikel)).updateName(first, last);
}

void StudentDB::updateDOB(Poco::Data::Date dob, unsigned int matrikel)
{
	students.at(static_cast<int>(matrikel)).updateDOB(dob);
}

void StudentDB::updateAddress(Address newAddress, unsigned int matrikel)
{
	students.at(static_cast<int>(matrikel)).updateAddress(newAddress);
}

void StudentDB::write(std::ostream &out) const
{
	//Writing all courses
	out << courses.size()<< std::endl;
	for( const auto& coursePair : courses){
		//DYNAMIC CAST TO USE CORRESPOND CLASS FUNCTION
	    if (const BlockCourse* blockCourse = dynamic_cast<const BlockCourse*>
	    (coursePair.second.get())) {
	    	blockCourse->write(out);
	    }
	    else if (const WeeklyCourse* weeklyCourse =
	    		dynamic_cast<const WeeklyCourse*>(coursePair.second.get())) {
	    	weeklyCourse->write(out);
	    }
	}
	//Writing all students
	out << students.size()<< std::endl;
	int numOfEnrollments = 0;
	for( const auto& studentPair : students){
		studentPair.second.write(out);
		numOfEnrollments += static_cast<int> (
				studentPair.second.getEnrollments().size());
	}

	//Writing all enrollments
	out << numOfEnrollments << std::endl;
	std::vector<std::vector<Enrollment> > allEnrollments;
	for( const auto& studentPair : students){
		const auto& student = studentPair.second;
		for(const auto& enrollment : student.getEnrollments()){
			out << student.getMatrikelNumber()<< ";";
			enrollment.write(out);
		}
	}
}

void StudentDB::read(std::istream &in)
{
	//delete DB before update
	deleteDatabase();

	std::string line;
	std::getline(in, line);
	int numOfCourses = std::stoi(line);
	//Iterate through all courses in the file
	for(int i = 0; i < numOfCourses; i++){
		std::getline(in, line, ';');

		//If line is for weekly course
		if(line == "W"){
			//Create a temp. weeklycourse obj, fill it with data and add to db
            std::unique_ptr<WeeklyCourse> weeklyCoursePtr =
            		std::make_unique<WeeklyCourse>( 0, "Default", "Default", 0,
            				Poco::DateTime::DaysOfWeek::SUNDAY,
							Poco::Data::Time (1,1,1), Poco::Data::Time (1,1,1));
            weeklyCoursePtr->read(in);
            courses.insert(std::make_pair(weeklyCoursePtr->getCourseKey(),
            		std::move(weeklyCoursePtr)));
		}
		//If line is for block course
		else if(line == "B"){
			//Create a temp. blockcourse obj, fill it with data and add to db
            std::unique_ptr<BlockCourse> blockCoursePtr =
            		std::make_unique<BlockCourse>( 0, "Default", "Default", 0,
            				Poco::Data::Date (1,1,1), Poco::Data::Date (1,1,1),
							Poco::Data::Time (1,1,1), Poco::Data::Time (1,1,1));
            blockCoursePtr->read(in);
            courses.insert(std::make_pair(blockCoursePtr->getCourseKey(),
            		std::move(blockCoursePtr)));
		}
	}
	//Iterate through all students
	std::getline(in, line);
	int numOfStudents = std::stoi(line);
	for(int k = 0; k < numOfStudents; k++){
		//Create a temp. student obj, fill it with data and add to db
		Student newStudent(
				"Don", "Joe",  Poco::Data::Date(1,1,1), Address(
						"NoWhere", 0, "NoWhere", "None"));
		newStudent.read(in);
		addStudent(newStudent);
	}
	//Iterate through all Enrollments
	std::getline(in, line);
	int numOfEnrollments = std::stoi(line);
	for(int j = 0; j < numOfEnrollments; j++){
		//get matrikel and coursekey from the line
		std::getline(in, line, ';');
		int matrikel = std::stoi(line);
		std::getline(in, line, ';');
		int courseID = std::stoi(line);
		const Course* coursePointer  = courses.at(courseID).get();
		Enrollment newEnrollment(coursePointer, "Dummy");
		newEnrollment.read(in);
		addEnrollment(matrikel, newEnrollment);
	}
}

void StudentDB::deleteDatabase()
{
	std::cout << "Number of courses: "<< courses.size() << std::endl;
	std::cout << "Number of students: "<< students.size() << std::endl;
	std::cout << "Deleting database...." << std::endl;
	courses.clear();
	students.clear();
	std::cout << "Number of courses after deletion: "<< courses.size() << std::endl;
	std::cout << "Number of students after deletion: "
			<< students.size() << std::endl;

}

void StudentDB::getStudentsFromServer(int numStudents)
{

    boost::asio::io_context io_context;

    // Resolve the server address and port
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("www.hhs.users.h-da.cloud", "4242");

    //Repeate the query as much as user wants
    for(int i = 0; i < numStudents; i++){
        // Create a socket and connect to the server
        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        //Prepare buffers
        boost::asio::streambuf request_buffer;
        boost::asio::streambuf response_buffer;

        // Use std::ostream to send data to the server
        std::ostream request_stream(&request_buffer);
        request_stream << "generate\n";  // Send "generate" command
        boost::asio::write(socket, request_buffer);

        // Use std::istream to receive the response from the server
        // Reads data from the server into response_buffer
        // until the delimiter \n is encountered.
        boost::asio::read_until(socket, response_buffer, "\n");
        std::istream response_stream(&response_buffer);
        std::string response;
        std::getline(response_stream, response);
        std::cout << "Received: " << response << std::endl;

        // Send the "quit" command to the server
        request_buffer.consume(request_buffer.size());
        // Clear the buffer before sending new data
        request_stream << "quit\n";  // Send "quit" command
        boost::asio::write(socket, request_buffer);

        // Read the server's "quit" response
        boost::asio::read_until(socket, response_buffer, "\n");
        std::getline(response_stream, response);
        std::cout << "Received: " << response << std::endl;
    	try{
    	    Poco::JSON::Parser parser;
    	    Poco::Dynamic::Var result = parser.parse(response);

    	    // Access the parsed JSON object
    	    Poco::JSON::Object::Ptr jsonObject =
    	    		result.extract<Poco::JSON::Object::Ptr>();

    	    // create Name object and get name info from that
    	    Poco::JSON::Object::Ptr nameObject = jsonObject->getObject("name");
    	    std::string firstName = nameObject->getValue<std::string>("firstName");
    	    std::string lastName = nameObject->getValue<std::string>("lastName");

    	    // create location object and get address info from it
    	    Poco::JSON::Object::Ptr locationObject =
    	    		jsonObject->getObject("location");
    	    std::string city = locationObject->getValue<std::string>("city");
    	    int postalCode = locationObject->getValue<int>("postCode");
    	    std::string street = locationObject->getValue<std::string>("street");

    	    // create D.O.B object and get dob info from it
    	    Poco::JSON::Object::Ptr dobObject = jsonObject->getObject("dateOfBirth");
    	    int year = 1900 + dobObject->getValue<int>("year");
    	    int month = 1 + dobObject->getValue<int>("month");
    	    int day = dobObject->getValue<int>("date");

    	    //Create adress and student instance from the data above
    	    Poco::Data::Date dob(year, month, day);
    	    Address newAddress(street, postalCode, city, " ");
    	    Student newStudent(firstName, lastName, dob, newAddress);
    	    addStudent(newStudent);
    	    std::cout << "Student added" << std::endl;
    	}
    	catch (Poco::Exception& ex) {
    		std::cerr << "Error: " << ex.displayText() << std::endl;
    	}

    }
}
