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
#include <iomanip>
#include <iostream>
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
        const uint8_t byte_size = sizeof(T);

        union {
            T value;
            uint8_t bytes[sizeof(T)];
        } t;

    public:
        void serialize(uint8_t* stream, T value, size_t index_start = 0) {
            static auto _serialize = [](uint8_t* stream, const uint8_t* bytes, uint8_t byte_size, size_t index_start) {
                if (endianness == Endianness::BO_LITTLE_ENDIAN && _is_system_little_endian()) {
                    std::copy(bytes, bytes + byte_size, stream + index_start);
                } else {
                    std::reverse_copy(bytes, bytes + byte_size, stream + index_start);
                }
            };

            this->t.value = value;
            _serialize(stream, this->t.bytes, this->byte_size, index_start);
        }

        void serialize(std::vector<uint8_t>& stream, T value, size_t index_start = 0) {
            this->serialize(stream.data(), value, index_start);
        }

        std::vector<uint8_t> serialize(T value) {
            std::vector<uint8_t> buffer(this->byte_size, 0x00);
            this->serialize(buffer.data(), value, 0);
            return buffer;
        }

        T deserialize(const uint8_t* stream, size_t index_start = 0) {
            static auto _deserialize = [](const uint8_t* stream, uint8_t* bytes, uint8_t byte_size, size_t index_start) {
                if (endianness == Endianness::BO_LITTLE_ENDIAN && _is_system_little_endian()) {
                    std::copy(stream + index_start, stream + index_start + byte_size, bytes);
                } else {
                    std::reverse_copy(stream + index_start, stream + index_start + byte_size, bytes);
                }
            };

            this->t.value = 0;
            _deserialize(stream, this->t.bytes, this->byte_size, index_start);
            return t.value;
        }

        T deserialize(const std::vector<uint8_t>& stream, size_t index_start = 0) {
            return this->deserialize(stream.data(), index_start);
        }

        friend std::ostream& operator<<(std::ostream& os, const byte_t& byte) {
            os << "0x ";
            os << std::hex << std::uppercase << std::setfill('0');
            for (uint8_t i = 0; i < byte.byte_size; ++i) {
                if (endianness == Endianness::BO_LITTLE_ENDIAN && _is_system_little_endian()) {
                    os << std::setw(2) << static_cast<uint16_t>(byte.t.bytes[i]);
                } else {
                    os << std::setw(2) << static_cast<uint16_t>(byte.t.bytes[byte.byte_size - 1 - i]);
                }

                if (i != byte.byte_size - 1) os << " ";
            }
            os << std::dec << std::nouppercase << std::setfill(' ');
            return os;
        }
    };


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
