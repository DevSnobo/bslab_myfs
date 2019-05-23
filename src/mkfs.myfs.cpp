//
//  mk.myfs.cpp
//  myfs
//
//  Created by Oliver Waldhorst on 07.09.17.
//  Copyright © 2017 Oliver Waldhorst. All rights reserved.
//

#include "myfs.h"
#include "blockdevice.h"
#include "macros.h"
#include <fstream>

int fileExists(char* &fileName);
int getFileSize(char* &fileName);

int main(int argNum, char *argArray[]) {

    if (argNum < 2) {
        fprintf(stderr, "error: too few arguments");
        fprintf(stderr, "usage: mkfs.myfs containerfile [<file-to-copy>, ...]");
    }

    if (argNum > 66) {
        fprintf(stderr, "error: too many arguments! 64 files max");
        fprintf(stderr, "usage: mkfs.myfs containerfile [<file-to-copy>, ...]");
    }

    //TODO: container darf nicht existieren

    //Zusammenfassen?
    //TODO: einzelne file names überprüfen in Argumenten, ob doppelt -> Melli
    //TODO: ob file names zu lang -> truncate()-Funktion: abschneiden nach letztem slash -> Melli

    //TODO: files existieren -> probeweise öffnen? -> Robin
    for (int i = 2; i < argNum; i++) {
        if (fileExists(argArray[i]) < 0) {
            return -1;
        }
    }


    //TODO: Größe gesamt < 30MB -> Leo
    // -> copy
    int totalSize = 0;
    for (int i = 2; i < argNum; i++) {
        totalSize += getFileSize(argArray[i]);
    }
    if (totalSize > (30 * 1024 * 1024)) {
        fprintf(stderr, "error: input files exceed 30MB");
    }


    // TODO: Implement file system generation & copying of files here
    
    return 0;
}

int fileExists(char* &fileName) {
    std::ifstream file(fileName, std::ifstream::in | std::ifstream::binary);

    if(!file.is_open()) {
        fprintf(stderr, "error: %s could not be opened or does not exist", fileName);
        return -1;
    }
    file.close();
    return 0;
}

int getFileSize(char* &fileName) {
    std::ifstream file(fileName, std::ifstream::in | std::ifstream::binary);

    if(!file.is_open()) {
        fprintf(stderr, "error: %s could not be opened or does not exist", fileName);
        return -1;
    }

    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.close();

    return fileSize;
}
