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

  logger::debug(
      "result ",
      sitl::SitlAnalyser()(
          sitl::ProceduralGTokenizer()(
              sitl::sr(
                  "struct string\n"
                  "begin\n"
                  "  param char b\n"
                  "  param char e\n"
                  "end\n"
                  "let int i '(+ i (- 1 12))'"))));

  logger::debug(
      "result : ",
      sitl::ExpressionAnalyser()(
          sitl::ExpressionGTokenizer()(
              sitl::sr(
                  "(add 1 (minus 2 \"toto\"))"))));

  return 0;
}