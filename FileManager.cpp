//
// Created by Aleksandar Kostic on 2019-09-30 for 3307 Assignment.
// This definition file implements the FileManager.h header file 
// This helps manages files; uses collection of system calls and 
// file I/O operations.
//

#include "FileManager.h"
using namespace std;

// This function will create an instance of FileManager and initializes it.
// Parameter: takes in a string, representing a file name
// Return: nothing
FileManager::FileManager(string fileName) {

    struct stat informationOfFile;
    stat(fileName.c_str(), &informationOfFile);

    nameOfFile = fileName;
    typeOfFile = setTypeOfFile();
    sizeOfFile = informationOfFile.st_size;
    sizeOfBlock = informationOfFile.st_size;
    ownerOfFileID = informationOfFile.st_uid;
    ownerOfFileString = getpwuid(ownerOfFileID)->pw_name;
    groupOfFile = informationOfFile.st_gid;
    groupOfFileString = getgrgid(groupOfFile)->gr_name;
    permissionsOfFile = setPermissionsOfFile();
    lastAccessOfFile = informationOfFile.st_atim;
    lastModificationOfFile = informationOfFile.st_mtim;
    lastStatusChangeOfFile = informationOfFile.st_ctim;
    sizeOfBlock = informationOfFile.st_blksize;
    expand(); // initializes childrenOfFile
    errorOfFile = 0;

    // not sure what to do if stat is not successful; instructions not
    // clear - initialize them to what?

}

// This function destroys and frees up any resources attaches to the object
// In this case, this is the default deconstructor.
// Parameter: nothing
// Return: nothing
FileManager::~FileManager() = default; // default deconstructor

// This function fills in the children of the file object function invoked on;
// creates a new file object for each file found in the directory.
// Parameter: none
// Return: int, representing error code of the function
int FileManager::expand() {

    if (typeOfFile != "Directory") {
        
        errorOfFile = ENOTSUP; // if not directory, no children
        
    }
    
    else { // otherwise, we are in a directory
        
        DIR *directoryPointer;
        struct dirent *directory;
        
        // open the directory, check if it was opened successfully
        directoryPointer = opendir(nameOfFile.c_str());
        if (directoryPointer == NULL) {
            
            errorOfFile = -1;
            return errorOfFile;
            
        }
        
        // for each file in directory, create new file object for the file
        // and push it into the vector container
        vector<FileManager> children;
        while ((directory = readdir(directoryPointer))) {
            
            children.push_back((FileManager(directory->d_name)));
            
        }
        
        // close directory and then initialize the children of the file
        closedir(directoryPointer);
        childrenOfFile = children;
        
    }
    
    return errorOfFile;

}

// This function will return the name of the file.
// Parameter: nothing
// Return: string, representing name of the file
string FileManager::getNameOfFile() {

    return nameOfFile;

}

// This function returns the type of the file
// Parameter: none
// Return: string, representing the file of the type
string FileManager::getTypeOfFile() {

    return typeOfFile;

}

// This function returns permissions of the file
// Parameter: none
// Return: string, representing permissions of the file
string FileManager::getPermissionsOfFile() {

    return permissionsOfFile;

}

// This function returns size of the file
// Parameter: none
// Return: off_t, representing size of file
off_t FileManager::getSizeOfFile() {

    return sizeOfFile;

}

// This function returns numeric owner of the file
// Parameter: none
// Return: uid_t, representing the numeric ID of the file owner
uid_t FileManager::getOwnerOfFileID() {

    return ownerOfFileID;

}

// This function returns the string name of the file owner
// Parameter: none
// Return: string, represents name of the file owner
string FileManager::getOwnerOfFileString() {

    return ownerOfFileString;

}

// This function returns the group id the file is associated with
// Parameter: none
// Return: gid_t, representing group id the file is associated with
gid_t FileManager::getGroupOfFile() {

    return groupOfFile;

}

// This function returns the group name the file is associated with
// Parameter: none
// Return: string, representing the group name file is associated with
string FileManager::getGroupOfFileString() {

    return groupOfFileString;

}

