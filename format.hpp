#ifndef __sitl_fmt_format_hpp__
#define __sitl_fmt_format_hpp__

#include <string_view>
#include <string>
#include <vector>
#include <array>
#include <map>

#include "meta.hpp"

namespace sitl::fmt
{
  template <typename T>
  struct formatter;

}

template <>
struct sitl::fmt::formatter<char>
{
  void format(
      std::string &buff, char c) const
  {
    buff.push_back(c);
  }
};

template <>
struct sitl::fmt::formatter<std::string_view>
{
  void format(
      std::string &buff,
      std::string_view s) const
  {
    buff.append(s);
  }
};

template <>
struct sitl::fmt::formatter<std::string>
{
  void format(
      std::string &buff,
      const std::string &s) const
  {
    sitl::fmt::formatter<std::string_view>{}.format(buff, s);
  }
};

template <size_t n>
struct sitl::fmt::formatter<char[n]>
{
  void format(
      std::string &buff,
      const char (&s)[n]) const
  {
    sitl::fmt::formatter<std::string_view>{}.format(buff, s);
  }
};

namespace sitl::fmt
{
  std::string_view
  bfmt(std::string &buff,
       std::string_view fmt);

  template <typename arg_t>
  std::string_view format(
      std::string &buff,
      std::string_view fm,
      const arg_t &arg);

  template <typename... args_t>
  std::string format(
      std::string_view fm,
      const args_t &...args);

  struct literal_format
  {
    std::string_view fmt;

    std::string operator()(const auto &...args)
    {
      return sitl::fmt::format(fmt, args...);
    }
  };
}

sitl::fmt::literal_format
operator"" _fmt(const char *f, size_t n);

template <typename arg_t>
std::string_view sitl::fmt::format(
    std::string &buff,
    std::string_view fm,
    const arg_t &arg)
{
  fm = sitl::fmt::bfmt(buff, fm);
  sitl::fmt::formatter<arg_t>{}.format(buff, arg);
  return fm;
}

template <typename... args_t>
std::string sitl::fmt::format(
    std::string_view fm,
    const args_t &...args)
{
  std::string buff;

  ((fm = sitl::fmt::format(buff, fm, args)), ...);
  buff.append(fm);

  return buff;
};

template <is_integer T>
struct sitl::fmt::formatter<T>
{
  class stack_array
  {
    char data[40];
    int i = -1;

  public:
    void push(char c) { data[++i] = c; }
    char pop() { return data[i--]; }
    bool empty() { return i == -1; }
  };

  void format(std::string &buff, T t) const
  {
    bool neg = t < 0;
    auto _abs = [](int i)
    { return i < 0 ? -i : i; };

    stack_array tbuff;

    if (t == 0)
      sitl::fmt::formatter<char>{}.format(buff, '0');
    else
      while (t != 0)
      {
        tbuff.push("0123456789"[_abs(t % 10)]);
        t /= 10;
      }

    if (neg)
      tbuff.push('-');

    while (not tbuff.empty())
      sitl::fmt::formatter<char>{}.format(buff, tbuff.pop());
  }
};

template <>
struct sitl::fmt::formatter<bool>
{
  void format(
      std::string &buff,
      const bool &b) const
  {
    sitl::fmt::formatter<std::string_view>{}
        .format(buff, (b ? "true" : "false"));
  }
};

namespace sitl::fmt
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

  consteval combined_style<2>
  operator|(style s1, style s2);

  template <size_t n>
  consteval combined_style<n + 1>
  operator|(combined_style<n> s1, style s2);

  template <size_t n>
  consteval combined_style<n + 1>
  operator|(style s1, combined_style<n> s2);

  template <typename T>
  constexpr styled_object<1, T>
  operator|(style s, const T &o);

  template <size_t n, typename T>
  constexpr styled_object<n, T>
  operator|(combined_style<n> s,
            const T &o);

  constexpr style reset{"\u001b[0m"};
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

  constexpr style cup{"\u001b[1A"};
  constexpr style cdown{"\u001b[1B"};
  constexpr style cright{"\u001b[1C"};
  constexpr style cleft{"\u001b[1D"};

}

consteval sitl::fmt::combined_style<2>
operator|(
    sitl::fmt::style s1,
    sitl::fmt::style s2)
{
  return {{s1, s2}};
}

template <size_t n>
consteval sitl::fmt::combined_style<n + 1>
operator|(sitl::fmt::combined_style<n> s1,
          sitl::fmt::style s2)
{
  sitl::fmt::combined_style<n + 1> s;

  for (size_t i = 0; i < n; ++i)
    s.styles[i] = s1.styles[i];
  s.styles[n] = s2;

  return s;
}

template <size_t n>
consteval sitl::fmt::combined_style<n + 1>
operator|(sitl::fmt::style s1,
          sitl::fmt::combined_style<n> s2)
{
  sitl::fmt::combined_style<n + 1> s;

  s.styles[0] = s;
  for (size_t i = 1; i < n; ++i)
    s.styles[i] = s2.styles[i];

  return s;
}

template <typename T>
constexpr sitl::fmt::styled_object<1, T>
operator|(sitl::fmt::style s, const T &o)
{
  return {{s}, o};
}

template <size_t n, typename T>
constexpr sitl::fmt::styled_object<n, T>
operator|(sitl::fmt::combined_style<n> s, const T &o)
{
  return {s.styles, o};
}

template <size_t n, typename T>
struct sitl::fmt::formatter<sitl::fmt::styled_object<n, T>>
{
  void format(
      std::string &buff,
      const sitl::fmt::styled_object<n, T> &so) const
  {
    for (auto &&s : so.styles)
      sitl::fmt::formatter<std::string_view>{}.format(buff, s.code);

    sitl::fmt::formatter<T>::format(buff, so.obj);
    sitl::fmt::formatter<std::string_view>{}.format(buff, reset.code);
  }
};

template <typename T>
struct sitl::fmt::formatter<std::vector<T>>
{
  void format(
      std::string &buff,
      const std::vector<T> &v) const
  {
    sitl::fmt::formatter<char>{}.format(buff, '{');

    for (size_t i = 0; i < v.size(); ++i)
    {
      sitl::fmt::formatter<T>{}.format(buff, v[i]);

      if (i < v.size() - 1)
        sitl::fmt::formatter<std::string_view>{}.format(buff, ", ");
    }

    sitl::fmt::formatter<char>{}.format(buff, '}');
  }
};

template <typename T, size_t n>
struct sitl::fmt::formatter<std::array<T, n>>
{
  void format(
      std::string &buff,
      const std::array<T, n> &v) const
  {
    sitl::fmt::formatter<char>{}.format(buff, '{');

    for (size_t i = 0; i < v.size(); ++i)
    {
      sitl::fmt::formatter<T>{}.format(buff, v[i]);

      if (i < v.size() - 1)
        sitl::fmt::formatter<std::string_view>{}.format(buff, ", ");
    }

    sitl::fmt::formatter<char>{}.format(buff, '}');
  }
};

template <typename K, typename V>
struct sitl::fmt::formatter<std::map<K, V>>
{
  void format(
      std::string &buff,
      const std::map<K, V> &m) const
  {
    sitl::fmt::formatter<char>{}.format(buff, '{');

    for (const auto &p : m)
    {
      sitl::fmt::formatter<K>{}.format(buff, p.first);
      sitl::fmt::formatter<std::string_view>{}.format(buff, ": ");
      sitl::fmt::formatter<V>{}.format(buff, p.second);
      sitl::fmt::formatter<char>{}.format(buff, ';');
    }

    sitl::fmt::formatter<char>{}.format(buff, '}');
  }
};

#endif
