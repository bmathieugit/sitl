#ifndef __lib_args_hpp__
#define __lib_args_hpp__

#include <string_view>
#include <span>

namespace lib
{
  class argument_parser
  {
    std::string_view prefix;
    std::string_view key_value_sep;
    std::string_view value_sep;

    std::span<char *> args;

  public:
    argument_parser(
        std::string_view _prefix,
        std::string_view _key_value_sep,
        std::string_view _value_sep, 
        int argc, char** argv);

    bool has(std::string_view arg);
    std::string_view get(std::string_view arg);
    std::string_view val(std::string_view arg);

    int integer(std::string_view arg, int def);
    bool boolean(std::string_view arg, bool def);
    std::string_view string(std::string_view arg, std::string_view def);
  };
}

#endif
