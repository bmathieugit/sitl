#include <lib/args.hpp>
#include <lib/logger.hpp>
#include "tests.cpp"

int main()
{
  TestResult result;
  const char *argv[] = {"file=toto.sitl", "verbose",
                        "int=-1200", "uint=1200"};

  int argc = 4;

  lib::CommandLine cmdl(argc, argv);

  test(cmdl.size() == 4, result);
  test(!cmdl.empty(), result);
  test(cmdl.contains("file"), result);
  test(cmdl.value("file") == sv("toto.sitl"), result);
  test(cmdl.value("verbose2") == sv(""), result);
  test(cmdl.flag("file"), result);
  test(cmdl.flag("verbose"), result);
  test(!cmdl.flag("verbose2"), result);
  test(cmdl.uinteger("uint") == 1200, result);
  test(cmdl.integer("uint") == 1200, result);
  test(cmdl.integer("int") == -1200, result);
  test(cmdl.uinteger("int") == 0, result);
  test(cmdl.uinteger("verbose") == 0, result);
  test(cmdl.integer("verbose") == 0, result);

  print_result(result);
}