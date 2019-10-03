

#include "abstractblockdevice.h"
#include <alloca.h>

AbstractBlockDevice::AbstractBlockDevice(const char* path, size_t block_size) : blockdevice(block_size), block_size(block_size) {
    if (this->blockdevice.open(path) < 0 && this->blockdevice.create(path) < 0) throw 1; //TODO: exception, errorcode
}

AbstractBlockDevice::~AbstractBlockDevice() {
    this->blockdevice.close();
}

size_t AbstractBlockDevice::typeErasedRead(void* destination, size_t start_block, size_t size) const {
    size_t block = start_block;
    char* write_pointer = static_cast<char*>(destination);
    char* buffer = reinterpret_cast<char*>(alloca(this->block_size));

    for (; size > 0; ++block) {
        size_t relevant_bytes = (size > this->block_size ? this->block_size : size);

        if (size >= this->block_size) const_cast<BlockDevice*>(&this->blockdevice)->read(block, write_pointer);
        else {
            const_cast<BlockDevice*>(&this->blockdevice)->read(block, buffer);
            std::memcpy(write_pointer, buffer, relevant_bytes);
        }

        write_pointer += relevant_bytes;
        size -= relevant_bytes;
    }

    return block - start_block;
}


size_t AbstractBlockDevice::typeErasedWrite(const void* source, size_t start_block, size_t size) {
    size_t block = start_block;
    const char* read_pointer = static_cast<const char*>(source);
    char* buffer = reinterpret_cast<char*>(alloca(this->block_size));

    for (; size > 0; ++block) {
        size_t relevant_bytes = (size > this->block_size ? this->block_size : size);
        if (size >= this->block_size) this->blockdevice.write(block, const_cast<char*>(read_pointer));
        else {
            std::memcpy(buffer, read_pointer, relevant_bytes);
            this->blockdevice.write(block, const_cast<char*>(buffer));
        }

        read_pointer += relevant_bytes;
        size -= relevant_bytes;
    }

    return block - start_block;
}
