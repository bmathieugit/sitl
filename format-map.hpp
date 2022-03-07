#ifndef __fmt_format_map_hpp__
#define __fmt_format_map_hpp__

#include <string>
#include <map>

#include "format-core.hpp"
#include "meta.hpp"

namespace fmt
{
  template <typename K, typename V>
  struct formatter<std::map<K, V>>
  {
    template <is_character C>
    void operator()(
        std::basic_string<C> &buff,
        const std::map<K, V> &m)
    {
      buff.push_back('{');

      for (const auto& p: m)
      {
        formatter<K>{}(buff, p.first);
        buff.append(": ");
        formatter<V>{}(buff, p.second);
        buff.push_back(';');
      }

      buff.push_back('}');
    }
  };
}

#endif