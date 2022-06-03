#include <lib/string.hpp>
#include <lib/logger.hpp>
#include <lib/args.hpp>
#include <lib/vector.hpp>

#include <tokens.hpp>

int main(int argc, char **argv)
{
  sitl::CommandLine args(argc, argv);

  if (args.contains(sitl::sr("file")))
  {
    sitl::StringCRange fname = args.value(sitl::sr("file"));
    sitl::logger::debug("file name found, fname");
  }

  sitl::StringCRange src = sitl::sr(
      "struct string\n"
      "begin\n"
      "  char* b\n"
      "  char* e\n"
      "end\n");

  // sitl::StringCRange src = sitl::sr("let ii int 00");

  sitl::Vector<sitl::Token> tokens = sitl::tokenize(src);

  for (auto &&token : tokens)
    sitl::logger::debug("token type : ", (int)token.type, ", value : ", token.value);

  // sitl::Vector<sitl::Node> nodes = sitl::syntax(tokens);

  // for (auto &&node : nodes)
  //   sitl::logger::debug("node{ type : ",(int) node.type,
  //                       "; depth : ", node.depth,
  //                       "; value : ", node.value, '}');

  return 0;
}