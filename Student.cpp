#include "Student.h"

Student::Student(string n, double g, int a, int asg) {
    name = n;
    gpa = g;
    attendance = a;
    assignments = asg;
}

double Student::predictScore() {
    return (gpa * 25 * 0.4) + (attendance * 0.3) + (assignments * 0.3);
}

char Student::predictGrade() {
    double score = predictScore();

    if (score >= 85)
        return 'A';
    else if (score >= 70)
        return 'B';
    else if (score >= 60)
        return 'C';
    else
        return 'D';
}
