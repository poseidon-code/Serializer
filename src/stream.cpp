#include <algorithm>
#include <cstdint>
#include <vector>

#include "serializer.hpp"

serializer::stream::stream(size_t length)
    : buffer(length, 0x00), index(0)
{}

serializer::stream::stream(const serializer::stream& other)
    : buffer(other.buffer), index(other.index)
{}

serializer::stream::stream(serializer::stream&& other) noexcept
    : buffer(std::move(other.buffer)), index(other.index)
{ other.index = 0; }

serializer::stream& serializer::stream::operator=(const serializer::stream& other) {
    if (this != &other) {
        this->buffer = other.buffer;
        this->index = other.index;
    }
    return *this;
}

serializer::stream& serializer::stream::operator=(serializer::stream&& other) noexcept {
    if (this != &other) {
        this->buffer = std::move(other.buffer);
        this->index = other.index;
        other.index = 0;
    }
    return *this;
}

std::vector<uint8_t> const serializer::stream::get() const {
    return this->buffer;
}

serializer::stream& serializer::stream::operator<<(const std::vector<uint8_t>& buffer) {
    std::copy(buffer.begin(), buffer.end(), this->buffer.begin() + this->index);
    this->index += buffer.size();
    return *this;
}

void serializer::stream::put(const uint8_t* buffer, size_t length, size_t index_start) {
    std::copy(buffer, buffer + length, this->buffer.begin() + index_start);
    this->index = this->index + (index_start - this->index) + length;
}

void serializer::stream::put(const std::vector<uint8_t>& buffer, size_t index_start) {
    this->put(buffer.data(), buffer.size(), index_start);
}
