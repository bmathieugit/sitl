#ifndef __lib_ios_hpp__
#define __lib_ios_hpp__

#include <string_view>
#include <cstdio>

#include "format.hpp"

namespace ios
{
  template <typename T>
  size_t fwrite(std::FILE *f, T *data, size_t count);

  void fprint(std::FILE *out, std::string_view s);
  void fprintln(std::FILE *out, std::string_view s);

  template <typename... args_t>
  void fprintf(std::FILE *out,
               std::string_view fmt,
               const args_t &...args);

  template <typename... args_t>
  void fprintfln(std::FILE *out,
                 std::string_view fmt,
                 const args_t &...args);

  template <typename... args_t>
  void printf(std::string_view fmt,
              args_t &&...args);

  template <typename... args_t>
  void printfln(std::string_view fmt,
                args_t &&...args);
}

template <typename T>
size_t ios::fwrite(std::FILE *f, T *data, size_t count)
{
  return std::fwrite(data, sizeof(T), count, f);
}

template <typename... args_t>
void ios::fprintf(
    std::FILE *out,
    std::string_view fmt,
    const args_t &...args)
{
  ios::fprint(out, fmt::format(fmt, args...));
}

template <typename... args_t>
void ios::fprintfln(
    std::FILE *out,
    std::string_view fmt,
    const args_t &...args)
{
  ios::fprintln(out, fmt::format(fmt, args...));
}

template <typename... args_t>
void ios::printf(
    std::string_view fmt,
    args_t &&...args)
{
  ios::fprintf(stdout, fmt, args...);
}

template <typename... args_t>
void ios::printfln(
    std::string_view fmt,
    args_t &&...args)
{
  ios::fprintfln(stdout, fmt, args...);
}

#endif