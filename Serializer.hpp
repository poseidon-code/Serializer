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

#pragma once

#include <algorithm>
#include <bit>
#include <cmath>
#include <concepts>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>



enum class Endianness {
    BO_LITTLE_ENDIAN = 0,
    BO_BIG_ENDIAN
};


template <typename T>
concept serializable = std::is_arithmetic_v<T> || std::is_enum_v<T>;

template <typename T>
concept integral = std::integral<T>;



namespace Serializer {
template <
    serializable T,
    Endianness endianness = Endianness::BO_BIG_ENDIAN
>
class byte_t {
private:
    const uint8_t byte_size = sizeof(T);
    union {T value; uint8_t bytes[sizeof(T)];} byte_split;

    static void _serialize(uint8_t* stream, const uint8_t* bytes, uint8_t byte_size, size_t index_start) {
        if constexpr (((endianness == Endianness::BO_LITTLE_ENDIAN) ^ (std::endian::native == std::endian::little)) == 0) {
            std::copy(bytes, bytes + byte_size, stream + index_start);
        } else {
            std::reverse_copy(bytes, bytes + byte_size, stream + index_start);
        }
    };

    static void _deserialize(const uint8_t* stream, uint8_t* bytes, uint8_t byte_size, size_t index_start) {
        if constexpr (((endianness == Endianness::BO_LITTLE_ENDIAN) ^ (std::endian::native == std::endian::little)) == 0) {
            std::copy(stream + index_start, stream + index_start + byte_size, bytes);
        } else {
            std::reverse_copy(stream + index_start, stream + index_start + byte_size, bytes);
        }
    };

public:
    void serialize(uint8_t* stream, T value, size_t index_start = 0) {
        this->byte_split.value = value;
        _serialize(stream, this->byte_split.bytes, this->byte_size, index_start);
    }

    void serialize(std::vector<uint8_t>& stream, T value, size_t index_start = 0) {
        serialize(stream.data(), value, index_start);
    }

    std::vector<uint8_t> serialize(T value) {
        std::vector<uint8_t> buffer(this->byte_size, 0x00);
        serialize(buffer.data(), value, 0);
        return buffer;
    }

    T deserialize(const uint8_t* stream, size_t index_start = 0) {
        this->byte_split.value = 0;
        _deserialize(stream, this->byte_split.bytes, this->byte_size, index_start);
        return this->byte_split.value;
    }

    T deserialize(const std::vector<uint8_t>& stream, size_t index_start = 0) {
        return deserialize(stream.data(), index_start);
    }
};

template <integral T>
static float itof(T value, uint16_t precision) {return static_cast<float>(value) / std::pow(10, precision);}

template <integral T>
static double itod(T value, uint16_t precision) {return static_cast<double>(value) / std::pow(10, precision);}

template <integral T>
static T ftoi(float value, uint16_t precision) {return static_cast<T>(value * std::pow(10, precision));}

template <integral T>
static T dtoi(double value, uint16_t precision) {return static_cast<T>(value * std::pow(10, precision));}



class Stream {
private:
    std::vector<uint8_t> buffer;
    size_t index;

public:
    Stream() = delete;

    Stream(size_t length)
        : buffer(length, 0x00), index(0)
    {};

    Stream(const Stream& other)
        : buffer(other.buffer), index(other.index)
    {}

    Stream(Stream&& other) noexcept
        : buffer(std::move(other.buffer)), index(other.index)
    { other.index = 0; }

    Stream& operator=(const Stream& other) {
        if (this != &other) {
            this->buffer = other.buffer;
            this->index = other.index;
        }
        return *this;
    }

    Stream& operator=(Stream&& other) noexcept {
        if (this != &other) {
            this->buffer = std::move(other.buffer);
            this->index = other.index;
            other.index = 0;
        }
        return *this;
    }

    ~Stream() = default;

    std::vector<uint8_t> const get() const {
        return this->buffer;
    }

