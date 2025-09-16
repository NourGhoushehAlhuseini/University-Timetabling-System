Nour Ghousheh Al Huseini
Student ID: T0326796
Module: SOFT20091 Software Design and Implementation
Git Repository:
https://olympus.ntu.ac.uk/T0326796/SOFT20091coursework1.git

-There are 14 total tests
-only run one test at a time
-the test cpp files are all commented out, you need to uncomment them when you wanna test them.
-make sure only one main()function is active, and the others should be commented out when testing.

Test 1 & 2: 
Admin login 
testAdminlogin.cpp

Tests both valid and invalid admin login using password input.
Enter correct password: admin555 
enter incorrect password:admin123 or any besides admin555


Test 3,4,5,& 6:
Module management (4 tests in one file)
test_module.cpp

add a new module- enter number 2 to add.
View the current module list- enter number 1 to view.
Edit a module name- enter number 3 to edit.
Delete a module- enter number 4 to delete.

test 7:
Create timetable
timetabletest.cpp

enter week number 
enter module
enter room
enter lecturer 
enter time
enter group

Displays the final created timetable

Test 8:
Timetable conflict detection
test_conflict_detection.cpp

Checks if the system can detect overlapping timetables
run the code, it loads preset data and prints conflict results.

Test 9&10:
Student login
test_student_login.cpp

Enter an invalid student ID: t00 to confirm its invalid.
enter valid student login with ID: t101. to confirm its valid.

Test 11,12,13,&14:
testViewWeekTimetable.cpp

enter choice 1 to view week
enter week: 1 to view time table fo that week.
search module: ai to view timetable with ai modules. 
input choice 3 to exporting the timetable as a .csv file 
the file path right now is string filePath = "C:\\Users\\nour ghousheh\\Desktop\\d\\SOFT20091coursework\\" + username + "_timetable.csv";
Make sure you update it in order to save in your desktop.




