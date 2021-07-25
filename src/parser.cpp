#include "parser.h"
#include <cstdlib>
#include <iterator>
#include <iostream>
#include <stack>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <math.h>

#define L_ASSOC    0
#define R_ASSOC    1
#define ARR_LEN(x) sizeof(x) / sizeof(x[0])

typedef std::map<std::string, std::pair<int, int>> operatorMap; /* e.g. ("+", {PRESEDENCE, ASSOC_VAL})*/

const operatorMap::value_type operators[] = {
    operatorMap::value_type("+", std::make_pair<int, int>(0, L_ASSOC)),
    operatorMap::value_type("-", std::make_pair<int, int>(0, L_ASSOC)),
    operatorMap::value_type("*", std::make_pair<int, int>(5, L_ASSOC)),
    operatorMap::value_type("/", std::make_pair<int, int>(5, L_ASSOC)),
    operatorMap::value_type("^", std::make_pair<int, int>(5, L_ASSOC)),
};

operatorMap opmap(operators, operators + ARR_LEN(operators)); /* range based map constructor */

std::vector<std::string>
tokenize(const std::string& input)
{
    std::stringstream stream(input);
    std::vector<std::string> res;
    while (stream) {
        token tok;
        /* 
			just check if it is a numeric value or not. 
			if it is, then it is a number
			if not, then assume that it is an operator, although it can be a function, a pharantesis, or a variable
		*/
        if (std::isalnum(stream.peek())) {
            stream >> tok.num;
            tok.data = std::to_string(tok.num);
            tok.type = token_type::NUMBER;
        }
        else {
            stream >> tok.c;
            if (tok.c == '*' || tok.c == '*' || tok.c == '/' || tok.c == '-' || tok.c == '^')
                tok.type = token_type::OPERATOR;
            else if (tok.c == '(')
                tok.type = token_type::L_PHARANTESIS;
            else if (tok.c == ')')
                tok.type = token_type::R_PHARANTESIS;

            tok.data = std::string(1, tok.c);
        }
        res.push_back(tok.data);
    }
    res.pop_back();
    return res;
}

/* helper utility functins */
bool isTokenOperator(const std::string& token)
{
    if (token == "*" || token == "+" || token == "/" || token == "-" || token == "^") return true;
    return false;
}

int getOperatorAssociativity(const std::string& token)
{
    return opmap.find(token)->second.second;
}

int cmpPrecedence(const std::string& t1, const std::string& t2)
{
    int p1 = opmap.find(t1)->second.first;
    int p2 = opmap.find(t2)->second.first;
    if (p1 < p2) return -1;
    if (p1 == p2) return 0;
    if (p1 > p2) return 1;
    return -999;
}

/* Shunting-yard algorithm by Djikstra */
const std::vector<std::string> get_rpn(const std::vector<std::string>& tokens)
{
    std::vector<std::string> res;
    std::list<std::string> out;
    std::stack<std::string> op_stack;

    for (const auto& token : tokens) {
        if (isTokenOperator(token)) {
            const std::string& o1 = token;
            if (!op_stack.empty()) {
                const std::string& o2 = op_stack.top();
                while (isTokenOperator(o2) && ((getOperatorAssociativity(o1) == L_ASSOC && cmpPrecedence(o1, o2) == 0) || (cmpPrecedence(o1, o2) == -1))) {
                    op_stack.pop();
                    out.push_back(o2);

                    if (!op_stack.empty())
                        const std::string& o2 = op_stack.top();
                    else
                        break;
                }
            }
            op_stack.push(o1);
        }
        else if (token == "(") {
            op_stack.push(token);
        }

        else if (token == ")") {
            std::string& o2 = op_stack.top();
            while (!op_stack.empty() && op_stack.top() != "(") {
                op_stack.pop();
                out.push_back(o2);
                o2 = op_stack.top();
            }

            op_stack.pop();

            if (o2 != "(") {
                std::cout << "Mismatched pharantesis. " << std::endl;
            }
        }

        else { /* number */
            out.push_back(token);
        }
    }

    while (!op_stack.empty()) {
        const std::string& o2 = op_stack.top();
        op_stack.pop();
        out.push_back(o2);
    }

    res.assign(out.begin(), out.end());
    return res;
}

float eval_rpn(const std::vector<std::string>& rpn)
{
    std::stack<std::string> out;
    for (const auto& token : rpn) {
        if (isTokenOperator(token)) {
            const std::string& o1 = out.top();
            out.pop();
            /* convert the strings into double */
            float e1 = atof(o1.c_str());

            const std::string& o2 = out.top();
            out.pop();
            float e2 = atof(o2.c_str());
            /* token would be a char anyway (e.g. '+', '*') */
            float sum = 0.0f;

            switch (token.c_str()[0]) {
                case '+':
                    sum += e1 + e2;
                    break;
                case '*':
                    sum += e1 * e2;
                    break;
                case '-':
                    sum += e2 - e1;
                    break;
                case '/':
                    sum += e2 / e1;
                    break;
                case '^':
                    sum += pow(e2, e1);
                    break;
            };
            out.push(std::to_string(sum));
        }
        else {
            out.push(token);
        }
    }
    return atof(out.top().c_str());
}
