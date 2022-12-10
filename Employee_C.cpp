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
	fullName[0] = ' ';
	fullName[1] = '\0';
	idNumber = 0;
	salary = 0;
	sex = ' ';
	//cout << "\n\nThe constructor has made a new object.";
}

void Employee_C::Set_FullName(char xName[])
{
	strcpy(fullName, xName);
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

/**the programmer must delete the allocated memory after calling
this function*/
char* Employee_C::Get_FullName() const
{
	char* name_Ptr = new char[MAX_NAME_SIZE];

	strcpy(name_Ptr, fullName);
	return name_Ptr;
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