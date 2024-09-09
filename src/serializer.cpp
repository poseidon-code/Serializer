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

Author : Pritam Halder
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


void Serializer::print(const uint8_t* stream, size_t length, std::string delimeter) {
    std::cout << std::hex << std::uppercase << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
        std::cout << std::setw(2)  << static_cast<uint>(stream[i]) << (i == length - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
}


void Serializer::print(const std::vector<uint8_t>& stream, std::string delimeter) {
    Serializer::print(stream.data(), stream.size(), delimeter);
}


void Serializer::print(const Serializer::Stream& stream, std::string delimeter) {
    Serializer::print(stream.get().data(), stream.get().size(), delimeter);
}


std::string Serializer::sprint(const uint8_t* stream, size_t length, std::string delimeter) {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
        oss << std::setw(2) << static_cast<uint>(stream[i]) << (i == length - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
    return oss.str();
}


std::string Serializer::sprint(const std::vector<uint8_t>& stream, std::string delimeter) {
    return Serializer::sprint(stream.data(), stream.size(), delimeter);
}


std::string Serializer::sprint(const Serializer::Stream& stream, std::string delimeter) {
    return Serializer::sprint(stream.get().data(), stream.get().size(), delimeter);
}
