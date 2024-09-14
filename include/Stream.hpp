/*
Serializer : A modern C++ binary data serializer library.
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

#pragma once

#include <cstdint>
#include <vector>
#include <string>


namespace Serializer {
class Stream {
private:
    std::vector<uint8_t> buffer;
    size_t index;

public:
    Stream() = delete;
    Stream(size_t length);
    Stream(const Stream& other);
    Stream(Stream&& other) noexcept;
    Stream& operator=(const Stream& other);
    Stream& operator=(Stream&& other) noexcept;
    ~Stream() = default;

    std::vector<uint8_t> const get() const;
    Stream& operator<<(const std::vector<uint8_t>& buffer);
    void put(const uint8_t* buffer, size_t length, size_t index_start = 0);
    void put(const std::vector<uint8_t>& buffer, size_t index_start = 0);
};

static void print(const Serializer::Stream& stream, std::string delimeter = " ");
static std::string sprint(const Serializer::Stream& stream, std::string delimeter = " ");
}
