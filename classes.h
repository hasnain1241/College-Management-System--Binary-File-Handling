#pragma once

#include"assignment.h"
#include"student.h"
#include"teacher.h"
#include "gradebook.h"


//helper functions

int str_length_return_(char* arr) {
	int size = 0;
	while (arr[size] != '\0') {
		size++;
	}
	++size;
	return size;
}




bool passwordmatcher_(char* arr1, char* arr2) {
	bool flag = true;
	if (str_length_return_(arr1) == str_length_return_(arr2)) {
		flag = true;
	}
	else {
		flag = false;
		return flag;
	}
	for (int i = 0; i < str_length_return_(arr1); i++) {
		if (arr1[i] == arr2[i]) {
			flag = true;
		}
		else {
			flag = false;
			return flag;
		}
	}
	return flag;
}




class classes {
public:
	student s[50];//composition
	assignment assign[5]; //composition
	teacher teach;//composition
	gradebook book;//composition
	char description[100];
	char subject[100];
	
	int total_students, total_assignments;//total students, assignments counter
	int id;

	classes() {
		total_students = 0;
		total_assignments = 0;
		for (int i = 0; i < 100; i++)
		{
			description[i] = '\0';
		}
		for (int i = 0; i < 100; i++)
		{
			subject[i] = '\0';
		}
	}
	classes(int id):id(id) {
		for (int i = 0; i < 50; i++) {
			s[i] = 0;
		}
		total_students = 0;
		total_assignments = 0;
		for (int i = 0; i < 100; i++)
		{
			description[i] = NULL;
		}
		for (int i = 0; i < 100; i++)
		{
			subject[i] = NULL;
		}
	}
	

	//adding students
	void addstudent(student& obj) {
		if (total_students > 49) {
			cout << "\nMaximum students are registered";
			return;
		}
		s[total_students] = obj;
		total_students++;
		cout << "\nStudent registered";
		book.addstudent();
	}

	//deleting students
	void delete_student(char* arr) {
		int index = -1;
		for (int i = 0; i < total_students; i++) {
			if (passwordmatcher_(s[i].getname(), arr)) {
				index = i;
				break;
			}
		}
		if (index != -1) {
			for (int i = index; i < total_students - 1; ++i) {
				s[i] = s[i + 1];
			}	
			total_students--;
			cout << "\nStudent deleted succesfully!";
		}	
		book.removestudent(index);
	}

	//updating assignment
	
	void updateassignment(assignment obj,int index) {
		if (index> 4) {
			cout << "\nYou entered wrong index";
			return;
		}
		assign[index] = obj;
	}
	


	//adding assignment
	void addassignment(assignment obj) {
		if (total_assignments > 4) {
			cout << "\nMaximum assignments are registered";
			return;
		}
		assign[total_assignments] = obj;
		total_assignments++;
		cout << "\nassignment registered\n";
		book.addassignment();
	}


	//removing assignment
	void remove_assignment(int num) {
		int index = num;
		if (index == 0 && total_assignments == 1) {
			assignment obj;
			assign[0] = obj;
			total_assignments--;
		}
		else if (index > -1) {
			for (int i = index; i < total_assignments - 1; ++i) {
				assign[i] = assign[i + 1];
			}
			total_assignments--;
			cout << "\nAssignments deleted succesfully!";
		}
		else{
			cout << "\nWrong input";
		}
		book.removeassignment(num);
	}


	//student index return
	int return_student_index(char* name) {
		for (int i = 0; i < total_students; i++) {
			if (passwordmatcher_(name, s[i].getname())) {
				return i;
			}
		}
		return -1;
	}
	

	//writing in file
	void write_in_file() {
		fstream obj1("classes.bin", ios::out | ios::binary | ios::beg);
		if (obj1.is_open()) {
			obj1.write((char*)&total_students, sizeof(total_students));
			cout << "\nStudents set!" << endl;
			obj1.write((char*)&total_assignments, sizeof(total_students));
			cout << "\nASS set!" << endl;
			obj1.write((char*)&teach, sizeof(teach));
			cout << "\nTeach set!" << endl;
			obj1.write((char*)&id, sizeof(id));
			cout << "\nID set!" << endl;
			obj1.write(description, sizeof(description));
			cout << "\nDescription set!" << endl;
			obj1.write(subject,sizeof(subject));
			cout << "\nSubjects set!" << endl;
			for (int i = 0; i < total_students;i++) {
				obj1.write((char*)&s[i], sizeof(s[i]));
			}
			for (int i = 0; i < total_assignments; i++) {
				obj1.write((char*)&assign[i], sizeof(assign[i]));
			}			
		}
		else {
			cout << "\nError while opening file";
		}
		obj1.close();
	}







	void operator=(classes& obj) {
		total_students = obj.total_students;
		total_assignments = obj.total_assignments;
		for (int i = 0; obj.description[i]!='\0'; i++) {
			this->description[i] = obj.description[i];
		}
		
		for (int i = 0; obj.subject[i]!='\0'; i++) {
			this->subject[i] = obj.subject[i];
		}
		
		teach = obj.teach;	
		id = obj.id;
		this->book = obj.book;
		for (int i = 0; i < obj.total_students; i++) {
			this->s[i] = obj.s[i];
		}
		for (int i = 0; i <obj.total_assignments; i++) {
			this->assign[i] = obj.assign[i];
		}

	}

	void display() {
		cout << "\nClass ID:" << id;
		cout << "\nTotal students: "<<total_students;
		cout << "\nTotal assignments: " << total_assignments;
		cout << "\nClass description: " ;

		for (int i = 0;  this->description[i] != '\0'; i++) {
			cout << description[i];
		}
		cout << "\nSubject: " ;
		for (int i = 0; this->subject[i]!='\0'; i++) {
			cout << subject[i];
		}
	}

};