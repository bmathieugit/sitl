#ifndef __lib_args_hpp__
#define __lib_args_hpp__

#include "string.hpp"
#include "array.hpp"

namespace lib
{
  template <typename char_t>
  class argument_parser
  {
    basic_string<char_t> prefix;
    basic_string<char_t> value_sep;
    basic_string<char_t> key_value_sep;

    argument_parser(
        basic_string_view<char_t> _prefix,
        basic_string_view<char_t> _value_sep,
        basic_string_view<char_t> _key_value_sep)
        : prefix(_prefix),
          value_sep(_value_sep),
          key_value_sep(_key_value_sep)
    {
    }
  };
}

#endif
