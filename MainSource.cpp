/**
Week 16 Final Exam
Tom Matz
12/9/2022
CIS 1202.201
*/


#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Employee_C.h"
#include <fstream>//step 1 for working with files
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

//Function prototypes

void Display_Class_Members(const Employee_C &);
Employee_C* Fill_Array();
void Extract_ID(const Employee_C [], fstream&);
void Find_Employee(fstream&, int, int*);

void Test_Salary_Setting(Employee_C &);
void Test_Methods();

const int MAX_NAME = 61;
int main()
{
	cout << setprecision(2) << fixed;

	Employee_C *Employee_Ptr;
	string binaryFN;	 
	int searchID,position;
	bool otraVez = true, testFlag = false;
	
	//*cout << "\nEnter 1 if you want to run tests; 0 if not> ";
	//*cin >> testFlag;
	/*cin.ignore();
	if (testFlag)
	{ cout << "\nI will call a test function first.";
		Test_Methods();
	}*/

	cout << "\nEnter a name for a binary file.> ";
	getline(cin, binaryFN);//Step 2 when working with files

	fstream binaryFile;//Step 3 the filestream object is defined.
	//and in Step 4 the filestream object is opened.
	binaryFile.open(binaryFN, ios::in | ios::out | ios::trunc | ios::binary);

	Employee_Ptr = Fill_Array();

	if (testFlag)
	{
		//test that the array is properly filled
		cout << Employee_Ptr->Get_FullName();
		for (int j = 0; j < 6; j++)
			Display_Class_Members(*(Employee_Ptr + j));
	}

	Extract_ID(Employee_Ptr, binaryFile);

	cout << "\n\tWould you like to change a salary?\n";
	cout << "If so, enter 1; if not enter 0> ";
	cin >> testFlag;

	while (testFlag)
		//test the update of the salary setting
	{
		int k;
		cout << "\nEnter an index value of 0 to the highest number you entered: ";
		cin >> k;
		Test_Salary_Setting(*(Employee_Ptr + k));
		cout << "\n\tWould you like to change another salary?\n";
		cout << "If so, enter 1; if not enter 0> ";
		cin >> testFlag;
	}

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

void Display_Class_Members(const Employee_C &xEmplObject)
{
	// NOTE:  the method Get_FullName returns a pointer
	//		to an array in the free store.  This memory
	//		must be deleted.
	
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
	// The returned pointer points to the 1st array element.
	//*It is incumbent on the calling program to DELETE this pointer[]
	//		when they are finished using it.

	Employee_C* enteredEmployee_P = new Employee_C[100];
	
	bool again = true;
	int enteredID;
	char enteredName[MAX_NAME];
	double enteredSalary;
	char enteredSex;

	//assign another pointer that points to the first array element
	//	The purpose of this pointer is to hold the address of the 1st array element.
	//		This is what is returned to the calling routine.  Without this
	//		the function would return the address of the (n+1) element
	//		after going through the while loop n times.

	Employee_C* zeroElement_P = nullptr;
	zeroElement_P = enteredEmployee_P;

	while (again)
	{
		//	NOTE:  I did not follow the hint as written in the requirements.
		//
		//	The reason for a pointer (instead of just an object) is:
		//		We need the Employee class object variable to be at its initial state
		//		when we make all the assignments.  More specifically,
		//		a problem occurs when Set_Salary is called.  If a single
		//		object is re-used, it will have a value for salary when
		//		set salary is called (from the previous pass).  This value
		//		will be deducted from the static variable.  So the static
		//		variable does not get accumulated.
		// Using a pointer object that is incremented
		//	on each pass through the loop.  Thus
		//	initializing Salary to 0.
		//Employee_C* tempEmployee_P = new Employee_C;

		//*** Begin inputting the record info
		cout << "\nEnter the employee's full name.> ";
		cin.get(enteredName, MAX_NAME);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "\nEnter the employee's ID number.> ";
		cin >> enteredID;
		cout << "\nEnter the employee's salary.> ";
		cin >> enteredSalary;
		cout << "\nEnter the employee's sex.> ";
		cin >> enteredSex;

		//tempEmployee_P->Set_FullName(enteredName);
		//tempEmployee_P->Set_IDNumber(enteredID);

		//check salary before settin
		/*cout << "\ntotal " << tempEmployee_P->Get_TotalOfAllSalaries();
		cout << endl;
		cout << tempEmployee_P->Get_Salary();*/

		//tempEmployee_P->Set_Salary(enteredSalary);

		////check salary after setting
		///*cout << "\ntotal " << tempEmployee_P->Get_TotalOfAllSalaries();
		//cout << endl;
		//cout << tempEmployee_P->Get_Salary();*/

		//tempEmployee_P->Set_Sex(enteredSex);
		////Here we assign the single pointer contents to the array pointer contents
		//*enteredEmployee_P = *tempEmployee_P;
		
		//filling the array directly
		enteredEmployee_P->Set_FullName(enteredName);
		enteredEmployee_P->Set_IDNumber(enteredID);
		enteredEmployee_P->Set_Salary(enteredSalary);
		enteredEmployee_P->Set_Sex(enteredSex);

		cout << "\nEnter 1 to add another employee or 0 to quit.> ";
		cin >> again;
		cin.ignore();

		enteredEmployee_P++;
	}
	return zeroElement_P;
}

void Extract_ID(const Employee_C empArray[], fstream &fileObjectPar)
{
	//this function finds the ID for each array element
	//	and writes it to a binary file
	// the while loop checks the flag to see if there is more to process
	// then it increments the index each pass through  (This assumes
	//	that an ID of 0 means no record has been added.)
	int i = 0;
	int tempID;
	
	//fileObjectPar.write(reinterpret_cast<char*>(&tempID), sizeof(tempID));
	bool moreToProcess = 1;
	while (moreToProcess)
	{
		tempID = empArray[i].Get_IDNumber();//access the ID private data
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
	//This function searches the fileObjectParameter (a binary file)
	//  for the xID parameter.
	//	  If the ID is found, the position(or record) is returned via the
	//	3rd parameter (Position).
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
			foundPos = (byteNum / 4)-1;  //Subtract 1 because the read operation
											//advances one record
		}
	}
	*Position = foundPos;
}
