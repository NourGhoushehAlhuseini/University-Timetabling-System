//#include <iostream>
//#include <vector>
//#include <string>
//#include <fstream>
//#include <algorithm>
//#include <limits>
//#include "SOFT20091coursework.h"
//
//using namespace std;
//
//int main() {
//    cout << "\nCreate Timetable\n";
//
//    string week, module, room, lecturer, time, group;
//
//    int w;
//    cout << "Enter week number (1 to 53): ";
//    cin >> w;
//    week = to_string(w);
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//
//    cout << "Enter module name: ";
//    getline(cin, module);
//
//    cout << "Enter room: ";
//    getline(cin, room);
//
//    cout << "Enter lecturer name: ";
//    getline(cin, lecturer);
//
//    string date;
//    vector<string> validDays = { "mon", "monday", "tue", "tuesday", "wed", "wednesday", "thu", "thursday", "fri", "friday" };
//    while (true) {
//        cout << "Enter day: ";
//        getline(cin, date);
//        transform(date.begin(), date.end(), date.begin(), ::tolower);
//        if (find(validDays.begin(), validDays.end(), date) != validDays.end()) break;
//        cout << "Invalid. Please enter a weekday.\n";
//    }
//
//    string timeStr;
//    while (true) {
//        cout << "Enter time (hh:mm): ";
//        getline(cin, timeStr);
//        if (timeStr.find(':') != string::npos && timeStr.length() >= 4 && timeStr.length() <= 5) break;
//        cout << "Invalid time format. Use hh:mm\n";
//    }
//
//    time = date + " " + timeStr;
//
//    cout << "Enter group: ";
//    getline(cin, group);
//
//    TimetableEntry testEntry = { week, module, room, lecturer, time, group };
//    vector<TimetableEntry> testTimetable;
//    testTimetable.push_back(testEntry);
//
// 
//    cout << "|Week:" << week << "|Module: " << module << "|Time: " << time
//        << "|Room:    " << room << "|Lecturer:   " << lecturer << "|Group:   " << group << endl;
//
//    return 0;
//}
