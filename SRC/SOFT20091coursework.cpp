#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <filesystem>
#include <algorithm> 
#include "SOFT20091coursework.h"





using namespace std;
namespace fs = std::filesystem;
template<typename T>
void saveListToFile(const vector<T>& list, const string& filename) { // saves a list like modules, rooms to a file txt
    ofstream out(filename);
    for (const auto& item : list) {
        out << item << "\n";
    }
    out.close();
}

template<typename T>
void loadListFromFile(vector<T>& list, const string& filename) {   // loads a list of items from txt file
    ifstream in(filename);
    list.clear();
    string line;
    while (getline(in, line)) {
        if (!line.empty()) list.push_back(line);
    }
    in.close();
}


bool getValidIntInput(int& var, int max = -1, const string& errorMsg = "Invalid input. Please enter a valid input.", int min = 1) { // checks if the user's input is a valid input
    cin >> var;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << errorMsg << "\n";
        return false;
    }
    if (max > 0 && (var < min || var > max)) {                                     // returns true if it's valid, false if not
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << errorMsg << "\n";
        return false;
    }

    return true;
}

template <typename T>
void displayList(const vector<T>& list, const string& title = "") {             // displays a numbered list of items passed in a vector
    if (!title.empty()) cout << " " << title << " \n";
    for (int i = 0; i < list.size(); ++i)
        cout << i + 1 << ". " << list[i] << "\n";                                // shows available options to the user
}

template <typename T>
int getSelectionFromList(const vector<T>& list, const string& prompt = "Select  number: ") {           // displays list and asks user to select an item by number
    if (list.empty()) {
        cout << "No options available.\n";
        return -1;
    }
    displayList(list);
    int choice;
    cout << prompt;
    if (!getValidIntInput(choice, list.size())) return -1;
    return choice - 1;
}
template<typename T>
void saveStructsToFile(const vector<T>& list, const string& filename) {       // saves a list of items to a file, each on a new line
    ofstream out(filename);
    for (const auto& item : list)
        out << item.toString() << "\n";
    out.close();
}

template<typename T>
void loadStructsFromFile(vector<T>& list, const string& filename, T(*fromLine)(const string&)) {   //  loads a list from txt file  into a vector 
    ifstream in(filename);
    list.clear();
    string line;
    while (getline(in, line)) {
        if (!line.empty()) list.push_back(fromLine(line));
    }
    in.close();
}


template <typename T>
void manageList(vector<T>& list, const string& label, const string& filename) {  // handles the viewing, adding, editing, and deleting
    int option;
    do {
        cout << "\nManage " << label << "s \n";
        cout << "1. View " << label << "s\n2. Add " << label << "\n3. Edit " << label << "\n4. Delete " << label << "\n0. Back\nChoice: ";
        if (!getValidIntInput(option)) continue;

        switch (option) {
        case 1:
            displayList(list, label + "s");
            break;
        case 2: {
            string val;
            cout << "Enter new " << label << ": ";
            cin.ignore();
            getline(cin, val);
            list.push_back(val);
            saveListToFile(list, filename);
            cout << label << " added.\n";
            break;
        }
        case 3: {
            int i = getSelectionFromList(list, "Select the " + label + " number to edit: ");
            if (i == -1) break;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter new " << label << " name: ";
            string newVal;
            getline(cin, newVal);
            list[i] = newVal;
            saveListToFile(list, filename);
            cout << label << " updated.\n";
            break;
        }
        case 4: {
            int i = getSelectionFromList(list, "Select the " + label + " number to delete: ");
            if (i == -1) break;
            cout << label << " deleted: " << list[i] << "\n";
            list.erase(list.begin() + i);
            saveListToFile(list, filename);
            break;
        }
        case 0: break;
        default: cout << "Invalid option.\n";
        }
    } while (option != 0);
}

string toLower(const string& str) {
    string lower = str;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}


TimetableEntry timetableFromLine(const string& line) {
    vector<string> parts;
    string l = line;
    size_t pos = 0;
    while ((pos = l.find('|')) != string::npos) {
        parts.push_back(l.substr(0, pos));
        l.erase(0, pos + 1);
    }
    parts.push_back(l);
    return { parts[0], parts[1], parts[2], parts[3], parts[4], parts[5] };
}


