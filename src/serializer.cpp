/*
serializer : A modern C++ binary data serializer library.
Copyright (C) 2024  Pritam Halder

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

Name : Pritam Halder
Email : pritamhalder.portfolio@gmail.com
*/

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "serializer.hpp"



void serializer::_serialize(uint8_t* stream, const uint8_t* bytes, uint8_t byte_size, size_t index_start, Endianness endianness) {
    if (endianness == Endianness::BO_LITTLE_ENDIAN && _is_system_little_endian()) {
        std::copy(bytes, bytes + byte_size, stream + index_start);
    } else {
        std::reverse_copy(bytes, bytes + byte_size, stream + index_start);
    }
}


void serializer::_deserialize(const uint8_t* stream, uint8_t* bytes, uint8_t byte_size, size_t index_start, Endianness endianness) {
    if (endianness == Endianness::BO_LITTLE_ENDIAN && _is_system_little_endian()) {
        std::copy(stream + index_start, stream + index_start + byte_size, bytes);
    } else {
        std::reverse_copy(stream + index_start, stream + index_start + byte_size, bytes);
    }
}


void serializer::print(const uint8_t* stream, size_t length, std::string delimeter) {
    std::cout << std::hex << std::uppercase << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
        std::cout << std::setw(2)  << static_cast<uint>(stream[i]) << (i == length - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
}


void serializer::print(const std::vector<uint8_t>& stream, std::string delimeter) {
    serializer::print(stream.data(), stream.size(), delimeter);
}


void serializer::print(const serializer::stream& stream, std::string delimeter) {
    serializer::print(stream.get().data(), stream.get().size(), delimeter);
}

std::string serializer::sprint(const uint8_t* stream, size_t length, std::string delimeter) {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
        oss << std::setw(2) << static_cast<uint>(stream[i]) << (i == length - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
    return oss.str();
}


std::string serializer::sprint(const std::vector<uint8_t>& stream, std::string delimeter) {
    return serializer::sprint(stream.data(), stream.size(), delimeter);
}


std::string serializer::sprint(const serializer::stream& stream, std::string delimeter) {
    return serializer::sprint(stream.get().data(), stream.get().size(), delimeter);
}
