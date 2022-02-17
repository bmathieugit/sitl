#ifndef __lib_format_ansi_hpp__
#define __lib_format_ansi_hpp__

#include "string_view.hpp"
#include "utility.hpp"
#include "array.hpp"
#include "algorithm.hpp"

namespace lib
{

  /*
  constexpr style red = "\u001b[31m"
  constexpr style bold = \u001b[1m
  constexpr style underline = "\u001b[4m"

  => red | bold | underline
  => format ("toto a #", (red | bold)(12));
  
  */
  template <character char_t>
  struct style
  {
    basic_string_view<char_t> code;
  };

  template <character char_t, size_t n>
  struct combined_style
  {
    array<style<char_t>, n> styles;
  };

  template <
      character char_t,
      size_t n,
      typename type_t>
  struct styled_object
  {
    array<style<char_t>, n> styles;
    const type_t &obj;
  };

  constexpr style<char> black{"\u001b[30m"};
  constexpr style<char> red{"\u001b[31m"};
  constexpr style<char> green{"\u001b[32m"};
  constexpr style<char> yellow{"\u001b[33m"};
  constexpr style<char> blue{"\u001b[34m"};
  constexpr style<char> magenta{"\u001b[35m"};
  constexpr style<char> cyan{"\u001b[36m"};
  constexpr style<char> white{"\u001b[37m"};

  constexpr style<char> bblack{"\u001b[40m"};
  constexpr style<char> bred{"\u001b[41m"};
  constexpr style<char> bgreen{"\u001b[42m"};
  constexpr style<char> byellow{"\u001b[43m"};
  constexpr style<char> bblue{"\u001b[44m"};
  constexpr style<char> bmagenta{"\u001b[45m"};
  constexpr style<char> bcyan{"\u001b[46m"};
  constexpr style<char> bwhite{"\u001b[47m"};

  constexpr style<char> bold{"\u001b[1m"};
  constexpr style<char> underline{"\u001b[4m"};
  constexpr style<char> reversed{"\u001b[7m"};
  constexpr style<char> reset{"\u001b[0m"};

  constexpr style<char> cup{"\u001b[1A"};
  constexpr style<char> cdown{"\u001b[1B"};
  constexpr style<char> cright{"\u001b[1C"};
  constexpr style<char> cleft{"\u001b[1D"};

  template <character char_t>
  consteval combined_style<char_t, 2>
  operator|(
      style<char_t> s1,
      style<char_t> s2)
  {
    return {{s1, s2}};
  }

  template <character char_t, size_t n>
  consteval combined_style<char_t, n + 1>
  operator|(
      combined_style<char_t, n> s1,
      style<char_t> s2)
  {
    combined_style<char_t, n + 1> s;
    lib::copy_all(
        s1.styles.begin(),
        s1.styles.end(),
        s.styles.begin());
    s.styles[n] = s2;
    return s;
  }

  template <character char_t, size_t n>
  consteval combined_style<char_t, n + 1>
  operator|(
      style<char_t> s1,
      combined_style<char_t, n> s2)
  {
    combined_style<char_t, n + 1> s;
    lib::copy_all(
        s1.styles.begin() + 1,
        s1.styles.end(),
        s.styles.begin());
    s.styles[0] = s2;
    return s;
  }

  template <
      character char_t,
      typename type_t>
  constexpr styled_object<char_t, 1, type_t>
  operator|(
      style<char_t> s,
      const type_t &o)
  {
    return {{s}, o};
  }

  template <
      character char_t,
      size_t n,
      typename type_t>
  constexpr styled_object<char_t, n, type_t>
  operator|(
      combined_style<char_t, n> s,
      const type_t &o)
  {
    return {s.styles, o};
  }

  template <typename char_t, size_t n,
            typename type_t>
  constexpr size_t length_of(
      const styled_object<char_t, n, type_t> &so)
  {
    return n * 5;
  }

  template <typename char_t, size_t n,
            typename type_t, typename buffer_t>
  inline void format_of(
      buffer_t &buff,
      const styled_object<char_t, n, type_t> &so)
  {
    for (auto &&s : so.styles)
      format_of(buff, s.code);
    format_of(buff, so.obj);
    format_of(buff, reset.code);
  }

}

#endif
