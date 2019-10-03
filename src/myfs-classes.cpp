//
// Created by melanie on 09.05.19.
//
#include "myfs-classes.h"

SuperBlock::SuperBlock(AbstractBlockDevice *blockdevice) {
    this->blockdevice = blockdevice;
    //TODO
}

SuperBlock::~SuperBlock() {
    free(this->superblock);
}

Dmap::Dmap(AbstractBlockDevice *blockDevice) {
    this->blockDevice = blockDevice;
    dmap = new uint8_t[7680];
    //TODO
}

Dmap::~Dmap() {
    delete[] dmap;
}

Fat::Fat(AbstractBlockDevice *blockDevice) {
    this->blockDevice = blockDevice;
    //TODO
}

Fat::~Fat() {
    free(this->fat);
}

File::File() {
    //TODO
}

File::~File() {
    //TODO
}

Root::Root(AbstractBlockDevice *blockDevice) {
    this->blockDevice = blockDevice;
    //TODO
}

Root::~Root() {
    free(this->root);
    //TODO
}

