#include <string.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>

#include "parser.h"

int main(int argc, char** argv)
{
    /*
        Example usage:
        * eval "10+4*12"
    */
    std::string input;
    for (int i = 1; i < argc; i++) {
        input += argv[i];
    }
    const auto& tokens     = tokenize(input);
    const auto& rpn_tokens = get_rpn(tokens);

    float res = eval_rpn(rpn_tokens);
    std::cout << res << std::endl;
}