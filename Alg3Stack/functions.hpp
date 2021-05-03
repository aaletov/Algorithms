#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>

bool checkBalanceBrackets(const char* const expr, int maxDeep); //max deep????
bool getPostfixFromInfix(const char* const infix, char* const postfix, int maxDeep);
double evalPostfix(char* const infix, int maxDeep);

#endif
