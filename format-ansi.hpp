#ifndef __lib_format_ansi_hpp__
#define __lib_format_ansi_hpp__

#include <string_view>
#include <array>

namespace lib
{

  struct style
  {
    std::string_view code;
  };

  template <size_t n>
  struct combined_style
  {
    std::array<style, n> styles;
  };

  template <
      size_t n,
      typename T>
  struct styled_object
  {
    std::array<style, n> styles;
    const T &obj;
  };

  constexpr style black{"\u001b[30m"};
  constexpr style red{"\u001b[31m"};
  constexpr style green{"\u001b[32m"};
  constexpr style yellow{"\u001b[33m"};
  constexpr style blue{"\u001b[34m"};
  constexpr style magenta{"\u001b[35m"};
  constexpr style cyan{"\u001b[36m"};
  constexpr style white{"\u001b[37m"};

  constexpr style bblack{"\u001b[40m"};
  constexpr style bred{"\u001b[41m"};
  constexpr style bgreen{"\u001b[42m"};
  constexpr style byellow{"\u001b[43m"};
  constexpr style bblue{"\u001b[44m"};
  constexpr style bmagenta{"\u001b[45m"};
  constexpr style bcyan{"\u001b[46m"};
  constexpr style bwhite{"\u001b[47m"};

  constexpr style bold{"\u001b[1m"};
  constexpr style underline{"\u001b[4m"};
  constexpr style reversed{"\u001b[7m"};
  constexpr style reset{"\u001b[0m"};

  constexpr style cup{"\u001b[1A"};
  constexpr style cdown{"\u001b[1B"};
  constexpr style cright{"\u001b[1C"};
  constexpr style cleft{"\u001b[1D"};

  consteval combined_style<2>
  operator|(
      style s1,
      style s2)
  {
    return {{s1, s2}};
  }

  template <size_t n>
  consteval combined_style<n + 1>
  operator|(
      combined_style<n> s1,
      style s2)
  {
    combined_style<n + 1> s;

    for (size_t i = 0; i < n; ++i)
      s.styles[i] = s1.styles[i];
    s.styles[n] = s2;

    return s;
  }

  template <size_t n>
  consteval combined_style<n + 1>
  operator|(
      style s1,
      combined_style<n> s2)
  {
    combined_style<n + 1> s;

    s.styles[0] = s;
    for (size_t i = 1; i < n; ++i)
      s.styles[i] = s2.styles[i];

    return s;
  }

  template <
      typename T>
  constexpr styled_object<1, T>
  operator|(
      style s,
      const T &o)
  {
    return {{s}, o};
  }

  template <
      size_t n,
      typename T>
  constexpr styled_object<n, T>
  operator|(
      combined_style<n> s,
      const T &o)
  {
    return {s.styles, o};
  }

  template <size_t n,
            typename T>
  constexpr size_t length_of(
      const styled_object<n, T> &so)
  {
    return n * 5;
  }

}

template <
    typename char_t,
    size_t n,
    typename T>
constexpr void format_of(
    std::basic_string<char_t> &buff,
    const lib::styled_object<n, T> &so)
{
  for (auto &&s : so.styles)
    format_of(buff, s.code);

  format_of(buff, so.obj);
  format_of(buff, lib::reset.code);
}

#endif
