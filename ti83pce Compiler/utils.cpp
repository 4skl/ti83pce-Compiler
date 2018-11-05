#include "pch.h"
#include "utils.h"

bool utils::string_contains(std::string value, std::string charset)
{
	for (size_t i = 0; i < charset.length(); i++) {
		if (value.find(charset.at(i)) != std::string::npos) {
			return true;
		}
	}
	return false;
}

bool utils::is_var_name(const std::string & value)
{
	for (size_t i = 0; i < value.length(); i++) {
		if (VAR_NAME_CHARSET.find_first_of(value.at(i)) == std::string::npos) {
			return false;
		}
	}
	return true;
}

bool utils::is_number(const std::string & value)
{
	//for (); verify if contains only numbers
	return DIGIT_LIST.find_first_of(value.at(0)) != std::string::npos
		&& (value.find_last_of('-') == 0 || value.find_last_of('-') == std::string::npos)
		&& (value.find_last_of('+') == 0 || value.find_last_of('+') == std::string::npos);
}

int64_t utils::number_conversion(std::string & number)//maxbase = 36 = basecharset.length()
{
	std::string basecharset = "0123456789abcdefghijklmnopqrstuvwxyz";
	std::transform(number.begin(), number.end(), number.begin(), ::tolower);
	size_t xpos = number.find_first_of('x');
	if (xpos != std::string::npos) {
		char sign = 1;
		std::stringstream textStream;
		if (number.at(0) != '-') {
			textStream = std::stringstream(number.substr(0, xpos));
		}
		else {
			textStream = std::stringstream(number.substr(1, xpos));
			sign = -1;
		}
		uint16_t base;
		textStream >> base;
		uint64_t value = 0;
		uint8_t power = 0;
		for (int i = number.length() - 1; i > xpos; i--) {
			value += (basecharset.find_first_of(number.at(i)))*pow(base, power);
			power++;
		}
		return value * sign;
	}
	else { // if no base specified, base is 10
		std::istringstream numberStream(number);
		int64_t value;
		numberStream >> value;
		return value;
	}
}

uint64_t utils::pow(uint64_t base, uint64_t exponent)
{
	uint64_t value = 1;
	for (int i = 0; i < exponent; i++) {
		value *= base;
	}

	return value;
}
