#include <lib/string.hpp>
#include <lib/logger.hpp>
#include <lib/args.hpp>
#include <lib/vector.hpp>

#include <sitl.hpp>

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
      "  param char b\n"
      "  param char e\n"
      "end\n"
      "let int i '(+ i (- 1 12))'");

  // sitl::StringCRange src = sitl::sr("let ii int 00");
  sitl::Vector<sitl::Token> silt_tokens = sitl::SitlTokenizer()(src);

  for (auto &&token : silt_tokens)
    sitl::logger::debug("token type : ", (int)token.type, ", value : ", token.value);

  sitl::logger::debug("result ", sitl::SitlAnalyser()(silt_tokens));

  sitl::StringCRange src2 = sitl::sr("(add 1 (minus 2 \"toto\"))");
  sitl::Vector<sitl::Token> lisp_tokens = sitl::LispTokenizer()(src2);
  for (auto &&token : lisp_tokens)
    sitl::logger::debug("token type : ", (int)token.type, ", value : ", token.value);

   sitl::logger::debug("result : ", sitl::ExpressionAnalyser()(lisp_tokens)); 

  return 0;
}