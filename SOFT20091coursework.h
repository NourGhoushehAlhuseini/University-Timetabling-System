#pragma once
#include <string>
#include <vector>

// structs

struct TimetableEntry {
    std::string week, module, room, lecturer, time, group;
    std::string toString() const;
};

struct StudentInfo {
    std::string id, name, group;
    std::string toString() const;
};

struct Lecturer {
    std::string name, module, sessionType;
    std::string toString() const;
};

// user class

class User {
protected:
    std::string username;
public:
    User(const std::string& uname);
    virtual void showMenu() = 0;
};

// admin class
class Admin : public User {
public:
    Admin(const std::string& uname);
    void showMenu() override;
    void searchTimetableConflicts();
    void manageModules();
    void manageStudentGroups();
    void manageSessions();
    void manageRooms();
    void registerStudents();
    void manageLecturers();
    void createTimetable();
};
// student class

class Student : public User {
    std::string group;
public:
    Student(std::string uname, std::string grp);
    void showMenu() override;
    void exportToCSV();
};



extern std::vector<TimetableEntry> timetableData;
extern std::vector<StudentInfo> students;
extern std::vector<Lecturer> lecturers;
extern std::vector<std::string> modules;
extern std::vector<std::string> rooms;
extern std::vector<std::string> studentGroups;
extern std::vector<std::string> sessionTypes;



bool authStudent(std::string& n, std::string& g);
