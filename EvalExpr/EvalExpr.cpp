#include "EvalExpr.hpp"


#include <stack>

using namespace std;

std::map<char, int> precedenceMap ={{'+',2}, {'-',2}, {'*',3}, {'/',3}, {'^',4}};

/*******************************************************************************
 * Function: main
 * ----------------
 * Description:
 *   This is the main function of the program. 
 *
 * Arguments:
 *   int argc     : Count of command line argument to program
 *   char *argv[] : Command line arguments array
 *
 * returns:
 *   int  : '0' on Success
 *          Non-Zero value on failure
 ******************************************************************************/
int main(int argc, char *argv[]){
  FUNC_ENTRY;

  if(argc < 2){
    ERROR_STM("Usage!!! "<<argv[0]<<" <One or more expressions each within individual \"\">");
    return -1;
  }

  for(int i = 1; i < argc; ++i){
    try{
      int iResult = evaluateExpr(argv[i]);
      DEBUG_STM("The Calculated Value of expression \""<<argv[i]<<"\" is "<<iResult);
    }
    catch(EvalExceptions& e){
      ERROR_STM(e.error());
    }
    catch(...){
      ERROR_STM("Uncaught Exception Thrown");
    }
  }
  
  return 0;
}


int evaluateExpr(std::string sExpr)
{
  FUNC_ENTRY;

  #if DEBUG
    DEBUG_STM("Input Expression is : "<<sExpr);
  #endif

  if (sExpr.length() == 0)
  {
    throw EvalExceptions(INVALID_EXPR);
  }

  std::stack<char> operatorStck;
  std::stack<int> valueStack;

  for(int i = 0; i < sExpr.length(); ++i)
  {
    #if DEBUG
      DEBUG_STM("Loop i : "<<i<<" character here "<<sExpr[i]);
    #endif
    
    //If the character is space continue to next position
    if(sExpr[i] == ' ')
      continue;

    if (sExpr[i] >= '0' && sExpr[i] <= '9')
    {
      string sTemp = "";
      while(sExpr[i] >= '0' && sExpr[i] <= '9'){
        sTemp += sExpr[i];
        i++;
      }
      i--;
      valueStack.push(atoi(sTemp.c_str()));
      #if DEBUG
        DEBUG_STM("The last Item pushed to Stack : "<<valueStack.top());
      #endif
    }
    else if (sExpr[i] == '(')
    {
      operatorStck.push(sExpr[i]);
      #if DEBUG
        DEBUG_STM("The last Item pushed to Stack : "<<operatorStck.top());
      #endif
    }
    else if (sExpr[i] == ')')
    {
      while(!operatorStck.empty() && operatorStck.top() != '(')
      {
        try{
          int iv1, iv2;
          char cO;
          if (valueStack.empty())
          {
            throw EvalExceptions(INVALID_EXPR);
          }
          else
          {
            iv1 = valueStack.top();
            valueStack.pop();
          }
          if (valueStack.empty())
          {
            throw EvalExceptions(INVALID_EXPR);
          }
          else
          {
            iv2 = valueStack.top();
            valueStack.pop();
          }
          if (operatorStck.empty())
          {
            throw EvalExceptions(INVALID_EXPR);
          }
          else
          {
            cO = operatorStck.top();
            operatorStck.pop();
          }
          int iResult = solveSimpleExpr(iv2, cO, iv1);
          valueStack.push(iResult);
          #if DEBUG
            DEBUG_STM("The last Item pushed to Stack : "<<valueStack.top());
          #endif
        }
        catch(...){
          throw;
        }
      }
      if(operatorStck.empty())
        throw EvalExceptions(MISSING_PARENTHESES);
      operatorStck.pop();
    }
    else if ( sExpr[i] == '+' || sExpr[i] == '-' || sExpr[i] == '*' || sExpr[i] == '/' )
    {
      while(!operatorStck.empty() && isSecondOperatorHigher(sExpr[i], operatorStck.top()) )
      {
        try{
          int iv1, iv2;
          char cO;
          if (valueStack.empty())
          {
            throw EvalExceptions(INVALID_EXPR);
          }
          else
          {
            iv1 = valueStack.top();
            valueStack.pop();
          }
          if (valueStack.empty())
          {
            throw EvalExceptions(INVALID_EXPR);
          }
          else
          {
            iv2 = valueStack.top();
            valueStack.pop();
          }
          if (operatorStck.empty())
          {
            throw EvalExceptions(INVALID_EXPR);
          }
          else
          {
            cO = operatorStck.top();
            operatorStck.pop();
          }
          int iResult = solveSimpleExpr(iv2, cO, iv1);
          valueStack.push(iResult);
          #if DEBUG
            DEBUG_STM("The last Item pushed to Stack : "<<valueStack.top());
          #endif
        }
        catch(...){
          throw;
        }
      }
      operatorStck.push(sExpr[i]);
      #if DEBUG
        DEBUG_STM("The last Item pushed to Stack : "<<operatorStck.top());
      #endif
    }
  }

  while(!operatorStck.empty())
  {
    try{
      int iv1, iv2;
      char cO;
      if (valueStack.empty())
      {
        throw EvalExceptions(INVALID_EXPR);
      }
      else
      {
        iv1 = valueStack.top();
        valueStack.pop();
      }
      if (valueStack.empty())
      {
        throw EvalExceptions(INVALID_EXPR);
      }
      else
      {
        iv2 = valueStack.top();
        valueStack.pop();
      }
      if (operatorStck.empty())
      {
        throw EvalExceptions(INVALID_EXPR);
      }
      else
      {
        cO = operatorStck.top();
        operatorStck.pop();
      }
      int iResult = solveSimpleExpr(iv2, cO, iv1);
      valueStack.push(iResult);
      #if DEBUG
        DEBUG_STM("The last Item pushed to Stack : "<<valueStack.top());
      #endif
    }
    catch(...){
      throw;
    }
  }

  if (!valueStack.empty())
  {
    return valueStack.top();
  }

  return 0;
}

