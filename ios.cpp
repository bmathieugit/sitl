#include "ios.hpp"

void sitl::ios::fprint(std::FILE *out, std::string_view s)
{
  sitl::ios::fwrite(out, s.data(), s.size());
}

void sitl::ios::fprintln(std::FILE *out, std::string_view s)
{
  sitl::ios::fprint(out, s);
  sitl::ios::fprint(out, "\n");
}