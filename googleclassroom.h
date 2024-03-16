#pragma once
#include"Headerfiles.h"
#include"notification.h"
#include"classes.h"
#include<time.h>

using namespace std;


//HELPER FUNCTIONS

bool isFileEmpty(const std::string& filename) {
	std::ifstream file(filename);
	return file.peek() == std::ifstream::traits_type::eof();
}



bool checkcnic(char* arr) {
	int k = 0;
	bool flag = true;
	while (arr[k] != '\0') {
		k++;
	}
	//k++;
	if (k < 13)//NCIC HAS TO 13 NUM LETTERS
	{
		flag = false;
	}

	for (int i = 0; i < 13; i++) {
		if (arr[i] >= '0' && arr[i] <= '9') {
			flag = true;
		}
		else {
			flag = false;
		}
	}
	return flag;
}

bool checkpassword(char* arr) {
	bool flag = false;
	bool flag1 = false;
	int k = 0;
	while (arr[k] != '\0') {
		k++;
	}
	//k++;
	if (k < 4) {
		return false;
	}
	for (int i = 0; i < k; i++) {
		if (arr[i] >= 'A' && arr[i] <= 'Z') {
			flag = true;
		}
		if (arr[i] >= '0' && arr[i] <= '9') {
			flag1 = true;
		}
	}
	if (flag && flag1) {
		return true;
	}
	else {
		return false;
	}

}

bool checkname(char* arr) {
	bool flag = false;
	for (int i = 0; i < 50; i++) {
		if (arr[i] == '\0') {
			return flag;
		}
		else if (arr[i] >= '0' && arr[i] <= '9') {
			flag = false;
			return flag;
		}
		else if (arr[i] >= 'A' && arr[i] <= 'Z') {
			flag = true;
		}
		else if (arr[i] >= 'a' && arr[i] <= 'z') {
			flag = true;
		}
	}
	return flag;
}

int str_length_return(char* arr) {
	int size = 0;
	while (arr[size] != '\0') {
		size++;
	}
	++size;
	return size;
}

