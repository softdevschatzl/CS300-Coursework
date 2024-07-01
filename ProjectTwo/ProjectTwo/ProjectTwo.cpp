#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

// Course class to represent each course
class Course {
public:
    string number;
    string title;
    vector<string> prerequisites;

    Course() = default;
    Course(string num, string t, vector<string> prereqs)
        : number(num), title(t), prerequisites(prereqs) {}
};

// Function prototypes
void loadCourses(map<string, Course>& courses, const string& filename);
void printCourseList(const map<string, Course>& courses);
void printCourseInformation(const map<string, Course>& courses, const string& courseNumber);
void displayMenu();

int main() {
    map<string, Course> courses;
    int choice;
    string filename;
    string courseNumber;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter the filename: ";
            getline(cin, filename);
            loadCourses(courses, filename);
            break;
        case 2:
            printCourseList(courses);
            break;
        case 3:
            cout << "Enter course number: ";
            getline(cin, courseNumber);
            printCourseInformation(courses, courseNumber);
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

void loadCourses(map<string, Course>& courses, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string number, title;
        vector<string> prerequisites;
        string prerequisite;

        getline(iss, number, ',');
        getline(iss, title, ',');

        while (getline(iss, prerequisite, ',')) {
            prerequisites.push_back(prerequisite);
        }

        Course course(number, title, prerequisites);
        courses[number] = course;
    }

    file.close();
    cout << "Courses loaded successfully." << endl;
}

void printCourseList(const map<string, Course>& courses) {
    vector<string> courseNumbers;
    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }
    sort(courseNumbers.begin(), courseNumbers.end());

    for (const string& courseNumber : courseNumbers) {
        cout << courseNumber << ", " << courses.at(courseNumber).title << endl;
    }
}

void printCourseInformation(const map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it == courses.end()) {
        cout << "Course not found." << endl;
        return;
    }

    const Course& course = it->second;
    cout << course.number << ", " << course.title << endl;
    cout << "Prerequisites: ";
    for (const string& prereq : course.prerequisites) {
        cout << prereq << ", ";
    }
    cout << endl;
}

void displayMenu() {
    cout << "Menu:" << endl;
    cout << "  1. Load Data Structure" << endl;
    cout << "  2. Print Course List" << endl;
    cout << "  3. Print Course Information" << endl;
    cout << "  9. Exit" << endl;
    cout << "Enter choice: ";
}
