#ifndef __lib_args_hpp__
#define __lib_args_hpp__

#include <lib/string.hpp>
#include <lib/array.hpp>
#include <lib/basic_types.hpp>

namespace lib
{

  class CommandLine
  {
  private:
    ArrayView<const char *> args;

  public:
    CommandLine(int argc, const char **argv) noexcept;
    CommandLine(const CommandLine &) noexcept = default;
    CommandLine(CommandLine &&) noexcept = default;
    CommandLine &operator=(const CommandLine &) noexcept = default;
    CommandLine &operator=(CommandLine &&) noexcept = default;
    ~CommandLine() noexcept = default;

  public:
    Size size() const noexcept;
    bool empty() const noexcept;

  public:
    bool contains(StringView wanted) const noexcept;
    StringView value(StringView wanted) const noexcept;
    Size uinteger(StringView wanted) const noexcept;
    long long integer(StringView wanted) const noexcept;
    bool flag(StringView wanted) const noexcept;
  };
}

#endif
