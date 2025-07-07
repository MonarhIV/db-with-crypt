#include <iostream>
using namespace std;
#include "Dcontroller.h"
#include "cryptdecrypt.h"

int main()
{
    system("chcp 65001>nul");
    Decrypt();
    Dcontroller controller;
    controller.LoadFile();
    char peek;
    while(peek!='z')
    {
        cout<<"a) Вывести всех студентов и их сессии"<<endl;
        cout<<"b) Вывести всех студентов"<<endl;
        cout<<"c) Добавить студента"<<endl;
        cout<<"d) Редактировать стдента"<<endl;
        cout<<"e) Удалить студента"<<endl;
        cout<<"f) Добавить сессию студенту"<<endl;
        cout<<"g) Изменить результаты сессии студента"<<endl;
        cout<<"h) Выполнить задание по варианту 87"<<endl;
        cout<<"z) Выход из программы"<<endl;
        cin>>peek;
        switch(peek) {
            case 'a':
                cout<<controller<<endl;
                break;
            case 'b':
                controller.Show();
                break;
            case 'c':
                controller.Add();
                break;
            case 'd':
                controller.Show();
                controller.Edit();
                break;
            case 'e':
                controller.Show();
                controller.Delete();
                break;
            case 'f':
                controller.Show();
                controller.AddRes();
                break;
            case 'g':
                controller.Show();
                controller.EditRes();
                break;
            case 'h':
                controller.Show();
                controller.FindBestWorst();
                break;
            case 'z':
                cout<<"Выход"<<endl;
                Crypt();
                return 1;
            default:
                cout<<"Неверный ввод"<<endl;
        }
    }
    Crypt();
    return 0;
}
