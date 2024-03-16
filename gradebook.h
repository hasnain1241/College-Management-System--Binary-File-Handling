#pragma once
#include"Headerfiles.h"

//template declaration
template<class T>
T** dynamic_memory_array(int row, int col)
{
	T** arr = new T * [row];
	for (int i = 0; i < row; i++) {
		arr[i] = new T[col];
	}
	return arr;
}



class gradebook {
private:
	double** marks;
	char* grade;
	int totalstudents, totalassignments;

public:
	gradebook() {
		marks = NULL;
		grade = NULL;
		totalstudents = 0;
		totalassignments = 0;
	}
	gradebook(int totalstudents) :totalstudents(totalstudents) {
		marks = dynamic_memory_array<double>(totalstudents, 0);
		grade = new char[totalstudents];
		totalassignments = 1;
		for (int i = 0; i < totalstudents; i++) {
			grade[i] = 'I';
		}
	}



	bool insertmarks(int marks, int student, int assignment) //inserting marks grades
	{
		if (assignment > this->totalassignments) {
			return false;
		}
		else {
			this->marks[student][assignment - 1] = marks;
			return true;
		}
	}
	void addassignment() //grades assignment
	{
		double** temp = dynamic_memory_array<double>(totalstudents, totalassignments);
		for (int i = 0; i < totalstudents; i++) {
			for (int j = 0; j < totalassignments; j++) {
				temp[i][j] = this->marks[i][j];
			}
		}

		for (int i = 0; i < totalassignments; ++i) {
			delete[] marks[i];
		}
		delete[] marks;

		marks = NULL;



		marks = dynamic_memory_array<double>(totalstudents, totalassignments + 1);
		for (int i = 0; i < totalstudents; i++) {
			for (int j = 0; j < totalassignments; j++) {
				this->marks[i][j] = temp[i][j];
			}
		}
		totalassignments++;
	}

	//removing grades

	void removeassignment(int assignment_number) {
		if (assignment_number > totalassignments) {
			cout << "\nWrong input";
			return;
		}
		double** temp = dynamic_memory_array<double>(totalstudents, totalassignments);
		for (int i = 0; i < totalstudents; i++) {
			for (int j = 0; j < totalassignments; j++) {
				if (j == assignment_number) {
					continue;
				}
				temp[i][j] = this->marks[i][j];
			}
		}

		for (int i = 0; i < totalassignments; ++i) {
			delete[] marks[i];
		}
		delete[] marks;

		marks = NULL;

		marks = dynamic_memory_array<double>(totalstudents, totalassignments - 1);
		int c = 0, r = 0;



		for (int i = 0; i < totalstudents; i++, r++) {
			for (int j = 0; j < totalassignments; j++, c++) {
				if (j == assignment_number) {
					c--;
					continue;
				}
				this->marks[r][c] = temp[i][j];
			}

		}

	}

	//add student grades

	void addstudent() {
		
		double** newArr = new double* [totalstudents+ 1];
		char* Arr = new char[totalstudents + 1];

		for (int i = 0; i < totalstudents; ++i) {
			Arr[i] = grade[i];
			newArr[i] = new double[totalassignments];
			for (int j = 0; j < totalassignments; ++j) {
				newArr[i][j] = marks[i][j];
			}
		}
		Arr[totalstudents] = 'I';

		newArr[totalstudents] = new double[totalassignments];
		for (int j = 0; j < totalassignments; ++j) {
			newArr[totalstudents][j] = 0;
		}

		for (int i = 0; i < totalstudents; ++i) {
			delete[] marks[i];
		}
		delete[] marks;
		delete[] grade;
		marks = newArr;
		grade = Arr;
		totalstudents++;
	}

	//remove student grades


	void removestudent(int num) {
		if (num < 0 || num >= totalstudents) {
			return;
		}
		double** newArr = new double* [totalstudents - 1];
		
		char* Arr = new char[totalstudents - 1];

		for (int i = 0, newRow = 0; i < totalstudents; ++i) {
			if (i != num) {
				Arr[newRow] = grade[i];
				newArr[newRow] = new double[totalassignments];
				for (int j = 0; j < totalassignments; ++j) {
					newArr[newRow][j] = marks[i][j];
				}
				newRow++;
			}
		}
		for (int i = 0; i < totalstudents; ++i) {
			delete[] marks[i];
		}
		delete[] marks;
		delete[] grade;

		marks = newArr;
		grade = Arr;
		
		
		totalstudents--;




	}


	void insertgrade(int student, char grade) {
		if ((student + 1) > totalstudents) {
			cout << "\nWrong input";
			return;
		}
		this->grade[student] = grade;
	}

	void operator=(gradebook& obj) {
		this->totalassignments = obj.totalassignments;
		this->totalstudents = obj.totalstudents;
		this->marks = dynamic_memory_array<double>(totalstudents, totalassignments);
		for (int i = 0; i < totalstudents; i++) {
			for (int j = 0; j < totalassignments; j++) {
				this->marks[i][j] = obj.marks[i][j];
			}
		}
		this->grade = new char[totalstudents];
		for (int i = 0; i < totalstudents; i++) {
			this->grade[i] = obj.grade[i];
		}
	}

	void readFromFile(const char* filename) {
		ifstream file(filename);
		if (!file.is_open()) {
			cout << "Error: File could not be opened.\n";
			return;
		}

		file >> totalstudents >> totalassignments;

		marks = dynamic_memory_array<double>(totalstudents, totalassignments);
		grade = new char[totalstudents];

		for (int i = 0; i < totalstudents; i++) {
			for (int j = 0; j < totalassignments; j++) {
				file >> marks[i][j];
			}
			file >> grade[i];
		}

		file.close();
	}

	void writeToFile(const char* filename) const {
		ofstream file(filename);
		if (!file.is_open()) {
			cout << "Error: File could not be opened for writing.\n";
			return;
		}

		file << totalstudents << " " << totalassignments << "\n";

		for (int i = 0; i < totalstudents; i++) {
			for (int j = 0; j < totalassignments; j++) {
				file << marks[i][j] << " ";
			}
			file << grade[i] << "\n";
		}
		file.close();
	}


	void display() {
		cout << "\nGrade ";
		for (int i = 0; i < totalassignments; i++) {
			cout << " \tAssignment " << i + 1;
		}
		for (int i = 0; i < totalstudents; i++) {
			cout << "\n" <<grade[i] ;
			for (int j = 0; j < totalassignments; j++) {
				cout << " \t" << marks[i][j];
			}
		}
	}
};