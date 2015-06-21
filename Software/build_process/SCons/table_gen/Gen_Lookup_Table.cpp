/*
//===========================================================================
// Copyright (c) : Pulserain Technology, LLC. 2015
//===========================================================================
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
*/


/****************************************************************************
* References:
*
* [1] C++11: Create 0 to N constexpr array in C++, Stackoverflow
*     http://stackoverflow.com/questions/19019252/c11-create-0-to-n-constexpr-array-in-c
*
* [2] Generating Lookup Table Constant Expressions in C++11, 
*     Joshua Napoli's blog, The Critical Section, Agile software development and C++ syntactic delights,
*     http://joshuanapoli.com/blog/2012/12/generating-lookup-table-constant-expressions-in-c11/
*
*****************************************************************************/


#include <cstdint>
#include <array>
#include <iostream>
#include <cmath>
#include <atomic>

template<typename T>
constexpr T look_up_table_elem (int i)
{
    return {};
}

template<>
constexpr uint16_t look_up_table_elem (int i)
{
    //return i;
   return round(cos (static_cast <long double>(i) / 2048 * 3.14159 / 4) * 32767);
}

template<typename T, int... N>
struct lookup_table_expand{};

template<typename T, int... N>
struct lookup_table_expand<T, 1, N...>
{
    static constexpr std::array<T, sizeof...(N) + 1> values = {{look_up_table_elem<T>(0), N... }};
};

template<typename T, int L, int... N> struct lookup_table_expand<T, L, N...> : lookup_table_expand<T, L-1, look_up_table_elem<T>(L-1), N...> {};

template<typename T, int... N>
constexpr std::array<T, sizeof...(N) + 1> lookup_table_expand<T, 1, N...>::values;

const std::array<uint16_t, 2048> x_table = lookup_table_expand<uint16_t, 2048>::values;

extern "C" void table_print()
{
    int index = 0;
    for (auto &x : x_table) {
        std::cout << index++ << " " << x << "\n";
    }
}
