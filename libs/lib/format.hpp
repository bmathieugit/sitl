#ifndef __lib_fmt_format_hpp__
#define __lib_fmt_format_hpp__

#include <string_view>
#include <string>
#include <vector>
#include <array>
#include <map>

#include <lib/meta.hpp>

namespace lib::fmt
{
  template <typename T>
  struct formatter;

  template <typename S>
  struct buffer;

  template <>
  struct buffer<std::string>
  {
    std::string buff;

    void push_back(char c)
    {
      buff.push_back(c);
    }

    void append(std::string_view sv)
    {
      buff.append(sv);
    }
  };

  template <>
  struct buffer<std::FILE *>
  {
    std::FILE *buff;

    void push_back(char c)
    {
      std::fputc(c, buff);
    }

    void append(std::string_view sv)
    {
      std::fwrite(sv.data(), sizeof(char),
                  sv.size(), buff);
    }
  };

  template <typename B>
  concept is_buffer =
      std::same_as<B, buffer<std::string>> or
      std::same_as<B, buffer<std::FILE *>>;
}

template <>
struct lib::fmt::formatter<char>
{
  void format(
      is_buffer auto &buff, char c) const
  {
    buff.push_back(c);
  }
};

template <>
struct lib::fmt::formatter<std::string_view>
{
  void format(
      is_buffer auto &buff,
      std::string_view s) const
  {
    buff.append(s);
  }
};

template <>
struct lib::fmt::formatter<std::string>
{
  void format(
      is_buffer auto &buff,
      const std::string &s) const
  {
    lib::fmt::formatter<std::string_view>{}.format(buff, s);
  }
};

template <size_t n>
struct lib::fmt::formatter<char[n]>
{
  void format(
      is_buffer auto &buff,
      const char (&s)[n]) const
  {
    lib::fmt::formatter<std::string_view>{}.format(buff, s);
  }
};

namespace lib::fmt
{

  std::string_view bfmt(
      is_buffer auto &buff,
      std::string_view fmt);

  template <typename arg_t>
  std::string_view format(
      is_buffer auto &buff,
      std::string_view fm,
      const arg_t &arg);

  template <typename... args_t>
  std::string format(
      std::string_view fm,
      const args_t &...args);

  template <typename... args_t>
  void format_to(
      std::FILE *out,
      std::string_view fm,
      const args_t &...args);

  struct literal_format
  {
    std::string_view fmt;

    std::string operator()(const auto &...args)
    {
      return lib::fmt::format(fmt, args...);
    }
  };

  struct literal_format_to
  {
    std::string_view fmt;

    std::string operator()(std::FILE *out, const auto &...args)
    {
      return lib::fmt::format_to(out, fmt, args...);
    }
  };
}

lib::fmt::literal_format
operator"" _fmt(const char *f, size_t n);

lib::fmt::literal_format_to
operator"" _fmtto(const char *f, size_t n);

std::string_view lib::fmt::bfmt(
    is_buffer auto &buff,
    std::string_view fmt)
{
  auto htag = fmt.find('#');
  auto part = fmt.substr(0, htag);

  buff.append(part);

  return fmt.substr(htag != fmt.size() ? htag + 1 : htag);
};

template <typename arg_t>
std::string_view lib::fmt::format(
    is_buffer auto &buff,
    std::string_view fm,
    const arg_t &arg)
{
  fm = lib::fmt::bfmt(buff, fm);
  lib::fmt::formatter<arg_t>{}.format(buff, arg);
  return fm;
}

template <typename... args_t>
void lib::fmt::format_to(
    std::FILE *out,
    std::string_view fm,
    const args_t &...args)
{
  lib::fmt::buffer<std::FILE *> buff{out};
  ((fm = lib::fmt::format(buff, fm, args)), ...);
  buff.append(fm);
}

template <typename... args_t>
std::string lib::fmt::format(
    std::string_view fm,
    const args_t &...args)
{
  lib::fmt::buffer<std::string> buff;
  ((fm = lib::fmt::format(buff, fm, args)), ...);
  buff.append(fm);
  return buff.buff;
};

