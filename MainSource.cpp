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
#include <limits>
#include <iomanip>

using namespace std;

//Function prototypes

void Test_Methods();
void Display_Class_Members(const Employee_C &);
Employee_C* Fill_Array();
void Extract_ID(const Employee_C [], fstream&);
void Find_Employee(fstream&, int, int*);
void Test_Salary_Setting(Employee_C);

const int MAX_NAME_SIZE = 61;
int main()
{
	cout << setprecision(2) << fixed;

	Employee_C *Employee_Ptr;
	string binaryFN;	 
	int searchID,position;
	bool otraVez = true;
	//cout << "\nI will call a test function first.";
	//Test_Methods();

	cout << "\nEnter a name for a binary file.> ";
	getline(cin, binaryFN);//Step 2 when working with files

	fstream binaryFile;//Step 3 the filestream object is defined.
	//and in Step 4 the filestream object is opened.
	binaryFile.open(binaryFN, ios::in | ios::out | ios::trunc | ios::binary);

	Employee_Ptr = Fill_Array();
	//test that the array is properly filled
	//cout << Employee_Ptr->Get_FullName();
	//for (int j = 0; j < 6; j++)
	//	Display_Class_Members(*(Employee_Ptr + j));

	//test the update of the salary setting
	/*int k;
	cout << "\nEnter an index value: ";
	cin >> k;
	Test_Salary_Setting(*(Employee_Ptr + k));*/

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

	cout << "\nHere is a total of all employees' salaries: $ ";
	cout << Employee_Ptr->Get_TotalOfAllSalaries();
	binaryFile.close();//Step 6 for files.

	delete[]Employee_Ptr;
	Employee_Ptr = nullptr;
	

	cout << endl << endl;
	system("pause");
	return 0;
}




void Test_Salary_Setting(Employee_C xEmploy)
{
	Display_Class_Members(xEmploy);
	
	double newSalary;
	
	cout << "\nEnter a new salary> ";
	cin >> newSalary;
	xEmploy.Set_Salary(newSalary);
	Display_Class_Members(xEmploy);
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
	cout << "\nSalary: $ " << xEmplObject.Get_Salary();
	cout << "\nSex: " << xEmplObject.Get_Sex();
	cout << "\nTotalSalaries: $ " << xEmplObject.Get_TotalOfAllSalaries();
}

Employee_C* Fill_Array()
{
	//this function returns a pointer to the main program
	//It first creates an array of Employee_C dynamically

	Employee_C* enteredEmployee_P = new Employee_C[100];
	//Employee_C tempEmployee;
	bool again = true;
	int index = 0, enteredID;
	char enteredName[MAX_NAME_SIZE];
	double enteredSalary;
	char enteredSex;

	//assign another pointer that points to the first array element
	Employee_C* zeroElement_P = nullptr;
	zeroElement_P = enteredEmployee_P;

	while (again)
	{
		//The employee object is created with a pointer.
		//The Employee class constructor will operate with each creation.
		//	and at the bottom of the loop the allocated memory
		//	 in the free store is deleted.
		Employee_C* tempEmployee_P = new Employee_C;;
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

		tempEmployee_P->Set_FullName(enteredName);
		
		tempEmployee_P->Set_IDNumber(enteredID);

		//check salary before settin
		/*cout << "\ntotal " << tempEmployee_P->Get_TotalOfAllSalaries();
		cout << endl;
		cout << tempEmployee_P->Get_Salary();*/


		tempEmployee_P->Set_Salary(enteredSalary);

		//check salary after setting
		/*cout << "\ntotal " << tempEmployee_P->Get_TotalOfAllSalaries();
		cout << endl;
		cout << tempEmployee_P->Get_Salary();*/

		tempEmployee_P->Set_Sex(enteredSex);
		
		*enteredEmployee_P = *tempEmployee_P;

		cout << "\nEnter 1 to add another employee or 0 to quit.> ";
		cin >> again;
		cin.ignore();

		enteredEmployee_P++;

		//I want to delete tempEmployee at the bottom of the loop
		delete tempEmployee_P;
		tempEmployee_P = nullptr;

	}
	return zeroElement_P;
}

void Extract_ID(const Employee_C empArray[], fstream &fileObjectPar)
{
	//this function finds the ID for each array element
	//	and writes it to a binary file
	// the while loop checks the flag to see if there is more to process
	// then it increments the index each pass through
	int i = 0;
	int tempID;
	
	//fileObjectPar.write(reinterpret_cast<char*>(&tempID), sizeof(tempID));
	bool moreToProcess = 1;
	while (moreToProcess)
	{
		tempID = empArray[i].Get_IDNumber();
		//cout << "\n tempID = " << tempID;
		
		if (tempID > 0)
		{
			//Step 5 for files -- processing
			fileObjectPar.write(reinterpret_cast<char*>(&tempID), sizeof(tempID));
		}
		else moreToProcess = false;
		i++;
	}
}

void Find_Employee(fstream &fileObjectPar, int xID,int *Position)
{
	int foundPos = -1;
	int fileID, byteNum;
	fileObjectPar.clear();// clear the EOF flag
	fileObjectPar.seekg(0, ios::beg);//move to the beginning

	//cout << std::boolalpha;
	//cout << "Min value for int: " << numeric_limits<int>::min() << '\n';
	//cout << "Max value for int: " << numeric_limits<int>::max() << '\n';
	//cout << "int is signed: " << numeric_limits<int>::is_signed << '\n';
	//cout << "Non-sign bits in int: " << numeric_limits<int>::digits << '\n';
	//cout << "int has infinity:  " << numeric_limits<int>::has_infinity << '\n';

	while (foundPos == -1 and !fileObjectPar.eof())
	{
		fileObjectPar.read(reinterpret_cast<char*>(&fileID), sizeof(fileID));
		if (fileID == xID)
		{
			byteNum = fileObjectPar.tellg();
			//cout << "\nBytenum = " << byteNum;
			foundPos = (byteNum / 4)-1;
		}
	}
	*Position = foundPos;
}
