//
// Created by Aleksandar Kostic on 2019-09-30 for 3307 Assignment.
// This header file is implemented by FileManager.cpp
// Furthermore, all the utilities use this header file for functionality.
//

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <pwd.h>
#include <grp.h>
#include <cstring>
#include <dirent.h>

class FileManager {

    public: // public functions of the class; accessible by utilities

        FileManager(std::string fileName);
        ~FileManager();
        int expand();
        std::string getNameOfFile();
        std::string getTypeOfFile();
        std::string getPermissionsOfFile();
        off_t getSizeOfFile();
        uid_t getOwnerOfFileID();
        std::string getOwnerOfFileString();
        gid_t getGroupOfFile();
        std::string getGroupOfFileString();
        timespec getLastAccessOfFile();
        timespec getLastModificationOfFile();
        timespec getLastStatusChangeOfFile();
        blksize_t getSizeOfBlock();
        std::vector<FileManager> getChildrenOfFile();
        int getErrorOfFile();
        std::string getErrorOfFileString();
        void setNameOfFile(std::string newFileName);
        int dump(std::fstream fileStream);
        int Rename(std::string newFileName);
        int remove();
        int compare(FileManager fileObject);

    private: // private members; not accessible

        std::string setTypeOfFile();
        std::string setPermissionsOfFile();
        struct stat informationOfFile;
        std::string nameOfFile;
        std::string typeOfFile;
        std::string permissionsOfFile;
        off_t sizeOfFile;
        uid_t ownerOfFileID;
        std::string ownerOfFileString;
        gid_t groupOfFile;
        std::string groupOfFileString;
        struct timespec lastAccessOfFile;
        struct timespec lastModificationOfFile;
        struct timespec lastStatusChangeOfFile;
        blksize_t sizeOfBlock;
        std::vector<FileManager> childrenOfFile; // if directory
        int errorOfFile;

};

#endif //FILEMANAGER_H
