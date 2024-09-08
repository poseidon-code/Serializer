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
#include <vector>

#include "serializer.hpp"



Serializer::stream::stream(size_t length)
    : buffer(length, 0x00), index(0)
{}

Serializer::stream::stream(const Serializer::stream& other)
    : buffer(other.buffer), index(other.index)
{}

Serializer::stream::stream(Serializer::stream&& other) noexcept
    : buffer(std::move(other.buffer)), index(other.index)
{ other.index = 0; }

Serializer::stream& Serializer::stream::operator=(const Serializer::stream& other) {
    if (this != &other) {
        this->buffer = other.buffer;
        this->index = other.index;
    }
    return *this;
}

Serializer::stream& Serializer::stream::operator=(Serializer::stream&& other) noexcept {
    if (this != &other) {
        this->buffer = std::move(other.buffer);
        this->index = other.index;
        other.index = 0;
    }
    return *this;
}

std::vector<uint8_t> const Serializer::stream::get() const {
    return this->buffer;
}

Serializer::stream& Serializer::stream::operator<<(const std::vector<uint8_t>& buffer) {
    std::copy(buffer.begin(), buffer.end(), this->buffer.begin() + this->index);
    this->index += buffer.size();
    return *this;
}

void Serializer::stream::put(const uint8_t* buffer, size_t length, size_t index_start) {
    std::copy(buffer, buffer + length, this->buffer.begin() + index_start);
    this->index = this->index + (index_start - this->index) + length;
}

void Serializer::stream::put(const std::vector<uint8_t>& buffer, size_t index_start) {
    this->put(buffer.data(), buffer.size(), index_start);
}
