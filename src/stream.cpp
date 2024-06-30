#include "serializer.hpp"


serializer::stream::stream(size_t length)
    : buffer(length, 0x00),
    index(0)
{}

std::vector<unsigned char> const serializer::stream::get() const {
    return this->buffer;
}

serializer::stream& serializer::stream::operator<<(const std::vector<unsigned char>& buffer) {
    std::copy(buffer.begin(), buffer.end(), this->buffer.begin() + this->index);
    this->index += buffer.size();
    return *this;
}

void serializer::stream::put(const std::vector<unsigned char>& buffer, size_t index_start) {
    std::copy(buffer.begin(), buffer.end(), this->buffer.begin() + index_start);
    this->index = this->index + (index_start - this->index) + buffer.size();
}

void serializer::stream::put(const unsigned char* buffer, size_t length, size_t index_start) {
    std::copy(buffer, buffer + length, this->buffer.begin() + index_start);
    this->index = this->index + (index_start - this->index) + length;
}
