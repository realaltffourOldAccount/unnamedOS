 #include "byte8.h"

auto byte8_malloc(size_t size)->byte8* {
	return (byte8*)malloc(size);
}

auto byte8_free(byte8* dest)->void {
	free(dest);
}

auto byte8_arrset(byte8* const dest, size_t size, const char* const src)->void {
	if (dest == nullptr) {
		std::cout << "Destination byte8 array is nullptr.\n";
		exit(1);
	}
	if (src == nullptr) {
		std::cout << "Sourrce byte8 array is nullptr.\n";
		exit(1);
	}

	for (int i = 0; i < size; i++) {
		*(dest+i) = byte8(*(src+i));
	}
}

auto byte8_set(byte8& byte, std::string hex)->void {
	// Check if hex is a hexadecimal value
	if (hex[0] != '0' || hex[1] != 'x') {
		std::cout << "Invalid hexadecimal value passed.\n";
		exit(1);
	}
	// Remove 0x from hex string
	std::reverse(hex.begin(), hex.end());
	hex.pop_back();
	hex.pop_back();
	std::reverse(hex.begin(), hex.end());
	
	// Convert Hexadecimal to integer and then to binary.
	unsigned int hexval = 0;
	
	std::stringstream ss;
	ss << std::hex << hex;
	ss >> hexval;

	// Set byte with hexval.
	byte = byte8(hexval);
}

auto byte8_set(byte8& byte, const unsigned int value)->void {
	byte = byte8(value);
}

auto byte8_getstr(const byte8& byte)->std::string {
	return byte.to_string();
}

auto byte8_getint(const byte8& byte)->unsigned int {
	return static_cast<unsigned int>(byte.to_ulong());
}

auto byte8_gethex(const byte8& byte)->std::string {
	std::string result;
	std::stringstream ss;
	ss << std::hex << byte.to_ulong();
	ss >> result;

	// Add 0x to the result string.
	std::reverse(result.begin(), result.end());
	result.push_back('x');
	result.push_back('0');
	std::reverse(result.begin(), result.end());
	
	return result;
}

auto str2byte8(const std::string& bin)->byte8 {
	if (bin.empty()) {
		std::cout << "Binary value can't be empty!\n";
		exit(1);
	}
	if (bin.size() > 8) {
		std::cout << "Binary value length must not be greater than 8!\n";
		exit(1);
	}
	return byte8(bin);
}

auto int2byte8(unsigned int val)->byte8 {
	if (!is8bitDecimal(val)) {
		std::cout << "Integer is not a 8-bit decimal!\n";
		exit(1);
	}
	return byte8(val);
}

auto hex2byte8(const std::string& hex)->byte8 {
	byte8 result;
	byte8_set(result, hex);
	return result;
}

auto is8bitDecimal(unsigned int val)->bool {
	return (val > 0) && (val <= 255);
}

auto isxbitDecimal(unsigned int val, int bits)->bool {
	return (val > 0) && (val <= (2^bits));
}
