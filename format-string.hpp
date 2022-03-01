#include <string_view>
#include <string>

#include "format-model.hpp"

namespace fmt
{
  template <typename C>
  void fmt(
      buffer<C> &buff,
      const std::basic_string_view<C> &v)
  {
    buff.append(v.begin(), v.end());
  }

  template <typename C>
  void fmt(
      buffer<C> &buff,
      const std::basic_string<C> &s)
  {
    fmt(buff,
        std::basic_string_view<C>(s));
  }

  template <typename C, size_t n>
  void fmt(
      buffer<C> &buff,
      const C (&s)[n])
  {
    fmt(buff,
        std::basic_string_view<C>(s, n));
  }

}