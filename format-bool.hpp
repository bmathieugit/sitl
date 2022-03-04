#include <array>
#include <string>
#include <concepts>

#include "meta.hpp"
#include "format-core.hpp"

namespace fmt
{
  template <is_boolean B>
  struct formatter<B>
  {
    template <typename C>
    void operator()(
        std::basic_string<C> &buff,
        const B &b)
    {
      buff.append(b ? "true" : "false");
    }
  };
}