//
// Created by Aleksandar Kostic on 2019-09-30 for 3307 Assignment.
// This definition file implements the MyMv.h header file 
// This will move and rename files around. Mimics mv behaviour.
//

#include "MyMv.h"
using namespace std;

// This function moves and renames files.
// Parameter: takes in current file, and a string (new file name)
// Return: nothing
void mymv(FileManager currentFile, string newName) {
	
	// Wasn't sure how to implement this; my idea was to rename the 
	// original file; if successful, this means it was on same file syste,.
	// Otherwise, it wasn't on same file system so we would have to dump
	// and remove to copy file and remove the original.
	// But for some reason my logic wasn't working
	
	int status = currentFile.Rename(newName.c_str()); // same file system
	
	if (status != 0) { // different file system; need to dump and remove
		
		fstream myStream;
		ofstream newFile;
		
		//currentFile.dump(myStream); // dump file to stream, then remove
		int statusRemove = remove(currentFile.getNameOfFile().c_str());
		if (statusRemove != 0) {
			
			cout << currentFile.getErrorOfFileString();
			
		}
		
		newFile.open(newName); // open a new file
		if (!newFile.is_open()) {
		
			cout << strerror(-1); // the getErrorString function wasn't working
		
		}
		
		// length of stream - used to indicate how much was put to stream
		myStream.seekg(0, myStream.end);
		int lengthOfStream = myStream.tellg();
		myStream.seekg(0, myStream.beg);
		
		char *buffer = new char[lengthOfStream];
		myStream.read(buffer, lengthOfStream); // put to new file
		
		newFile.close();
		myStream.close();
		
		FileManager(newName.c_str()); // create new file
			
	}
	
}

// Main is used to prompt for user input and calls mymv function
// Parameters: none
// Return: 0 if successful termination, -1 otherwise
int main() {
	
	string input; // prompts for user input
	cout << "Type where you would like to move the file "; 
	cin >> input;
	
	FileManager currentFile = FileManager("firstFile");
	// creates an initial FileManager
	
	mymv(currentFile, input); // pass initial FileManager & input
	
	return 0;
	
}
