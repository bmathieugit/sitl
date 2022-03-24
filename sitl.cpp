#include <fstream>
#include <streambuf>
#include <string>
#include <string_view>
#include <vector>

#include <lib/args.hpp>
#include <lib/logger.hpp>
//#include "tokens.hpp"

//#include "syntax.hpp"
//#include <iostream>
#include <lib/test.hpp>

int main(int argc, char **argv)
try
{
  lib::logger::info("# #"_fmt(1, 2));

  lib::cmdline aparse("--", "=", ",", argc, argv);
  std::string_view fname = aparse.string("file");
  lib::logger::info("filename found '#'", fname);

  std::ifstream src(fname.data());

  std::string strsrc{
      std::istreambuf_iterator<char>(src),
      std::istreambuf_iterator<char>()};

  // std::vector<sitl::token<char>> tks = sitl::tokens(std::string_view(strsrc));
  // sitl::tree<sitl::node> ast;

  // bool stype = sitl::syntax_type(tks.begin(), tks.end());

  // logger::info("resultat of syntax : #", stype);
  return EXIT_SUCCESS;
}
catch (std::exception &e)
{
  lib::logger::error("exception #", std::string_view(e.what()));
}