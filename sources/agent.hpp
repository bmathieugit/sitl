#ifndef __sitl_agent_hpp__
#define __sitl_agent_hpp__

#include <lib/string.hpp>

namespace sitl
{
  /**
   * @brief Le trait Agent décrit ce que doit
   * pouvoir faire un agent de compilation.
   * Celui-ci doit pouvoir prendre une String
   * en paramètre et tester si elle est compatible
   * avec le traitement que l'agent veut en faire.
   *
   * @tparam T Type implémentant le concept d'Agent
   */
  template <typename T>
  concept Agent = requires(T &agent, const String &s)
  {
    agent.test(s)->bool;
    agent.act(s);
  }
}

#endif
