#include <array>
#include <string>
#include <concepts>

#include "format-model.hpp"
#include "meta.hpp"

namespace fmt
{
  template <
      typename C>
  void fmt(
      buffer<C> &buff,
      is_boolean auto b)
  {
    buff.append(b ? "true" : "false");
  }
}