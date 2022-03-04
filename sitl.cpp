#include <fstream>
#include <streambuf>
#include <string>
#include <string_view>
#include <vector>

#include "ios.hpp"
#include "args.hpp"
#include "tokens.hpp"
#include "logger.hpp"

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

  for (const sitl::token &tk : tks)
    logger::debug("..token # -> #", (int)tk.tp, tk.val);

  logger::debug("size #", tks.size());

  std::vector<int> is = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  logger::info("vector #", is);

  return EXIT_SUCCESS;
}
catch (std::exception &e)
{
  ios::printf("exception #", std::string_view(e.what()));
}