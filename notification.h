#pragma once
#include"Headerfiles.h"
class notification {
private:
	string note;
public:
	notification() {
		note = " ";
	}

	notification(string n):note(n){}


    //PURE VIRTUAL FUNCTIONS
	virtual void print() = 0;
	virtual void writetofile() = 0;
	virtual void readtofile() = 0;
    virtual void getData() = 0;
    virtual void clearfile() = 0;



};


class notify_assignment : public notification {
private:
    string assignmentName;
    string dueDate;
public:
    notify_assignment() : notification() {
        assignmentName = " ";
        dueDate = " ";
    }

    notify_assignment(string name, string date) : notification("Assignment"), assignmentName(name), dueDate(date) {}

    void print() override {
        cout << "Assignment: " << "Assignment" << " 22-09-2023 "  << endl;
    }

    void getData() {

        cout << "Enter your assignment details :" << endl;
        cin >> assignmentName;
        cout << "Enter Due date :" << endl;
        cin >> dueDate;

        cout << "SAVED: " << endl;
    }


    void writetofile() override {
        ofstream outFile("assignment.txt");
        if (outFile.is_open()) {
            outFile << "Assignment: " << assignmentName << " With Due date , "<< dueDate << endl;
            outFile.close();
        }
        else {
            cout << "Error opening file for writing!" << endl;
        }
    }

    void readtofile() override {
        ifstream inFile("assignment.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            inFile.close();
        }
        else {
            cout << "Error opening file for reading!" << endl;
        }
    }

    void clearfile() {
        ofstream outFile("assignment.txt", std::ofstream::out | std::ofstream::trunc);
        if (outFile.is_open()) {
            outFile.close();
            cout << "Assignment data cleared successfully." << endl;
        }
        else {
            cout << "Error clearing assignment data." << endl;
        }
    }

};


class notify_grade : public notification {
private:
    string courseName;
    char grade;
public:
    notify_grade() : notification() {
        courseName = " ";
        grade = ' ';
    }

    notify_grade(string course, char g) : notification("Grade"), courseName(course), grade(g) {}

    void print() override {
        cout << "Course: " << courseName << ", Grade: " << grade << endl;
    }

    void getData()
    {
        cout << "Enter your course details :" << endl;
        cin >> courseName;
        cout << "Enter Grade  :" << endl;
        cin >> grade;

        cout << "SAVED: " << endl;

    }


    void writetofile() override {
        ofstream outFile("grade.txt");
        if (outFile.is_open()) {
            outFile << "Course: " << courseName << ", Grade: " << grade << endl;
            outFile.close();
        }
        else {
            cout << "Error opening file for writing!" << endl;
        }
    }

    void readtofile() override {
        ifstream inFile("grade.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            inFile.close();
        }
        else {
            cout << "Error opening file for reading!" << endl;
        }
    }

    void clearfile() {
        ofstream outFile("grade.txt", std::ofstream::out | std::ofstream::trunc);
        if (outFile.is_open()) {
            outFile.close();
            cout << "Grade data cleared successfully." << endl;
        }
        else {
            cout << "Error clearing grade data." << endl;
        }
    }
};

