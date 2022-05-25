#include <fstream>
#include <streambuf>

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

  sitl::StringCRange src = sitl::sr("int i = \"coucou");
  sitl::Vector<sitl::Token> tokens = sitl::tokenize(src);

  for (const sitl::Token &token : tokens)
    sitl::logger::debug(token.value, " : ", (int)token.type);

  return EXIT_SUCCESS;
}