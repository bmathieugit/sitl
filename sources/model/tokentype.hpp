#ifndef __sitl_tokentype_hpp__
#define __sitl_tokentype_hpp__

namespace sitl
{
  enum class TokenType : int
  {
    LABEL,
    NUMBER,
    BLANK,
    STRING,
    EOL,
    ERROR,
    WHILE,
    STRUCT,
    BEGIN,
    END,
    PARAM,
    LET,
    EXPR,
    IF,
    RETURN,
    FUN,
    PROC,
    LPAR,
    RPAR
  };

  using TT = TokenType;
}

#endif