#include <lib/args.hpp>

using namespace lib;

static int toint(StringView s) noexcept
{
  int res = 0;

  bool neg = s.range().starts_with(sv("-"));
  bool pos = s.range().starts_with(sv("+"));

  if (pos || neg)
  {
    auto tmp = s.sub(1);
    s = StringView(tmp.begin(), tmp.end());
  }

  bool all_digits = s.range().all_of(
      [](char c)
      { return '0' <= c && c <= '9'; });

  if (all_digits)
    for (char c : s)
      res = res * 10 + (c - '0');

  return neg ? -res : res;
}

static Size touint(StringView s) noexcept
{
  Size res = 0;

  bool all_digits = s.range().all_of(
      [](char c)
      { return '0' <= c && c <= '9'; });

  if (all_digits)
    for (char c : s)
      res = res * 10 + (c - '0');

  return res;
}

CommandLine::CommandLine(
    int argc, const char **argv) noexcept
    : args(argv, argc) {}

Size CommandLine::size() const noexcept
{
  return args.size();
}

bool CommandLine::empty() const noexcept
{
  return args.empty();
}

bool CommandLine::contains(StringView wanted) const noexcept
{
  return args.range().any_of(
      [wanted](const StringView &arg)
      { return arg.range().starts_with(wanted); });
}

StringView CommandLine::value(StringView wanted) const noexcept
{
  auto found = args.range().find_if(
      [wanted](const StringView &arg)
      { return arg.range().starts_with(wanted); });

  return found != args.end()
             ? (StringView(*found)).range().after('=').as<StringView>()
             : StringView();
}

Size CommandLine::uinteger(StringView wanted) const noexcept
{
  StringView v = value(wanted);
  return touint(v);
}

long long CommandLine::integer(StringView wanted) const noexcept
{
  StringView v = value(wanted);
  return toint(v);
}

bool CommandLine::flag(StringView wanted) const noexcept
{
  return contains(wanted);
}
