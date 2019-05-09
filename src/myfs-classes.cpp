//
// Created by melanie on 09.05.19.
//
#include "myfs-classes.h"

SuperBlock::SuperBlock(BlockDevice *blockDevice) {
    this->blockDevice = blockDevice;
    //TODO
}

SuperBlock::~SuperBlock() {
    free(this->superblock);
}

Dmap::Dmap(BlockDevice *blockDevice) {
    this->blockDevice = blockDevice;
    //TODO
}

Dmap::~Dmap() {
    free(this->dmap);
}

Fat::Fat(BlockDevice *blockDevice) {
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

Root::Root(BlockDevice *blockDevice) {
    this->blockDevice = blockDevice;
    //TODO
}

Root::~Root() {
    free(this->root);
    //TODO
}

