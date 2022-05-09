#include <fstream>
#include <streambuf>
#include <lib/string.hpp>
#include <lib/range.hpp>
#include <lib/logger.hpp>
//#include "tokens.hpp"

//#include "syntax.hpp"
//#include <iostream>

bool starts_with_file(const char *arg)
{
  return lib::StringView(arg)
      .range()
      .starts_with("--file="_sv);
}

int main(int argc, char **argv)
{
  auto args = lib::rangeof(argv, argc);
  auto found = args.find_if(starts_with_file);

  if (found != args.end())
  {
    auto fname = lib::StringView(*found)
                     .range()
                     .after('=')
                     .as<lib::StringView>();
    lib::StringView fileFoundMessage = "file name found #";
    lib::logger::info(fileFoundMessage, fname);
  }

  // std::vector<sitl::token<char>> tks = sitl::tokens(std::string_view(strsrc));
  // sitl::tree<sitl::node> ast;

  // bool stype = sitl::syntax_type(tks.begin(), tks.end());

  // logger::info("resultat of syntax : #", stype);
  return EXIT_SUCCESS;
}