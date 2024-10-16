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

#include <cmath>
#include <concepts>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>


template <typename T>
using enable_if_integral = typename std::enable_if<std::is_integral<T>::value, int>::type;


namespace Serializer {

template <typename T, enable_if_integral<T> = 0>
static float itof(T value, uint16_t precision) {return static_cast<float>(value) / std::pow(10, precision);}

template <typename T, enable_if_integral<T> = 0>
static double itod(T value, uint16_t precision) {return static_cast<double>(value) / std::pow(10, precision);}

template <typename T, enable_if_integral<T> = 0>
static T ftoi(float value, uint16_t precision) {return static_cast<T>(value * std::pow(10, precision));}

template <typename T, enable_if_integral<T> = 0>
static T dtoi(double value, uint16_t precision) {return static_cast<T>(value * std::pow(10, precision));}

static void print(const uint8_t* stream, size_t length, const std::string& delimeter = " ") {
    std::cout << std::hex << std::uppercase << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
        std::cout << std::setw(2)  << static_cast<uint>(stream[i]) << (i == length - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
}

static void print(const std::vector<uint8_t>& stream, const std::string& delimeter = " ") {
    print(stream.data(), stream.size(), delimeter);
}

static std::string sprint(const uint8_t* stream, size_t length, const std::string& delimeter = " ") {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
        oss << std::setw(2) << static_cast<uint>(stream[i]) << (i == length - 1 ? "" : delimeter);
    std::cout << std::dec << std::nouppercase << std::setfill(' ');
    return oss.str();
}

static std::string sprint(const std::vector<uint8_t>& stream, const std::string& delimeter = " ") {
    return sprint(stream.data(), stream.size(), delimeter);
}

}