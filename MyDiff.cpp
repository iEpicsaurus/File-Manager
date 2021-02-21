//
// Created by Aleksandar Kostic on 2019-09-30 for 3307 Assignment.
// This definition file implements the MyDiff.h header file 
// This will compare two files and report if they are diff/same;
// mimics behaviour of diff.
//

#include "MyDiff.h"
using namespace std;

// This function compares two files named as parameters and outputs if
// they are the same or not; mimics behaviour of diff
// Parameter: takes in two strings, representing two file names
// Return: nothing
void mydiff(string fileName1, string fileName2) {
	
	FileManager fileOne = FileManager(fileName1); // creates 2 objects
	FileManager fileTwo = FileManager(fileName2);
	
	int status = fileName1.compare(fileName2); // compare them
	// compare will print whether they are same or not
	
	if (status != 0) {
		
		cout << fileOne.getErrorOfFileString();
		
	}
	
}

// Main is used to prompt for user input and calls mydiff function
// Parameters: none
// Return: 0 if successful termination, -1 otherwise
int main() {
	
	string file1, file2; // takes two files as input
	cout << "Enter the name of first file " << endl;
	cin >> file1;
	
	cout << "Enter the name of second file " << endl;
	cin >> file2;
	
	mydiff(file1, file2); // passes the two files into mydiff
	
	return 0;
	
}
