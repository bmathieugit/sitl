#include "format.hpp"

std::string_view fmt::bfmt(
    std::string &buff,
    std::string_view fmt)
{
  auto htag = fmt.find('#');
  auto part = fmt.substr(0, htag);

  buff.append(part);

  return fmt.substr(htag != fmt.size() ? htag + 1 : htag);
};