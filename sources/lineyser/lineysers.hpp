#ifndef __sitl_lineysers_hpp__
#define __sitl_lineysers_hpp__

#include <lineyser/lineyser.hpp>
#include <model/tokentype.hpp>

namespace sitl
{
  using BeginLineyser = Lineyser<LT::BEGIN, TT::BEGIN>;
  using EndLineyser = Lineyser<LT::END, TT::END>;
  using StructLineyser = Lineyser<LT::STRUCT, TT::STRUCT, TT::LABEL>;
  using ParamLineyser = Lineyser<LT::PARAM, TT::PARAM, TT::LABEL, TT::LABEL>;
  using LetLineyser = Lineyser<LT::LET, TT::LET, TT::LABEL, TT::LABEL, TT::EXPR>;
  using IfLineyser = Lineyser<LT::IF, TT::IF, TT::EXPR>;
}

#endif