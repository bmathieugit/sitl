#ifndef __sitl_compiler_hpp__
#define __sitl_compiler_hpp__

#include <string_view>
#include <string>
#include <vector>

namespace std
{

}

namespace sitl
{
  struct Lexem
  {
    std::size_t type;
    std::string val;
  };

  struct Node
  {
    std::size_t type;
    std::size_t offset;
    std::string val;
  };

  class LexemStep
  {
  public:
    std::vector<Lexem> lexems(
        std::string_view filename);
  };

  class SyntaxStep
  {
  public:
    std::vector<Node> ast(
        const std::vector<Lexem> &lexems);
  };

  class SemanticStep
  {
  public:
    std::size_t check(
        const std::vector<Node> &ast);
  };

  class CompilerStatus
  {
  };

  class Compiler
  {
    LexemStep &les;
    SyntaxStep &sys;
    SemanticStep &sms;

  public:
    Compiler(
        LexemStep &lexemst,
        SyntaxStep &syntaxst,
        SemanticStep &semanticst);

    Compiler(const Compiler &) = default;
    Compiler(Compiler &&) = default;
    ~Compiler() = default;
    Compiler &operator=(const Compiler &) = default;
    Compiler &operator=(Compiler &&) = default;

  public:
    void compile(std::string_view filename);
  };

}

#endif