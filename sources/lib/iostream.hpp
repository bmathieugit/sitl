#ifndef __lib_fmt_iostream_hpp__
#define __lib_fmt_iostream_hpp__

#include <cstdio>

#include <lib/string.hpp>
#include <lib/range.hpp>
#include <lib/array.hpp>
#include <lib/meta.hpp>

namespace sitl
{
  template <typename OUT, typename... Args>
  concept Output = requires(OUT &out,
                            Args &&...args,
                            const StringCRange &s)
  {
    out.append(s);
    out.append(char{});
  };

  struct OutputSize
  {
    Size size = 0;
  };

  template <Output OUT>
  class OutputWriter
  {
  public:
    template <typename... Args>
    constexpr auto write(Args &&...args) noexcept
    {
      auto out = OUT(forward<Args>(args)...);
      if constexpr (not same_as<decltype(out.result()), void>)
        return out.result();
    }
  };

  struct StringOutput
  {
    String res;

    template <typename... Args>
    constexpr StringOutput(Args &&...args) noexcept
        : res(String((OutputSize() + ... + args).size))
    {
      (*this << ... << forward<Args>(args));
    }

    constexpr void append(Range<const char *> sv) noexcept
    {
      res.lappend(sv);
    }

    constexpr void append(char c) noexcept
    {
      res.lpush_back(c);
    }

    constexpr String &&result() noexcept
    {
      return move(res);
    }
  };

  using StringWriter = OutputWriter<StringOutput>;

  struct FileOutput
  {
    std::FILE *out;

    template <typename... Args>
    FileOutput(std::FILE *f, Args &&...args) noexcept
        : out(f)
    {
      (*this << ... << forward<Args>(args));
    }

    void append(char c) noexcept
    {
      std::fputc(c, out);
    }

    void append(StringCRange sv) noexcept
    {
      std::fwrite(sv.begin(), sizeof(char), sv.size(), out);
    }

    void result() noexcept {}
  };

  using FileWriter = OutputWriter<FileOutput>;

  template <typename... Args>
  void print(Args &&...args) noexcept
  {
    FileWriter().write(stdout, forward<Args>(args)...);
  }

  template <typename... Args>
  void println(Args &&...args) noexcept
  {
    FileWriter().write(stdout, forward<Args>(args)..., '\n');
  }
}

namespace sitl
{
  template <Output OUT>
  constexpr OUT &operator<<(OUT &buff, char c) noexcept
  {
    buff.append(c);
    return buff;
  }

  constexpr OutputSize operator+(OutputSize size, char) noexcept
  {
    return {size.size + 1};
  }

  template <Output OUT>
  constexpr OUT &operator<<(OUT &buff, StringCRange s) noexcept
  {
    buff.append(s);
    return buff;
  }

  constexpr OutputSize operator+(OutputSize size, StringCRange sv) noexcept
  {
    return {size.size + sv.size()};
  }

  template <Output OUT>
  constexpr OUT &operator<<(OUT &buff, const char *s) noexcept
  {
    return buff << StringCRange(s, s + StrLen<char>()(s));
  }

  constexpr OutputSize operator+(OutputSize size, const char *s) noexcept
  {
    return {size.size + StrLen<char>()(s)};
  }

  template <Output OUT>
  constexpr OUT &operator<<(OUT &buff, bool b) noexcept
  {
    return buff << (b ? sr("true") : sr("false"));
  }

  constexpr OutputSize operator+(OutputSize size, bool) noexcept
  {
    return {size.size + 5};
  }

  class StackArray
  {
    char data[40];
    int i = -1;

  public:
    constexpr void push(char c) noexcept { data[++i] = c; }
    constexpr char pop() noexcept { return data[i--]; }
    constexpr bool empty() noexcept { return i == -1; }
  };

  template <Output OUT, IsUnsignedInteger T>
  constexpr OUT &operator<<(OUT &buff, T t) noexcept
  {

    StackArray tbuff;

    if (t == 0)
      buff.append('0');
    else
      while (t != 0)
      {
        tbuff.push("0123456789"[t % 10]);
        t /= 10;
      }

    while (!tbuff.empty())
      buff.append(tbuff.pop());

    return buff;
  }

  template <Output OUT, IsSignedInteger T>
  constexpr OUT &operator<<(OUT &buff, T t) noexcept
  {

    bool neg = t < 0;

    T tmp = neg ? -t : t;

    StackArray tbuff;

    if (tmp == 0)
      buff.append('0');
    else
      while (tmp != 0)
      {
        tbuff.push("0123456789"[tmp % 10]);
        tmp /= 10;
      }

    if (neg)
      buff.append('-');

    while (!tbuff.empty())
      buff.append(tbuff.pop());

    return buff;
  }

  template <IsInteger T>
  constexpr OutputSize operator+(OutputSize size, T) noexcept
  {
    return {size.size + sizeof(T) * 4};
  }
}

#endif
