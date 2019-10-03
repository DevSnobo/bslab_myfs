//
// Created by melanie on 26.07.19.
//

int main(int argc, char* argv[]) {
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


}
