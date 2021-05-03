#include "functions.hpp"
#include <iostream>
#include <cassert>
#include "stackarray.hpp"
#include "errors.hpp"

bool checkBalanceBrackets(const char* const expr, int maxDeep)
{
  StackArray<char> curlyBraces(maxDeep);
  StackArray<char> squareBrackets(maxDeep);
  StackArray<char> roundBrackets(maxDeep);

  try
  {
    int i = 0;
    while (expr[i] != '\0')
    {
      switch (expr[i])
      {
      case '{':
        curlyBraces.push(expr[i]);
        break;
      case '}':
        curlyBraces.pop();
        break;
      case '[':
        squareBrackets.push(expr[i]);
        break;
      case ']':
        squareBrackets.pop();
        break;
      case '(':
        roundBrackets.push(expr[i]);
        break;
      case ')':
        roundBrackets.pop();
        break;
      default: 
        break;
      }
      i++;
    }
  }
  catch(StackUnderflow& exc)
  {
    return false;
  }
  catch(StackOverflow& exc)
  {
    return false;
  }
  
  if (!curlyBraces.isEmpty() || !squareBrackets.isEmpty() || !roundBrackets.isEmpty())
  {
    return false;
  }
  else
  {
    return true;
  }
}

bool getPostfixFromInfix(const char* const infix, char* postfix, int maxDeep)
{
  if (!checkBalanceBrackets(infix, maxDeep))
  {
    return false;
  }
  StackArray<char> stack(maxDeep);
  int i = 0;
  int lastInserted = 0;
  while (infix[i] != '\0')
  {
    if (std::isdigit(infix[i]))
    {
      postfix[lastInserted] = infix[i];
      lastInserted++;
    }
    else
    {  
      switch (infix[i])
      {
      case '(':
        stack.push(infix[i]);
        break;
      case ')':
        while (stack.top() != '(')
        {
          postfix[lastInserted] = stack.pop();
          lastInserted++;
        }
        stack.pop();
        break;
      case '*':
      case '/':
        while (!stack.isEmpty())
        {
          if (stack.top() == '*' || stack.top() == '/')
          {
            postfix[lastInserted] = stack.pop();
            lastInserted++;
          }
          else
          {
            break;
          }
        }
        stack.push(infix[i]);
        break;
      case '+':
      case '-':
        while (!stack.isEmpty()) 
        {
          if (stack.top() == '*' || stack.top() == '/' || stack.top() == '+' || stack.top() == '-')
          {
            postfix[lastInserted] = stack.pop();
            lastInserted++;
          }
          else
          {
            break;
          }
        }
        stack.push(infix[i]);
        break;
      default:
        throw -1;
        break;
      }
    }
    i++;
  }
  while (!stack.isEmpty())
  {
    postfix[lastInserted] = stack.pop();
    lastInserted++;
  }
  postfix[lastInserted] = '\0';
  return true;
}

double evalPostfix(char* postfix, int maxDeep)
{
  double a = 0;
  double b = 0;
  double result = 0;
  int i = 0;
  StackArray<double> stack(maxDeep);
  while (postfix[i] != '\0')
  {
    if (std::isdigit(postfix[i]))
    {
      stack.push((postfix[i]) - ('0'));
    }
    else 
    {
      assert(!stack.isEmpty());
      b = stack.pop();
      assert(!stack.isEmpty());
      a = stack.pop();
      switch (postfix[i])
      {
      case '+':
        stack.push(a + b);
        break;
      case '-':
        stack.push(a - b);
        break;
      case '*':
        stack.push(a * b);
        break;
      case '/':
        stack.push(a / b);
        break;
      default:
        throw("Unknown char in postfix string!");
        break;
      }
    }
    i++;
  }
  assert(!stack.isEmpty());
  result = stack.pop();
  assert(stack.isEmpty());
  return result;
}
