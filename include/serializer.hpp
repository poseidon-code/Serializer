#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>


namespace serializer {
    enum Endianness {
        BO_LITTLE_ENDIAN,
        BO_BIG_ENDIAN
    };


    class stream {
    private:
        std::vector<unsigned char> buffer;
        size_t index;

    public:
        stream() = delete;
        stream(size_t length);

        std::vector<unsigned char> const get() const;
        stream& operator<<(const std::vector<unsigned char>& buffer);
        void put(const std::vector<unsigned char>& buffer, size_t index_start = 0);
        void put(const unsigned char* buffer, size_t length, size_t index_start = 0);
    };


    class byte_8 {
    private:
        Endianness endianness;
        const uint8_t byte_size = 8;

        union {
            int64_t value;
            unsigned char bytes[8];
        } t;

    public:
        byte_8(Endianness endianness = Endianness::BO_BIG_ENDIAN);

        std::vector<unsigned char> serialize(int64_t value);
        void serialize(unsigned char* stream, int64_t value, size_t index_start = 0);
        void serialize(std::vector<unsigned char>& stream, int64_t value, size_t index_start = 0);
        int64_t deserialize(const unsigned char* stream, size_t index_start = 0);
        int64_t deserialize(const std::vector<unsigned char>& stream, size_t index_start = 0);
        friend std::ostream& operator<<(std::ostream& os, const byte_8& byte);
    };

    std::ostream& operator<<(std::ostream& os, const byte_8& byte);


    class byte_4 {
    private:
        Endianness endianness;
        const uint8_t byte_size = 4;

        union {
            int32_t value;
            unsigned char bytes[4];
        } t;

    public:
        byte_4(Endianness endianness = Endianness::BO_BIG_ENDIAN);

        std::vector<unsigned char> serialize(int32_t value);
        void serialize(unsigned char* stream, int32_t value, size_t index_start = 0);
        void serialize(std::vector<unsigned char>& stream, int32_t value, size_t index_start = 0);
        int32_t deserialize(const unsigned char* stream, size_t index_start = 0);
        int32_t deserialize(const std::vector<unsigned char>& stream, size_t index_start = 0);
        friend std::ostream& operator<<(std::ostream& os, const byte_4& byte);
    };

    std::ostream& operator<<(std::ostream& os, const byte_4& byte);


    class byte_2 {
    private:
        Endianness endianness;
        const uint8_t byte_size = 2;

        union {
            int16_t value;
            unsigned char bytes[2];
        } t;

    public:
        byte_2(Endianness endianness = Endianness::BO_BIG_ENDIAN);

        std::vector<unsigned char> serialize(int16_t value);
        void serialize(unsigned char* stream, int16_t value, size_t index_start = 0);
        void serialize(std::vector<unsigned char>& stream, int16_t value, size_t index_start = 0);
        int16_t deserialize(const unsigned char* stream, size_t index_start = 0);
        int16_t deserialize(const std::vector<unsigned char>& stream, size_t index_start = 0);
        friend std::ostream& operator<<(std::ostream& os, const byte_2& byte);
    };

    std::ostream& operator<<(std::ostream& os, const byte_2& byte);


    class byte_1 {
    private:
        Endianness endianness;
        const uint8_t byte_size = 1;

        union {
            int8_t value;
            unsigned char bytes[1];
        } t;

    public:
        byte_1(Endianness endianness = Endianness::BO_BIG_ENDIAN);

        std::vector<unsigned char> serialize(int8_t value);
        void serialize(unsigned char* stream, int8_t value, size_t index_start = 0);
        void serialize(std::vector<unsigned char>& stream, int8_t value, size_t index_start = 0);
        int8_t deserialize(const unsigned char* stream, size_t index_start = 0);
        int8_t deserialize(const std::vector<unsigned char>& stream, size_t index_start = 0);
        friend std::ostream& operator<<(std::ostream& os, const byte_1& byte);
    };

    std::ostream& operator<<(std::ostream& os, const byte_1& byte);


    void print(const unsigned char* stream, int length, std::string delimeter = " ");
    void print(const std::vector<unsigned char>& stream, std::string delimeter = " ");
    void print(const serializer::stream& stream, std::string delimeter = " ");
    std::string sprint(const unsigned char* stream, int length, std::string delimeter = " ");
    std::string sprint(const std::vector<unsigned char>& stream, std::string delimeter = " ");
    std::string sprint(const serializer::stream& stream, std::string delimeter = " ");
}

void _serialize(
    unsigned char* stream,
    unsigned char* bytes,
    uint8_t byte_size,
    uint index_start = 0,
    serializer::Endianness endianness = serializer::Endianness::BO_BIG_ENDIAN
);

void _deserialize(
    const unsigned char* stream,
    unsigned char* bytes,
    uint8_t byte_size,
    uint index_start = 0,
    serializer::Endianness endianness = serializer::Endianness::BO_BIG_ENDIAN
);
