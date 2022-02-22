#include <fstream>
#include <streambuf>
#include <string>
#include <string_view>

#include "ios.hpp"
#include "args.hpp"

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

  lib::fprintfln(stdout, "content of # : \n#", fname, strsrc);

  return EXIT_SUCCESS;
}