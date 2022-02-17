#ifndef __lib_ios_hpp__
#define __lib_ios_hpp__

#include "file.hpp"
#include "string_view.hpp"
#include "format.hpp"

namespace lib
{
  void fprint(file &out, string_view s)
  {
    out.write(s);
  }

  void fprintln(file &out, string_view s)
  {
    fprint(out, s);
    out.push_back('\n');
  }

  template <typename... args_t>
  void fprintf(file &out, string_view f, const args_t &...args)
  {
    fformat(out, f, args...);
  }

  template <typename... args_t>
  void fprintfln(file &out, string_view f, const args_t &...args)
  {
    fprintf(out, f, args...);
    fprintln(out, "");
  }

  void print(string_view s)
  {
    fprint(cout, s);
  }

  template <typename... args_t>
  void printf(string_view f, const args_t &...args)
  {
    fprintf(cout, f, args...);
  }

  void println(string_view s)
  {
    fprintln(cout, s);
  }

  template <typename... args_t>
  void printfln(string_view f, const args_t &...args)
  {
    fprintfln(cout, f, args...);
  }
}

namespace lib
{
  void fprint(file &out, wstring_view s)
  {
    out.write(s);
  }

  void fprintln(file &out, wstring_view s)
  {
    fprint(out, s);
    out.push_back('\n');
  }

  template <typename... args_t>
  void fprintf(file &out, wstring_view f, const args_t &...args)
  {
    fformat(out, f, args...);
  }

  template <typename... args_t>
  void fprintfln(file &out, wstring_view f, const args_t &...args)
  {
    fprintf(out, f, args...);
    fprintln(out, "\n");
  }

  void print(wstring_view s)
  {
    fprint(cout, s);
  }

  template <typename... args_t>
  void printf(wstring_view f, const args_t &...args)
  {
    fprintf(cout, f, args...);
  }

  void println(wstring_view s)
  {
    fprintln(cout, s);
  }

  template <typename... args_t>
  void printfln(wstring_view f, const args_t &...args)
  {
    fprintfln(cout, f, args...);
  }
}

// namespace lib
//  {
//    scan
//  }

#endif