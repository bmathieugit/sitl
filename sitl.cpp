#include "ios.hpp"
#include "args.hpp"

int main(int argc, char **argv)
{
  lib::argument_parser aparse("--", "=", ",");
  aparse.init(argc, argv);

  if (aparse.has("file"))
  {
    lib::fprint(stdout, "has file arg\n");

    std::string_view filename = aparse.string("file", "");

    lib::fprintfln(stdout, "filename found '#'", filename);
  }

  return EXIT_SUCCESS;
}