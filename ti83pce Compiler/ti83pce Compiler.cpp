// ti83pce Compiler.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include "defines.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


void clear_spaces(std::string &input);


std::string reading(std::string & input);
std::string parsing(const std::string & inst);


std::string variable_initialisation(const std::string & input);
std::string variable_type_conversion(std::string & type);

std::string if_statement_parsing(const std::string & input);
std::string while_statement_parsing(const std::string & input);
std::string for_statement_parsing(const std::string & input);

std::string numeric_calculus_parsing(std::string input);

std::string function_creation_parsing(const std::string & input);


std::vector<std::string> variablesVector[2];//[0] name | [1] type


int main()
{
	//reading arguments
	std::string inputFileName, outputFileName;
	if(__argc == 2) {
		inputFileName.assign(__argv[1]);
		size_t extensionPosition = inputFileName.find_last_of('.');
		if (extensionPosition != std::string::npos) {
			outputFileName.assign(__argv[1], extensionPosition);
		} 
		else {
			outputFileName.assign(__argv[1]);
		}
		outputFileName.append(".ti83pcez80");
	}
	else if (__argc == 3) {
		inputFileName.assign(__argv[1]);
		outputFileName.assign(__argv[2]);
	}
	else {
		std::cout << "Usage : " << __argv[0] << " <input file> [output file]" << std::endl;
		return ERROR_ARGS;
	}
	//reading input file
	std::fstream inputFile;
	inputFile.open(inputFileName, std::fstream::in);
	if (!inputFile) {
		std::cerr << "Unable to read " << inputFileName << std::endl;
		return ERROR_READ;
	}
	std::string inputCode = "";
	std::string line;
	while (std::getline(inputFile,line)) {
		inputCode += " " + line;
	}

	inputFile.close();
	std::clog << inputCode << std::endl;
	clear_spaces(inputCode);
	std::string outputCode = reading(inputCode);
	std::clog << outputCode << std::endl;

	//writing output file
	std::fstream outputFile;
	outputFile.open(outputFileName, std::fstream::out);
	if (!inputFile) {
		std::cerr << "Unable to write " << outputFileName << std::endl;
		return ERROR_WRITE;
	}
	for (size_t i = 0; i < outputCode.length(); i++) {
		outputFile << outputCode.c_str()[i];
	}
	outputFile.close();

	return SUCCESS;
}

void erase_spaces(std::string &input);
void add_spaces(std::string &input);
void back_to_spaces(std::string & input);

void clear_spaces(std::string &input)
{
	//back_to_spaces(input); //unused because using getline() for reading the file
	add_spaces(input);
	erase_spaces(input);
}

void back_to_spaces(std::string & input) {
	bool inQuotes = false;
	for (size_t i = 0; i < input.length(); i++) {
		char c = input.at(i);
		if (c == '"') inQuotes = !inQuotes;
		if ( (c == '\n' || c== '\t' || c == '\r' )  && !inQuotes) {
			input.replace(i,1, " ");
		}
	}
}

void erase_spaces(std::string & input)
{

	bool inQuotes = false;
	for (size_t i = 0; i < input.length(); i++) {
		char c = input.at(i);
		if (c == '"') inQuotes = !inQuotes;
		if (c == ' ' && !inQuotes) {//erase spaces if have more than 1 space
			size_t j = i + 1;
			for (j; j < input.length() && input.at(j) == ' '; j++);
			if (j - i > 1) {
				input.erase(i, j - i-1);
			}
		}
	}
	return;

}

void add_spaces(std::string & input)
{
	std::string charset = "(){}[]+-*/%,!|&=<>;.^~";
	bool inQuotes = false;
	for (size_t i = 0; i < input.length(); i++) {
		char c = input.at(i);
		if (c == '"') inQuotes = !inQuotes;
		for (size_t j = 0;!inQuotes && j < charset.length(); j++) {
			if (c == charset.at(j)) {
				input.insert(i+1, " ");
				input.insert(i, " ");
				i++;
			}
		}
	}
	return;
}

std::string reading(std::string & input)
{
	std::string output;
	bool inQuotes = false;
	size_t lastInst = 0;
	for (size_t i = 0; i < input.length(); i++) {
		if (input.at(i) == '"') {
			inQuotes = !inQuotes;
		}else if (input.at(i) == ';' && !inQuotes) {
			output.append(parsing(input.substr(lastInst, i + 1 - lastInst)));
			lastInst = i+1;
		}
	}
	return output;
}

