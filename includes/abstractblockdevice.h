//
// Created by melanie on 26.07.19.
//

#ifndef FILESYSTEM_ABSTRACTBLOCKDEVICE_H
#define FILESYSTEM_ABSTRACTBLOCKDEVICE_H

#include <type_traits>
#include <cstring>
#include "blockdevice.h"

class AbstractBlockDevice {
private:

    BlockDevice blockdevice;
    size_t block_size;


    size_t typeErasedRead(void* destination, size_t start_block, size_t size) const;

    size_t typeErasedWrite(const void* source, size_t start_block, size_t size);


public:

    AbstractBlockDevice(const char* path, size_t block_size);
    ~AbstractBlockDevice();

    template<typename T> inline typename std::enable_if<std::is_pointer<T>::value, size_t>::type read(T destination, size_t block, size_t count = 1) const {
        static_assert(std::is_trivially_copyable<T>::value, "Reading a persisted instance of T would result in erroneous behaviour");

        return this->typeErasedRead(destination, block, sizeof(typename std::remove_pointer<T>::type) * count);
    }


    template<typename T> inline typename std::enable_if<!std::is_array<T>::value && !std::is_pointer<T>::value, size_t>::type read(T& destination, size_t block) const {
        return this->read(&destination, block);
    }


    template<typename T, size_t N> inline size_t read(T (&destination)[N], size_t block) const {
        return this->read(&destination[0], block, N);
    }


    template<typename T> inline typename std::enable_if<std::is_pointer<T>::value, size_t>::type write(const T source, size_t block, size_t count = 1) {
        static_assert(std::is_trivially_copyable<T>::value, "Persisting an instance of T would result in erroneous behaviour");

        return this->typeErasedWrite(source, block, sizeof(typename std::remove_pointer<T>::type) * count);
    }


    template<typename T> inline typename std::enable_if<!std::is_array<T>::value && !std::is_pointer<T>::value, size_t>::type write(const T& source, size_t block) {
        return this->write(&source, block);
    }


    template<typename T, size_t N> inline size_t write(const T (&source)[N], size_t block) {
        return this->write(&source[0], block, N);
    }

};
#endif //FILESYSTEM_ABSTRACTBLOCKDEVICE_H