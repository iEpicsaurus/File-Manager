//
// Created by Aleksandar Kostic on 2019-09-30 for 3307 Assignment.
// This definition file implements the MyLs.h header file 
// This will list the contents of a directory; for other filse, it shows
// name of file. Includes long form listing. Mimics behaviour of ls.
//

#include "MyLs.h"
using namespace std;

// This function compares prints contents of directory; if it is a file,
// prints name of file. Mimics behaviour of ls.
// Parameter: takes in string, representing two file names
// Return: nothing - output to terminal
void myls(string fileName) {
	
	// using name of file, create FileManager object and access its
	// children; directory = list contents of directory
	// file = show name of file
	FileManager file = FileManager(fileName);
	
	if (file.getTypeOfFile() != "Directory") { // dealing with file
		
		cout << file.getNameOfFile() << endl;
		
	}
	
	else { // dealing with directory
	
		vector<FileManager> children = file.getChildrenOfFile();
	
		// access children and print contents of directory (children
		// are member files of the directory)
		for (unsigned int i = 0; i < children.size(); i++) {
		
			FileManager currentChild = children.at(i);
			cout << currentChild.getNameOfFile() << " " << currentChild.getPermissionsOfFile() << endl;
		
		}
		
	}
	
}

// Main is used to prompt for user input and calls myls function
// Parameters: none
// Return: 0 if successful termination, -1 otherwise
int main() {
	
	string input; // promps for user input
	cout << "Enter name of directory/file: ";
	cin >> input;
	
	myls(input); // passes user input into myls function
	
	return 0;
	
}
