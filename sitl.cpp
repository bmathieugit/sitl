#include <fstream>
#include <streambuf>
#include <string>
#include <string_view>
#include <vector>

#include "ios.hpp"
#include "args.hpp"
#include "tokens.hpp"
#include "logger.hpp"

#include "syntax.hpp"
#include <iostream>

int main(int argc, char **argv)

try
{
  lib::cmdline aparse("--", "=", ",", argc, argv);
  std::string_view fname = aparse.string("file");
  logger::info("filename found '#'", fname);

  std::ifstream src(fname.data());

  std::string strsrc{
      std::istreambuf_iterator<char>(src),
      std::istreambuf_iterator<char>()};

  std::vector<sitl::token> tks = sitl::tokens(strsrc);
  bool stype = sitl::syntax_type(tks.begin(), tks.end());

  logger::info("resultat of syntax : #", stype);
  return EXIT_SUCCESS;
}
catch (std::exception &e)
{
  ios::printf("exception #", std::string_view(e.what()));
}