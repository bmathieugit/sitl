#ifndef __sitl_compiler_hpp__
#define __sitl_compiler_hpp__

#include <agent.hpp>
#include <lib/tuple.hpp>

namespace sitl
{
  /**
   * @brief Un Compiler permet de procéder à la
   * compilation ligne à ligne du langage sitl.
   * Il contient au moins deux agents. Un agent pour
   * gérer les erreurs et les autres agents pour
   * agir en fonction des lignes de codes correctes.
   *
   * @tparam ERROR agent responsable des erreurs
   * @tparam AGENTS agents en charges de l'interprétation
   * des lignes de codes.
   */
  template <Agent ERROR, Agent... AGENTS>
  class Compiler
  {
    Tuple<ERROR, AGENTS...> agents;

  public:
    constexpr Compiler(const ERROR &err, const AGENTS &...ags)
        : agents(err, ags...) {}

    constexpr Compiler(const Compiler &) = default;
    constexpr Compiler(Compiler &&) = default;
    constexpr Compiler& operator=(const Compiler&) = default;
    constexpr Compiler& operator=(Compiler&&) = default;
    constexpr ~Compiler() = default;
    
  };
}

#endif
