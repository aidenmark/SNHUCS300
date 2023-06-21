/* 
Aeriel Denmark
CS 300 - DSA:  Analysis and Design
Yurik - 7-1 Project Two
due Sun 6/18/23
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

// Course class
class Course {
public:
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;

    Course(const std::string& number, const std::string& title, const std::vector<std::string>& prereqs)
        : courseNumber(number), courseTitle(title), prerequisites(prereqs) {}
};

// Function to split a string by a delimiter
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to trim leading and trailing whitespaces from a string
std::string trim(const std::string& str) {
    const auto strBegin = str.find_first_not_of(" \t");
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(" \t");
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

// Function to load course data from a file and store it in the data structure
void loadDataStructure(const std::string& filename, std::map<std::string, Course>& courses) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> courseInfo = split(line, ',');
        if (courseInfo.size() < 2) {
            std::cout << "Error: Invalid line format. Each line must have at least two parameters." << std::endl;
            continue;
        }

        std::string courseNumber = trim(courseInfo[0]);
        std::string courseTitle = trim(courseInfo[1]);
        std::vector<std::string> prerequisites;
        for (size_t i = 2; i < courseInfo.size(); i++) {
            prerequisites.push_back(trim(courseInfo[i]));
        }

        courses[courseNumber] = Course(courseNumber, courseTitle, prerequisites);
    }

    file.close();
    std::cout << "Data loaded successfully." << std::endl;
}

// Function to print the alphanumeric list of courses
void printCourseList(const std::map<std::string, Course>& courses) {
    std::vector<std::string> courseNumbers;
    for (const auto& course : courses) {
        courseNumbers.push_back(course.first);
    }

    std::sort(courseNumbers.begin(), courseNumbers.end());

    for (const auto& courseNumber : courseNumbers) {
        const Course& course = courses.at(courseNumber);
        std::cout << "Course Number: " << course.courseNumber << std::endl;
        std::cout << "Course Title: " << course.courseTitle << std::endl;
        std::cout << std::endl;
    }
}

// Function to print course information and prerequisites
void printCourseInformation(const std::string& courseNumber, const std::map<std::string, Course>& courses) {
    if (courses.count(courseNumber) == 0) {
        std::cout << "Course not found." << std::endl;
        return;
    }

    const Course& course = courses.at(courseNumber);
    std::cout << "Course Number: " << course.courseNumber << std::endl;
    std::cout << "Course Title: " << course.courseTitle << std::endl;

    if (!course.prerequisites.empty()) {
        std::cout << "Prerequisites: ";
        for (const auto& prerequisite : course.prerequisites) {
            std::cout << prerequisite << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string filename;
    std::map<std::string, Course> courses;
    bool dataLoaded = false;

    while (true) {
        std::cout << "Menu:\n";
        std::cout << "a. Load Data Structure\n";
        std::cout << "b. Print Course List\n";
        std::cout << "c. Print Course\n";
        std::cout << "d. Exit\n";
        std::cout << "Enter your choice: ";

        char choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 'a': {
                std::cout << "Enter the filename: ";
                std::getline(std::cin, filename);
                loadDataStructure(filename, courses);
                dataLoaded = true;
                break;
            }
            case 'b': {
                if (dataLoaded) {
                    printCourseList(courses);
                } else {
                    std::cout << "Error: Data structure not loaded. Please load the data first." << std::endl;
                }
                break;
            }
            case 'c': {
                if (dataLoaded) {
                    std::string courseNumber;
                    std::cout << "Enter the course number: ";
                    std::getline(std::cin, courseNumber);
                    printCourseInformation(courseNumber, courses);
                } else {
                    std::cout << "Error: Data structure not loaded. Please load the data first." << std::endl;
                }
                break;
            }
            case 'd':
                std::cout << "Exiting program. Goodbye!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }

        std::cout << std::endl;
    }
}


/*
To compile and run the code, you can use a C++ compiler such as GCC or Clang. For example, 
with GCC, you can save the code in a file called "advising_program.cpp" and compile it using 
the following command
*/

g++ -std=c++11 -o advising_program advising_program.cpp

// To run the program: //

./advising_program


