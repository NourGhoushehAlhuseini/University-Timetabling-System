#include <iostream>
#include "SOFT20091coursework.h"

#include <fstream>
template<typename T>
void saveListToFile(const std::vector<T>& list, const std::string& filename) {
    std::ofstream out(filename);
    for (const auto& item : list) {
        out << item << "\n";
    }
    out.close();
}

template<typename T>
void loadListFromFile(std::vector<T>& list, const std::string& filename) {
    std::ifstream in(filename);
    list.clear();
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) list.push_back(line);
    }
    in.close();
}

//int main() {
  // timetableData.clear();
   //students.clear();

   //timetableData.push_back({ "1", "AI", "lab 1", "Dr. ada", "Monday 10:00", "Group a" });
   //students.push_back({ "t100", "tommy", "group a" });

    //std::cout << "\n csv export test\n";
    //Student testStudent("tommy", "Group a");
    //testStudent.exportToCSV();

    //return 0;
//}
