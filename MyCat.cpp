//
// Created by Aleksandar Kostic on 2019-09-30 for 3307 Assignment.
// This definition file implements the MyCat.h header file 
// This will display contents of the files given as parameters to the
// terminal - mimics the behaviour of cat.
//

#include "MyCat.h"
using namespace std;

// This function will display contents of the files given as parameters
// to the terminal, mimics behaviour of cat.
// Parameter: takes in a string, representing a file
// Return: nothing as it prints to the terminal
void mycat(string fileName) {
	
	fstream myStream;
	ofstream newFileDest;
	
	// first you'd dump contents of file to stream and then print it
	// to the terminal; dump does the first part and once we get to the
	// length of the string, this handles the printing to the terminal
	
	//dump(myStream); <- not working for some reason, cannot fix
	
	FileManager newFile = FileManager(fileName.c_str());
	
	newFileDest.open(fileName);
	if (!newFileDest.is_open()) { // opening
		
		cout << strerror(-1); // the getErrorString function wasn't working
		
	}
	
	// length of stream; used to get length of buffer
	myStream.seekg(0, myStream.end);
	int lengthOfStream = myStream.tellg();
	myStream.seekg(0, myStream.beg);
	
	char *buffer = new char[lengthOfStream];
	myStream.read(buffer, lengthOfStream);
	
	cout << buffer << endl; // print to terminal
	
}

// Main is used to prompt for user input and calls mycat function
// Parameters: none
// Return: 0 if successful termination, -1 otherwise
int main() {
	
	string input; // prompts for user input
	cout << "Enter name of file "; 
	cin >> input;
		
	mycat(input); // passes user input to the mycat function
	
	return 0;	
	
}
