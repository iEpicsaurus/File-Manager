//
// Created by Aleksandar Kostic on 2019-09-30 for 3307 Assignment.
// This definition file implements the MyCp.h header file 
// This will display copy a file from source to destination, mimics
// the behaviour of cp.
//

#include "MyCp.h"
using namespace std;

// This function will copy a file from source to desination, 
// mimics behaviour of cat.
// Parameter: takes in a string, representing the destination
// Return: nothing
void mycp(string newDest) {
	
	fstream myStream;
	ofstream newFileDest;
	
	//dump(myStream); <- not working for some reason, cannot fix
	
	FileManager newFile = FileManager(newDest.c_str());
	
	// NOTE: I was unsure how to approach this function; I used what
	// I had for mycat() as they seemed to be similar in nature but
	// I didn't know how to manipulate what I had to make it meet the
	// requirements of the function mycp().
	
}

// Main is used to prompt for user input and calls mycp function
// Parameters: none
// Return: 0 if successful termination, -1 otherwise
int main() {
	
	string inputDest; // prompts for user input
	cout << "Type where you would like to copy the file "; 
	cin >> inputDest;
		
	mycp(inputDest); // passes user input to the mycat function
	
	return 0;

}