bool passwordmatcher(char* arr1, char* arr2) {
	bool flag = true;
	if (str_length_return(arr1) == str_length_return(arr2)) {
		flag = true;
	}
	else {
		flag = false;
		return flag;
	}
	for (int i = 0; i < str_length_return(arr1); i++) {
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




//MAIN UI CLASS

class googleclassroom {
public:
	teacher tea;
	student stud;
	classes* first;
	int total;

	//DEFAULT CONSTRUCTOR

	googleclassroom() {
		total = 0;
	}
	


	//ADDING DELETING CLASSES

	void add_classes(classes& obj) {
		if (total == 0) {
			first = new classes;
			*first = obj;
			total++;
			return;
		}
		else {
			total++;
			classes* temp = new classes[total];

			for (int i = 0; i < total-1; i++) {
				temp[i] = first[i];
			}
			temp[total - 1] = obj;
			first = temp;

		}
		cout << "\nClass Added succesfully!";
	}

	void delete_class(int id) {
		int index=-1;
		for (int i = 0; i < total; i++) {
			if (first[i].id == id) {
				index = i;
				break;
			}
		}
		if (index != -1) {
			for (int i = index; i < total- 1; ++i) {
				first[i] = first[i + 1];
			}
			--total;
			classes* temp = new classes[total];
			for (int i = 0; i < total; ++i) {
				temp[i] = first[i];
			}
			first = temp;
			cout << "\nClass deleted succesfully!";
		}
		if (this->total == 0) {
			fstream outfile("classes.bin", ios::out | ios::trunc);
			outfile.close();
		}
	}




	//REGISTER, LOGIN, MENU

	void registeration_teacher();
	void registeration_student();
	void teacher_login();
	void student_login();
	void teacher_menu();
	void student_menu();
	void menu();

	//RETURNING CLASS INDEX
	int return_class_index(int id) {
		for (int i = 0; i < total; i++) {
			if (first[i].id == id) {
				return i;
			}
		}
		return -1;
	}

	//void menu();


	//WRITING IN CLASSES
	void write_classes() {
		for (int i = 0; i < total; i++) {
			first[i].write_in_file();
		}
	}
	void operator=(googleclassroom& obj) {
		this->tea = obj.tea;
		this->stud = obj.stud;
		this->total = obj.total;
		for (int i = 0; i < this->total; i++) {
			this->add_classes(obj.first[i]);
		}
	}
};


//MENU

void googleclassroom::menu() {
	int opt;
	cout << "\t\t\t\t------------------------" << endl;
	cout << "\t\t\t\t   Welcome to Our" << endl;
	cout << "\t\t\t\t   Classroom System" << endl;
	cout << "\t\t\t\t------------------------" << endl;
	cout << "\t\t\t\tChoose an option:" << endl;
	cout << "\t\t\t\t1 - Register as a Student" << endl;
	cout << "\t\t\t\t2 - Register as a Teacher" << endl;
	cout << "\t\t\t\t3 - Login as a Teacher" << endl;
	cout << "\t\t\t\t4 - Login as a Student" << endl;
	cout << "\t\t\t\t------------------------" << endl;
	cout << "\t\t\t\tENTER: ";
	cin >> opt;
	switch (opt) {
	case 1:
		this->registeration_student();
		break;
	case 2:
		this->registeration_teacher();
		break;
	case 3:
		this->teacher_login();
		break;
	case 4:
		this->student_login();
		break;
	default:
		cout << "\nWrong input,try again!";
		this->menu();
	}
}


//STUDENT REGISTRATION

void googleclassroom::registeration_student() {
	system("cls");
	char arr[100];
	int num;
	bool flag = true;


	char arr1[16];
	string s;

	do {
		cin.ignore();
		cout << "\n\t\t\t\tEnter the name of the Student Please: ";
		cin.get(arr, 50);
		
		flag = checkname(arr);
		if (!flag) {
			cout << "\nWrong credentials";
			cout << "\nIt should not have special characters or numbers!";
		}
	} while (!flag);
	flag = true;
	
	stud.setname(arr);
	do {
		cin.ignore();
		cout << "\n\t\t\t\tEnter your CNIC: ";
		cin.get(arr, 14);
		flag = checkcnic(arr);
		if (!flag) {
			cout << "\nWrong credentials try again!";
			continue;
		}

	} while (!flag);
	stud.setCNIC(arr);
	
	flag = true;


	bool flag1 = false;
	do {
		cin.ignore();
		cout << "\n\t\t\t\tEnter your password: ";
		cin.get(arr, 16);
		flag = checkpassword(arr);
		if (!flag) {
			cout << "\nIt should have atleast one upper case and One numeric letter";
			continue;
		}
		cin.ignore();
		cout << "\n\t\t\t\tEnter your password again: ";
		cin.get(arr1, 16);
		flag1 = passwordmatcher(arr, arr1);
		if (!flag1) {
			cout << "\nPasswords don't match!";
			cout << "\nTry again!";
		}
	} while (!flag && !flag1);
	
	stud.setpassword(arr);
	cin.ignore();
	cout << "\n\t\t\t\tEnter your gender: ";
	cin.get(arr, 15);
	
	stud.setgender(arr);
	cin.ignore();
	cout << "\n\t\t\t\tEnter your address: ";
	cin.get(arr, 100);
	stud.setaddress(arr);
	int ids[5];
	cout << "\n\t\tEnter the subject codes you want to be enrolled in(codes start from 1-10 and there are 5 subjects for each student): ";
	for (int i = 0; i < 5; i++) {
		cin >> ids[i];
	}
	stud.setcla(ids);
	string s1(stud.getname());
	stud.id = s1;
	


	fstream obj1("student.bin", ios::out | ios::app | ios::binary);
	if (obj1.is_open()) {
		obj1.write((char*)&stud, sizeof(stud));
		cout << "\nYou are succesfuly registered";
	}
	else {
		cout << "\nError while opening file";
	}
	obj1.close();
	system("cls");
	this->menu();
}

//TEACHER REGISTRATION

void googleclassroom::registeration_teacher() {
	system("cls");
	char arr[100];
	int num=0;
	bool flag = true;


	char arr1[16];
	string s;

	do {
		cin.ignore();
		cout << "\n\t\t\t\tEnter your name: ";

		cin.get(arr, 50);
		flag = checkname(arr);
		if (!flag) {
			cout << "\n\t\t\t\tWrong credentials";
			cout << "\n\t\t\tIt should not have special characters or numbers!";
		}
	} while (!flag);
	flag = true;

	tea.setname(arr);
	do {
		cin.ignore();
		cout << "\n\t\t\t\tEnter your CNIC: ";
		cin.get(arr, 14);
		flag = checkcnic(arr);
		if (!flag) {
			cout << "\n\t\t\t\tWrong credentials try again!";
			continue;
		}

	} while (!flag);
	tea.setCNIC(arr);
	cin.ignore();
	flag = true;


	bool flag1 = false;
	do {
		cin.ignore();
		cout << "\n\t\t\t\tEnter your password: ";
		cin.get(arr, 16);
		flag = checkpassword(arr);
		if (!flag) {
			cout << "\n\t\t\t\tIt should have atleast one upper case and One numeric letter";
			continue;
		}
		cin.ignore();
		cout << "\nEnter your password again: ";
		cin.get(arr1, 16);
		flag1 = passwordmatcher(arr, arr1);
		if (!flag1) {
			cout << "\n\t\t\t\tPasswords don't match!";
			cout << "\n\t\t\t\tTry again!";
		}
	} while (!flag && !flag1);

	tea.setpassword(arr);
	cin.ignore();
	cout << "\n\t\t\t\tEnter your subject: ";
	cin.get(arr, 100);
	tea.setsubject(arr);

	char* temp;
	temp = stud.getcnic();
	temp += 9;
	string s1(tea.getname());
	tea.id = s1 ;


	fstream obj1("teacher.bin", ios::out | ios::app | ios::binary);
	if (obj1.is_open()) {
		obj1.write((char*)&tea, sizeof(tea));
		cout << "\n\t\t\t\tYou are succesfuly registered";
	}
	else {
		cout << "\n\t\t\t\tError while opening file";
	}
	obj1.close();
	system("cls");
	this->menu();
}


//TEACHER LOGIN
void googleclassroom::teacher_login() {
	system("cls");
	char name[50];
	char password[16];
	bool flag1;
	cin.ignore();
	cout << "\n\t\t\t\tEnter your name: ";
	cin.get(name, 50);
	cin.ignore();
	cout << "\n\t\t\t\tEnter your password: ";
	cin.get(password, 16);
	
	bool f1 = true;
	bool f2 = true;
	fstream object("teacher.bin", ios::in | ios::beg | ios::binary);
	if (object.is_open()) {
		while (object.read((char*)&tea, sizeof(tea))) {
			f1 = passwordmatcher(name, tea.getname());
			f2 = passwordmatcher(password, tea.getpassword());
			if (f1 && f2) {
				cout << "\n\t\t\t\t\tSuccesfully login!";
			}
		}
	}
	object.close();
	if (f1 == false || f2 == false) {
		int num = 0;
		cout << "\n\t\t\t\t\tLogin failed!";
		cout << "\n\t\t\t\t\tDo you want to try again? (1/0)";
		cin >> num;
		if (num == 1) {
			teacher_login();
		}
		else if (num == 0) {
			
			exit(0);
		}

	}
	classes temp;
	fstream file("classes.bin", ios::in | ios::out | ios::binary);
	int count = 0;
	if (file.is_open()) {
		while (file.read((char*)&temp.total_students, sizeof(temp.total_students)) &&
			file.read((char*)&temp.total_assignments, sizeof(temp.total_assignments)) &&
			file.read((char*)&temp.teach, sizeof(temp.teach)) &&
			file.read((char*)&temp.id, sizeof(temp.id)) &&
			file.read(temp.description, sizeof(temp.description)) &&
			file.read(temp.subject, sizeof(temp.subject))) {
			for (int i = 0; i < temp.total_students; i++) {
				file.read((char*)&temp.s[i], sizeof(temp.s[i]));
			}
			for (int i = 0; i < temp.total_assignments; i++) {
				file.read((char*)&temp.assign[i], sizeof(temp.assign[i]));
			}
			if (temp.teach == tea) {
				this->add_classes(temp);
			}
		}
	}
	else {
		cout << "\nError in opening file";
	}



	this->teacher_menu();


}

//STUDENT LOGIN

void googleclassroom::student_login() {

	system("cls");
	char name[50];
	char password[16];
	bool flag1 = false;
	cin.ignore();
	cout << "\n\t\t\t\tEnter your name: ";
	cin.get(name, 50);
	cin.ignore();
	cout << "\n\t\t\t\tEnter your password: ";
	cin.get(password, 16);
	
	bool f1 = true;
	bool f2 = true;
	fstream object("student.bin", ios::in | ios::beg | ios::binary);
	if (object.is_open()) {
		while (object.read((char*)&stud, sizeof(stud))) {
			f1 = passwordmatcher(name, stud.getname());
			f2 = passwordmatcher(password, stud.getpassword());
			if (f1 && f2) {
				cout << "\n\t\t\t\tSuccesfully login!";
				this->student_menu();
			}
		}
	}
	object.close();
	if (f1 == false || f2 == false) {
		int num = 0;
		cout << "\n\t\t\t\tLogin failed!";
		cout << "\n\t\t\t\tDo you want to try again? (1/0)";//ASKING FOR UR CHOICE
		cin >> num;
		if (num == 1) {
			student_login();
		}
		else if (num == 0) {
			exit(0);
		}

	}
	
	
	classes temp;
	fstream file("classes.bin", ios::in | ios::out | ios::binary | ios::beg);
	int count = 0;
	bool ch = true;

	if (file.is_open()) {
		file.seekg(0, ios::beg); 

		while (file.read((char*)&temp.total_students, sizeof(temp.total_students)) &&
			file.read((char*)&temp.total_assignments, sizeof(temp.total_assignments)) &&
			file.read((char*)&temp.teach, sizeof(temp.teach)) &&
			file.read((char*)&temp.id, sizeof(temp.id)) &&
			file.read((char*)&temp.description, sizeof(temp.description)) &&
			file.read((char*)&temp.subject, sizeof(temp.subject))) {

			for (int i = 0; i < temp.total_students; i++) {
				file.read((char*)&temp.s[i], sizeof(temp.s[i]));
				if (temp.s[i]== stud)  {					
					this->add_classes(temp);
				}
			}
			for (int i = 0; i < temp.total_assignments; i++) {
				file.read((char*)&temp.assign[i], sizeof(temp.assign[i]));
				this->first[count].updateassignment(temp.assign[i], i);
			}
			count++;
		}
		cout << "\n\t\t\t\tClass exists!" << endl;
	}
	else {
		cout << "\n\t\t\t\tError in opening file";
	}

	file.close();


	//this->student_menu();

}

//TEACHER MENU

void googleclassroom::teacher_menu() {
	system("cls");
	
	int opt;
	int id;
	char arr[20];
	classes cs;
	student tem;
	bool check;
	cout << "\n\t\t\t  Teachers Menu:";
	cout << "\n\t\t\t  -------------------------";
	cout << "\n\t\t\t  1. View enrolled classes";
	cout << "\n\t\t\t  2. Create class";
	cout << "\n\t\t\t  3. Delete class";
	cout << "\n\t\t\t  4. Create assignment";
	cout << "\n\t\t\t  5. Delete assignment";
	cout << "\n\t\t\t  6. Enter assignment marks";
	cout << "\n\t\t\t  7. Mark grades";
	cout << "\n\t\t\t  8. Add students";
	cout << "\n\t\t\t  9. Remove students";
	cout << "\n\t\t\t  10. Download submissions";
	cout << "\n\t\t\t  12. Notify Assignment";
	cout << "\n\t\t\t  13. Notify Grades";
	cout << "\n\t\t\t  14. Clear Grades Notification";
	cout << "\n\t\t\t  15. Clear Assignment Notification";
	cout << "\n\t\t\t  16. Update Assignment or Grade Notification";
	cout << "\n\t\t\t  11. Logout";
	cout << "\n\t\t\t  -------------------------";
	cout << "\n\t\t\t  Option: ";
	cin >> opt;
	if (opt == 1) {
		cout << "\nEnrolled classes are: ";
		for (int i = 0; i < total; i++) {
			first[i].display();
		}
	}
	else if (opt == 2) {
		string str;
		classes obj;
		cout << "\n\t\t\t\tEnter class ID: ";
		cin >> id;
		obj.id = id;
		cin.ignore();
		cout << "\n\t\t\t\tEnter class description: ";
		cin.get(obj.description, 99);
		cin.ignore();
		cout << "\n\t\t\t\tEnter subject: ";
		cin.get(obj.subject, 99);
		this->add_classes(obj);
		for (int i = 0; i < total; i++) {
			first[i].teach = tea;
		}
	
		
	}
	else if (opt == 3) {
		cout << "\n\t\t\t\tEnter class ID: ";
		cin >> id;
		this->delete_class(id);
		for (int i = 0; i < total; i++) {
			first[i].teach = tea;
		}
	}
	else if (opt == 4) {
		if (total == 0) {
			cout << "\nYou cannot make an assignment because you're not enrolled in a class";
			Sleep(3000);
			this->teacher_menu();
		}
		string dead;
		assignment ass;
		int mar;
		cout << "\n\t\t\t\tEnter class ID: ";
		cin >> id;
	
		bool flag = true;
		cin.ignore();
		cout << "\nEnter title: ";
		cin.get(ass.title, 50);
		cin.ignore();
		cout << "\nEnter Description: ";
		cin.get(ass.description, 50);

		cout << "\nEnter total marks:";
		cin >> mar;
		ass.marks = mar;
		do{
			cin.ignore();
			cout << "\nEnter assignment deadline (YYYY-MM-DD HH:MM): ";
			cin >> dead;
			tm tm = {};
			istringstream ss(dead);
			ss >> get_time(&tm, "%Y-%m-%d %H:%M");
			if (ss.fail()) {
				cout << "\nError passing the deadline string ." << endl;
				cout << "\nTry again";
				continue;
			}
			
			
			ass.tim = mktime(&tm);
			if (ass.time_check()) {
				cout << "\nWrong time entered, you have entered a previous date\nTry again!";
				continue;
			}
			flag = false;
		} while (flag);
		flag = true;
		do {
			cout << "\n\t\t\t\tEnter the index of class: i.e. (0-4) ";
			cin >> id;
			if (id > total) {
				cout << "\n\t\t\t\tEntered wrong credentials";
				continue;
			}
			first[id].addassignment(ass);
			flag = false;
		} while (flag);
	}
	else if (opt == 5) {
		
		bool flag = true;
		do {
			cout << "\n\t\t\t\tEnter the index of class: ";
			cin >> id;
			if (id > total) {
				cout << "\n\t\t\t\tEntered wrong credentials";
				continue;
			}
			cout << "\n\t\t\t\tEnter assignment number: ";
			cin >> opt;
			--opt;
			if (first[id].total_assignments <= 0) {
				cout << "\nInsufficent assignments";
				Sleep(5000);//SLEEP FOR 5s
				this->teacher_menu();
			}
			first[id].remove_assignment(opt);
			flag = false;
		} while (flag);
	
	}
	else if (opt == 6) {
		
		
		bool flag = true;
		do {
			cout << "\n\t\t\t\tEnter the index of class: ";
			cin >> id;
			if (id > total) {
				cout << "\n\t\t\t\tEntered wrong credentials";
				continue;
			}
			cin.ignore();
			cout << "\n\t\t\t\tEnter student name: ";
			cin.get(arr, 20);
			opt = first[id].return_student_index(arr);
			int marks,  assig;
			cout << "\n\t\t\t\tEnter the marks: ";
			cin >> marks;
			cout << "\n\t\t\t\tEnter assignment number: ";
			cin >> assig;
			if (!first[id].book.insertmarks(marks, opt, assig)) {
				cout << "\n\t\t\t\tAssignment's are insufficent add  more assignments";
			}
			flag = false;
		} while (flag);		
	}
	else if (opt == 7) {
		bool flag = true;
		char ch;
		do {
			cout << "\nEnter the index of class: ";
			cin >> id;
			if (id > total) {
				cout << "\nEntered wrong credentials";
				continue;
			}
			cin.ignore();
			cout << "\nEnter student name: ";
			cin.get(arr, 20);
			opt = first[id].return_student_index(arr);
			cout << "\nEnter grade: ";
			cin >> ch;
			first[id].book.insertgrade(opt, ch);
			flag = false;
		} while (flag);
	}
	else if (opt == 8) {
		if (total == 0) {
			cout << "\nNo class is created";
			Sleep(5000);
			teacher_menu();
		}
		cout << "\nEnter the class id: ";
		int king = 0;
		cin >> opt;
		cin.ignore();
		cout << "\nEnter the students name: ";
		cin.get(arr, 20);
		check = true;
		fstream input("student.bin",ios::in| ios::out | ios::binary|ios::beg);
		while (input.read((char*)&tem, sizeof(tem))) {
			cout << "\nStudent file read successfully!" << endl;
			if (passwordmatcher(arr, tem.getname())) {
				cout << "\nStudent matches with the file name!" << endl;
				for (int i = 0; i < 5 &&check ; i++) {
					if (tem.cla[i] == opt) {
						first[this->return_class_index(opt)].addstudent(tem);
						check = false;
					}
					
				}
			}
			if (!check) {
				break;
			}	
		}



		input.close();
	}
	else if (opt == 9) {
		cout << "\nEnter the class id: ";
		cin >> opt;
		cin.ignore();
		cout << "\nEnter the students name: ";
		cin.get(arr, 20);
		check = true;
		fstream input("student.bin", ios::in | ios::out | ios::binary | ios::beg);
		while (input.read((char*)&tem, sizeof(tem))) {
			if (passwordmatcher(arr, tem.getname())) {
				for (int i = 0; i < 5 && check; i++) {
					if (tem.cla[i] == opt) {
						first[this->return_class_index(opt)].delete_student(tem.getname());
						tem.cla[i] = 0;
						check = false;
					}
				}
			}
			if (!check) {
				break;
			}
		}
	
	}
	else if (opt == 10) {
		cout << "\nEnter the class ID: ";
		cin >> opt;
		cin.ignore();
		cout << "\nEnter the students name: ";
		cin.get(arr, 20);
		cout << "\nFollowing is the work submitted:\n";
		first[opt].s[first[opt].return_student_index(arr)].sub.download(arr);
		first[opt].s[first[opt].return_student_index(arr)].sub.display();

	}
	else if (opt == 11) {
		
		this->write_classes();
		first = NULL;
		total = 0;
		this->menu();
	}

	else if (opt == 12)
	{
		notify_assignment n1;
		n1.getData();
		n1.writetofile();
	}

	else if (opt == 13)
	{
		notify_grade n2;
		n2.getData();
		n2.writetofile();
	}

	else if (opt == 14)

		{
			notify_grade n3;
			n3.clearfile();
		}

	else if (opt == 15)

		{
		notify_assignment n4;
		n4.clearfile();
		}

	else if (opt == 16)
	{
		int hasso;
		cout << "Press one for assignment notification updation and 2 for grade notification\n";
		cin >> hasso;

		if (hasso == 1)
		{
			notify_assignment n1;
			n1.clearfile();
			n1.getData();
			n1.writetofile();
		}

		else {
			notify_grade n2;
			n2.clearfile();
			n2.getData();
			n2.writetofile();

		}


		}





	cout << "\nPress 1 for teachers menu, 2 for menu and press any other key to exit:\n ";
	cin >> opt;
	if (opt == 1) {
		system("cls");
		teacher_menu();
	}
	else if (opt == 2)
	{
		system("cls");
		menu();
	}

	else {
		
		this->write_classes();
		first = NULL;
		total = 0;
		exit(0);
	}
}


//student menu

void googleclassroom::student_menu() {
	system("cls");
	int opt;
	string nam;
	cout << "\t\t\t\t------------------------" << endl;
	cout << "\t\t\t\t    Student Menu" << endl;
	cout << "\t\t\t\t------------------------" << endl;
	cout << "\t\t\t\t1 - View enrolled classes" << endl;
	cout << "\t\t\t\t2 - View assignments" << endl;
	cout << "\t\t\t\t3 - Submit assignment" << endl;
	cout << "\t\t\t\t4 - View grade book" << endl;
	cout << "\t\t\t\t6 - Get Assignment Notifications" << endl;
	cout << "\t\t\t\t7 - Get Grade Notifications" << endl;
	cout << "\t\t\t\t5 - Logout" << endl;
	cout << "\t\t\t\t------------------------" << endl;
	cout << "\t\t\t\tEnter: ";
	cin >> opt;
	if (opt == 1) {
		cout << "\nEnrolled classes are: ";
		for (int i = 0; i < total; i++) {
			first[i].display();
		}
	}
	else if (opt == 2) {
		int nu = 0;
		bool flag = true;
		do {
			cout << "\nEnter the subject index:\n ";
			cin >> opt;
			if (first[opt].total_assignments == 0) {
				cout << "\nNo assignment has been uploaded";
				break;
			}
			if (opt > total) {
				cout << "\nWrong credentials try again(subject value increases the total): ";
				continue;
			}
			
			cout << "\nEnter the assignment number\n: ";
			cin >> nu;
			if (first[opt].total_assignments < opt) {
				cout << "\nWrong credentials try again(assignment value increases the total): ";
				continue;
			}
			flag = false;
		} while (flag);
		first[opt].assign[nu].display();
	}
	else if (opt == 3) {
		
		cout << "\nHow do you want to upload";
		cout << "\n1-text file\n2-text\n";
		cin >> opt;

		if (opt == 1) {
			cin.ignore();
			cout << "\nEnter the name of the file:";
			getline(cin, nam);
			stud.sub.upload_file(nam,this->stud.getname());			
		}
		else if (opt == 2) {
			cin.ignore();
			cout << "\nEnter the text:";
			getline(cin, nam);
			stud.sub.upload_text(nam, this->stud.getname());
		}
	}
	else if (opt == 4) {
		cout << "\nEnter the class index i.e. (0,1,2,3): ";
		cin >> opt;
		
		first[opt].book.readFromFile(first[opt].subject);
		
		//if (isFileEmpty(first[opt].subject)) {
		//	std::cout <<"No records found \n" ;
		//}
		//else {
		//	first[opt].book.display();
		//	//std::cout << "The file is not empty.\n";
		//}

		first[opt].book.display();

		//int r=first[opt].book.display();
	}
	else if (opt == 5) {

		this->write_classes();
		first = NULL;
		total = 0;
		this->menu();
	}

	else if (opt == 6)
	{
		notify_assignment n1;
		n1.readtofile();

	}

	else if (opt == 7)
	{
		notify_grade n2;
		n2.readtofile();
	}


	cout << "\nPress 1 for student menu, 2 for menu and press any other key to exit : \n";
	cin >> opt;
	if (opt == 1) {
		system("cls");
		this->student_menu();
	}
	
	else if (opt == 2)
	{
		system("cls");
		menu();
	}

	else {
		this->write_classes();
		first = NULL;
		total = 0;
		exit(0);
	}
}

