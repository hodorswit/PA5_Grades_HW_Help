/******************************
Dalton McGinnis
04/27/2017
PA5_McGinnis_Dalton.cpp

********************************/

// Headers
#include <iostream>					// cout/cin
#include <iomanip>					// text formating
#include <cstdlib>					// exit and system
#include <string>					// strings
#include <fstream>					// file processing
#include <sstream>
using namespace std;

// Global variables
const string FILENAME = "NamesGrades.txt";	// The name of the file that you will read
const int MAX_GRADES = 5;
const int MAX_STUDENTS = 22;
double grade1, grade2, grade3, grade4, grade5;

struct Student
{
	string fName;
	string lName;
	double grades[MAX_GRADES] = { grade1, grade2, grade3, grade4, grade5 };
	double average;
	int max;
	int min;
};
Student studentsArray[MAX_STUDENTS];				// there are 22 students in this array


// Function declarations
void loadStudentArray(string fileName, Student studentArray[], int size);
void sortStudentArray(Student studentsArray[], int size);
//void displayStudentInfo(Student studentsArray[]);
void displayAverages(Student studentsArray[], string students[], int grades[][MAX_GRADES], int studentCount);
void displayMin(string students[], int grades[][MAX_GRADES], int studentCount);
void displayMax(string students[], int grades[][MAX_GRADES], int studentCount);
char getLetterGrade(double grade);

int main()
{

	int size = 0;

	//	Your code goes here
	loadStudentArray(FILENAME, studentsArray, size);
	sortStudentArray(studentsArray, size);

	int studentCount = 0;		// number of students processed
	int grades[MAX_STUDENTS][MAX_GRADES];		// table of grades
	string students[MAX_STUDENTS];		// list of student names
	char choice;		// make a decision

	// Loop until user says to quit
	do
	{
		// Present the menu 
		cout << "\n Grade Report Program\n\n";
		cout << "\t1. Display Average Grades\n"
			<< "\t2. Display Maximum Grades\n"
			<< "\t3. Display Minimum Grades\n"
			<< "\t4. Quit Program\n\n";
		cout << "Enter your choice (1-4): ";
		cin >> choice;

		while (getchar() != '\n');	// flush

									// Process choice
		switch (choice)
		{
		case '1':		// Average
			displayAverages(students, grades, studentCount);
			break;

		case '2':		// Maximum 
			displayMax(students, grades, studentCount);
			break;

		case '3':		// Minimum
			displayMin(students, grades, studentCount);
			break;

		case '4':		// Quit
			break;

		default:
			cout << "Invalid Option. Please try again\n\n";
		}

		if (choice != '4')
		{
			cout << endl;
			system("PAUSE");
			system("CLS");
		}
	} while (choice != '4');


	//	Make sure we place the end message on a new line
	cout << endl;

	//	The following is system dependent.  It will only work on Windows
	system("PAUSE");

	/*
	// A non-system dependent method is below
	cout << "Press any key to continue";
	cin.get();
	*/
	return 0;
}

// load the file contents into an array
void loadStudentArray(string fileName, Student studentsArray[], int size)
{
	string line;
	int i = 0;
	double grade1;
	double grade2;
	double grade3;
	double grade4;
	double grade5;
	double total = 0;

	
	ifstream myfile(fileName);		// input file stream
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, line);
			stringstream ssin(line);
			ssin >> studentsArray[i].fName;
			ssin >> studentsArray[i].lName;
			ssin >> grade1;
			ssin >> grade2;
			ssin >> grade3;
			ssin >> grade4;
			ssin >> grade5;
			total = grade1 + grade2 + grade3 + grade4 + grade5;
			studentsArray[i].average = total / 5;
			studentsArray[i].min = studentsArray[5].min;
			studentsArray[i].max = studentsArray[1].max;

			cout << line << endl;
		}
	}
	// close the file 
	myfile.close();
}

void sortStudentArray(Student studentsArray[], int size)
{
	bool didSwap;		// did we do a swap?

						// Go through each element from size - 1 to element 1
	for (double i = size - 1; i > 0; i--)
	{
		didSwap = false;		// assume no swaps

								// check all the remaining elements from 0 to i
		for (int j = 0; j < i; j++)
		{
			if (studentsArray[j].grades > studentsArray[j + 1].grades)
			{
				swap(studentsArray[j].grades, studentsArray[j + 1].grades);
				didSwap = true;
			}
		}	// end of inner loop
		if (!didSwap) break;
	}	// end of the outer loop



	//bool didSwap = true;				// assign didSwap to ture
	//while (didSwap == true)
	//{
	//	didSwap = false;			// assume no swaps

	//	for (int i = 0; i < MAX_GRADES; i++)
	//	{
	//		if (studentsArray[i].grades < studentsArray[i + 1].grades)
	//		{
	//			Student tempStudent = { studentsArray[i].fName, studentsArray[i].lName, studentsArray[i].grades[i], studentsArray[i].min, studentsArray[i].max };
	//			studentsArray[i] = studentsArray[i + 1];
	//			studentsArray[i + 1] = tempStudent;
	//			didSwap = true;
	//		}
	//	}
	//}
}

void displayAverages(Student studentsArray[], string students[], int grades[][MAX_GRADES], int studentCount)
{
	double average;		// average grade of students
	int total;			// total of all grades (accumulator)
						// get the longest name

	// Setup the table header
	cout << setprecision(1) << fixed << showpoint;
	cout << "\n\nStudent Averages\n";
	cout << setw(1) << left << "Student"
		<< setw(8) << right << "Average"
		<< setw(10) << "Grade" << endl;

	for (int i = 0; i < studentCount; i++)
	{
		cout << setw(1) << left << students[i];
		total = 0;		// zero out/clear the accumulator
		for (int j = 0; j < MAX_GRADES; j++)
		{
			total += grades[i][j];
		}
		average = static_cast<double>(total) / MAX_GRADES;
		cout << setw(8) << right << average
			<< setw(10) << getLetterGrade(static_cast<int>(average))
			<< endl;
	}

}

void displayMin(string students[], int grades[][MAX_GRADES], int studentCount)
{
}

void displayMax(string students[], int grades[][MAX_GRADES], int studentCount)
{
}

char getLetterGrade(double grade)
{
	if (grade < 60)
		return 'F';
	else if (grade < 70)
		return 'D';
	else if (grade < 80)
		return 'C';
	else if (grade < 90)
		return 'B';
	else if (grade <= 100)
		return 'A';
}
