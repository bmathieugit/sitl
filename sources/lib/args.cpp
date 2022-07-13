#include <lib/args.hpp>

using namespace sitl;

static int toint(StringCRange s) noexcept
{
  int res = 0;

  bool neg = s.starts_with(sr("-"));
  bool pos = s.starts_with(sr("+"));

  if (pos || neg)
  {
    auto tmp = s.sub(1);
    s = StringCRange(tmp.begin(), tmp.end());
  }

  bool all_digits = s.all_of(
      [](char c)
      { return '0' <= c && c <= '9'; });

  if (all_digits)
    for (char c : s)
      res = res * 10 + (c - '0');

  return neg ? -res : res;
}

static Size touint(StringCRange s) noexcept
{
  Size res = 0;

  bool all_digits = s.all_of(
      [](char c)
      { return '0' <= c && c <= '9'; });

  if (all_digits)
    for (char c : s)
      res = res * 10 + (c - '0');

  return res;
}

CommandLine::CommandLine(
    int argc, char **argv) noexcept
    : args(argv, argv + argc) {}

Size CommandLine::size() const noexcept
{
  return args.size();
}

bool CommandLine::empty() const noexcept
{
  return args.empty();
}

bool CommandLine::contains(StringCRange wanted) const noexcept
{
  return args.any_of(
      [wanted](const char* arg)
      { return sr(arg).starts_with(wanted); });
}

StringCRange CommandLine::value(StringCRange wanted) const noexcept
{
  auto found = args.find_if(
      [wanted](const char* arg)
      { return sr(arg).starts_with(wanted); });

  return found != args.end()
             ? sr(*found).after('=')
             : StringCRange();
}

Size CommandLine::uinteger(StringCRange wanted) const noexcept
{
  StringCRange v = value(wanted);
  return touint(v);
}

long long CommandLine::integer(StringCRange wanted) const noexcept
{
  StringCRange v = value(wanted);
  return toint(v);
}

bool CommandLine::flag(StringCRange wanted) const noexcept
{
  return contains(wanted);
}
