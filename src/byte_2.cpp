#include <iomanip>
#include <iostream>

#include "serializer.hpp"


serializer::byte_2::byte_2(serializer::Endianness endianness)
    : endianness(endianness)
{}

std::vector<unsigned char> serializer::byte_2::serialize(int16_t value) {
    std::vector<unsigned char> buffer(this->byte_size, 0x00);
    this->t.value = value;
    _serialize(buffer.data(), this->t.bytes, this->byte_size, 0, this->endianness);
    return buffer;
}

void serializer::byte_2::serialize(unsigned char* stream, int16_t value, size_t index_start) {
    this->t.value = value;
    _serialize(stream, this->t.bytes, this->byte_size, index_start, this->endianness);
}

void serializer::byte_2::serialize(std::vector<unsigned char>& stream, int16_t value, size_t index_start) {
    this->t.value = value;
    _serialize(stream.data(), this->t.bytes, this->byte_size, index_start, this->endianness);
}

int16_t serializer::byte_2::deserialize(const unsigned char* stream, size_t index_start) {
    this->t.value = 0;
    _deserialize(stream, this->t.bytes, this->byte_size, index_start, this->endianness);
    return t.value;
}

int16_t serializer::byte_2::deserialize(const std::vector<unsigned char>& stream, size_t index_start) {
    this->t.value = 0;
    _deserialize(stream.data(), this->t.bytes, this->byte_size, index_start, this->endianness);
    return t.value;
}

std::ostream& serializer::operator<<(std::ostream& os, const byte_2& byte) {
    os << "0x ";
    os << std::hex << std::uppercase << std::setfill('0');
    for (uint8_t i = 0; i < byte.byte_size; ++i) {
        if (byte.endianness == serializer::Endianness::BO_LITTLE_ENDIAN)
            os << std::setw(2) << static_cast<uint16_t>(byte.t.bytes[i]) << (i == byte.byte_size - 1 ? "" : " ");
        else
            os << std::setw(2) << static_cast<uint16_t>(byte.t.bytes[byte.byte_size - 1 - i]) << (i == byte.byte_size - 1 ? "" : " ");
    }
    os << std::dec << std::nouppercase << std::setfill(' ');
    return os;
}
