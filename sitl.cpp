#include <fstream>
#include <streambuf>
#include <string>
#include <string_view>
#include <vector>

#include "ios.hpp"
#include "args.hpp"
#include "tokens.hpp"

int main(int argc, char **argv)

try
{
  lib::cmdline aparse("--", "=", ",", argc, argv);
  std::string_view fname = aparse.string("file");
  lib::printfln("filename found '#'", fname);

  std::ifstream src(fname.data());

  std::string strsrc{
      std::istreambuf_iterator<char>(src),
      std::istreambuf_iterator<char>()};

  std::vector<sitl::token> tks = sitl::tokens(strsrc);

  for (const sitl::token &tk : tks)
    lib::printfln("..token # -> #", (int)tk.tp, fmt::green | tk.val);

  lib::printfln("size #", tks.size());


  return EXIT_SUCCESS;
}
catch (std::exception &e)
{
  lib::printf("exception #", std::string_view(e.what()));
}