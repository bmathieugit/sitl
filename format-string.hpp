#include <string_view>
#include <string>

#include "format-core.hpp"
#include "meta.hpp"

namespace fmt
{
  template <>
  struct formatter<std::string>
  {
    void operator()(
        std::string &buff,
        const std::string &s)
    {
      buff.append(s);
    }
  };

  template <>
  struct formatter<std::string_view>
  {
    void operator()(
        std::string &buff,
        const std::string_view &s)
    {
      buff.append(s);
    }
  };

  template <size_t n>
  struct formatter<char[n]>
  {
    void operator()(
        std::string &buff,
        const char (&s)[n])
    {
      buff.append(std::string_view(s, n));
    }
  };

  template <>
  struct formatter<char>
  {
    void operator()(
        std::basic_string<char> &buff,
        char c)
    {
      buff.push_back(c);
    }
  };

}