std::string parsing(const std::string & inst) {
	std::clog << "Parsing : { " << inst << " } " << std::endl;
	std::istringstream stringStream(inst);
	std::string start;
	stringStream >> start;
	//verify if start with a data type
	std::string lstart = start;
	std::transform(lstart.begin(), lstart.end(), lstart.begin(), ::tolower);
	for (int i = 0; i < VAR_TYPES_C; i++) {
		if (strcmp(VAR_TYPES[i], lstart.c_str()) == 0) {
			return variable_initialisation(inst);
			break;
		}
	}
	
	//verify if start with a integrated function

	//verify if start with a variable name

	//verify if start with a user function
}

std::string variable_initialisation(const std::string & input)//input contains the initialisation of the variable
{
	std::string output;
	std::istringstream stringStream(input);
	std::string type;
	stringStream >> type;
	std::transform(type.begin(), type.end(), type.begin(), ::tolower);
	std::string name;
	stringStream >> name;
	//std::clog << "type : " << type << " name : " << name;
	std::string hasValue;
	stringStream >> hasValue;

	output.append(VAR_PREFIX);
	output.append(type);
	output.append("_");
	output.append(name);
	if (std::find(variablesVector[0].begin(), variablesVector[0].end(), output) != variablesVector[0].end()) {
		std::cerr << name << " is already defined" << std::endl;
	}
	else {
		variablesVector[0].push_back(name);
		variablesVector[1].push_back(type);
	}
	std::string newVar = output;

	if (hasValue.compare("=") == 0) {
		std::string value;
		size_t pos1 = stringStream.tellg();
		size_t pos2 = input.find_first_of(';');
		value = input.substr(pos1, pos2);
		if (value.at(0) == '"') {//is text
			output.append(": .db ");
			output.append(value);
		}
		else if (utils::is_number(value)) {//is number
			output.append(": .");
			output.append(variable_type_conversion(type));
			output.append(" ");
			std::ostringstream oss;
			oss << utils::number_conversion(value);
			std::string valuestring(oss.str());
			output.append(valuestring);
		}
		else if (utils::string_contains(value,OP_SIGN)) {// is calculus
			output.append(": .");
			output.append(variable_type_conversion(type));
			output.append(" 0\n");//initialise variables with 0
			output.append(numeric_calculus_parsing(value));
			output.append(") \\ ld (");
			output.append(newVar);
			output.append("), hl");
		}
		else {//is a variable
			std::string inputVar = VAR_PREFIX;
			inputVar.append(type);
			inputVar.append("_");
			inputVar.append(value);
			if (std::find(variablesVector[0].begin(), variablesVector[0].end(), value) != variablesVector[0].end()) {//check if var is existing
				output.append(": .");
				output.append(variable_type_conversion(type));
				output.append(" 0");//initialise variables with 0
				output.append(" \\ ld hl, (");
				output.append(inputVar);
				output.append(") \\ ld (");
				output.append(newVar);
				output.append("), hl");
			}
			else {
				std::cerr << value << " doesn't exist" << std::endl;
			}
		}

	}
	else if (hasValue.compare(";") == 0) {
		
		output.append(": .");
		output.append(variable_type_conversion(type));
		output.append(" 0");//initialise variables with 0

	}
	else {
		std::cerr << " \";\" neded at the definition of " << name << std::endl;
	}
	output.append("\n");
	return output;
}

std::string variable_type_conversion(std::string & type)
{
	const char* type_c = type.c_str();
	if (strcmp(type_c,VAR_TYPES[0]) == 0 || strcmp(type_c, VAR_TYPES[1]) == 0) {//byte || sbyte
		return std::string("db");
	}
	else if (strcmp(type_c, VAR_TYPES[2]) == 0 || strcmp(type_c, VAR_TYPES[3]) == 0) {
		return std::string("dw");
	}
	else {
		std::cerr << "type " << type << " is invalid" << std::endl;
	}
	return std::string();
}


std::string two_op_calculus(const std::string & input);
std::string numeric_calculus_parsing(std::string input)
{
	std::string output;
	size_t parenthesisHeight = 0;
	size_t higestHeight = 0;
	size_t higestParenthesisPosition = 0;
	for (size_t i = 0; i < input.size(); i++) {
		if (input.at(i) == '(') {
			parenthesisHeight++;
			if (parenthesisHeight > higestHeight) {
				higestParenthesisPosition = i;
			}
		}
		else if (input.at(i) == ')') {
			parenthesisHeight--;
		}
	}
	size_t parenthesisEnd = input.find_first_of(')', higestParenthesisPosition);
	for (size_t i = higestParenthesisPosition; i < parenthesisEnd; i++) {
		
	}

	return std::string();
}


std::string two_op_calculus(const std::string & input)
{
	if (utils::is_number(input)) {
	}
	return std::string();
}