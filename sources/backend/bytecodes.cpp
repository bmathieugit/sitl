#include <backend/bytecodes.hpp>
#include <lib/iostream.hpp>
#include <lib/logger.hpp>

using namespace sitl::backend;

///// Bytecode

Bytecode::Bytecode(lib::StringView _bytes) noexcept
    : bytes(_bytes)
{
}

Bytecode &Bytecode::operator=(lib::StringView _bytes) noexcept
{
  bytes.clear();
  bytes.append(_bytes);
  return *this;
}

lib::StringView Bytecode::bytecode() const noexcept
{
  return bytes;
}

///// BytecodeInstruction

BytecodeInstruction::BytecodeInstruction(lib::StringView inst)
{
  if (!inst.empty())
  {
    if (inst[0] == '.')
    {
      verb = inst.range().before(' ');
      lib::StringView args = inst.range().after(' ');

      if (!args.empty())
      {
        if (args[0] == '\'')
          arg1 = args.range().inside('\'', '\'');
        else
          arg1 = args.range().before(' ');

        lib::logger::debug("arg1 ", arg1);
        

        args = lib::StringView(arg1.end()).range().after(' ');
        lib::logger::debug("args ", args);

        if (args[0] == '\'')
          arg2 = args.range().inside('\'', '\'');
        else
          arg2 = args.range().before(' ');

        lib::logger::debug("arg2 ", arg2);

        args = lib::StringView(arg2.end()).range().after(' ');
        lib::logger::debug("args ", args);

        if (args[0] == '\'')
          arg3 = args.range().inside('\'', '\'');
        else
          arg3 = args.range().before(' ');
      }
    }
  }
}

///// BytecodeInterpreter

PreparedBytecode BytecodeInterpreter::prepare(const Bytecode &bytecode) const noexcept
{
  PreparedBytecode prepared;
  lib::StringView bc = bytecode.bytecode();
  lib::StringView sinst = bc.range().before('\n');
  lib::StringView tail = bc.range().after('\n');

  while (!sinst.empty())
  {
    prepared.instrs.push_back(BytecodeInstruction(sinst));
    sinst = tail.range().before('\n');
    tail = tail.range().after('\n');
  }

  return prepared;
}

bool BytecodeInterpreter::interpret(const PreparedBytecode &prepared) const noexcept
{
  lib::Vector<lib::String> strings;

  for (const BytecodeInstruction &inst : prepared.instrs)
  {
    if (inst.verb == sv(".string"))
    {
      strings.push_back(inst.arg2);
    }
    else if (inst.verb == sv(".print"))
    {
      if (inst.arg1 == sv("stdout"))
        lib::FileWriter().write(stdout, strings[0]);
    }
  }

  return true;
}