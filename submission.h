#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

class submission {
public:
    char work[1000];
    char name[30];
    submission() {
        for (int i = 0; i < 1000; i++) {
            work[i] = '\0';
        }
        for (int i = 0; i < 30; i++) {
            name[i] = '\0';
        }
    }


    //DOWNLOADING AND UPLOADING FILE
    bool upload_file(const string& fil, const string& n) {
        ifstream file(fil);
        if (file.is_open()) {
            char data;
            int i = 0;
            while (file.get(data) && i < 1000 - 1) {
                work[i++] = data;
            }
            work[i] = '\0'; 
            cout << "\nFile is uploaded on the classroom";
            file.close();
            this->write(n);
            return true;
        }
        else {
            cout << "\nFile doesn't exist on system";
            return false;
        }
    }

    void upload_text(const string& text, const string& n) {
        strncpy(work, text.c_str(), sizeof(work) - 1);
        work[sizeof(work) - 1] = '\0';
        this->write(n);
    }

    void write(const string& name) {
        ofstream file(name + ".txt");
        if (file.is_open()) {
            file.write(work, sizeof(work));
            cout << "\nData written succesfully";
        }
        file.close();
    }

    void download(const string& name) {
        fstream file(name + ".txt");
        if (file.is_open()) {
            file.read(work, sizeof(work));
        }
    }

    void operator=(int i) {
        memset(work, 0, sizeof(work));
    }

    void operator=(submission& obj) {
        strncpy(work, obj.work, sizeof(work) - 1);
        work[sizeof(work) - 1] = '\0'; 
    }

    void display() {
        string s(work);
        cout << s;
    }
};
