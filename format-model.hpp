#ifndef __format_model_hpp__
#define __format_model_hpp__

#include <string>

namespace fmt
{
  template <typename C>
  using buffer = std::basic_string<C>;
}

#endif