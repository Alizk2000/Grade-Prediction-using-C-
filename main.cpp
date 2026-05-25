#include "Student.h"
#include <vector>

int main() {
    vector<Student> students;

    students.push_back(Student("Ali", 3.5, 90, 85));
    students.push_back(Student("Sara", 2.8, 75, 70));

    for (auto s : students) {
        cout << "Name: " << s.name << endl;
        cout << "Predicted Score: " << s.predictScore() << endl;
        cout << "Predicted Grade: " << s.predictGrade() << endl;
        cout << endl;
    }

    return 0;
}
