/*
 * SimpleUI.cpp
 *
 *  Created on: Dec 21, 2024
 *      Author: Admin
 */

#include "SimpleUI.h"
#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>
#include <memory>

SimpleUI::SimpleUI(StudentDB& db): db{db} {}

void SimpleUI::obtainFromServer()
{
	std::cout << "How many students do you want to query: ";
	int numStudents;
	std::cin >> numStudents;
	db.getStudentsFromServer(numStudents);
}

void SimpleUI::run()
{
    std::cout << std::endl<< "=*=*=* Student Management System =*=*=*" << std::endl;
    std::cout << "	1. Add new Course" << std::endl;
    std::cout << "	2. Print courses" << std::endl;
    std::cout << "	3. Add new student" << std::endl;
    std::cout << "	4. Add enrollment" << std::endl;
    std::cout << "	5. Print students" << std::endl;
    std::cout << "	6. Search student" << std::endl;
    std::cout << "	7. Update student" << std::endl;
    std::cout << "	8. Write to file" << std::endl;
    std::cout << "	9. Read file to update DB" << std::endl;
    std::cout << "	10. Obtaining test data from server" << std::endl;
    std::cout << "	Enter the number of your choice: ";

    int command;
    std::cin >> command;
    switch(command){
    case 1:
    	addNewCourse();
    	break;
    case 2:
    	listCourses();
    	break;
    case 3:
    	addNewStudent();
    	break;
    case 4:
    	addEnrollment();
    	break;
    case 5:
    	printStudents();
    	break;
    case 6:
    	searchStudent();
    	break;
    case 7:
    	updateStudent();
    	break;
    case 8:
    	write();
    	break;
    case 9:
    	read();
    	break;
    case 10:
    	obtainFromServer();
    	break;
    default:
        std::cout << "###ERR: Invalid selection! Please enter a "
        		"number between 1 and 7." << std::endl;
        break;

    }
}

bool SimpleUI::addNewCourse()
{
	std::cout << "====== Start adding a new course ======"<< std::endl<< std::endl;

	std::cout << "Insert 1 for block course, 2 for weekly course: ";
    int courseType;
    std::cin >> courseType;
    std::cout << "Course key: ";
    unsigned int key;
    std::cin >> key;

    // Choose title, major, points
    std::cout << "Course title: ";
    std::string title;
    std::getline(std::cin >> std::ws, title);
    std::cout << "Course major: ";
    std::string major;
    std::getline(std::cin >> std::ws, major);
    std::cout << "Credit points: ";
    float creditPoints;
    std::cin >> creditPoints;

    // Input time and date info
    int hour, minute;
    std::cout <<"Enter class start time in 24h format(8:30am = 8 30) "
    		"with 'Enter' between each element: "<< std::endl;
    std::cin >> hour >> minute;
    Poco::Data::Time startTime(hour, minute, 00);
    std::cout <<"Enter class end time in 24h format(10:00am = 10 00) "
    		"with 'Enter' between each element: "<< std::endl;
    std::cin >> hour >> minute;
    Poco::Data::Time endTime(hour, minute, 00);

    //If course is weekly
    if(courseType == 1){
    	int day, month, year;
    	std::cout <<"Enter class start date in dd.mm.yyyy format "
    			"with 'Enter' between each element: "<< std::endl;
    	std::cin >> day >> month >> year;
        Poco::Data::Date startDate(year, month, day);

        std::cout <<"Enter class end date in dd.mm.yyyy format "
        		"with 'Enter' between each element: "<< std::endl;
        std::cin >> day >> month >> year;
        Poco::Data::Date endDate(year, month, day);

        std::unique_ptr<BlockCourse> blockCoursePtr = std::make_unique<BlockCourse>(
        		key, title, major, creditPoints, startDate,
        		endDate, startTime, endTime);
        db.addCourse(std::move(blockCoursePtr));
        std::cout <<"====== Block course added ======" << std::endl<< std::endl;
        return true;
    }

    //If course is block
    if(courseType == 2){
        std::cout << "=== Choose a week day ===" << std::endl;
        std::cout << "0. Sunday" << std::endl;
        std::cout << "1. Monday" << std::endl;
        std::cout << "2. Tuesday" << std::endl;
        std::cout << "3. Wednesday" << std::endl;
        std::cout << "4. Thursday" << std::endl;
        std::cout << "5. Friday" << std::endl;
        std::cout << "6. Saturday" << std::endl;
        std::cout << std::endl; // Extra space for clarity
        std::cout << "Enter the number of your choice: ";
        int dayNumber;
        std::cin >> dayNumber;
        if(0<= dayNumber && dayNumber <= 6){
            Poco::DateTime::DaysOfWeek weekDay =
            		static_cast<Poco::DateTime::DaysOfWeek>(dayNumber);
            std::unique_ptr<WeeklyCourse> weeklyCoursePtr =
            		std::make_unique<WeeklyCourse>( key, title, major, creditPoints,
            				weekDay, startTime, endTime);
            db.addCourse(std::move(weeklyCoursePtr));

            std::cout <<"====== Weekly course added ======" << std::endl;
            return true;
        }
        std::cout <<"###ERR: Can't add course because "
        		"invalid for weekday" << std::endl<< std::endl;
        return false;
    }
    return false;
}

