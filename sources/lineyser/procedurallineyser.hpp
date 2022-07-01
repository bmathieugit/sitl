#ifndef __sitl_procedural_linayeser_hpp__
#define __sitl_procedural_linayeser_hpp__

#include <lineyser/globallineyser.hpp>
#include <lineyser/lineysers.hpp>

namespace sitl
{
  using ProceduralLineyser =
      GlobalLineyser<
          StructLineyser,
          BeginLineyser,
          ParamLineyser,
          EndLineyser,
          LetLineyser>;
}

#endif