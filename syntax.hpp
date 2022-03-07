#ifndef __sitl_syntax_hpp__
#define __sitl_syntax_hpp__

#include "tree.hpp"
#include "tokens.hpp"

namespace sitl
{
  // Ce que l'on veut c'est construire l'ast de sitl
  // Il faut donc une fonction qui permette de mettre en place
  // une description de cette ast via une sorte de grammaire
  // exprimée par l'imbrication fonctionnelle.

  // Un type est exprimé de la manière suivante :
  //   token : type
  //   token : id
  //   token : lbrace
  //   list of arg
  //   token : rbrace
  //
  // Un arg ext expirmé de la manière suivante :
  //   token : id
  //   token : colon
  //   token : id
  //   token : semicolon

  auto token_of(sitl::token_type tt)
  {
    return [tt]<typename I>(I b, I e) -> bool
    {
      return b != e and *b.tp == tt;
    };
  }

  auto this_is(auto... fn)
  {
    return [=]<typename I>(I b, I e) -> bool
    {
      return fn(b, e);
    };
  }

  template <typename I>
  bool syntax_type(I b, I e)
  {
    using tt = sitl::token_type;

    return this_is(
        token_of(tt::kw_type),
        token_of(tt::sm_id),
        token_of(tt::smlbrace),
        //  list_of(syntax_arg),
        token_of(tt::sm_rbrace))(b, e);
  }
}

#endif