bool isSecondOperatorHigher(char Operator1, char Operator2)
{
  FUNC_ENTRY;
  #if DEBUG
    DEBUG_STM("Operator1 "<<Operator1<<" Operator2 "<<Operator2);
  #endif

  if(Operator2 == '(' || Operator2 == ')')
    return false;

  if (precedenceMap[Operator2] >= precedenceMap[Operator1])
  {
    #if DEBUG
      DEBUG_STM("Returning true");
    #endif
    return true;
  }
  else
  {
    #if DEBUG
      DEBUG_STM("Returning false");
    #endif
    return false;
  }
}

int solveSimpleExpr(int Value1, char cOperator, int Value2){
  FUNC_ENTRY;
  #if DEBUG
    DEBUG_STM(Value1<<" "<<cOperator<<" "<<Value2);
  #endif
  switch(cOperator){
    case '+' : 
              return (Value1 + Value2);
              break;;
    case '-' : 
              return (Value1 - Value2);
              break;;
    case '*' : 
              return (Value1 * Value2);
              break;;
    case '/' : 
              if (Value2 == 0)
                throw EvalExceptions(DIVIDE_BY_ZERO);
              return (Value1 / Value2);
              break;;
    case '(' :
              throw EvalExceptions(MISSING_PARENTHESES);
              break;;
    default :
              throw EvalExceptions(INVALID_OPERATOR);
              break;;
  }
}

EvalExceptions::EvalExceptions() : _error_code_m(DEFAULT_ERROR){
  FUNC_ENTRY;
}

EvalExceptions::EvalExceptions(const char * error_text) : _error_code_m(error_text){
  FUNC_ENTRY;
}

const char * EvalExceptions::error () const throw (){
  return _error_code_m.c_str();
}
