#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include <string>
using namespace std;

class Results {
public:
    string number_of_s;
    vector<string> subjects;
    vector<string> marks;
    float average_result = 0;
};

class student {
public:
    string last_name;
    string name;
    string patronymic;
    string birth_date;
    string arrival_year;
    string faculty;
    string department;
    string group;
    string markbook_num;
    string gender;
    float average_sess_res = 0;
    vector<Results> results;
    friend ostream& operator<<(ostream& os, student &st);
};

#endif // STUDENT_H