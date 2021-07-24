#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <sstream>

enum class token_type {
    OPERATOR,
    NUMBER,
    L_PHARANTESIS,
    R_PHARANTESIS,
};

struct token {
    char c;
    float num;
    std::string data;
    token_type type;
    token() : c(0), num(0.0f) {}
};

std::vector<std::string> tokenize(const std::string& input);

const std::vector<std::string> get_rpn(const std::vector<std::string>& tokens);

float eval_rpn(const std::vector<std::string>& rpn);

#endif  // PARSER_H