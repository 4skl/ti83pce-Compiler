#pragma once

#include "defines.h"

#include <cstdint>
#include <string>
#include <algorithm>
#include <sstream>

class utils
{
public:
	
	static bool string_contains(std::string value, std::string charset);

	static bool is_var_name(const std::string & value);
	static bool is_number(const std::string & value);

	static int64_t number_conversion(std::string & number);
	static uint64_t unsigned_number_conversion(std::string & number);

	static uint64_t pow(uint64_t base, uint64_t exponent);
};

