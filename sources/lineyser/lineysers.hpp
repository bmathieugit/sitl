#ifndef __sitl_lineysers_hpp__
#define __sitl_lineysers_hpp__

#include <lineyser/lineyser.hpp>
#include <model/tokentype.hpp>

namespace sitl
{
  using BeginLineyser = Lineyser<DepthModifier(1), LT::BEGIN, TT::BEGIN>;
  using EndLineyser = Lineyser<DepthModifier(-1), LT::END, TT::END>;
  using StructLineyser = Lineyser<DepthModifier(0), LT::STRUCT, TT::STRUCT, TT::LABEL>;
  using ParamLineyser = Lineyser<DepthModifier(0), LT::PARAM, TT::PARAM, TT::LABEL, TT::LABEL>;
  using LetLineyser = Lineyser<DepthModifier(0), LT::LET, TT::LET, TT::LABEL, TT::LABEL, TT::EXPR>;
  using IfLineyser = Lineyser<DepthModifier(0), LT::IF, TT::IF, TT::EXPR>;
}

#endif