// This function returns the last time the file was accessed
// Parameter: none
// Return: timespec, representing the last time the file was accessed
timespec FileManager::getLastAccessOfFile() {

    return lastAccessOfFile;

}

// This function returns the last time the file was modified
// Parameter: none
// Return: timespec, representing the last time the file was modified
timespec FileManager::getLastModificationOfFile() {

    return lastModificationOfFile;

}

// This function returns the last time the file's last status change
// Parameter: none
// Return: timespec, representing the file's last status change
timespec FileManager::getLastStatusChangeOfFile() {

    return lastStatusChangeOfFile;

}

// This function returns the size of the block
// Parameter: none
// Return: blksize_t, representing the size of the block
blksize_t FileManager::getSizeOfBlock() {

    return sizeOfBlock;

}

// This function returns the children associated with the file
// Parameter: none
// Return: vector<FileManager>, representing the children of file
vector<FileManager> FileManager::getChildrenOfFile() {

    return childrenOfFile;

}

// This function returns the numeric error of the file
// Parameter: none
// Return: int, representing the numeric error of the file
int FileManager::getErrorOfFile() {

    return errorOfFile;

}

// This function returns the error of the file in string form
// Parameter: none
// Return: string, representing the numeric error of the file in string form
string FileManager::getErrorOfFileString() {

    return strerror(errorOfFile);

}

// This function sets name of existing file to new specified name
// Parameter: takes in a string, representing the new file name
// Return: nothing
void FileManager::setNameOfFile(string newFileName){

    nameOfFile = newFileName;

}

// This function dumps the contents of named file to specified file stream.
// Can be used to copy file, display contents to terminal, and so on.
// Parameter: fstream, representing file stream
// Return: int, representing error code of operation
int FileManager::dump(fstream fileStream) {

    // if not regular file, return error
    if (typeOfFile != "Regular File") {
        
        errorOfFile = ENOTSUP;
        return errorOfFile;
        
    }
    
    // This part deals with opening the filestream, checking to see if it
    // was opened successfulling, and writing blocks of data to file stream
    fileStream.open(nameOfFile);
    
    if(!fileStream.is_open()) {
        
        errorOfFile = -1;
        return errorOfFile;
        
    }
    
    // Write blocks of data to file stream based on sizeOfBlock
    char *buffer = new char[sizeOfBlock];
    
    while (!fileStream.eof()) {
        
        fileStream.write(buffer, sizeOfBlock);
        
    }
    
    return errorOfFile;

}

// This function wchanges the name of the file from its existing name to
// the new name provided (changes attribute and name on file on disk).
// Parameter: takes in a string, representing new file name
// Return: int, representing error code of function
int FileManager::Rename(string newFileName) {

    // Create temp variable to store old name of file; then set the new name
    // and then process the rename using the system call
    string oldFileName = nameOfFile;
    setNameOfFile(newFileName);
    
    
    int status = rename(oldFileName.c_str(), nameOfFile.c_str());
    if (status != 0) {
        
        errorOfFile = -1;
        
    }
    
    return errorOfFile;

}

// This function removes the file from the file system
// Parameter: nothing
// Return: int, representing error code of function
int FileManager::remove() {

    // system call to clear/reset attributes of file object
    int status = unlink(this->nameOfFile.c_str());

    if (status != 0) {

        errorOfFile = status;

    }
    
    return errorOfFile;

}

