#ifndef __lib_ios_hpp__
#define __lib_ios_hpp__

#include <string_view>
#include <cstdio>

#include "format.hpp"

namespace lib
{
  template <typename T>
  size_t fwrite(FILE *f, T *data, size_t count)
  {
    return std::fwrite(data, sizeof(T), count, f);
  }

  template <typename C>
  void fprint(
      FILE *out,
      basic_view<C> s)
  {
    fwrite(out, s.data(), s.size());
  }

  template <typename C>
  void fprintln(
      FILE *out,
      basic_view<C> s)
  {
    fprint(out, s);
    fprint(out, basic_view<C>("\n"));
  }

  template <
      typename C,
      typename... args_t>
  void fprintf(
      FILE *out,
      basic_view<C> fmt,
      const args_t &...args)
  {
    fprint(out, (basic_view<C>)format(fmt, args...));
  }

  template <
      typename C,
      typename... args_t>
  void fprintfln(
      FILE *out,
      basic_view<C> fmt,
      const args_t &...args)
  {
    fprintln(out, (basic_view<C>)format(fmt, args...));
  }

  template <typename C>
  void fprint(
      FILE *out,
      const C *s)
  {
    fprint(out, basic_view<C>(s));
  }

  template <typename C>
  void fprintln(
      FILE *out,
      const C *s)
  {
    fprintln(out, basic_view<C>(s));
  }

  template <
      typename C,
      typename... args_t>
  void fprintf(
      FILE *out,
      const C *fmt,
      const args_t &...args)
  {
    fprintf(out, basic_view<C>(fmt), args...);
  }

  template <
      typename C,
      typename... args_t>
  void fprintfln(
      FILE *out,
      const C *fmt,
      const args_t &...args)
  {
    fprintfln(out, basic_view<C>(fmt), args...);
  }

  template <
      typename C,
      typename... args_t>
  void printf(
      basic_view<C> fmt,
      args_t &&...args)
  {
    fprintf(stdout, fmt, args...);
  }

  template <
      typename C,
      typename... args_t>
  void printfln(
      basic_view<C> fmt,
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
    fprintf(stdout, basic_view<C>(fmt), args...);
  }

  template <
      typename C,
      typename... args_t>
  void printfln(
      const C *fmt,
      args_t &&...args)
  {
    fprintfln(stdout, basic_view<C>(fmt), args...);
  }
}

#endif