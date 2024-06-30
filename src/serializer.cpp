#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "serializer.hpp"


void serializer::print(const unsigned char* stream, int length, std::string delimeter) {
    std::cout << std::hex << std::uppercase << std::setfill('0');
    for (int i = 0; i < length; ++i) std::cout << std::setw(2)  << static_cast<uint>(stream[i]) << (i == length - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
}

void serializer::print(const std::vector<unsigned char>& stream, std::string delimeter) {
    std::cout << std::hex << std::uppercase << std::setfill('0');
    for (int i = 0; i < stream.size(); ++i) std::cout << std::setw(2)  << static_cast<uint>(stream[i]) << (i == stream.size() - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
}

void serializer::print(const serializer::stream& stream, std::string delimeter) {
    std::cout << std::hex << std::uppercase << std::setfill('0');
    for (int i = 0; i < stream.get().size(); ++i) std::cout << std::setw(2)  << static_cast<uint>(stream.get()[i]) << (i == stream.get().size() - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
}

std::string serializer::sprint(const unsigned char* stream, int length, std::string delimeter) {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0');
    for (int i = 0; i < length; ++i) oss << std::setw(2) << static_cast<uint>(stream[i]) << (i == length - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
    return oss.str();
}

std::string serializer::sprint(const std::vector<unsigned char>& stream, std::string delimeter) {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0');
    for (int i = 0; i < stream.size(); ++i) oss << std::setw(2) << static_cast<uint>(stream[i]) << (i == stream.size() - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
    return oss.str();
}

std::string serializer::sprint(const serializer::stream& stream, std::string delimeter) {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0');
    for (int i = 0; i < stream.get().size(); ++i) oss << std::setw(2) << static_cast<uint>(stream.get().data()[i]) << (i == stream.get().size() - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
    return oss.str();
}

void _serialize(
    unsigned char* stream,
    unsigned char* bytes,
    uint8_t byte_size,
    uint index_start,
    serializer::Endianness endianness
) {
    if (endianness == serializer::Endianness::BO_LITTLE_ENDIAN) {
        for (uint8_t i = 0; i < byte_size; ++i)
            stream[index_start + i] = bytes[i];
    } else {
        for (uint8_t i = 0; i < byte_size; ++i)
            stream[index_start + i] = bytes[byte_size - 1 - i];
    }
}

void _deserialize(
    const unsigned char* stream,
    unsigned char* bytes,
    uint8_t byte_size,
    uint index_start,
    serializer::Endianness endianness
) {
    if (endianness == serializer::Endianness::BO_LITTLE_ENDIAN) {
        for (uint8_t i = 0; i < byte_size; ++i)
            bytes[i] = stream[index_start + i];
    } else {
        for (uint8_t i = 0; i < byte_size; ++i)
            bytes[byte_size - 1 - i] = stream[index_start + i];
    }
}
