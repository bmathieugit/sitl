#ifndef __lib_args_hpp__
#define __lib_args_hpp__

#include <lib/string.hpp>
#include <lib/array.hpp>
#include <lib/basic_types.hpp>

namespace sitl
{
  class CommandLine
  {
  private:
    Range<char **> args;

  public:
    CommandLine(int argc, char **argv) noexcept;
    CommandLine(const CommandLine &) noexcept = default;
    CommandLine(CommandLine &&) noexcept = default;
    CommandLine &operator=(const CommandLine &) noexcept = default;
    CommandLine &operator=(CommandLine &&) noexcept = default;
    ~CommandLine() noexcept = default;

  public:
    Size size() const noexcept;
    bool empty() const noexcept;

  public:
    bool contains(StringCRange wanted) const noexcept;
    StringCRange value(StringCRange wanted) const noexcept;
    Size uinteger(StringCRange wanted) const noexcept;
    long long integer(StringCRange wanted) const noexcept;
    bool flag(StringCRange wanted) const noexcept;

  public:
    StringCRange operator[](Size i) const noexcept
    {
      return sitl::sr(args[i]);
    }
  };
}

#endif
