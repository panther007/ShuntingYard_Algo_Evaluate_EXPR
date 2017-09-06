#ifndef _EVALEXPR_HPP
#define _EVALEXPR_HPP

#include <iostream>
#include <exception>
#include <map>

#include "ErrorCodes.hpp"

#define DEBUG_STM(fmt) \
        std::cout<<__FILE__<<":"<<__FUNCTION__<<":"<<__LINE__<<": "<<fmt<<std::endl
#define ERROR_STM(fmt) \
        std::cerr<<__FILE__<<":"<<__FUNCTION__<<":"<<__LINE__<<": "<<fmt<<std::endl

#if DEBUG
  #define FUNC_ENTRY DEBUG_STM("Function Entry")
#else
  #define FUNC_ENTRY ;
#endif

struct EvalExceptions : public std::exception
{

  EvalExceptions();
  EvalExceptions(const char * error_text);
  const char * error () const throw ();
  std::string _error_code_m;
};

int evaluateExpr(std::string sExpr);
bool isSecondOperatorHigher(char Operator1, char Operator2);
int solveSimpleExpr(int Value1, char cOperator, int Value2);

#endif //#ifndef _EVALEXPR_HPP

