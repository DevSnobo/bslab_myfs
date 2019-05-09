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

    if (argNum > 66) {
        fprintf(stderr, "error: too many arguments! 64 files max");
        fprintf(stderr, "usage: mkfs.myfs containerfile [<file-to-copy>, ...]");
    }

    //TODO: container darf nicht existieren

    //Zusammenfassen?
    //TODO: einzelne file names überprüfen in Argumenten, ob doppelt -> Melli
    //TODO: ob file names zu lang -> truncate()-Funktion: abschneiden nach letztem slash -> Melli

    //TODO: files existieren -> probeweise öffnen? -> Robin

    //TODO: Größe gesamt < 30MB -> Leo
    // -> copy






    // TODO: Implement file system generation & copying of files here
    
    return 0;
}
