#include <compiler.hpp>

sitl::Compiler::Compiler(
    LexemStep &lexemst,
    SyntaxStep &syntaxst,
    SemanticStep &semanticst)

    : les{lexemst},
      sys{syntaxst},
      sms{semanticst}
{
}

void sitl::Compiler::compile(
    std::string_view filename)
{
  // std::vector<Lexem> lexems = les.lexems(filename);
  // std::vector<Node> ast = sys.ast(lexems);
  // std::size_t result = sms.check(ast);
}
