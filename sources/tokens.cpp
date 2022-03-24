//#include "tokens.hpp"

#include <string_view>

static constexpr std::string_view lower =
    "abcdefghijklmnopqrstuvwxyz";

static constexpr std::string_view upper =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static constexpr std::string_view digit =
    "0123456789";

static constexpr std::string_view blank =
    " \n\t\r";

static constexpr std::string_view alnum =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
    "_";

static constexpr std::string_view alpha =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "_";
