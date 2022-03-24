#include <string_view>
#include <string>

#include <lib/format.hpp>

lib::fmt::literal_format
operator""_fmt(const char *f, size_t n)
{
  return {{f, n}};
}

lib::fmt::literal_format_to
operator""_fmtto(const char *f, size_t n)
{
  return {{f, n}};
}
