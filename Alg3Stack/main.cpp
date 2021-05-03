#include <iostream>
#include <cstring>
#include "stackarray.hpp"
#include "functions.hpp"
#include "errors.hpp"
#include "tests.hpp"

int main()
{
  const int MAX_DEEP = 10;
  try
  {
    testCheckBalanceBrackets(std::cout);
    testPostfixToInfix(std::cout);  
    const char* infix = "(8+2*5)/(1+3*2-4)";
    char* postfix = new char[strlen(infix)];
    getPostfixFromInfix(infix, postfix, MAX_DEEP);
    std::cout << infix << " = " << postfix << ' ';
    std::cout << evalPostfix(postfix, MAX_DEEP) << std::endl;    
  }
  catch (StackUnderflow& exc) 
  {
    std::cerr << exc.getError() << '\n' << exc.what() << '\n';
  }
  catch (StackOverflow& exc) 
  {
    std::cerr << exc.getError() << '\n' << exc.what() << '\n';
  }
  catch (WrongSizeException& exc) 
  {
    std::cerr << exc.getError() << '\n' << exc.what() << '\n';
  }
  catch (std::exception& exc)
  {
    std::cerr << "Some other exception" << '\n' << exc.what() << '\n';
  }
}