void SimpleUI::listCourses() const
{
	std::cout << std::endl<< "====== Start listing all courses ======"
			<< std::endl<< std::endl;
	int counter = 0;
	for(const auto& coursePair : db.getCourses()){
        std::cout << "--- Course "<< counter << " ---"<<std::endl;
		std::string title =coursePair.second->getTitle();
	    std::cout << "Title: "<< coursePair.second->getTitle() << std::endl;
	    std::cout << "Course key: "<< coursePair.second->getCourseKey() << std::endl;
	    std::cout << "Major : "<< coursePair.second->getMajor() << std::endl;
	    std::cout << "CP : "<< coursePair.second->getCreditPoints() << std::endl;
	    counter++;

	    //second gives the smart pointer, get return the actual pointer
	    // must save to block course, because coursePair.second is of still of
	    //type const course and therefore cant use derived class's func
	    //Print info of BlockCourse
	    if (const BlockCourse* blockCourse = dynamic_cast<const BlockCourse*>
	    (coursePair.second.get())) {
	    	std::cout << "Block course"<< std::endl;
	    	std::string startDate =
	    			std::to_string(blockCourse->getStartDate().day()) + "." +
					std::to_string(blockCourse->getStartDate().month())+ "." +
					std::to_string(blockCourse->getStartDate().year());
	    	std::string endDate = std::to_string(blockCourse->getEndDate().day()) +
	    			"." + std::to_string(blockCourse->getEndDate().month() )+ "." +
					std::to_string(blockCourse->getEndDate().year());
	    	std::string startTime =
	    			std::to_string(blockCourse->getStartTime().hour()) +
	    			":" + std::to_string(blockCourse->getStartTime().minute());
	    	std::string endTime = std::to_string(blockCourse->getEndTime().hour()) +
	    			":" + std::to_string(blockCourse->getEndTime().minute() );
	    	std::cout << "Start date: "<< startDate << std::endl;
	    	std::cout << "End date: "<< endDate << std::endl;
	    	std::cout << "Start time: "<< startTime << std::endl;
	    	std::cout << "End time: "<< endTime << std::endl;
	    	std::cout << "--------------------"<< std::endl;
	    }
	    //Print info of WeeklyCourse
	    else if (const WeeklyCourse* weeklyCourse =
	    		dynamic_cast<const WeeklyCourse*>(coursePair.second.get())) {
	    	std::cout << "Weekly course"<< std::endl;
	    	std::string startTime =
	    			std::to_string(weeklyCourse->getStartTime().hour()) + ":" +
					std::to_string(weeklyCourse->getStartTime().minute());
	    	std::string endTime = std::to_string(weeklyCourse->getEndTime().hour()) +
	    			":" + std::to_string(weeklyCourse->getEndTime().minute());
	    	std::cout << "Day of week: "
	    			<< weeklyCourse->getDayName(weeklyCourse->getDayOfWeek())
					<< std::endl;
	    	std::cout << "Start time: "<< startTime << std::endl;
	    	std::cout << "End time: "<< endTime << std::endl;
	    	std::cout << "--------------------"<< std::endl;
	    }
	}
	std::cout << std::endl<< "====== All courses listed ======" << std::endl;
}

