#include "ios.hpp"
#include "algorithm.hpp"
#include "string.hpp"
#include "vector.hpp"
#include <cstring>
#include <cstdio>

int main(int argc, char **argv)
{
  lib::vector<lib::string> args(lib::span_of(argv, argc));

  for (auto&& arg: args)
    lib::printfln("arg #", arg);

  return EXIT_SUCCESS;
}