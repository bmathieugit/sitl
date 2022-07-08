#ifndef __sitl_compiler_hpp__
#define __sitl_compiler_hpp__

#include <agent.hpp>
#include <lib/tuple.hpp>
#include <lib/string.hpp>

namespace sitl
{
  template <Agent ERROR, Agent... AGENTS>
  class Compiler
  {
    Tuple<ERROR, AGENTS...> agents;

  public:
    
    constexpr Compiler(const ERROR &err, const AGENTS &...ags)
        : agents(err, ags...) {}

    constexpr Compiler(const Compiler &) = default;
    constexpr Compiler(Compiler &&) = default;
    constexpr Compiler &operator=(const Compiler &) = default;
    constexpr Compiler &operator=(Compiler &&) = default;
    constexpr ~Compiler() = default;

  public:
    
    void compile(const String &src)
    {
      auto rsrc = src.range();

      do
      {
        Size l = 0;
        compileLine(rsrc.go_after('\n'), l, MakeSequence<ERROR, AGENTS...>());
      } 
      while (rsrc.size() != 0);
    }

  private:
    
    template <TupleIndex ... i>
    void compileLine(StringCRange line, Size lnum, TupleSequence<i...>)
    {
      compileLine(line, lnum, get<i>(agents)...);
    }

    void compileLine(
      StringCRange line, Size lnum, 
      ERROR &err, auto &first, auto &...tails)
    {
      if (first.test(line))
        first.act(line, lnum);
      else if constexpr (sizeof...(tails) != 0)
        compileLine(line, lnum, err, tails);
      else 
        err.act(line, lnum);
    }
  };
}

#endif
