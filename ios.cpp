#include "ios.hpp"

void ios::fprint(std::FILE *out, std::string_view s)
{
  fwrite(out, s.data(), s.size());
}

void ios::fprintln(std::FILE *out, std::string_view s)
{
  fprint(out, s);
  fprint(out, "\n");
}