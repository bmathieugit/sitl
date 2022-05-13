#include <fstream>
#include <streambuf>

#include <lib/string.hpp>
#include <lib/range.hpp>
#include <lib/logger.hpp>


struct hexs
{
  char c1;
  char c2;
};

constexpr hexs to_hex(const char c) noexcept
{
  constexpr lib::StringView hextable = "0123456789ABCDEF";
  return {
      hextable[(c & 0b11110000) >> 4],
      hextable[(c & 0b00001111)]};
}

constexpr lib::String to_hex(lib::StringView s)
{
  lib::String shex(s.size() * 2);

  for (auto c : s)
  {
    auto [c1, c2] = to_hex(c);
    shex.push_back(c1);
    shex.push_back(c2);
  }

  return shex;
}

bool starts_with_file(const char *arg)
{
  return lib::StringView(arg)
      .range()
      .starts_with("--file="_sv);
}

int main(int argc, char **argv)
{
  auto args = lib::rangeof(argv, argc);
  auto found = args.find_if(starts_with_file);

  if (found != args.end())
  {
    auto fname = lib::StringView(*found)
                     .range()
                     .after('=')
                     .as<lib::StringView>();
    lib::logger::info("file name found ", fname);
  }

  lib::String clear = "Ut tempor dolor nec libero laoreet imperdiet."
                      " Integer at tortor sapien. Etiam accumsan vel ipsum blandit pellentesque."
                      " Nullam elementum, dui ac fermentum bibendum, neque mauris dignissim sapien,"
                      " in ullamcorper dui orci ut arcu. Aenean vehicula consequat nisl, ut tristique"
                      " nisi congue sed. Praesent ante nulla, condimentum congue tempor vel, luctus in"
                      " dui. Proin at ipsum vulputate, faucibus urna sed, vulputate ex. Etiam tristique"
                      " orci vel dui aliquam tincidunt id ut risus. Morbi eget ipsum massa. Proin pretium"
                      " vestibulum metus vel molestie. Donec laoreet pretium augue, eget porta neque"
                      " eleifend eget. Proin sit amet ullamcorper nisl, quis congue turpis. Sed auctor"
                      " nisl nec sapien rhoncus, at blandit sapien scelerisque.";

  lib::logger::info(to_hex(clear));
  // std::vector<sitl::token<char>> tks = sitl::tokens(std::string_view(strsrc));
  // sitl::tree<sitl::node> ast;

  // bool stype = sitl::syntax_type(tks.begin(), tks.end());

  // logger::info("resultat of syntax : #", stype);
  return EXIT_SUCCESS;
}