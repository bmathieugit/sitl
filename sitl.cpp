#include "ios.hpp"

#include <vector>
#include <string>
#include <algorithm>

struct person
{
  std::string name;
};

size_t length_of(const person &p)
{
  return p.name.size();
}

void format_of(
    std::string &buff,
    const person &p)
{
  format_of(buff, p.name);
}

int main(int argc, char **argv)
{
  std::vector<std::string> args(argv + 1, argv + argc);
  std::string_view __file = "--file";

  auto found = std::find_if(
      args.begin(), args.end(),
      [&__file](const std::string &arg)
      { return arg == __file; });

  std::fprintf(stdout, "%s\n", lib::format("this is #", 42).c_str());

  if (found == args.end())
  {
    lib::fprintfln(stdout, "No argument # found", __file);
    return EXIT_SUCCESS;
  }

  for (auto &&arg : args)
    lib::fprintfln(stdout, "arg #", arg);

  person robert = {"robert"};

  lib::fprintfln(stdout, "#", robert);
  lib::fprintfln(stdout, "#", robert);

  return EXIT_SUCCESS;
}