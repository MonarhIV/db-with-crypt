#include "cryptdecrypt.h"

void Crypt() {
    srand(time(NULL));
    char* pass = new char[64];
    for(int i = 0; i < 64; ++i) {
        switch(rand()%3) {
        case 0:
            pass[i] = rand() % 10 + '0';
            break;
        case 1:
            pass[i] = rand() % 26 + 'A';
            break;
        case 2:
            pass[i] = rand() % 26 + 'a';
        }
    }
    string command ="openssl\\bin\\openssl.exe enc -aes-256-cbc -iter 1000000 -in data.txt -out data.txt.enc -pass pass:";
    command+=pass;
    command.resize(161);
    system(command.c_str());
    if(remove("data.txt")!=0) {
        cout<<"[ERROR] - deleting file"<<endl;
    }

    ofstream file;
    file.open("key.txt", ios::binary);
    file.write(pass,65);
    file.close();

    command = "openssl\\bin\\openssl.exe rsautl -encrypt -inkey rsa.public -pubin -in key.txt -out key.txt.enc";
    system(command.c_str());
    if(remove("key.txt")!=0) {
        cout<<"[ERROR] - deleting file"<<endl;
    }
}

void Decrypt() {
    string command = "openssl\\bin\\openssl.exe rsautl -decrypt -inkey rsa.private -in key.txt.enc -out key.txt";
    system(command.c_str());
    if(remove("key.txt.enc")!=0) {
        cout<<"[ERROR] - deleting file"<<endl;
    }
    char* pass = new char[64];
    ifstream file;
    file.open("key.txt", ios::binary);
    file.read(pass, 65);
    file.close();
    if(remove("key.txt")!=0) {
        cout<<"[ERROR] - 3deleting file"<<endl;
    }
    command="openssl\\bin\\openssl.exe enc -aes-256-cbc -d -iter 1000000 -in data.txt.enc -out data.txt -pass pass:";
    command+=pass;
    command.resize(164);
    system(command.c_str());
    if(remove("data.txt.enc")!=0) {
        cout<<"[ERROR] - deleting file"<<endl;
    }
}