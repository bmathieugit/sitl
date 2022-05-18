#include <fstream>
#include <streambuf>

#include <lib/string.hpp>
#include <lib/logger.hpp>
#include <lib/args.hpp>

#include <backend/bytecodes.hpp>

int main(int argc, char **argv)
{
  lib::CommandLine args(argc, argv);

  if (args.contains("file"))
  {
    lib::StringView fname = args.value("file");
    lib::logger::debug("file name found, fname");
  }

  sitl::backend::Bytecode bytes(
    ".string S1 'hello world'\n"
    ".print stdout S1\n");

  sitl::backend::BytecodeInterpreter interpreter;
  auto prepared = interpreter.prepare(bytes);
  interpreter.interpret(prepared);

  return EXIT_SUCCESS;
}