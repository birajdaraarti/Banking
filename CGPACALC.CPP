#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Course {
    string name;
    int credits;
    char grade;
    double gradePoint;
};

// Convert grade to grade point
double getGradePoint(char grade) {
    switch(toupper(grade)) {
        case 'A': return 4.0;
        case 'B': return 3.0;
        case 'C': return 2.0;
        case 'D': return 1.0;
        case 'F': return 0.0;
        default: return -1.0; // invalid grade
    }
}

int main() {
    int numCourses;
    cout << "Enter the number of courses: ";
    cin >> numCourses;

    vector<Course> courses(numCourses);
    double totalGradePoints = 0.0;
    int totalCredits = 0;

    for (int i = 0; i < numCourses; ++i) {
        cout << "\nCourse " << i + 1 << ":\n";
        cout << "Name: ";
        cin >> ws; // eat any leading whitespace
        getline(cin, courses[i].name);

        cout << "Credits: ";
        cin >> courses[i].credits;

        cout << "Grade (A-F): ";
        cin >> courses[i].grade;

        courses[i].gradePoint = getGradePoint(courses[i].grade);
        if (courses[i].gradePoint == -1.0) {
            cout << "Invalid grade entered. Please use A-F.\n";
            --i;
            continue;
        }

        totalGradePoints += courses[i].gradePoint * courses[i].credits;
        totalCredits += courses[i].credits;
    }

    double cgpa = totalGradePoints / totalCredits;

    // Output results
    cout << fixed << setprecision(2);
    cout << "\nIndividual Course Results:\n";
    for (const auto& course : courses) {
        cout << "Course: " << course.name
             << ", Grade: " << course.grade
             << ", Grade Point: " << course.gradePoint << "\n";
    }

    cout << "\nTotal Credits: " << totalCredits << endl;
    cout << "Total Grade Points: " << totalGradePoints << endl;
    cout << "CGPA: " << cgpa << endl;

    return 0;
}
