#include <fstream>
#include <streambuf>
#include <string>
#include <string_view>
#include <vector>

#include "args.hpp"
#include "logger.hpp"
//#include "tokens.hpp"

//#include "syntax.hpp"
//#include <iostream>
#include "test.hpp"

int main(int argc, char **argv)
try
{
  sitl::logger::info("# #"_fmt(1, 2));

  sitl::cmdline aparse("--", "=", ",", argc, argv);
  std::string_view fname = aparse.string("file");
  sitl::logger::info("filename found '#'", fname);

  std::ifstream src(fname.data());

  std::string strsrc{
      std::istreambuf_iterator<char>(src),
      std::istreambuf_iterator<char>()};

  "this is a test suite"_suite(
      "this is a test"_test(
          []
          {
            std::array<int, 3> i = {1, 2, 3};
            sitl::logger::info("#", i);
            sitl::test::assert::that(
                sitl::test::is::equals{},
                i.size(), (size_t)3);
          }),
      "this is a second test"_test(
          []
          {
            std::array<int, 3> i = {1, 2, 3};
            sitl::logger::debug("nous avons un soucis #", i);
            sitl::test::assert::equals(i.size(), (size_t)4);
          }),
      "this is a third test"_test(
          []
          {
            std::array<int, 4> i = {1, 2, 2, 4};
            sitl::logger::debug("nous avons un soucis # 2", i);
          }))
      .run();

  // std::vector<sitl::token<char>> tks = sitl::tokens(std::string_view(strsrc));
  // sitl::tree<sitl::node> ast;

  // bool stype = sitl::syntax_type(tks.begin(), tks.end());

  // logger::info("resultat of syntax : #", stype);
  return EXIT_SUCCESS;
}
catch (std::exception &e)
{
  sitl::logger::error("exception #", std::string_view(e.what()));
}