StudentInfo studentFromLine(const string& line) {
    size_t p1 = line.find('|'), p2 = line.rfind('|');
    return {
        line.substr(0, p1),
        line.substr(p1 + 1, p2 - p1 - 1),
        line.substr(p2 + 1)
    };
}

Lecturer lecturerFromLine(const string& line) {
    size_t p1 = line.find('|'), p2 = line.rfind('|');
    return {
        line.substr(0, p1),
        line.substr(p1 + 1, p2 - p1 - 1),
        line.substr(p2 + 1)
    };
}


vector<TimetableEntry> timetableData;
vector<string> studentGroups;
vector<string> modules;
vector<StudentInfo> students;
vector<string> rooms;
vector<string> sessionTypes;
vector<Lecturer> lecturers;

std::string TimetableEntry::toString() const {
    return week + "|" + module + "|" + room + "|" + lecturer + "|" + time + "|" + group;
}

std::string StudentInfo::toString() const {
    return id + "|" + name + "|" + group;
}

std::string Lecturer::toString() const {
    return name + "|" + module + "|" + sessionType;
}

// constructor for User
User::User(const std::string& uname) : username(uname) {}

    // constructor
Admin::Admin(const std::string& uname) : User(uname) {}

    // showMenu implementation
    void Admin::showMenu() {
        int choice;
        do {
            cout << "\nAdmin Dashboard \n";
            cout << "1.  Modules\n";
            cout << "2. Student Groups\n";
            cout << "3.  Sessions\n";
            cout << "4. Register Students\n";
            cout << "5. Register Lecturers\n";
            cout << "6. Manage Rooms\n";         
            cout << "7. Create Timetable\n";
            cout << "8. Search Timetable Conflicts\n";
            cout << "0. Log out\n";
            cout << "Choice: ";

            if (!getValidIntInput(choice)) {
                choice = -1;
                continue;
            }

            switch (choice) {
            case 1: manageModules(); break;
            case 2: manageStudentGroups(); break;
            case 3: manageSessions(); break;
            case 4: registerStudents(); break;
            case 5: manageLecturers(); break;
            case 6: manageRooms(); break;
            case 7: createTimetable(); break;
            case 8: searchTimetableConflicts(); break;
            case 0: cout << "Logged out\n"; break;
            default: cout << "Invalid option\n";
            }
        } while (choice != 0);
    }

    void Admin::manageModules() {
        manageList(modules, "Module", "modules.txt");    // lets the admin add, edit, or delete modules

    }


    void Admin::manageStudentGroups() {
        manageList(studentGroups, "Group", "groups.txt");  // allows the admin manage student groups

    }


    void Admin::manageSessions() {
        manageList(sessionTypes, "Session Type", "session_types.txt");  // lets the admin define session types 

    }


    void Admin::registerStudents() {  // registers a new student and assigns them to a group
        string name, group;

        cin.ignore();
        while (true) {
            cout << "Enter student name: ";
            getline(cin, name);

            bool valid = !name.empty();
            for (char c : name) {
                if (!isalpha(c) && c != ' ') {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                cout << "Invalid name. Please enter a name.\n";
            }
            else {
                break;
            }
        }

        cout << "Available groups:\n";
        for (int i = 0; i < studentGroups.size(); ++i)
            cout << i + 1 << ". " << studentGroups[i] << "\n";

        cout << "Select group number: ";
        int g;
        if (!getValidIntInput(g, studentGroups.size())) return;


        if (g >= 1 && g <= studentGroups.size()) {
            group = studentGroups[g - 1];
            string id = "t" + to_string(students.size() + 30);
            students.push_back({ id, name, group });
            saveStructsToFile(students, "students.txt");
            cout << "Student registered and assigned to group. ID: " << id << "\n";
        }

        else {
            cout << "Invalid input. Please enter a valid input.\n";
        }
    }


    void Admin::manageLecturers() { // shows the lecturer menu where the admin can add lecturers or assign them to modules
        int option;
        do {
            cout << "\n Manage Lecturers \n";
            cout << "1. View Lecturers\n2. Add Lecturer\n3. Assign Lecturer to Module & Session\n0. Back\nChoice: ";

            if (!getValidIntInput(option)) continue;

            switch (option) {

            case 1:
                for (const auto& l : lecturers)
                    cout << "Name: " << l.name << ", Module: " << l.module << ", Session: " << l.sessionType << "\n";
                break;

            case 2: {
                string name;
                cout << "Enter lecturer name: ";
                cin.ignore();
                getline(cin, name);
                lecturers.push_back({ name, "Unassigned", "Unassigned" });
                saveStructsToFile(lecturers, "lecturers.txt");
                cout << "Lecturer added.\n";
                break;
            }

            case 3: {
                for (int i = 0; i < lecturers.size(); ++i)
                    cout << i + 1 << ". " << lecturers[i].name << "\n";
                int li;
                cout << "Select lecturer number: ";
                cin >> li;
                if (li < 1 || li > lecturers.size()) { cout << "Invalid.\n"; break; }

                for (int j = 0; j < modules.size(); ++j)
                    cout << j + 1 << ". " << modules[j] << "\n";
                int mi;
                cout << "Select module number: ";
                cin >> mi;
                if (mi < 1 || mi > modules.size()) { cout << "Invalid.\n"; break; }

                for (int k = 0; k < sessionTypes.size(); ++k)
                    cout << k + 1 << ". " << sessionTypes[k] << "\n";
                int si;
                cout << "Select session type number: ";
                cin >> si;
                if (si < 1 || si > sessionTypes.size()) { cout << "Invalid.\n"; break; }

                lecturers[li - 1].module = modules[mi - 1];
                lecturers[li - 1].sessionType = sessionTypes[si - 1];
                saveStructsToFile(lecturers, "lecturers.txt");
                cout << "Lecturer assigned to module and session.\n";
                break;
            }


            case 0: break;
            default: cout << "Invalid option.\n";
            }
        } while (option != 0);
    }

    void Admin::manageRooms() {  // allows the admin add, view, or remove rooms
        manageList(rooms, "Room", "rooms.txt");

    }

    void Admin::createTimetable() { // creates a new timetable entry or updates an existing one
        int initialChoice;
        cout << "\nCreate Timetable\n";
        cout << "1. Create a new timetable \n";
        cout << "2. Update an existing timetable \n";
        cout << "0. Back\n"; 
        cout << "Choice: ";
        if (!getValidIntInput(initialChoice, 2, "Invalid choice.", 0)) return;

        if (initialChoice == 0) {
            cout << "Returning to Admin Menu\n";
            return;
        }

        if (initialChoice == 1) {
            // for creating a new timetable 
            string week, module, room, lecturer, time, group;

            int w;
            cout << "Enter week number (1 to 53): ";
            if (!getValidIntInput(w, 53)) return;
            week = to_string(w);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (modules.empty()) {
                cout << "No modules available. Please add modules first.\n";
                return;
            }
            cout << "Available modules:\n";
            displayList(modules);
            int m;
            cout << "Select module number: ";
            if (!getValidIntInput(m, modules.size())) return;
            module = modules[m - 1];

            
            if (rooms.empty()) {
                cout << "No rooms available. Please add rooms first.\n"; 
                return;
            }
            cout << "Available rooms:\n";
            displayList(rooms);
            int r;
            cout << "Select room number: ";
            if (!getValidIntInput(r, rooms.size())) return;
            room = rooms[r - 1];

            
            if (lecturers.empty()) {
                cout << "No lecturers available. Please add lecturers first.\n"; 
                return;
            }
            cout << "Available lecturers:\n";
            for (int i = 0; i < lecturers.size(); ++i)
                cout << i + 1 << ". " << lecturers[i].name << " (" << lecturers[i].module << ", " << lecturers[i].sessionType << ")\n";
            int l;
            cout << "Select lecturer number: ";
            if (!getValidIntInput(l, lecturers.size())) return;
            lecturer = lecturers[l - 1].name;

            
            string date;
            vector<string> validDays = { "mon", "monday", "tue", "tuesday", "wed", "wednesday", "thu", "thursday", "fri", "friday" }; //to enter a day for time table
            while (true) {
                cout << "Enter day: ";
                cin >> date;
                transform(date.begin(), date.end(), date.begin(), ::tolower);
                if (find(validDays.begin(), validDays.end(), date) != validDays.end()) break;
                cout << "Invalid. Please enter a weekday.\n";
            }

            string timeStr;
            while (true) {
                cout << "Enter time: ";
                cin >> timeStr;
                if (timeStr.find(':') != string::npos && timeStr.length() >= 4 && timeStr.length() <= 5) break; //to enter a time 
                cout << "Invalid. Please enter time like 10:00.\n";
            }
            time = date + " " + timeStr;

           
            if (studentGroups.empty()) {
                cout << "No student groups available. Please add groups first.\n";
                return;
            }
            cout << "Available groups:\n";
            displayList(studentGroups);
            int g;
            cout << "Select group number: ";
            if (!getValidIntInput(g, studentGroups.size())) return;
            group = studentGroups[g - 1];

            
            timetableData.push_back({ week, module, room, lecturer, time, group });
            cout << "\nTimetable added:\n";
            cout << "--------------------------------------------\n";
            cout << " Week:         " << week << "\n";
            cout << " Module:       " << module << "\n";
            cout << " Time:         " << time << "\n";
            cout << " Room:         " << room << "\n";
            cout << " Lecturer:     " << lecturer << "\n";
            cout << " Group:        " << group << "\n";
            cout << "--------------------------------------------\n";
        } else if (initialChoice == 2) {
            
            if (timetableData.empty()) {
                cout << "No timetable available to update.\n";
                return;
            }

            cout << "\nSelect the timetable to update:\n";
            vector<string> existingEntries;
            for (size_t i = 0; i < timetableData.size(); ++i) {
                existingEntries.push_back("Week: " + timetableData[i].week +
                                         ", Module: " + timetableData[i].module +
                                         ", Group: " + timetableData[i].group +
                                         ", Time: " + timetableData[i].time +
                                         ", Room: " + timetableData[i].room +
                                         ", Lecturer: " + timetableData[i].lecturer);
            }
            int entryIndex = getSelectionFromList(existingEntries, "Enter the number of entry to update: ");

            if (entryIndex != -1) {
                TimetableEntry& entryToUpdate = timetableData[entryIndex];
                int updateFieldChoice;
                do {
                    cout << "\nWhat to update?\n";
                    cout << "1. Module\n";
                    cout << "2. Room\n";
                    cout << "3. Lecturer\n";
                    cout << "4. Day and Time\n";
                    cout << "5. Week\n";
                    cout << "6. Group\n";
                    cout << "0. Back to Create Timetable menu\n";
                    cout << "Choice: ";
                    if (!getValidIntInput(updateFieldChoice, 6, "Invalid choice.", 0)) continue;

                    switch (updateFieldChoice) {
                        case 1: {
                            cout << "Available modules:\n";
                            displayList(modules);
                            int m;
                            cout << "Select new module number: ";
                            if (getValidIntInput(m, modules.size())) {
                                entryToUpdate.module = modules[m - 1];
                                cout << "Module updated.\n";
                            }
                            break;
                        }
                        case 2: {
                            cout << "Available rooms:\n";
                            displayList(rooms);
                            int r;
                            cout << "Select new room number: ";
                            if (getValidIntInput(r, rooms.size())) {
                                entryToUpdate.room = rooms[r - 1];
                                cout << "Room updated.\n";
                            }
                            break;
                        }
                        case 3: {
                            cout << "Available lecturers:\n";
                            for (int i = 0; i < lecturers.size(); ++i)
                                cout << i + 1 << ". " << lecturers[i].name << " (" << lecturers[i].module << ", " << lecturers[i].sessionType << ")\n";
                            int l;
                            cout << "Select new lecturer number: ";
                            if (getValidIntInput(l, lecturers.size())) {
                                entryToUpdate.lecturer = lecturers[l - 1].name;
                                cout << "Lecturer updated.\n";
                            }
                            break;
                        }
                        case 4: {
                            string newDate;
                            vector<string> validDays = { "mon", "monday", "tue", "tuesday", "wed", "wednesday", "thu", "thursday", "fri", "friday" };
                            while (true) {
                                cout << "Enter new day: ";
                                cin >> newDate;
                                transform(newDate.begin(), newDate.end(), newDate.begin(), ::tolower);
                                if (find(validDays.begin(), validDays.end(), newDate) != validDays.end()) break;
                                cout << "Invalid. Please enter a weekday.\n";
                            }
                            string newTime;
                            while (true) {
                                cout << "Enter new time: ";
                                cin >> newTime;
                                if (newTime.find(':') != string::npos && newTime.length() >= 4 && newTime.length() <= 5) break;
                                cout << "Invalid. Please enter time like 10:00.\n";
                            }
                            entryToUpdate.time = newDate + " " + newTime;
                            cout << "Day and Time updated.\n";
                            break;
                        }
                        case 5: {
                            int newWeek;
                            cout << "Enter new week number (1 to 53): ";
                            if (getValidIntInput(newWeek, 53)) {
                                entryToUpdate.week = to_string(newWeek);
                                cout << "Week updated.\n";
                            }
                            break;
                        }
                        case 6: {
                            cout << "Available groups:\n";
                            displayList(studentGroups);
                            int g;
                            cout << "Select new group number: ";
                            if (getValidIntInput(g, studentGroups.size())) {
                                entryToUpdate.group = studentGroups[g - 1];
                                cout << "Group updated.\n";
                            }
                            break;
                        }
                        case 0:
                            cout << "Returning to Create Timetable menu.\n";
                            break;
                        default:
                            cout << "Invalid option.\n";
                    }
                } while (updateFieldChoice != 0);
            }
        }

        // save updated data
        saveStructsToFile(timetableData, "timetable.txt");

       
            }



    void Admin::searchTimetableConflicts() {   // checks the timetable for any scheduling conflicts same room, lecturer, or group at same time

        if (timetableData.empty()) {
            cout << "No timetable entries available.\n";
            return;
        }

        cout << "\nTimetable Conflict Checker \n";

        bool foundConflict = false;


        for (size_t i = 0; i < timetableData.size(); ++i) {
            for (size_t j = i + 1; j < timetableData.size(); ++j) {
                const auto& a = timetableData[i];
                const auto& b = timetableData[j];

                if (a.week == b.week && a.time == b.time) {
                    bool lecturerConflict = a.lecturer == b.lecturer;
                    bool roomConflict = a.room == b.room;
                    bool groupConflict = a.group == b.group;

                    if (lecturerConflict || roomConflict || groupConflict) {
                        foundConflict = true;
                        cout << "\nConflict Found (Week " << a.week << ", Time: " << a.time << ")\n";
                        cout << "Entry A - Module: " << a.module << ", Room: " << a.room
                            << ", Lecturer: " << a.lecturer << ", Group: " << a.group << "\n";
                        cout << "Entry B - Module: " << b.module << ", Room: " << b.room
                            << ", Lecturer: " << b.lecturer << ", Group: " << b.group << "\n";

                        if (lecturerConflict) cout << " - Same Lecturer Conflict\n";
                        if (roomConflict) cout << " - Same Room Conflict\n";
                        if (groupConflict) cout << " - Same Group Conflict\n";
                    }
                }
            }
        }

        if (!foundConflict) {
            cout << "No conflicts detected.\n";
        }
    }

    // student class

Student::Student(string uname, string grp) : User(uname), group(grp) {}

    void Student::showMenu() {   // shows student dashboard
        int c;
        do {
            while (true) {
                cout << "\nStudent Dashboard\n1. View Timetable\n2. Search Timetables\n3. Export Timetable\n0. Log out \nChoice: ";
                if (getValidIntInput(c, 3, "Invalid input. Please enter a number between 0 and 3.", 0)) break;

            }

            string val;
            if (c == 1) {
                cout << "Enter week: ";
                cin >> val;

                vector<string> weekdays = { "monday", "tuesday", "wednesday", "thursday", "friday" };

                bool hasAny = false;
                for (const string& day : weekdays) {
                    cout << "\n " << day << " \n";
                    bool found = false;
                    for (const auto& e : timetableData) {
                        
                        string entryDay = toLower(e.time.substr(0, e.time.find(' ')));
                        if (e.week == val && e.group == group && entryDay == day) {
                            cout << e.time << " | " << e.module << " | " << e.room << " | " << e.lecturer << "\n";
                            found = true;
                            hasAny = true;
                        }
                    }
                    if (!found) {
                        cout << "No classes for the day.\n";
                    }
                }

                if (!hasAny) {
                    cout << "No timetable entries found for Week " << val << ".\n";
                }
            }

           else if (c == 2) {
    cout << "search time table: ";
    cin.ignore();
    string val;
    getline(cin, val);

    // convert user input to lowercase
    transform(val.begin(), val.end(), val.begin(), ::tolower);

    bool found = false;
    for (const auto& e : timetableData) {
        // convert each field to lowercase before comparing
        if (
            e.group == group &&
            (
                toLower(e.week).find(val) != string::npos ||
                toLower(e.module).find(val) != string::npos ||
                toLower(e.room).find(val) != string::npos ||
                toLower(e.lecturer).find(val) != string::npos
                )
            )

    {
            cout << e.week << " | " << e.module << " | " << e.time
                 << " | " << e.room << " | " << e.lecturer << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "no match.\n";
    }
}
            else if (c == 3) exportToCSV();
        } while (c != 0);
        cout << "Logging out";
    }

    void Student::exportToCSV() {
        string filePath = "C:\\Users\\nour ghousheh\\Desktop\\d\\SOFT20091coursework\\" + username + "_timetable.csv";    // saves timetable to a .csv file
        ofstream f(filePath);

        if (!f.is_open()) {
            cout << "Failed to save CSV to: " << filePath << "\n";
            return;
        }
        f << "Student Name: " << username << "\n";
        for (const auto& s : students) {
            if (s.name == username) {
                f << "Student ID: " << s.id << "\n";
                break;
            }
        }

        f << "\nWeek,Module,Time,Room,Lecturer\n";

        for (auto& e : timetableData) {
            if (e.group == group)
                f << e.week << "," << e.module << "," << e.time << "," << e.room << "," << e.lecturer << "\n";
        }

        f.close();
        cout << "Exported to: " << filePath << "\n";
    }


bool authStudent(string& n, string& g) {
    string id;
    cout << "Student ID: "; getline(cin, id);   // checks if student ID exists 
    for (auto& s : students) if (s.id == id) { n = s.name; g = s.group; return true; }
    return false;
}

int main() {
  loadListFromFile(modules, "modules.txt");
  loadListFromFile(studentGroups, "groups.txt");
  loadListFromFile(rooms, "rooms.txt");
  loadListFromFile(sessionTypes, "session_types.txt");
  loadStructsFromFile(students, "students.txt", studentFromLine);
  loadStructsFromFile(lecturers, "lecturers.txt", lecturerFromLine);
  loadStructsFromFile(timetableData, "timetable.txt", timetableFromLine);
   int role;
   string input;

   while (true) {         // asks user to choose between admin or student
   cout << " Nottingham Trent University Timetabling \n1. Admin\n2. Student\nChoice: ";
   getline(cin, input);

      if (input == "1" || input == "2") {
          role = stoi(input);
           break;
        }
         {
         cout << "Invalid input. Please enter 1 or 2.\n";
        }
    }

    if (role == 1) {
     string adminPass;
     const string correctPass = "admin123";  // admin password 

       while (true) {
        cout << "Enter Admin Password: "; // asks admin to eneter password 
          getline(cin, adminPass);

         if (adminPass == correctPass) {
              cout << "Access granted.\n";
              Admin("AdminUser").showMenu();
                break;
            }
            else {
             cout << "Incorrect password. Please try again.\n";
            }
       }
    }

    else if (role == 2) {
      string name, group;
       while (true) {
         if (authStudent(name, group)) {
           Student(name, group).showMenu();
             break;
            }
            else {
              cout << "Invalid login. Please try again.\n";
           }
        }
    }

  
    return 0;
}