template <is_integer T>
struct lib::fmt::formatter<T>
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

  void format(is_buffer auto &buff, T t) const
  {
    bool neg = t < 0;
    auto _abs = [](int i)
    { return i < 0 ? -i : i; };

    stack_array tbuff;

    if (t == 0)
      lib::fmt::formatter<char>{}.format(buff, '0');
    else
      while (t != 0)
      {
        tbuff.push("0123456789"[_abs(t % 10)]);
        t /= 10;
      }

    if (neg)
      tbuff.push('-');

    while (not tbuff.empty())
      lib::fmt::formatter<char>{}.format(buff, tbuff.pop());
  }
};

template <>
struct lib::fmt::formatter<bool>
{
  void format(
      is_buffer auto &buff,
      const bool &b) const
  {
    lib::fmt::formatter<std::string_view>{}
        .format(buff, (b ? "true" : "false"));
  }
};

namespace lib::fmt
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

consteval lib::fmt::combined_style<2>
operator|(
    lib::fmt::style s1,
    lib::fmt::style s2)
{
  return {{s1, s2}};
}

template <size_t n>
consteval lib::fmt::combined_style<n + 1>
operator|(lib::fmt::combined_style<n> s1,
          lib::fmt::style s2)
{
  lib::fmt::combined_style<n + 1> s;

  for (size_t i = 0; i < n; ++i)
    s.styles[i] = s1.styles[i];
  s.styles[n] = s2;

  return s;
}

template <size_t n>
consteval lib::fmt::combined_style<n + 1>
operator|(lib::fmt::style s1,
          lib::fmt::combined_style<n> s2)
{
  lib::fmt::combined_style<n + 1> s;

  s.styles[0] = s;
  for (size_t i = 1; i < n; ++i)
    s.styles[i] = s2.styles[i];

  return s;
}

template <typename T>
constexpr lib::fmt::styled_object<1, T>
operator|(lib::fmt::style s, const T &o)
{
  return {{s}, o};
}

template <size_t n, typename T>
constexpr lib::fmt::styled_object<n, T>
operator|(lib::fmt::combined_style<n> s, const T &o)
{
  return {s.styles, o};
}

template <size_t n, typename T>
struct lib::fmt::formatter<lib::fmt::styled_object<n, T>>
{
  void format(
      is_buffer auto &buff,
      const lib::fmt::styled_object<n, T> &so) const
  {
    for (auto &&s : so.styles)
      lib::fmt::formatter<std::string_view>{}.format(buff, s.code);

    lib::fmt::formatter<T>::format(buff, so.obj);
    lib::fmt::formatter<std::string_view>{}.format(buff, reset.code);
  }
};

template <typename T>
struct lib::fmt::formatter<std::vector<T>>
{
  void format(
      is_buffer auto &buff,
      const std::vector<T> &v) const
  {
    lib::fmt::formatter<char>{}.format(buff, '{');

    for (size_t i = 0; i < v.size(); ++i)
    {
      lib::fmt::formatter<T>{}.format(buff, v[i]);

      if (i < v.size() - 1)
        lib::fmt::formatter<std::string_view>{}.format(buff, ", ");
    }

    lib::fmt::formatter<char>{}.format(buff, '}');
  }
};

template <typename T, size_t n>
struct lib::fmt::formatter<std::array<T, n>>
{
  void format(
      is_buffer auto &buff,
      const std::array<T, n> &v) const
  {
    lib::fmt::formatter<char>{}.format(buff, '{');

    for (size_t i = 0; i < v.size(); ++i)
    {
      lib::fmt::formatter<T>{}.format(buff, v[i]);

      if (i < v.size() - 1)
        lib::fmt::formatter<std::string_view>{}.format(buff, ", ");
    }

    lib::fmt::formatter<char>{}.format(buff, '}');
  }
};

template <typename K, typename V>
struct lib::fmt::formatter<std::map<K, V>>
{
  void format(
      is_buffer auto &buff,
      const std::map<K, V> &m) const
  {
    lib::fmt::formatter<char>{}.format(buff, '{');

    for (const auto &p : m)
    {
      lib::fmt::formatter<K>{}.format(buff, p.first);
      lib::fmt::formatter<std::string_view>{}.format(buff, ": ");
      lib::fmt::formatter<V>{}.format(buff, p.second);
      lib::fmt::formatter<char>{}.format(buff, ';');
    }

    lib::fmt::formatter<char>{}.format(buff, '}');
  }
};

#endif
