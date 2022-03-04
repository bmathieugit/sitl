#include <string_view>
#include <string>

#include "format-core.hpp"
#include "meta.hpp"

namespace fmt
{
  template <is_character C>
  struct formatter<std::basic_string<C>>
  {
    void operator()(
        std::basic_string<C> &buff,
        const std::basic_string<C> &s)
    {
      buff.append(s);
    }
  };

  template <is_character C>
  struct formatter<std::basic_string_view<C>>
  {
    void operator()(
        std::basic_string<C> &buff,
        const std::basic_string_view<C> &s)
    {
      buff.append(s);
    }
  };

  template <is_character C, size_t n>
  struct formatter<C[n]>
  {
    void operator()(
        std::basic_string<C> &buff,
        const C (&s)[n])
    {
      buff.append(std::basic_string_view<C>(s, n));
    }
  };

  template <is_character C>
  struct formatter<C>
  {
    void operator()(
        std::basic_string<C> &buff,
        C c)
    {
      buff.push_back(c);
    }
  };

}