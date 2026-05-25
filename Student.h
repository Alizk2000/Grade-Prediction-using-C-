#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
using namespace std;

class Student {
public:
    string name;
    double gpa;
    int attendance;
    int assignments;

    Student(string n, double g, int a, int asg);

    double predictScore();
    char predictGrade();
};

#endif
