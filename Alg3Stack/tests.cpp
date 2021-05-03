#include "tests.hpp"
#include <iomanip>
#include <cstring>
#include "functions.hpp"

bool testCheckBalanceBrackets(std::ostream& out)
{
  bool result = true;
  bool sumRes = true;
  const int maxDeep = 15;
  const char* text00 = " ok ";
  const char* text01 = "( ) ok ";
  const char* text02 = "( ( [] ) ) ok ";
  const char* text03 = "( ( [ { } [ ] ( [ ] ) ] ) ) OK";
  const char* text04 = "( ( [ { } [ ] ( [ ] ) ] ) ) ) extra right parenthesis ";
  const char* text05 = "( ( [{ }[ ]([ ])] ) extra left parenthesis ";
  const char* text06 = "( ( [{ ][ ]([ ])]) ) unpaired bracket ";

  const char* texts[] = { text00, text01, text02, text03, text04, text05, text06 };
  for (int i = 0; i < 7; i++)
  {
    out << texts[i] << '\n';
    result = checkBalanceBrackets(texts[i], maxDeep);
    sumRes = sumRes && result;
    out << "The expression is ";
    if (result)
    {
      out << "correct" << '\n' << '\n';
    }
    else
    {
      out << "incorrect" << '\n' << '\n';
    }
  }

  return result;
}

void testPostfixToInfix(std::ostream& out)
{
  const int MAX_DEEP = 10;
  const char* infixExps[5];
  double evaledInfix[] = { 6.3928571, -11, -3.9, -33.25, -51 };
  char* postfixExps[5];

  infixExps[0] = "(1+2)*3/4+(5-6/7)";
  infixExps[1] = "5-(4*8-(7-3)+4)/2";
  infixExps[2] = "3/(4+6)*(6-3*3)-3";
  infixExps[3] = "5-(4*8+(7-3)+(3/4)*(1+2))";
  infixExps[4] = "(6-3*3)-(4*8+(7-3)*4)";

  for (int i = 0; i < 5; i++)
  {
    postfixExps[i] = new char[strlen(infixExps[i]) + 1];
    getPostfixFromInfix(infixExps[i], postfixExps[i], MAX_DEEP);
    out << "expectation: " << evaledInfix[i] << '\n'
        << "reality: " << evalPostfix(postfixExps[i], MAX_DEEP) << '\n'
        << "infix: " << infixExps[i] << '\n'
        << "postfix: " << postfixExps[i] << '\n' << '\n';
    delete [] postfixExps[i];
  }
}
