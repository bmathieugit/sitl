#ifndef __sitl_linetype_hpp__
#define __sitl_linetype_hpp__

namespace sitl
{
  enum class LineType : int
  {
    STRUCT,
    BEGIN,
    END,
    PARAM,
    ERROR,
    IF,
    ELSE,
    WHILE,
    RETURN, 
    FUN, 
    LET
  };

  using LT = LineType;
}

#endif