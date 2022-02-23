#include <fstream>
#include <streambuf>
#include <string>
#include <string_view>
#include <vector>

#include "ios.hpp"
#include "args.hpp"
#include "tokens.hpp"

int main(int argc, char **argv)
{
  std::ios::sync_with_stdio(false);
  lib::cmdline aparse("--", "=", ",", argc, argv);
  std::string_view fname = aparse.string("file");
  lib::fprintfln(stdout, "filename found '#'", fname);

  std::ifstream src(fname.data());

  std::string strsrc{
      std::istreambuf_iterator<char>(src),
      std::istreambuf_iterator<char>()};

  std::vector<sitl::token> tks = sitl::tokens(strsrc);
  for (const sitl::token &tk : tks)
    lib::fprintfln(stdout, "token # -> #", (int)tk.tp, tk.val);
  lib::fprintfln(stdout, "size #", tks.size());
  return EXIT_SUCCESS;
}