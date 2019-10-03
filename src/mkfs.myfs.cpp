//
//  mk.myfs.cpp
//  myfs
//
//  Created by Oliver Waldhorst on 07.09.17.
//  Copyright © 2017 Oliver Waldhorst. All rights reserved.
//
#include <string.h>
#include <stdint.h>
#include "myfs.h"
#include "blockdevice.h"
#include "macros.h"
#include <fstream>
#include <iostream>
using namespace std;

struct TestStruct {
    size_t x, y, z;
};


int fileExists(const char* fileName);
int getFileSize(const char* &fileName);

int main(int argNum, const char *argArray[]) {

    MyFS* instance = new MyFS();

    if (argNum < 2) {
        fprintf(stderr, "error: too few arguments");
        fprintf(stderr, "usage: mkfs.myfs containerfile [<file-to-copy>, ...]");
        return -1;
    }

    if (argNum > 66) {
        fprintf(stderr, "error: too many arguments! 64 files max");
        fprintf(stderr, "usage: mkfs.myfs containerfile [<file-to-copy>, ...]");
        return -1;
    }

    for (int i = 2; i < argNum - 1; i++) {
        if (strcmp(instance->getFileName(*(argArray + i)), instance->getFileName(*(argArray + i + 1))) == 0) {
            fprintf(stderr, "error: duplicate files are not allowed\n");
            return -1;
        }
        if (strlen(instance->getFileName(*(argArray + i))) > 255) {
            fprintf(stderr, "error: filename too long!");
            return -1;
        }
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

    printf("%s", "success");

    // TODO: Implement file system generation & copying of files here
    AbstractBlockDevice device("/path/to/container/file", BLOCK_SIZE);



    TestStruct a = { .x = 21, .y = 42, .z = 1337 };
    TestStruct b;
    device.write(a, 0);
    device.read(b, 0);
    std::cout << b.x << " " << b.y << " " << b.z << std::endl;

    const char* just_a_string = "i'm just a boring string which likes being boring";
    char buffer_for_just_a_string[100];
    device.write(just_a_string, 10, strlen(just_a_string) + 1);
    device.read(buffer_for_just_a_string, 10, strlen(just_a_string) + 1);
    std::cout << buffer_for_just_a_string << std::endl;

    unsigned int int_array[] = { 42, 21, 1337, 1234, 4711 };
    unsigned int int_array_read[sizeof(int_array) / sizeof(int_array[0])];
    device.write(int_array, 3);
    device.read(int_array_read, 3);

    for (size_t index = 0; index < sizeof(int_array_read) / sizeof(int_array_read[0]); ++index) {
        std::cout << int_array_read[index] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}

int fileExists(const char* fileName) {
    std::ifstream file(fileName, std::ifstream::in | std::ifstream::binary);

    if(!file.is_open()) {
        fprintf(stderr, "error: %s could not be opened or does not exist", fileName);
        return -1;
    }
    file.close();
    return 0;
}

int getFileSize(const char* &fileName) {
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
