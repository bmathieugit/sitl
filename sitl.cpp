#include <fstream>
#include <streambuf>
#include <string>
#include <string_view>
#include <vector>

#include "ios.hpp"
#include "args.hpp"
//#include "tokens.hpp"
#include "logger.hpp"

//#include "syntax.hpp"
//#include <iostream>


// template <>
// struct keyword<char>
// {
//   constexpr keyword(
//       std::basic_string_view<char> sv)
//       : kw(sv) {}

//   std::basic_string_view<char> kw;
// };

// template <>
// struct keyword<wchar_t>
// {
//   constexpr keyword(
//       std::basic_string_view<wchar_t> sv)
//       : kw(sv) {}

//   std::basic_string_view<wchar_t> kw;
// };



int main(int argc, char **argv)
try
{
  lib::cmdline aparse("--", "=", ",", argc, argv);
  std::string_view fname = aparse.string("file");
  logger::info("filename found '#'", fname);

  // std::ifstream src(fname.data());

  // std::string strsrc{
  //     std::istreambuf_iterator<char>(src),
  //     std::istreambuf_iterator<char>()};

  // std::vector<sitl::token<char>> tks = sitl::tokens(std::string_view(strsrc));
  // sitl::tree<sitl::node> ast;

  // bool stype = sitl::syntax_type(tks.begin(), tks.end());

  // logger::info("resultat of syntax : #", stype);
  return EXIT_SUCCESS;
}
catch (std::exception &e)
{
  ios::printf("exception #", std::string_view(e.what()));
}