bool SimpleUI::addNewStudent()
{
	std::cout << "====== Start adding a new student ======"<< std::endl << std::endl;
	std::cout << "Please insert info of the student!!"<< std::endl;

	//Query for student info
    std::cout << "First name: ";
    std::string first;
    std::getline(std::cin >> std::ws, first);
    std::cout << "Last name: ";
    std::string last;
    std::getline(std::cin >> std::ws, last);
    int day, month, year;
    std::cout <<"Enter student's DOB in dd.mm.yyyy format "
    		"with 'Enter' between each element: "<< std::endl;
    std::cin >> day >> month >> year;
    Poco::Data::Date dob(year, month, day);

    //Query for address
	std::cout << "Please insert address information of the student!!"<< std::endl;
    std::cout << "Street: ";
    std::string street;
    std::getline(std::cin >> std::ws, street);
    std::cout << "Postal code: ";
    unsigned short postal;
    std::cin >> postal;
    std::cout << "City name: ";
    std::string city;
    std::getline(std::cin >> std::ws, city);
    //Extra address info
    std::cout << "Do you want to add additional info? 1 for yes, 2 for no. ";
    int extra;
    std::cin >> extra;
    std::string addiInfo = " ";
    if(extra == 1){
        std::cout << "Additional info: ";
        std::getline(std::cin >> std::ws, addiInfo);
    }

    //Create address and student instance
    Address newAddress(street, postal, city, addiInfo);
    Student newStudent(first, last, dob, newAddress);
    db.addStudent(newStudent);
    std::cout <<"====== New student added ======" << std::endl<< std::endl;
    return true;
}

void SimpleUI::addEnrollment()
{
	std::cout << "====== Start adding a new enrollment ======"<<
			std::endl<< std::endl;
    std::cout << "Matriculation number of student: ";
    int matrikel;
    std::cin >> matrikel;
    std::cout << "Course key: ";
    int courseID;
    std::cin >> courseID;
    std::cout << "Semester: ";
    std::string sem;
    std::cin >> sem;

    //If such course and student exist
    if(db.courseExists(courseID) && db.studentExists(matrikel)){
    	const Course* coursePointer = db.getCourses().at(courseID).get();
    	//and such enrollment not exists
    	if(!db.enrollmentAlreadyExists(courseID, matrikel)){
    		//then create and add such enrollment
        	Enrollment newEnrollment(coursePointer, sem);
        	db.addEnrollment(matrikel, newEnrollment);
            std::cout <<"====== New enrollment added ======" <<
            		std::endl<< std::endl;
            return void();
    	}
    	std::cout << "###ERR: Enrollment already exists" <<
    			std::endl<< std::endl;
    	return void();
    }
    std::cout <<"###ERR: Either student or course key is invalid " <<
    		std::endl<< std::endl;
}

void SimpleUI::printStudents() const
{
	std::cout << "====== Start printing student list ======"<<
			std::endl<< std::endl;
	int counter = 0;

	//Itereate through each pair in students map and print the info
	for(auto& studentPair: db.getStudents()){
		const Student& student = studentPair.second;
        std::cout << "-------- Student "<< counter <<" --------"<< std::endl;
	    std::cout << "Name: "<< student.getFirstName()<< " "<<
	    		student.getLastName() << std::endl;
	    std::cout << "Matrikel number: "<<
	    		std::to_string(student.getMatrikelNumber())<< std::endl;
    	std::string dob = std::to_string(student.getDateOfBirth().day()) +
    			"." + std::to_string(student.getDateOfBirth().month()) +
				"." + std::to_string(student.getDateOfBirth().year());
	    std::cout << "D.O.B : "<< dob << std::endl;

	    std::string address = student.getAddress().getStreet() + ", " +
	    		std::to_string(student.getAddress().getPostalCode()) +
				" " +student.getAddress().getCityName();
	    std::cout << "Address : "<< address<< " | "<<
	    		student.getAddress().getAdditionalInfo() << std::endl;
		counter ++;

		//For each student, iterate through his enrollments
	    const std::vector<Enrollment>& enrollments = student.getEnrollments();
		std::cout << "---Students enrollments---"<< std::endl;
	    for(const Enrollment& enroll : enrollments){
	    	std::cout << "Course: "<< enroll.getCourse()->getTitle()<< std::endl;
	    	std::cout << "Key: "<< enroll.getCourse()->getCourseKey() <<std::endl;
		    std::cout << "Grade: "<< std::to_string(enroll.getGrade())<< std::endl;
		    std::cout << "Semester: "<< enroll.getSemester()<< std::endl<< std::endl;
	    }
	}
	std::cout << "====== End of student list ======"<< std::endl;
}

