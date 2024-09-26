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
#include <cmath>
#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>



enum class Endianness {
    BO_LITTLE_ENDIAN = 0,
    BO_BIG_ENDIAN
};


template <typename T>
using enable_if_serializable = typename std::enable_if<std::integral_constant<bool, std::is_arithmetic<T>::value || std::is_enum<T>::value>::value, int>::type;


namespace Serializer {
static constexpr bool _is_system_little_endian() {
    union {int16_t value; uint8_t bytes[sizeof(value)];} x{};
    x.value = 1;
    return x.bytes[0] == 1;
};

template <
    typename T,
    Endianness endianness = Endianness::BO_BIG_ENDIAN,
    enable_if_serializable<T> = 0
>
class byte_t {
private:
    const uint8_t byte_size = sizeof(T);
    union {T value; uint8_t bytes[sizeof(T)];} byte_split;

    static inline void _serialize(uint8_t* stream, const uint8_t* bytes, uint8_t byte_size, size_t index_start) {
        if constexpr (((endianness == Endianness::BO_LITTLE_ENDIAN) ^ _is_system_little_endian()) == 0) {
            std::copy(bytes, bytes + byte_size, stream + index_start);
        } else {
            std::reverse_copy(bytes, bytes + byte_size, stream + index_start);
        }
    };

    static inline void _deserialize(const uint8_t* stream, uint8_t* bytes, uint8_t byte_size, size_t index_start) {
        if constexpr (((endianness == Endianness::BO_LITTLE_ENDIAN) ^ _is_system_little_endian()) == 0) {
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
}


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
