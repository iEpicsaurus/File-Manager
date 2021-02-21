//
// Created by Aleksandar Kostic on 2019-09-30 for 3307 Assignment.
// This definition file implements the MyRm.h header file 
// This removes given files listed. Mimics rm behaviour.
//

#include "MyRm.h"
using namespace std;

// This function remove given files listed. Mimics rm behaviour.
// Parameter: takes in a string, representing a file to remove
// Return: nothing
void myrm(string fileToRemove) {
	
	int status = remove(fileToRemove.c_str()); // removes file
	
	if (status != 0) { // removal failure
		
		FileManager file = FileManager(fileToRemove);
		cout << file.getErrorOfFileString() << endl;
		
	}
	
}

// Main is used to prompt for user input and calls myrm function
// Parameters: none
// Return: 0 if successful termination, -1 otherwise
int main() {
	
	string fileToRemove; // prompts for input
	cout << "Type the names of files you would like to remove "; 
	cin >> fileToRemove;
		
	myrm(fileToRemove); // passes input to myrm
	
	return 0;
	
}
