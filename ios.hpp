#ifndef __lib_ios_hpp__
#define __lib_ios_hpp__

#include <string_view>
#include <cstdio>

#include "format.hpp"

namespace ios
{
  template <typename T>
  size_t fwrite(std::FILE *f, T *data, size_t count)
  {
    return std::fwrite(data, sizeof(T), count, f);
  }

  template <typename C>
  void fprint(
      std::FILE *out,
      std::basic_string_view<C> s)
  {
    fwrite(out, s.data(), s.size());
  }

  template <typename C>
  void fprintln(
      std::FILE *out,
      std::basic_string_view<C> s)
  {
    fprint(out, s);
    fprint(out, std::basic_string_view<C>("\n"));
  }

  template <
      typename C,
      typename... args_t>
  void fprintf(
      std::FILE *out,
      std::basic_string_view<C> fmt,
      const args_t &...args)
  {
    fprint(out, (std::basic_string_view<C>)fmt::format(fmt, args...));
  }

  template <
      typename C,
      typename... args_t>
  void fprintfln(
      std::FILE *out,
      std::basic_string_view<C> fmt,
      const args_t &...args)
  {
    fprintln(out, (std::basic_string_view<C>)fmt::format(fmt, args...));
  }

  template <typename C>
  void fprint(
      std::FILE *out,
      const C *s)
  {
    fprint(out, std::basic_string_view<C>(s));
  }

  template <typename C>
  void fprintln(
      std::FILE *out,
      const C *s)
  {
    fprintln(out, std::basic_string_view<C>(s));
  }

  template <
      typename C,
      typename... args_t>
  void fprintf(
      std::FILE *out,
      const C *fmt,
      const args_t &...args)
  {
    fprintf(out, std::basic_string_view<C>(fmt), args...);
  }

  template <
      typename C,
      typename... args_t>
  void fprintfln(
      std::FILE *out,
      const C *fmt,
      const args_t &...args)
  {
    fprintfln(out, std::basic_string_view<C>(fmt), args...);
  }

  template <
      typename C,
      typename... args_t>
  void printf(
      std::basic_string_view<C> fmt,
      args_t &&...args)
  {
    fprintf(stdout, fmt, args...);
  }

  template <
      typename C,
      typename... args_t>
  void printfln(
      std::basic_string_view<C> fmt,
      args_t &&...args)
  {
    fprintfln(stdout, fmt, args...);
  }

  template <
      typename C,
      typename... args_t>
  void printf(
      const C *fmt,
      args_t &&...args)
  {
    fprintf(stdout, std::basic_string_view<C>(fmt), args...);
  }

  template <
      typename C,
      typename... args_t>
  void printfln(
      const C *fmt,
      args_t &&...args)
  {
    fprintfln(stdout, std::basic_string_view<C>(fmt), args...);
  }
}

#endif