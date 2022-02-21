#ifndef __lib_ios_hpp__
#define __lib_ios_hpp__

#include <string_view>
#include <cstdio>

#include "format.hpp"

namespace lib
{
  template <typename char_t>
  void fprint(
      FILE *out,
      std::basic_string_view<char_t> s)
  {
    std::fwrite(s.data(), sizeof(char_t), s.size(), out);
  }

  template <typename char_t>
  void fprintln(
      FILE *out,
      std::basic_string_view<char_t> s)
  {
    fprint(out, s);
    fprint(out, std::basic_string_view<char_t>("\n"));
  }

  template <
      typename char_t,
      typename... args_t>
  void fprintf(
      FILE *out,
      std::basic_string_view<char_t> fmt,
      const args_t &...args)
  {
    fprint(out, format(fmt, args...));
  }

  template <
      typename char_t,
      typename... args_t>
  void fprintfln(
      FILE *out,
      std::basic_string_view<char_t> fmt,
      const args_t &...args)
  {
    fprintln(out, format(fmt, args...));
  }
}



#endif