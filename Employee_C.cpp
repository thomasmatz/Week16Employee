/**
Tom Matz
12/9/2022
Employee Class implementation file
*/

#define _CRT_SECURE_NO_WARNINGS

#include "Employee_C.h"
#include <cstring>
#include <iostream>

using namespace std;

double Employee_C::totalOfAllSalaries = 0;

Employee_C::Employee_C()
{
	fName_Ptr = nullptr;
	idNumber = 0;
	salary = 0;
	sex = ' ';
	//cout << "\n\nThe constructor has made a new object.";
}
Employee_C::~Employee_C()
{
	delete[] fName_Ptr;
	//cout << "\n\nThe destructor has just run.";
}
void Employee_C::Set_FullName(char xName[])
{
	fName_Ptr = new char[MAX_NAME_SIZE];
	strcpy(fName_Ptr, xName);
}
void Employee_C::Set_IDNumber(int xID)
{
	idNumber = xID;
}
void Employee_C::Set_Salary(double xSal)
{
	//first deduct the current salary from the static variable
	totalOfAllSalaries -= salary;
	salary = xSal;
	totalOfAllSalaries += salary;
}
void Employee_C::Set_Sex(char xSex)
{
	sex = xSex;
}
char* Employee_C::Get_FullName() const
{
	//fName_Ptr = new char[MAX_NAME_SIZE];
	//strcpy(fName_Ptr, fullName);
	return fName_Ptr;
}
int Employee_C::Get_IDNumber() const
{
	return idNumber;
}
double Employee_C::Get_Salary() const
{
	return salary;
}
char Employee_C::Get_Sex() const
{
	return sex;
}
double Employee_C::Get_TotalOfAllSalaries() const
{
	return totalOfAllSalaries;
}
void Employee_C::Reset_TotalOfAllSalaries()
{
	//  This method is needed for testing.
	//	after making a test database, there
	//	needs to be a way to set the total 
	//	back to 0.
	totalOfAllSalaries = 0;
}