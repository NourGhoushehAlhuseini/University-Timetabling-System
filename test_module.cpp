//#include <iostream>
//#include "SOFT20091coursework.h"
//
//template <typename T>
//void displayList(const std::vector<T>& list, const std::string& title = "") {
//    if (!title.empty()) std::cout << " " << title << " \n";
//    for (int i = 0; i < list.size(); ++i)
//        std::cout << i + 1 << ". " << list[i] << "\n";
//}
//
//template <typename T>
//int getSelectionFromList(const std::vector<T>& list, const std::string& prompt = "Select number: ") {
//    if (list.empty()) {
//        std::cout << "No options available.\n";
//        return -1;
//    }
//    displayList(list);
//    int choice;
//    std::cout << prompt;
//    std::cin >> choice;
//    return choice - 1;
//}
//
//int main() {
//    std::cout << "\nAdmin Module Management Acceptance Test\n";
//
//    modules.clear();
//
//    int choice;
//    do {
//        std::cout << "\nAdmin Module Dashboard Menu\n";
//        std::cout << "1. View Modules\n";
//        std::cout << "2. Add Module\n";
//        std::cout << "3. Edit Module\n";
//        std::cout << "4. Delete Module\n";
//        std::cout << "0. Exit\n";
//        std::cout << "Choice: ";
//        std::cin >> choice;
//
//        switch (choice) {
//        case 1:
//            displayList(modules, "Modules");
//            //break;
//
//        case 2: {
//            std::string newModule;
//            std::cin.ignore();
//            std::cout << "Enter new module name: ";
//            std::getline(std::cin, newModule);
//            modules.push_back(newModule);
//            std::cout << "Module added successfully.\n";
//            break;
//        }
//
//        case 3: {
//            int index = getSelectionFromList(modules, "Select module number to edit: ");
//            if (index >= 0) {
//                std::cin.ignore();
//                std::string newName;
//                std::cout << "Enter new name: ";
//                std::getline(std::cin, newName);
//                modules[index] = newName;
//                std::cout << "Module updated successfully.\n";
//            }
//            break;
//        }
//
//        case 4: {
//            int index = getSelectionFromList(modules, "Select module number to delete: ");
//            if (index >= 0) {
//                std::cout << "Deleting module: " << modules[index] << "\n";
//                modules.erase(modules.begin() + index);
//                std::cout << "Module deleted successfully.\n";
//            }
//            break;
//        }
//
//        case 0:
//            std::cout << "Exiting Module Management.\n";
//            break;
//
//        default:
//            std::cout << "Invalid input.\n";
//        }
//    } while (choice != 0);
//
//    return 0;
//}
