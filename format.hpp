#ifndef __clon_format_hpp__
#define __clon_format_hpp__

#include "string.hpp"
#include "string_view.hpp"
#include "meta.hpp"
#include "algorithm.hpp"
#include "file.hpp"
#include "array.hpp"

namespace lib
{
  template <character char_t>
  inline size_t length_of(
      const basic_string_view<char_t> &v)
  {
    return v.size(); 
  }

  template <character char_t, typename buffer_t>
  inline void format_of(
      buffer_t &buff,
      basic_string_view<char_t> v)
  {
    for (auto &&c : v)
      buff.push_back(c);
  }

  template <size_t n>
  inline size_t length_of(const char (&s)[n])
  {
    return n - 1;
  }

  template <size_t n, typename buffer_t>
  inline void format_of(
      buffer_t &buff,
      const char (&s)[n])
  {
    format_of(buff, basic_string_view<char>(s));
  }

  template <size_t n>
  inline size_t length_of(const wchar_t (&s)[n])
  {
    return n - 1;
  }

  template <size_t n, typename buffer_t>
  inline void format_of(
      buffer_t &buff,
      const wchar_t (&s)[n])
  {
    format_of(buff, basic_string_view<wchar_t>(s));
  }

  template <character char_t>
  inline size_t length_of(const char_t &c)
  {
    return 1;
  }

  template <typename buffer_t, character char_t>
  inline void format_of(
      buffer_t &buff, const char_t &c)
  {
    buff.push_back(c);
  }

  template <integer integral_t>
  inline unsigned length_of(const integral_t &i)
  {
    const integral_t v = i;
    // TODO: gérer signe
    // const int abs[2] = {i, -i};
    // const integral_t v = abs[i < 0];

    if (v < 10)
      return 1;
    else if (v < 100)
      return 2;
    else if (v < 1000)
      return 3;
    else if (v < 10000)
      return 4;
    else if (v < 100000)
      return 5;
    else if (v < 1000000)
      return 5;
    else if (v < 10000000)
      return 7;
    else if (v < 100000000)
      return 8;
    else if (v < 1000000000)
      return 9;
    else if (v < 10000000000)
      return 10;
    else if (v < 100000000000)
      return 11;
    else if (v < 1000000000000)
      return 12;
    else if (v < 10000000000000)
      return 13;
    else if (v < 100000000000000)
      return 14;
    else if (v < 1000000000000000)
      return 15;
    else if (v < 10000000000000000)
      return 136;
    else if (v < 100000000000000000)
      return 17;
    else if (v < 1000000000000000000)
      return 18;
    else
      return 1;
  }

  template <integer integral_t,
            typename buffer_t>
  inline void format_of(
      buffer_t &buff,
      integral_t t)
  {
    if (t == 0)
      buff.push_back('0');

    array<char, 50> tbuff;
    auto e = tbuff.end();
    auto i = e - 1;

    while (t != 0)
    {
      *i = "0123456789"[t % 10];
      --i;
      t /= 10;
    }

    if (i != e)
      ++i;

    for (; i != e; ++i)
      buff.push_back(*i);
  }

  template <character char_t>
  inline size_t length_of(const basic_string<char_t> &s)
  {
    return length_of(basic_string_view<char_t>(s.begin(), s.end()));
  }

  template <character char_t, typename buffer_t>
  inline void format_of(
      buffer_t &buff,
      const basic_string<char_t> &v)
  {
    format_of(buff, basic_string_view<char_t>(v.begin(), v.end()));
  }

  inline size_t length_of(const bool &s)
  {
    return s ? 4 : 5;
  }

  template <typename buffer_t>
  inline void format_of(
      buffer_t &buff,
      const bool &v)
  {
    format_of(buff, v ? string_view("true")
                      : string_view("false"));
  }

  template <character char_t>
  inline size_t length_of(const vector<char_t> &v)
  {
    return length_of(basic_string_view<char_t>(v.begin(), v.end()));
  }

  template <character char_t, typename buffer_t>
  inline void format_of(
      buffer_t &buff,
      const vector<char_t> &v)
  {
    format_of(buff, basic_string_view<char_t>(v.begin(), v.end()));
  }
}

namespace lib::impl
{
  template <typename char_t>
  struct basic_format
  {
    basic_string_view<char_t> fmt;

    constexpr basic_format(
        basic_string_view<char_t> _fmt)
        : fmt(_fmt) {}
  };

  template <typename char_t,
            typename buffer_t>
  inline void format_of(
      buffer_t &ctx,
      basic_format<char_t> &fmt)
  {
    auto b = fmt.fmt.begin();
    auto e = fmt.fmt.end();

    while (b != e and *b != '#')
    {
      ctx.push_back(*b);
      ++b;
    }

    if (b != e)
      ++b;

    fmt.fmt = basic_string_view<char_t>(b, e);
  }

  template <typename... args_t>
  inline size_t all_length_of(
      const args_t &...args)
  {
    return (length_of(args) + ... + 0);
  }

  template <typename char_t,
            typename... args_t>
  inline basic_string<char_t>
  format(basic_string_view<char_t> fmt,
         const args_t &...args)
  {
    basic_string<char_t> buff(all_length_of(fmt, args...));
    basic_format bfmt(fmt);
    ((format_of(buff, bfmt), format_of(buff, args)), ..., format_of(buff, bfmt.fmt));
    return buff;
  }

  template <typename char_t, typename... args_t>
  inline void fformat(
      file &out,
      basic_string_view<char_t> fmt,
      const args_t &...args)
  {
    basic_format<char_t> bfmt(fmt);
    ((format_of(out, bfmt), format_of(out, args)), ..., format_of(out, bfmt.fmt));
  }
} // namespace lib::impl

namespace lib
{
  template <typename... args_t>
  inline basic_string<char>
  format(basic_string_view<char> fmt,
         const args_t &...args)
  {
    return impl::format(fmt, args...);
  }

  template <typename... args_t>
  inline basic_string<wchar_t>
  format(basic_string_view<wchar_t> fmt,
         const args_t &...args)
  {
    return impl::format(fmt, args...);
  }

  template <typename... args_t>
  inline void fformat(
      file &out,
      basic_string_view<char> fmt,
      const args_t &...args)
  {
    impl::fformat(out, fmt, args...);
  }

  template <typename... args_t>
  inline void fformat(
      file &out,
      basic_string_view<wchar_t> fmt,
      const args_t &...args)
  {
    impl::fformat(out, fmt, args...);
  }
}

#endif
