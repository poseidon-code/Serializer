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
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Stream.hpp"



Serializer::Stream::Stream(size_t length)
    : buffer(length, 0x00), index(0)
{}

Serializer::Stream::Stream(const Serializer::Stream& other)
    : buffer(other.buffer), index(other.index)
{}

Serializer::Stream::Stream(Serializer::Stream&& other) noexcept
    : buffer(std::move(other.buffer)), index(other.index)
{ other.index = 0; }

Serializer::Stream& Serializer::Stream::operator=(const Serializer::Stream& other) {
    if (this != &other) {
        this->buffer = other.buffer;
        this->index = other.index;
    }
    return *this;
}

Serializer::Stream& Serializer::Stream::operator=(Serializer::Stream&& other) noexcept {
    if (this != &other) {
        this->buffer = std::move(other.buffer);
        this->index = other.index;
        other.index = 0;
    }
    return *this;
}

std::vector<uint8_t> const Serializer::Stream::get() const {
    return this->buffer;
}

Serializer::Stream& Serializer::Stream::operator<<(const std::vector<uint8_t>& buffer) {
    std::copy(buffer.begin(), buffer.end(), this->buffer.begin() + this->index);
    this->index += buffer.size();
    return *this;
}

void Serializer::Stream::put(const uint8_t* buffer, size_t length, size_t index_start) {
    std::copy(buffer, buffer + length, this->buffer.begin() + index_start);
    this->index = this->index + (index_start - this->index) + length;
}

void Serializer::Stream::put(const std::vector<uint8_t>& buffer, size_t index_start) {
    this->put(buffer.data(), buffer.size(), index_start);
}

void Serializer::print(const Serializer::Stream& stream, std::string delimeter) {
    const uint8_t* t_stream = stream.get().data();
    const size_t length = stream.get().size();

    std::cout << std::hex << std::uppercase << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
        std::cout << std::setw(2)  << static_cast<uint>(t_stream[i]) << (i == length - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
}

std::string Serializer::sprint(const Serializer::Stream& stream, std::string delimeter) {
    const uint8_t* t_stream = stream.get().data();
    const size_t length = stream.get().size();

    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
        oss << std::setw(2) << static_cast<uint>(t_stream[i]) << (i == length - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
    return oss.str();
}
