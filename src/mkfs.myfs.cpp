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

int main(int argNum, char *argArray[]) {

    if (argNum < 2) {
        fprintf(stderr, "error: too few arguments");
        fprintf(stderr, "usage: mkfs.myfs containerfile [<file-to-copy>, ...]");
    }
    //TODO: container darf nicht existieren
    //TODO: einzelne file names überprüfen in Argumenten, ob doppelt
    //TODO: files existieren -> probeweise öffnen?
    //TODO: ob file names zu lang
    //TODO: Größe gesamt < 30MB
    //TODO: max files 64 (max args 66)
    // -> copy






    // TODO: Implement file system generation & copying of files here
    
    return 0;
}
