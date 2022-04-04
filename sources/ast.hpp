#ifndef __sitl_ast_hpp__
#define __sitl_ast_hpp__

#include <string>
#include <string_view>
#include <vector>
#include <memory>

namespace sitl::syntax
{
  struct node
  {
    std::vector<node> nodes;
  };
}

namespace sitl
{
  struct attribute
  {
    std::string name;
    std::string type;
  };

  struct type
  {
    std::string name;
    std::string type;
    std::vector<attribute> attrs;
  };

  struct argument
  {
    std::string name;
    std::string type;
  };

  struct instruction
  {
  };

  struct function
  {
    std::string name;
    std::string type;
    std::vector<argument> args;
    std::vector<std::unique_ptr<instruction>> instrs;
  };

  struct expression
  {
  };

  struct boolean_expression : public expression
  {
  };

  struct or_expression : public boolean_expression
  {
    std::unique_ptr<boolean_expression> lbexpr;
    std::unique_ptr<boolean_expression> rbexpr;
  };

  struct and_expression : public boolean_expression
  {
    std::unique_ptr<boolean_expression> lbexpr;
    std::unique_ptr<boolean_expression> rbexpr;
  };

  struct false_expression : public boolean_expression
  {
  };

  struct true_expression : public boolean_expression
  {
  };

  struct if_ : public instruction
  {
    std::unique_ptr<boolean_expression> boolexpr;
    std::vector<std::unique_ptr<instruction>> instrs;
  };

  struct while_ : public instruction
  {
    std::unique_ptr<boolean_expression> boolexpr;
    std::vector<std::unique_ptr<instruction>> instrs;
  };

  struct variable : public expression
  {
    std::string name;
  };

  struct affectation : public instruction
  {
    variable var;
    expression val;
  };

  struct let : instruction
  {
    std::string type;
    affectation aff;
  };

}

#endif