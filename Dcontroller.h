#ifndef DCONTROLLER_H
#define DCONTROLLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "student.h"

using namespace std;


class Dcontroller{
    vector<student> data;
    void Update();
    bool FreeId(string id);
    student& GetStudent(string id);
    void CalculateAll();
    void CalculateAllTotal();
    float GetSessionAverage(string id, string num);
    float GetMultipleSessionAverage(string id, vector<string> num);
public:
    void LoadFile();
    void Show();
    void Add();
    void Edit();
    void Delete();
    void AddRes();
    void EditRes();
    void FindBestWorst();
    friend  ostream& operator<<(ostream& os, Dcontroller& src);
};

#endif // DCONTROLLER_H