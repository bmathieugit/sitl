#ifndef __fmt_format_vector_hpp__
#define __fmt_format_vector_hpp__

#include <string>
#include <vector>

#include "format-core.hpp"
#include "meta.hpp"

namespace fmt
{
  template <typename T>
  struct formatter<std::vector<T>>
  {
    template <is_character C>
    void operator()(
        std::basic_string<C> &buff,
        const std::vector<T> &v)
    {
      buff.push_back('{');

      for (size_t i = 0; i < v.size(); ++i)
      {
        formatter<T>{}(buff, v[i]);

        if (i < v.size() - 1)
          buff.append(", ");
      }

      buff.push_back('}');
    }
  };
}

#endif