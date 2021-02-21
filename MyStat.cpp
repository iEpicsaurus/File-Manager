//
// Created by Aleksandar Kostic on 2019-09-30 for 3307 Assignment.
// This definition file implements the MyStat.h header file 
// This outputs all the information on the file. Mimics stat behaviour.
//

#include "MyStat.h"
using namespace std;

// This function outputs all information on file. Mimics stat behaviour.
// Parameter: takes in a string, representing a file
// Return: nothing as it prints to the terminal
void mystat(string fileName) {
	
	FileManager file = FileManager(fileName);
	vector<FileManager> children = file.getChildrenOfFile();
	
	cout << "File Name: " << file.getNameOfFile() << endl;
	cout << "File Type: " << file.getTypeOfFile() << endl;
	cout << "File Permissions: " << file.getPermissionsOfFile() << endl;
	cout << "File Size: " << file.getSizeOfFile() << endl;
	cout << "Size of Blick: " << file.getSizeOfBlock() << endl;
	cout << "File Owner ID: " << file.getOwnerOfFileID() << endl;
	cout << "File Owner String: " << file.getOwnerOfFileString() << endl;
	cout << "File Group ID: " << file.getGroupOfFile() << endl;
	cout << "File Group String: " << file.getGroupOfFileString() << endl;
	//cout << "Time Last Accessed: " << file.getLastAccessOfFile() << endl; these three not working
	//cout << "Time Last Modified: " << file.getLastModificationOfFile() << endl;
	//cout << "Time Last Status Change: " << file.getLastStatusChangeOfFile() << endl;
	cout << "Error of File: " << file.getErrorOfFile() << endl;
	cout << "Error of File String: " << file.getErrorOfFileString() << endl;
	cout << "Children of File: " << endl;
	
	if (file.getTypeOfFile() != "Directory") { // not directory = no children
		
		cout << "None" << endl;
		
	}
	
	else { // directory = children
	
		for (unsigned int i = 0; i < children.size(); i++) {
			
			FileManager currentChild = children.at(i);
			cout << currentChild.getNameOfFile() << endl;
			// iterates through children and prints their name
		
		}
		
	}
	
}

// Main is used to prompt for user input and calls mystat function
// Parameters: none
// Return: 0 if successful termination, -1 otherwise
int main() {
	
	string file; // prompts for user input
	cout << "Enter name of file " << endl;
	cin >> file;
	
	mystat(file); // passes input into mystat
	
	return 0;
	
}
