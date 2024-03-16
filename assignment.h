#pragma once
#include<time.h>

class assignment {
private:
	
public:
	char attached[50], title[50], description[50];
	double marks;
	time_t tim;

	//Default Constructor 

	assignment() { 
		for (int i = 0; i < 50; i++) {
			attached[i] = '\0';
			title[i] = '\0';
			description[i] = '\0';
		}
		marks = 0;
		tim = NULL;
	}

	//Parametrized constructor
	assignment(string title, string description, double marks)  {
		tim = NULL;
		strcpy(this->title, title.c_str());
		strcpy(this->description, description.c_str());


		this->marks = marks;
	}



	//To check the deadline

	bool time_check() {
		time_t t = time(nullptr);
		if (t > tim) {
			return true;
		}
		else {
			return false;
		}

	}

	void display() {
		cout << "\nTitle: ";
		for (int i = 0; i < title[i] != '\0'; i++) {
			cout << title[i];
		}
		cout << "\nDescription: " ;
		for (int i = 0; i < description[i] != '\0'; i++) {
			cout << description[i];
		}
		cout << "\nTotal marks: " << marks;
	}

	void operator=(assignment& obj) {
		for (int i = 0;  obj.attached[i] != '\0'; i++) {
			this->attached[i] = obj.attached[i];
		}
		for (int i = 0; obj.description[i] != '\0'; i++) {
			this->description[i] = obj.description[i];
		}
		for (int i = 0; obj.title[i] != '\0'; i++) {
			this->title[i] = obj.title[i];
		}
		this->marks = obj.marks;
		tim = obj.tim;
	}

};

