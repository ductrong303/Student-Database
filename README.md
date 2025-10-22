# 🧑‍🎓 Student Database Management System (APT_Lab_3_StudentDB)

A simple **console-based Student Management System** that allows users to manage student records, courses, and enrollments.  
This project demonstrates file handling, structured data management, and menu-driven interaction in a C++ application.

---

## 🚀 Features

- ➕ Add new courses and students  
- 🧾 Print lists of students and courses  
- 🎓 Add student enrollments  
- 🔍 Search and update student records  
- 💾 Write data to file and read from file to update the database  
- 🌐 Retrieve test data from a server (mock/test mode)

---

## 🖥️ Example Console Output

### 📂 Starting Program

```
APT_Lab_3_StudentDB started.

=*=*=* Student Management System =*=*=*
    1. Add new Course
    2. Print courses
    3. Add new student
    4. Add enrollment
    5. Print students
    6. Search student
    7. Update student
    8. Write to file
    9. Read file to update DB
    10. Obtaining test data from server
    Enter the number of your choice: 9
====== Start update database using file ======

Name of the file to read (with type ending): 3StudentsDB.txt
Number of courses: 0
Number of students: 0
Deleting database....
Number of courses after deletion: 0
Number of students after deletion: 0
====== Updating database using file ended ======
```

---

### 🧾 Printing Student List

```
====== Start printing student list ======

-------- Student 0 --------
Name: Peter Olsen
Matrikel number: 100000
D.O.B : 23.11.1998
Address : 7158 Spurvevej, 21361 Juelsminde | 
---Students enrollments---
Course: APT
Key: 5387
Grade: 2.300000
Semester: WS2018

-------- Student 1 --------
Name: Josephine Stein
Matrikel number: 100001
D.O.B : 5.3.1997
Address : 2575 Tannenweg, 49733 Delitzsch | Apartement 6b
---Students enrollments---

-------- Student 2 --------
Name: Trong Ng
Matrikel number: 100005
D.O.B : 30.3.2000
Address : wqcq, 43 wsas |  
---Students enrollments---
Course: APT
Key: 5387
Grade: 2.800000
Semester: SS2019

====== End of student list ======
```

---

### 📚 Listing Courses

```
====== Start listing all courses ======

--- Course 0 ---
Title: C Programming
Course key: 2371
Major : Automation
CP : 5
Block course
Start date: 16.9.2019
End date: 20.9.2019
Start time: 14:15
End time: 19:15
--------------------

--- Course 1 ---
Title: APT
Course key: 5387
Major : Automation
CP : 5
Weekly course
Day of week: Wednesday
Start time: 17:45
End time: 19:15
--------------------

====== All courses listed ======
```

---

---

## 🧠 Concepts Demonstrated

- Object-Oriented Programming (OOP)
- File I/O (reading/writing structured data)
- Data structures and pointers
- Menu-driven program logic
- Basic data validation

---

## 👨‍💻 Author

**Your Name**  
📧 your.email@example.com  
📘 [LinkedIn](https://linkedin.com/in/yourprofile) | 💻 [GitHub](https://github.com/yourusername)
