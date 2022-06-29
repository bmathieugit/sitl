#ifndef __sitl_line_hpp__
#define __sitl_line_hpp__

#include <model/linetype.hpp>
#include <lib/vector.hpp>
#include <model/token.hpp>

namespace sitl
{
  struct Line
  {
    LineType type;
    Depth depth;
    Vector<Token> tokens;
  };
}

#endif