    Stream& operator<<(const std::vector<uint8_t>& buffer) {
        std::copy(buffer.begin(), buffer.end(), this->buffer.begin() + this->index);
        this->index += buffer.size();
        return *this;
    }

    void put(const uint8_t* buffer, size_t length, size_t index_start = 0) {
        std::copy(buffer, buffer + length, this->buffer.begin() + index_start);
        this->index = this->index + (index_start - this->index) + length;
    }

    void put(const std::vector<uint8_t>& buffer, size_t index_start = 0) {
        this->put(buffer.data(), buffer.size(), index_start);
    }
};



static void print(const uint8_t* stream, size_t length, std::string delimeter = " ") {
    std::cout << std::hex << std::uppercase << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
        std::cout << std::setw(2)  << static_cast<uint>(stream[i]) << (i == length - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
}

static void print(const std::vector<uint8_t>& stream, std::string delimeter = " ") {
    print(stream.data(), stream.size(), delimeter);
}

static void print(const Serializer::Stream& stream, std::string delimeter = " ") {
    print(stream.get().data(), stream.get().size(), delimeter);
}

static std::string sprint(const uint8_t* stream, size_t length, std::string delimeter = " ") {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
        oss << std::setw(2) << static_cast<uint>(stream[i]) << (i == length - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
    return oss.str();
}

static std::string sprint(const std::vector<uint8_t>& stream, std::string delimeter = " ") {
    return sprint(stream.data(), stream.size(), delimeter);
}

static std::string sprint(const Serializer::Stream& stream, std::string delimeter = " ") {
    return sprint(stream.get().data(), stream.get().size(), delimeter);
}
};


static Serializer::byte_t<uint8_t, Endianness::BO_BIG_ENDIAN>       ubyte_1_be;
static Serializer::byte_t<uint16_t, Endianness::BO_BIG_ENDIAN>      ubyte_2_be;
static Serializer::byte_t<uint32_t, Endianness::BO_BIG_ENDIAN>      ubyte_4_be;
static Serializer::byte_t<uint64_t, Endianness::BO_BIG_ENDIAN>      ubyte_8_be;
static Serializer::byte_t<int8_t, Endianness::BO_BIG_ENDIAN>        byte_1_be;
static Serializer::byte_t<int16_t, Endianness::BO_BIG_ENDIAN>       byte_2_be;
static Serializer::byte_t<int32_t, Endianness::BO_BIG_ENDIAN>       byte_4_be;
static Serializer::byte_t<int64_t, Endianness::BO_BIG_ENDIAN>       byte_8_be;
static Serializer::byte_t<float, Endianness::BO_BIG_ENDIAN>         fpbyte_4_be;
static Serializer::byte_t<double, Endianness::BO_BIG_ENDIAN>        fpbyte_8_be;

static Serializer::byte_t<uint8_t, Endianness::BO_LITTLE_ENDIAN>    ubyte_1_le;
static Serializer::byte_t<uint16_t, Endianness::BO_LITTLE_ENDIAN>   ubyte_2_le;
static Serializer::byte_t<uint32_t, Endianness::BO_LITTLE_ENDIAN>   ubyte_4_le;
static Serializer::byte_t<uint64_t, Endianness::BO_LITTLE_ENDIAN>   ubyte_8_le;
static Serializer::byte_t<int8_t, Endianness::BO_LITTLE_ENDIAN>     byte_1_le;
static Serializer::byte_t<int16_t, Endianness::BO_LITTLE_ENDIAN>    byte_2_le;
static Serializer::byte_t<int32_t, Endianness::BO_LITTLE_ENDIAN>    byte_4_le;
static Serializer::byte_t<int64_t, Endianness::BO_LITTLE_ENDIAN>    byte_8_le;
static Serializer::byte_t<float, Endianness::BO_LITTLE_ENDIAN>      fpbyte_4_le;
static Serializer::byte_t<double, Endianness::BO_LITTLE_ENDIAN>     fpbyte_8_le;
