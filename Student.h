#ifndef STUDENT
#define STUDENT

#include <string>
#include <iostream>
using namespace std;

class Student{
private:
	/* STUDENT ATTRIBUTES */


public:
	/* CONSTRUCTORS */
	string mNumber;
	string firstName;
	string lastName;

	Student(){
		mNumber = "00000000";
		firstName  = "";
		lastName = "";
	}
	Student(string mNumber){
		this->mNumber = mNumber;
		firstName = "";
		lastName = "";
	}
	Student(string mNumber, string firstName, string lastName){
		this->mNumber = mNumber;
		this->firstName = firstName;
		this->lastName = lastName;
	}

	/* STUDENTS GETTER AND SETTER METHODS */
	string getFirstName(){ return firstName; }
	string getLastName(){ return lastName; }
	string getMNumber(){ return mNumber; }
	void setFirstName(string name){ this->firstName = name; }
	void setLastName(string name){ this->lastName = name; }
	void setMNumber(string mNumber){ this->mNumber = mNumber; }

	bool lessFirst(const Student& s){
		return stoi(this->firstName) < stoi(s.firstName);
	}
	bool lessLast(const Student& s){
		return stoi(this->lastName) < stoi(s.lastName);
	}
	bool greaterFirst(Student s){
		return stoi(this->firstName) > stoi(s.firstName);
	}
	bool greaterLast(const Student& s){
		return stoi(this->lastName) > stoi(s.lastName);
	}

	/* STUDENT OVERLOADS */
	bool operator<(const Student& s){
		return stoi(this->mNumber) < stoi(s.mNumber);
	}
	bool operator>(const Student& s){
		return stoi(this->mNumber) > stoi(s.mNumber);
	}
	bool operator==(const Student& s){
		return stoi(this->mNumber) == stoi(s.mNumber);
	}
	bool operator!=(const Student& s){
		return stoi(this->mNumber) != stoi(s.mNumber);
	}
	friend ostream& operator<<(ostream& os, const Student& s){
		os << s.mNumber;
		return os;
	}
	operator string&() {
    	return this->mNumber;
  }
};

#endif