void SimpleUI::searchStudent() const
{
	std::cout << std::endl<< "====== Start searching for student ======" <<
			std::endl<< std::endl;
	std::cout << "Insert keyword (lower case): ";
	std::string keyword;
    std::getline(std::cin >> std::ws, keyword);

	std::cout << "Search results: "<< std::endl;
	//Itereate through each pair in students map to find such keyword in name
	for(const std::pair<const int, Student>& studentPair: db.getStudents()){
		const Student& student = studentPair.second;
		std::string first = student.getFirstName();
		std::string last = student.getLastName();
		//Change names to lower case
	    for (char& c : first) {
	        c = std::tolower(static_cast<unsigned char>(c));
	    }
	    for (char& c : last) {
	    	c = std::tolower(static_cast<unsigned char>(c));
	    }
	    //Find sub string in the first and last name
		if(first.std::string::find(keyword) != std::string::npos ||
				last.std::string::find(keyword) != std::string::npos){
			std::cout << "---------"<< std::endl;
			std::cout << student.getFirstName()<< " "<< student.getLastName()<<
					" - "<< std::to_string(student.getMatrikelNumber())<< std::endl;
		}
	}
	std::cout << std::endl<< "====== Search finished ======" << std::endl;
}

void SimpleUI::updateStudent()
{
	std::cout << "====== Start updating a student ======"<< std::endl<< std::endl;
    std::cout << "What is the matrikel number of the student: ";
    unsigned int matrikel;
    std::cin >> matrikel;

    //If student with such matrikel exists
    if(db.studentExists(static_cast <int>(matrikel)) ){
    	const Student& student = db.getStudents().at(static_cast <int>(matrikel));
	    std::cout << "!!! Student found. Choose one of these options:" << std::endl;

	    //Then prints all info that user can change
	    std::cout <<std::endl << "0. Exit the process"<< std::endl;
	    std::cout << "1. Name: "<< student.getFirstName()<< " "<<
	    		student.getLastName() << std::endl;
    	std::string dob = std::to_string(student.getDateOfBirth().day()) +
    			"." + std::to_string(student.getDateOfBirth().month())+ "." +
				std::to_string(student.getDateOfBirth().year());
	    std::cout << "2. D.O.B : "<< dob << std::endl;
	    std::string address = student.getAddress().getStreet() + ", " +
	    		std::to_string(student.getAddress().getPostalCode()) +
				" " +student.getAddress().getCityName();
	    std::cout << "3. Address : "<< address<< " | "<<
	    		student.getAddress().getAdditionalInfo() << std::endl;

	    const std::vector<Enrollment>& enrollments = student.getEnrollments();
	    // Printing enrollment info
	    std::vector <unsigned int> enrollmentCourseIDs;
	    if (enrollments.size() > 0){
			std::cout <<std::endl << "4. Enrollments"<< std::endl<< std::endl;
		    for(const Enrollment& enroll : enrollments){
		    	std::cout << "	Course: "<< enroll.getCourse()->getTitle()<<
		    			"- Key: "<< enroll.getCourse()->getCourseKey() <<std::endl;
			    std::cout << "	Grade: "<<
			    		std::to_string(enroll.getGrade())<< std::endl;
			    std::cout << "	Semester: "<<
			    		enroll.getSemester()<< std::endl<< std::endl;
			    enrollmentCourseIDs.push_back(enroll.getCourse()->getCourseKey());
		    }
	    }
	    else std::cout << "Student has no enrollments"<< std::endl<< std::endl;

	    // Query user for what to change
	    std::cout <<std::endl << "Which property do you want to update?"<< std::endl;
	    int option;
	    std::cin >> option;
	    if(option == 0){
	    	std::cout << "====== Exit update process ======"<< std::endl<< std::endl;
	    	return void();
	    }
	    // Change name
	    else if(option == 1){
	    	std::cout << "!!! Please insert the new name:"<< std::endl;
	        std::cout << "First name: ";
	        std::string first;
	        std::getline(std::cin >> std::ws, first);

	        std::cout << "Last name: ";
	        std::string last;
	        std::getline(std::cin >> std::ws, last);

	        db.updateName(first, last, matrikel);
	    }
	    // Change D.O.B
	    else if(option == 2){
	    	std::cout << "!!! Please insert the new D.O.B in dd.mm.yyyy "
	    			"format with Enter between elements:"<< std::endl;
	        int day, month, year;
	        std::cin >> day >> month >> year;
	        Poco::Data::Date dob(year, month, day);
	        db.updateDOB(dob, matrikel);
	    }
	    // Change address
	    else if(option == 3){
	    	std::cout << "!!! Please insert address "
	    			"information of the student"<< std::endl;
	        std::cout << "Street: ";
	        std::string street;
	        std::getline(std::cin >> std::ws, street);

	        std::cout << "Postal code: ";
	        unsigned short postal;
	        std::cin >> postal;
	        std::cout << "City name: ";
	        std::string city;
	        std::getline(std::cin >> std::ws, city);

	        std::cout << "Do you want to add additional info? 1 for yes, 2 for no.";
	        int extra;
	        std::cin >> extra;
	        std::string addiInfo = " ";
	        if(extra == 1){
	            std::cout << "Additional info: ";
	            std::getline(std::cin >> std::ws, addiInfo);
	        }
	        Address newAddress(street, postal, city, addiInfo);
	        db.updateAddress(newAddress, matrikel);
	    }

	    //Change enrollment
	    else if(option == 4 && enrollments.size() > 0){
	    	std::cout << "Please type in the key of the course "
	    			"that should be changed"<< std::endl;
	        unsigned int courseKey;
	        std::cin >> courseKey;
	        if(find(enrollmentCourseIDs.begin(), enrollmentCourseIDs.end(),
	        		courseKey) != enrollmentCourseIDs.end()){
		    	std::cout << "Type 1 to change grade, 2 to "
		    			"remove enrollment:"<< std::endl;
		        int option;
		        std::cin >> option;
		        if(option == 1){
			    	std::cout << "What is the grade:"<< std::endl;
			        float grade;
			        std::cin >> grade;
		        	db.updateGrade(grade, courseKey, matrikel);
			    	std::cout << "!!! New grade is updated:"<< std::endl;
		        }
		        else if(option ==2){
		        	db.removeEnrollment(courseKey, matrikel);
		        	std::cout << "!!! Enrollment for course"<< courseKey
		        			<< " is removed "<< std::endl;
		        }
		        else std::cout << "###ERR: Invalid option "<< std::endl;
	        }
	        else{
	        	std::cout << "###ERR: Student does not have enrollment "
	        			"with course of such key"<< std::endl;
	        }
	    }
    }
    else{
	    std::cout << "###ERR: Can't found student "
	    		"with such matrikel number"<< std::endl;

    }
    std::cout <<"====== Update student ended ======" << std::endl<< std::endl;
}

void SimpleUI::write() const
{
	std::cout << "====== Start writing database to file ======"<<
			std::endl<< std::endl;
	std::string fileName;
	std::cout << "What should be the file name?: ";
	std::cin >> fileName;
	std::ofstream myfile;
	myfile.open(fileName);

	this->db.write(myfile);
	myfile.close();
    std::cout <<"====== Writing database to file ended ======" <<
    		std::endl<< std::endl;
}

void SimpleUI::read()
{
	std::cout << "====== Start update database using file ======"<<
			std::endl<< std::endl;

	std::string fileName;
	std::cout << "Name of the file to read (with type ending): ";
	std::cin >> fileName;
    std::ifstream inputFile(fileName, std::ifstream::in);

    // Check if the file opened successfully
    if (!inputFile) {
        std::cerr << "Error opening the file!" << std::endl;
        return void();
    }
    this->db.read(inputFile);
	inputFile.close();
    std::cout <<"====== Updating database using file ended ======" <<
    		std::endl<< std::endl;
}
