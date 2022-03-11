#ifndef __sitl_syntax_hpp__
#define __sitl_syntax_hpp__

#include <span>
#include <string_view>
#include <tuple>
#include "std/vector"
#include "std/optional

#include "tokens.hpp"



namespace sitl
{
  // Ce que l'on veut c'est construire l'ast de sitl
  // Il faut donc une fonction qui permette de mettre en place
  // une description de cette ast via une sorte de grammaire
  // exprimée par l'imbrication fonctionnelle.

  //
  // Un arg ext expirmé de la manière suivante :
  //   token : id
  //   token : colon
  //   token : id
  //   token : semicolon

  // type : name
  //   arg : name type
  //   arg ; name type

  enum class ast_node_type
  {
    type,
    type_name,
    attribut,
    attribut_name,
    attribut_type
  };

  template <typename C>
  class ast
  {
    ast_node_type type;
    std::basic_string_view<C> val;

    std::opt<std::vec<ast<C>>> sast;
  };

  template <typename I, typename C>
  std::tuple<ast<C>, std::span<token<C>>>
  ast_arg(std::span<token<C>> tks)
  {
    using tt = ttype;
    using ant = ast_node_type;

    ast<C> arg;

    if (tks.size() >= 3)
    {
      if (tks[0].tp == tt::sm_id and
          tks[1].tp == tt::sm_id and
          tks[2].tp == tt::semi_scolon)
        return {
            ant::attribut,
            "",
            {{ant::attribut_name, tks[0].val},
             {ant::attribut_type, tks[1].val}}};
    }
  }

  // ast_type permet de construire les nodes nécessaires pour
  // représenter un type avec un nom et ses arguments
  // Un type est exprimé de la manière suivante :
  //   token : type
  //   token : id
  //   token : lbrace
  //   list of arg
  //   token : rbrace
  template <typename I>
  std::variant<std::span<token>, std::string>
  ast_type(std::span<token> tks, tree<node> &ast, unsigned parent)
  {
    if (tks.size() >= 4)
    {
      if (tks[0].tp == ttype::kw_type and tks[1].tp == ttype::sm_id and tks[2].tp == ttype::sm_lbrace)
      {
        auto tparent = ast.push({ast_node_type::type}, parent);
        ast.push({ast_node_type::type_name, tks[1].val}, tparent);

        tks = ast_arg(tks.subspan(3), ast, tparent);

        if (tks.size() >= 1)
        {
          if (tks[0].tp == ttype::sm_rbrace)
            return tks.subspan(1);
          else
            return fmt::format("unexcepted token #", tks[0].tp);
        }
      }
    }
  }

} // namespace sitl

#endif