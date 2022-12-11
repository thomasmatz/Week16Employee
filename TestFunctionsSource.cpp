/**
Week 16 Final Exam
Tom Matz
12/9/2022
CIS 1202.201
*/

#include <iostream>
#include "Employee_C.h"

#include <string>
#include <limits>
#include <iomanip>

using namespace std;

void Test_Salary_Setting(Employee_C &);
void Test_Methods();
void Display_Class_Members(const Employee_C&);

const int NAME_LENGTH = 61;

void Test_Salary_Setting(Employee_C &xEmploy)
{
	//The parameter is passed by reference, because
	//this function will purposefully change
	//	the salary in the "database".
	Display_Class_Members(xEmploy);

	double newSalary;
	cout << "\nEnter a new salary> ";
	cin >> newSalary;
	xEmploy.Set_Salary(newSalary);
	Display_Class_Members(xEmploy);
}

void Test_Methods()
{
	//This function tests the mutators
	// of the Employee class.  It makes a test array
	// of 5 elements.
	const int TEST_SIZE = 5;

	Employee_C testEmployee[TEST_SIZE];
	int i = 0;
	bool again = true;
	while (again && i<5)
	{
		char enteredName[NAME_LENGTH];
		int enteredID;
		double enteredSalary;
		char enteredSex;
		cout << "\nEnter the following: ";
		cout << "\nfull name> ";
		cin.get(enteredName, NAME_LENGTH);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "\nID:> ";
		cin >> enteredID;
		cout << "\nSalary> ";
		cin >> enteredSalary;
		cout << "\nSex> ";
		cin >> enteredSex;

		testEmployee[i].Set_FullName(enteredName);
		testEmployee[i].Set_IDNumber(enteredID);
		testEmployee[i].Set_Salary(enteredSalary);
		testEmployee[i].Set_Sex(enteredSex);

		Display_Class_Members(testEmployee[i]);

		i++;
		cout << "\nEnter 1 to continue; 0 to quit> ";
		cin >> again;
		cin.ignore();
	}
	//when finished with this test data, reset totalSalaries to 0
	testEmployee[0].Reset_TotalOfAllSalaries();
}