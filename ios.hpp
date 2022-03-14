#ifndef __sitl_ios_hpp__
#define __sitl_ios_hpp__

#include <string_view>
#include <cstdio>

#include "format.hpp"

namespace sitl::ios
{
  template <typename T>
  size_t fwrite(std::FILE *f, T *data, size_t count);

  void fprint(std::FILE *out, std::string_view s);
  void fprintln(std::FILE *out, std::string_view s);

  void fprintf(std::FILE *out,
               std::string_view fmt,
               const auto &...args);

  void fprintfln(std::FILE *out,
                 std::string_view fmt,
                 const auto &...args);

  void printf(std::string_view fmt,
              const auto &...args);

  void printfln(std::string_view fmt,
                const auto &...args);
}

template <typename T>
size_t sitl::ios::fwrite(std::FILE *f, T *data, size_t count)
{
  return std::fwrite(data, sizeof(T), count, f);
}

void sitl::ios::fprintf(
    std::FILE *out,
    std::string_view fmt,
    const auto &...args)
{
  sitl::ios::fprint(out, sitl::fmt::format(fmt, args...));
}

void sitl::ios::fprintfln(
    std::FILE *out,
    std::string_view fmt,
    const auto &...args)
{
  sitl::ios::fprintln(out, sitl::fmt::format(fmt, args...));
}

void sitl::ios::printf(
    std::string_view fmt,
    const auto &...args)
{
  sitl::ios::fprintf(stdout, fmt, args...);
}

void sitl::ios::printfln(
    std::string_view fmt,
    const auto &...args)
{
  sitl::ios::fprintfln(stdout, fmt, args...);
}

#endif