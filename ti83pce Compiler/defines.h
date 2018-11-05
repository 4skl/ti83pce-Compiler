#ifndef DEFINES_H
#define DEFINES_H

constexpr auto OUTPUT_FILE_EXTENSION = ".ez80";

//define code reference

//define var types
constexpr auto VAR_TYPES_C = 5;
constexpr char VAR_TYPES[VAR_TYPES_C][16] = {"byte","sbyte","short","sshort","string"};

//define variable prefix names
constexpr auto VAR_PREFIX = "var_";
constexpr auto PTR_PREFIX = "ptr_";

//define error codes
constexpr auto SUCCESS = 0;
constexpr auto ERROR_ARGS = 1;
constexpr auto ERROR_READ = 2;
constexpr auto ERROR_WRITE = 3;

//define types list
const std::string DIGIT_LIST = "+-0123456789";
const std::string OP_SIGN = "+-*/%^!~<>=&|";
const std::string VAR_NAME_CHARSET = "_azertyuiopqsdfghjklmwxcvbnAZERTYUIOPQSDFGHJKLMWXCVBN0123456789";

#endif //DEFINES_H