/**
Week 16 Final Exam
Tom Matz
12/9/2022
CIS 1202.201
*/

#include <iostream>
#include "Employee_C.h"
#include <fstream>//step 1 for working with files
#include <string>

using namespace std;

//Function prototypes

void Test_Methods();
void Display_Class_Members(const Employee_C &);
Employee_C* Fill_Array();
void Extract_ID(const Employee_C [], fstream&);
void Find_Employee(fstream&, int, int*);

const int MAX_NAME_SIZE = 61;
int main()
{
	Employee_C *Employee_Ptr;
	string binaryFN;	 
	int searchID,position;
	bool otraVez = true;
	cout << "\nI will call a test function first.";
	Test_Methods();

	cout << "\nEnter a name for a binary file.> ";
	getline(cin, binaryFN);//Step 2 when working with files

	fstream binaryFile;//Step 3 the filestream object is defined.
	//and in Step 4 the filestream object is opened.
	binaryFile.open(binaryFN, ios::in | ios::out | ios::trunc | ios::binary);

	Employee_Ptr = Fill_Array();
	Extract_ID(Employee_Ptr, binaryFile);

	while (otraVez)
	{
		cout << "Enter an employee ID to search.> ";
		cin >> searchID;
		Find_Employee(binaryFile, searchID, &position);
		if (position >= 0)
		{
			cout << "\nThe employee's data was found:";
			Display_Class_Members(*(Employee_Ptr + position));
		}
		else
		{
			cout << "\nError: " << searchID << " is not in the data base";
		}
		cout << "\nEnter 1 to continue; or 0 to quit.> ";
		cin >> otraVez;
	}

	cout << "\nHere is a total of all employees' salaries: ";
	cout << Employee_Ptr->Get_TotalOfAllSalaries();
	

	cout << endl << endl;
	system("pause");
	return 0;

}
void Test_Methods()
{
	const int TEST_SIZE = 5;
	
	Employee_C testEmployee[TEST_SIZE];
	int i = 0;
	bool again = true;;
	while (again)
	{
		char enteredName[MAX_NAME_SIZE];
		int enteredID;
		double enteredSalary;
		char enteredSex;
		cout << "\nEnter the following: ";
		cout << "\nfull name> ";
		cin.get(enteredName, MAX_NAME_SIZE);
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
}

void Display_Class_Members(const Employee_C &xEmplObject)
{
	cout << "\nHere are the values for this employee: ";
	cout << "\nName: " << xEmplObject.Get_FullName();
	cout << "\nID: " << xEmplObject.Get_IDNumber();
	cout << "\nSalary: " << xEmplObject.Get_Salary();
	cout << "\nSex: " << xEmplObject.Get_Sex();
	cout << "\nTotalSalaries: " << xEmplObject.Get_TotalOfAllSalaries();
}

Employee_C* Fill_Array()
{
	//this function returns a pointer to the main program
	//It first creates an array of Employee_C dynamically

	Employee_C* enteredEmployee_P = new Employee_C[100];
	Employee_C tempEmployee;
	bool again = true;
	int index = 0, enteredID;
	char enteredName[MAX_NAME_SIZE];
	double enteredSalary;
	char enteredSex;

	while (again)
	{
		cout << "\nEnter the employee's full name.> ";
		cin.get(enteredName, MAX_NAME_SIZE);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "\nEnter the employee's ID number.> ";
		cin >> enteredID;
		
		cout << "\nEnter the employee's salary.> ";
		cin >> enteredSalary;

		cout << "\nEnter the employee's sex.> ";
		cin >> enteredSex;

		tempEmployee.Set_FullName(enteredName);
		tempEmployee.Set_IDNumber(enteredID);
		tempEmployee.Set_Salary(enteredSalary);
		tempEmployee.Set_Sex(enteredSex);
		*(enteredEmployee_P) = tempEmployee;

		cout << "\nEnter 1 to add another employee or 0 to quit.> ";
		cin >> again;

		enteredEmployee_P++;
	}
	return enteredEmployee_P;
}

void Extract_ID(const Employee_C empArray[], fstream &fileObjectPar)
{
	int i = 0;
	int tempID;
	bool moreToProcess = true;
	while (moreToProcess)
	{
		tempID = empArray[i].Get_IDNumber();
		if (tempID > 0)
		{
			//Step 5 for files -- processing
			fileObjectPar.write(reinterpret_cast<char*>(&tempID), sizeof(tempID));
		}
		else moreToProcess = false;
	}
}

void Find_Employee(fstream &fileObjectPar, int xID,int *Position)
{
	int foundPos = -1;
	int fileID, byteNum;
	fileObjectPar.clear();// clear the EOF flag
	fileObjectPar.seekg(0, ios::beg);//move to the beginning
	while (foundPos == -1 and !fileObjectPar.eof())
	{
		fileObjectPar.read(reinterpret_cast<char*>(&fileID), sizeof(fileID));
		if (fileID == xID)
		{
			byteNum = fileObjectPar.tellg();

			foundPos = byteNum / 2;
		}
	}
	*Position = foundPos;
}
