#include <lib/string.hpp>
#include <lib/logger.hpp>
#include <lib/args.hpp>
#include <lib/vector.hpp>

#include <sitl.hpp>

int main(int argc, char **argv)
{
  namespace logger = sitl::logger;
  sitl::CommandLine args(argc, argv);

  if (args.contains(sitl::sr("file")))
  {
    sitl::StringCRange fname = args.value(sitl::sr("file"));
    logger::debug("file name found, fname");
  }

  auto proclines = sitl::ProceduralLineyser()(
      sitl::ProceduralGTokenizer()(
          sitl::sr(
              "struct string\n"
              "begin\n"
              "  param char b\n"
              "  param char e\n"
              "end\n"
              "let int i '(+ i (- 1 12))'")));
  for (const sitl::Line &l : proclines)
    logger::debug("type ", (int)l.type, " depth ", l.depth);
/* 
  auto exprlines = sitl::ExpressionLineyser()(
      sitl::ExpressionGTokenizer()(
          sitl::sr(
              "(add 1 (minus 2 \"toto\"))")));

  for (const sitl::Line &l : exprlines)
    logger::debug("type: ", (int)l.type); */

  return 0;
}