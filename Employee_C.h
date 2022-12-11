//#pragma once
/**
Tom Matz
12/9/2022
Employee Class header file
*/

#ifndef Employee_C_H
#define Employee_C_H

class Employee_C
{
public:
	Employee_C();
	~Employee_C();
	void Set_FullName(char[]);
	void Set_IDNumber(int);
	void Set_Salary(double);
	void Set_Sex(char);
	char* Get_FullName() const;
	int Get_IDNumber() const;
	double Get_Salary() const;
	char Get_Sex() const;
	double Get_TotalOfAllSalaries() const;
	void Reset_TotalOfAllSalaries();
private:
	static const int MAX_NAME_SIZE = 61;
	//char fullName[MAX_NAME_SIZE];
	char* fName_Ptr;
	int idNumber;
	double salary;
	char sex;
	static double totalOfAllSalaries;
};
#endif // !Employee_C_H
