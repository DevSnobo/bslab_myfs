//
//  myfs-classes.h
//  myfs
//
//  Created by Oliver Waldhorst on 07.09.17.
//  Copyright © 2017 Oliver Waldhorst. All rights reserved.
//

#ifndef myfs_classes_h
#define myfs_classes_h
#include <stdint.h>
#include "abstractblockdevice.h"
#define NAME_LENGTH 255
#define BLOCK_SIZE 512
#define NUM_DIR_ENTRIES 64
#define NUM_OPEN_FILES 64

// TODO: Add structures of your file system here
// TODO: wars das? besprechen
#define SIZE_SUPER 1
#define SIZE_DMAP 15
#define SIZE_FAT 240
#define SIZE_ROOT 64
#define SIZE_DATA 61440

#define START_SUPER 0
#define START_DMAP (SIZE_SUPER + START_SUPER) // 1
#define START_FAT (SIZE_DMAP + START_DMAP)  // 16
#define START_ROOT (SIZE_FAT + START_FAT)  // 256
#define START_DATA (SIZE_ROOT + START_ROOT)  // 320

#define MAGICNUMBER 0xBADCODED

enum class Initialization {
    DEFAULT_INIT,
    DEVICE_INIT
};

class SuperBlock {

private:
    struct {
        uint32_t magicnumber;
    } persistable_items;
    AbstractBlockDevice* blockdevice;
    uint16_t blockSize = BLOCK_SIZE;
    uint16_t sizeFs = SIZE_SUPER + SIZE_DMAP + SIZE_FAT + SIZE_ROOT + SIZE_DATA;
    uint8_t sizeSuper = SIZE_SUPER;
    uint8_t sizeDmap = SIZE_DMAP;
    uint8_t sizeFat = SIZE_FAT;
    uint8_t sizeRoot = SIZE_ROOT;
    uint16_t size_data = SIZE_DATA;

    uint8_t posSuper = START_SUPER;
    uint8_t posDmap = START_DMAP;
    uint8_t posFat = START_FAT;
    uint16_t posRoot = START_ROOT;
    uint16_t posData = START_DATA;
    uint8_t currFilesCount;
    uint8_t currOpenFilesCount;

    public:
        SuperBlock(AbstractBlockDevice* blockdevice); //Blockdevice wird wegen read()-Methode mitgegeben


};

class Dmap {
    private:
        AbstractBlockDevice* blockDevice;
        uint8_t* dmap; //15 blöcke dmap * 512 byte pro Block -> bitmap
    public:
        Dmap(AbstractBlockDevice* blockDevice);
        ~Dmap();
};

class Fat {
    private:
        AbstractBlockDevice* blockDevice;
        uint16_t fat[61140];
    public:
        Fat(AbstractBlockDevice* blockDevice);
        ~Fat();
};

class File {
private:
    char *fileName;
    uint16_t fileSize;
    uint32_t userId;
    uint32_t groupId;
    uint16_t permissions;
    uint64_t atime; //letzer Zugriff
    uint64_t mtime; //letze Änderung
    uint64_t ctime; //letzte Statusänderung
    uint16_t firstBlock;
public:
    File();

    ~File();

};

class Root {
    private:
        AbstractBlockDevice* blockDevice;
        File root[64];
    public:
        Root(AbstractBlockDevice* blockDevice);
        ~Root();
};


#endif /* myfs_classes_h */
