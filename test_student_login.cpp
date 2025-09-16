//#include <iostream>
//#include "SOFT20091coursework.h"
//
//using namespace std;
//
//int main() {
//   
//  students.clear();
//  students.push_back({ "t101", "Alice", "Group A" });
//
//  string name, group, inputID;
//
//  cout << "\nStudent login test\n";
//  cout << "Student ID: ";
//  getline(cin, inputID);
//
//
//  bool loginSuccess = false;
//  for (auto& s : students) {
//    if (s.id == inputID) {
//        name = s.name;
//       group = s.group;
//       loginSuccess = true;
//            break;
//        }
//   }
//
//    if (!loginSuccess) {
//     cout << " Invalid login for ID: " << inputID << "\n";
//    }
//    else {
//    cout << " login was accepted. Name: " << name << ", Group: " << group << "\n";
//   }
//
//    return 0;
//}
