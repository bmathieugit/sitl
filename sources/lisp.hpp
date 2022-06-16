#ifndef __sitl_lisp_hpp__
#define __sitl_lisp_hpp__

#include <lib/string.hpp>

namespace lisp
{
  enum class TokenType : int
  {
    LPAR,
    RPAR,
    STRING,
    NUMBER,
    LABEL,
    ERROR
  };

  struct Token
  {
    TokenType type;
    StringCRange value;
  };

}

#endif