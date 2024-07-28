# Serializer

A binary data serializer in modern C++. Encodes & Decodes data to/from bytes with Little & Big Endian byte orders.

## Usage Examples

### 1. Plain Old Arrays

```cpp
#include <iostream>

#include "serializer.hpp"

int main() {
    const size_t stream_length = 16;
    unsigned char stream[stream_length] = {0}; // create the bytes array
    serializer::byte_t<int64_t> byte_8; // create a default serializer object (Big Endian) of 8 bytes

    byte_8.serialize(stream, 0x1122334455667788); // serialize the data and start putting it from 0 index of bytes array

    byte_8.serialize(stream, 0x8877665544332211, 8); // serialize the data and start putting it from 8th index of bytes array

    serializer::print(stream, stream_length); // prints the entire bytes array (default delimeter "<space>")
    std::cout << "\n";

    int64_t deserialized_value1 = byte_8.deserialize(stream); // returns the data after deserializing from 0 index of bytes array
    int64_t deserialized_value2 = byte_8.deserialize(stream, 8); // returns the data after deserializing from 8th index of bytes array

    std::cout << std::hex << "0x" << deserialized_value1 << ", 0x" << deserialized_value2 << std::dec << "\n";


    return 0;
}

```

### 2. Vector of Bytes

```cpp
#include <iostream>
#include <vector>

#include "serializer.hpp"

int main() {
    const size_t stream_length = 16;
    std::vector<unsigned char> stream(16, 0x00); // create bytes vector with size & default values

    byte_8_le.serialize(stream, 0x1122334455667788); // serialize the data and start putting it from 0 index of bytes vector (using the libray provided, 8-byte signed integer in little endian byte order - object)

    std::vector<unsigned char> serialized_value2 = byte_8_le.serialize(0x1122334455667788); // returns the bytes vector of the serialized data
    for (auto byte : serialized_value2) std::cout << std::hex << static_cast<uint>(byte) << " "; std::cout << std::dec << "\n"; // prints the returned bytes vector
    std::copy(serialized_value2.begin(), serialized_value2.end(), stream.begin() + 8); // putting the returned bytes vector to the `stream` bytes vector from its 8th index

    std::string stream_str = serializer::sprint(stream, ", "); // returns the bytes as a string with <comma> delimeter
    std::cout << stream_str << "\n"; // prints the returned string

    int64_t deserialized_value1 = byte_8_le.deserialize(stream); // returns the data after deserializing from 0 index of bytes array
    int64_t deserialized_value2 = byte_8_le.deserialize(stream.data(), 8); // returns the data after deserializing from 8th index of internal memory of the bytes array

    std::cout << std::hex << "0x" << deserialized_value1 << " - 0x" << deserialized_value2 << std::dec << "\n";


    return 0;
}
```

### 3. `stream`

```cpp
#include <iostream>

#include "serializer.hpp"

int main() {
    const size_t stream_length = 16;
    serializer::stream stream(stream_length); // create a stream object with length
    serializer::byte_t<int64_t, Endianness::BO_BIG_ENDIAN> byte_8; // create a serializer object (Big Endian) of 8 bytes

    stream << byte_8.serialize(0x1122334455667788); // serialize the data and put it into the stream after previous

    stream.put(byte_8.serialize(0x1122334455667788), 8); // serialize the data and start putting it from 8th index of the stream

    serializer::print(stream); // prints the entire stream
    std::cout << "\n";

    int64_t deserialized_value1 = byte_8.deserialize(stream.get()); // returns the data after deserializing from 0 index of stream vector
    int64_t deserialized_value2 = byte_8.deserialize(stream.get().data(), 8); // returns the data after deserializing from 8th index of internal stream array

    std::cout << std::hex << "0x" << deserialized_value1 << " - 0x" << deserialized_value2 << std::dec << "\n";


    return 0;
}
```

## [GPL v3 License](./LICENSE)

serializer : A modern C++ binary data serializer library. \
Copyright (C) 2024 Pritam Halder

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
