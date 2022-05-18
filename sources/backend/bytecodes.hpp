#ifndef __sitl_backend_bytecodes_hpp__
#define __sitl_backend_bytecodes_hpp__

#include <lib/string.hpp>
#include <lib/vector.hpp>

namespace sitl::backend
{
  class Bytecode
  {
  private:
    lib::String bytes;

  public:
    Bytecode() noexcept = default;
    explicit Bytecode(lib::StringView) noexcept;
    Bytecode(const Bytecode &) noexcept = default;
    Bytecode(Bytecode &&) noexcept = default;
    ~Bytecode() noexcept = default;
    Bytecode &operator=(lib::StringView) noexcept;
    Bytecode &operator=(const Bytecode &) noexcept = default;
    Bytecode &operator=(Bytecode &&) noexcept = default;

  public:
    lib::StringView bytecode() const noexcept;
  };

  struct BytecodeInstruction
  {
    lib::StringView verb;
    lib::StringView arg1;
    lib::StringView arg2;
    lib::StringView arg3;

    BytecodeInstruction() = default;
    BytecodeInstruction(lib::StringView inst);
  };

  struct PreparedBytecode
  {
    lib::Vector<BytecodeInstruction> instrs = lib::Vector<BytecodeInstruction>(20);
  };

  class BytecodeInterpreter
  {
  public:
    PreparedBytecode prepare(const Bytecode &bytecode) const noexcept;
    bool interpret(const PreparedBytecode &prepared) const noexcept;
  };
}

#endif