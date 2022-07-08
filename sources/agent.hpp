#ifndef __sitl_agent_hpp__
#define __sitl_agent_hpp__

#include <lib/string.hpp>

namespace sitl
{
  template <typename T>
  concept Agent = requires(T &agent, const String &s)
  {
    agent.test(s)->bool;
    agent.act(s);
  }
}

#endif
