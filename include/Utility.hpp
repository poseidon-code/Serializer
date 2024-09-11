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

#include <cmath>
#include <concepts>
#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>


template <typename T>
concept integral = std::integral<T>;


namespace Serializer {
template <integral T>
static float itof(T value, uint16_t precision) {return static_cast<float>(value) / std::pow(10, precision);}

template <integral T>
static double itod(T value, uint16_t precision) {return static_cast<double>(value) / std::pow(10, precision);}

template <integral T>
static T ftoi(float value, uint16_t precision) {return static_cast<T>(value * std::pow(10, precision));}

template <integral T>
static T dtoi(double value, uint16_t precision) {return static_cast<T>(value * std::pow(10, precision));}


static void print(const uint8_t* stream, size_t length, const std::string& delimeter = " ");
static void print(const std::vector<uint8_t>& stream, const std::string& delimeter = " ");
static std::string sprint(const uint8_t* stream, size_t length, const std::string& delimeter = " ");
static std::string sprint(const std::vector<uint8_t>& stream, const std::string& delimeter = " ");
}