// This function compares contents of two files and outputs if they
// are the same or different.
// Parameter: takes in a FileManager object, fileObject, to compare with
// Return: int, representing error code of function
int FileManager::compare(FileManager fileObject) {

    ifstream myFile, otherFile;
    
    // Open both files, then see if successfully opened
    myFile.open(this->nameOfFile);
    otherFile.open(fileObject.nameOfFile);
    
    if (!myFile.is_open() || !otherFile.is_open()) {
        
        errorOfFile = -1;
        return errorOfFile;
        
    }
    
    // For performance, read based on sizeOfBlock
    char *bufferMyFile = new char[sizeOfBlock];
    char *bufferOtherFile = new char[sizeOfBlock];
    int flag = 0; // used to indicate whether or not to output the files
                  // being the same at the end of the function
    
    while (!myFile.eof()) { // continue until end of file is reached
        
        myFile.read(bufferMyFile, sizeOfBlock); // read from both
        otherFile.read(bufferOtherFile, sizeOfBlock);
        
        // compare the files
        if (memcmp(bufferMyFile, bufferOtherFile, sizeOfBlock) != 0) {
            
            flag = 1; // when there is a different, set flag
            cout << "Files are different" << endl;
            
        }
        
    }
    
    if (flag == 0) { // if flag set in while loop, files are different
        
        cout << "Files are the same" << endl;
        
    }
    
    return errorOfFile;

}

// This function is used to initialize the type of the file
// Parameter: nothing
// Return: string, representing type of file
string FileManager::setTypeOfFile() {

    string fileType;
    
    switch(informationOfFile.st_mode & S_IFMT) { // checks stat()

        case S_IFBLK:
            fileType = "Block Device";
            break;

        case S_IFCHR:
            fileType = "Character Device";
            break;

        case S_IFDIR:
            fileType = "Directory";
            break;

        case S_IFIFO:
            fileType = "FIFO/Pipe";
            break;

        case S_IFLNK:
            fileType = "Symbolic Link";
            break;

        case S_IFREG:
            fileType = "Regular File";
            break;

        case S_IFSOCK:
            fileType = "Socket";
            break;

        default:
            fileType = "Unknown";
            break;

    }
    
    return fileType;

}

// This function is used to initialize permissions of file
// Parameter: none
// Return: string, representing file permissions
string FileManager::setPermissionsOfFile() {
    
    string finalString;
    
    // deals with first part of permissions; indicate file/directory
    if (typeOfFile == "Directory") {

        finalString = "d";

    }

    if (typeOfFile == "Regular File") {

        finalString = "-";

    }
    
    // deals with user permissions; read
    if (informationOfFile.st_mode & S_IRUSR) { // checks from stat()
        
        finalString = finalString + "r";
        
    }
    
    else {
        
        finalString = finalString + "-";
        
    }
    
    // deals with user permissions; write
    if (informationOfFile.st_mode & S_IWUSR) {
        
        finalString = finalString + "w";
        
    }
    
    else {
        
        finalString = finalString + "-";
        
    }
    
    // deals with user permissions; execute
    if (informationOfFile.st_mode & S_IXUSR) {
        
        finalString = finalString + "x";
        
    }
    
    else {
        
        finalString = finalString + "-";
        
    }
    
    // deals with group permissions; read
    if (informationOfFile.st_mode & S_IRGRP) {
        
        finalString = finalString + "r";
        
    }
    
    else {
        
        finalString = finalString + "-";
        
    }
    
    // deals with group permissions; write
    if (informationOfFile.st_mode & S_IWGRP) {
        
        finalString = finalString + "w";
        
    }
    
    else {
        
        finalString = finalString + "-";
        
    }
    
    // deals with group permissions; execute
    if (informationOfFile.st_mode & S_IXGRP) {
        
        finalString = finalString + "x";
        
    }
    
    else {
        
        finalString = finalString + "-";
        
    }
    
    // deals with others permissions; read
    if (informationOfFile.st_mode & S_IROTH) {
        
        finalString = finalString + "r";
        
    }
    
    else {
        
        finalString = finalString + "-";
        
    }
    
    // deals with others permissions; write
    if (informationOfFile.st_mode & S_IWOTH) {
        
        finalString = finalString + "w";
        
    }
    
    else {
        
        finalString = finalString + "-";
        
    }
    
    // deals with others permissions; execute
    if (informationOfFile.st_mode & S_IXOTH) {
        
        finalString = finalString + "x";
        
    }
    
    else {
        
        finalString = finalString + "-";
        
    }
    
    return finalString;
    
}
