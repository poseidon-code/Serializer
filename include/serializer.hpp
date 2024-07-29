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

#include <cstdint>
#include <string>
#include <vector>


enum Endianness {
    BO_LITTLE_ENDIAN,
    BO_BIG_ENDIAN
};


namespace serializer {
    constexpr bool _is_system_little_endian() {
        union {int16_t value; uint8_t bytes[sizeof(value)];} x;
        x.value = 1;
        return x.bytes[0] == 1;
    };



    template <typename T, Endianness endianness = Endianness::BO_BIG_ENDIAN>
    class byte_t {
    private:
        static const uint8_t byte_size = sizeof(T);

        static union {
            T value;
            uint8_t bytes[sizeof(T)];
        } t;

        static void _serialize(uint8_t* stream, const uint8_t* bytes, uint8_t byte_size, size_t index_start) {
            if constexpr (endianness == Endianness::BO_LITTLE_ENDIAN && _is_system_little_endian()) {
                std::copy(bytes, bytes + byte_size, stream + index_start);
            } else {
                std::reverse_copy(bytes, bytes + byte_size, stream + index_start);
            }
        };

        static void _deserialize(const uint8_t* stream, uint8_t* bytes, uint8_t byte_size, size_t index_start) {
            if constexpr (endianness == Endianness::BO_LITTLE_ENDIAN && _is_system_little_endian()) {
                std::copy(stream + index_start, stream + index_start + byte_size, bytes);
            } else {
                std::reverse_copy(stream + index_start, stream + index_start + byte_size, bytes);
            }
        };

    public:
        static void serialize(uint8_t* stream, T value, size_t index_start = 0) {
            t.value = value;
            _serialize(stream, t.bytes, byte_size, index_start);
        }

        static void serialize(std::vector<uint8_t>& stream, T value, size_t index_start = 0) {
            serialize(stream.data(), value, index_start);
        }

        static std::vector<uint8_t> serialize(T value) {
            std::vector<uint8_t> buffer(byte_size, 0x00);
            serialize(buffer.data(), value, 0);
            return buffer;
        }

        static T deserialize(const uint8_t* stream, size_t index_start = 0) {
            t.value = 0;
            _deserialize(stream, t.bytes, byte_size, index_start);
            return t.value;
        }

        static T deserialize(const std::vector<uint8_t>& stream, size_t index_start = 0) {
            return deserialize(stream.data(), index_start);
        }
    };


    static byte_t<uint8_t, Endianness::BO_BIG_ENDIAN> ubyte_1_be;
    static byte_t<uint16_t, Endianness::BO_BIG_ENDIAN> ubyte_2_be;
    static byte_t<uint32_t, Endianness::BO_BIG_ENDIAN> ubyte_4_be;
    static byte_t<uint64_t, Endianness::BO_BIG_ENDIAN> ubyte_8_be;
    static byte_t<int8_t, Endianness::BO_BIG_ENDIAN> byte_1_be;
    static byte_t<int16_t, Endianness::BO_BIG_ENDIAN> byte_2_be;
    static byte_t<int32_t, Endianness::BO_BIG_ENDIAN> byte_4_be;
    static byte_t<int64_t, Endianness::BO_BIG_ENDIAN> byte_8_be;
    static byte_t<float, Endianness::BO_BIG_ENDIAN> fpbyte_4_be;
    static byte_t<double, Endianness::BO_BIG_ENDIAN> fpbyte_8_be;

    static byte_t<uint8_t, Endianness::BO_LITTLE_ENDIAN> ubyte_1_le;
    static byte_t<uint16_t, Endianness::BO_LITTLE_ENDIAN> ubyte_2_le;
    static byte_t<uint32_t, Endianness::BO_LITTLE_ENDIAN> ubyte_4_le;
    static byte_t<uint64_t, Endianness::BO_LITTLE_ENDIAN> ubyte_8_le;
    static byte_t<int8_t, Endianness::BO_LITTLE_ENDIAN> byte_1_le;
    static byte_t<int16_t, Endianness::BO_LITTLE_ENDIAN> byte_2_le;
    static byte_t<int32_t, Endianness::BO_LITTLE_ENDIAN> byte_4_le;
    static byte_t<int64_t, Endianness::BO_LITTLE_ENDIAN> byte_8_le;
    static byte_t<float, Endianness::BO_LITTLE_ENDIAN> fpbyte_4_le;
    static byte_t<double, Endianness::BO_LITTLE_ENDIAN> fpbyte_8_le;


    class stream {
    private:
        std::vector<uint8_t> buffer;
        size_t index;

    public:
        stream() = delete;
        stream(size_t length);
        stream(const stream& other);
        stream(stream&& other) noexcept;
        stream& operator=(const stream& other);
        stream& operator=(stream&& other) noexcept;
        ~stream() = default;

        std::vector<uint8_t> const get() const;
        stream& operator<<(const std::vector<uint8_t>& buffer);
        void put(const uint8_t* buffer, size_t length, size_t index_start = 0);
        void put(const std::vector<uint8_t>& buffer, size_t index_start = 0);
    };



    void print(const uint8_t* stream, size_t length, std::string delimeter = " ");
    void print(const std::vector<uint8_t>& stream, std::string delimeter = " ");
    void print(const serializer::stream& stream, std::string delimeter = " ");
    std::string sprint(const uint8_t* stream, size_t length, std::string delimeter = " ");
    std::string sprint(const std::vector<uint8_t>& stream, std::string delimeter = " ");
    std::string sprint(const serializer::stream& stream, std::string delimeter = " ");
}
