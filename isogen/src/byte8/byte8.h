#ifndef BYTE8_H
#define BYTE8_H

#include <bitset>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <algorithm>

#include <iostream>

using byte8 = std::bitset<8>;

// Allocation, and freeing of byte8.
auto byte8_malloc(size_t size)->byte8*;
auto byte8_free(byte8* dest)->void;

// Set byte8 array values.
auto byte8_arrset(byte8* const dest, size_t size, const char* const src)->void;


// Set byte8 values.
auto byte8_set(byte8& byte, std::string hex)->void;
auto byte8_set(byte8& byte, const unsigned int value)->void;

// Get byte8 value.
auto byte8_getstr(const byte8& byte)->std::string;
auto byte8_getint(const byte8& byte)->unsigned int;
auto byte8_gethex(const byte8& byte)->std::string;

// Convert to byte8.
auto str2byte8(const std::string& val)->byte8;
auto int2byte8(unsigned int val)->byte8;
auto hex2byte8(const std::string& val)->byte8;

// Misc functions.
constexpr auto is8bitDecimal(unsigned int val)->bool;

#endif
