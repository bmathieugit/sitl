#include <lib/string.hpp>
#include <lib/args.hpp>
#include <lib/utility.hpp>
#include <lib/iostream.hpp>

using namespace sitl;

struct HexCResult
{
  char c1;
  char c2;
};

HexCResult hexc(char c) noexcept
{
  return {
      "0123456789abcdef"[(c & 0b11110000) >> 4],
      "0123456789abcdef"[(c & 0b00001111)]};
}

char decc(char c1, char c2) noexcept
{
  // FIXME: correction de la fonction
  return 0b00000000 | (c1 << 4) | c2;
}

int main(int argc, char **argv)
{
  CommandLine cmdl(argc, argv);

  if (cmdl.size() >= 2)
  {
    StringCRange conv = cmdl[1];

    if (conv == sr("b16"))
    {
      if (cmdl.size() >= 3)
      {
        StringCRange src = cmdl[2];

        for (char c : src)
        {
          auto [c1, c2] = hexc(c);
          print(c1, c2);
        }
      }
      else
      {
        int c;
        while ((c = std::getchar()) != EOF)
        {
          // print((char)c);
          auto [c1, c2] = hexc(c);
          print(c1, c2);
        }
      }
    }
    else if (conv == sr("b10"))
    {
      if (cmdl.size() >= 3)
      {
        StringCRange src = cmdl[2];

        char c1;
        char c2;
        bool second = false;

        for (char c : src)
        {
          if (!second)
          {
            c1 = c;
            second = true;
          }
          else
            c2 = c;

          if (second)
          {
            print(decc(c1, c2));
            second = false;
          }
        }
      }
      else
      {
        char c1;
        char c2;
        bool second = false;

        int c;

        while ((c = std::getchar()) != EOF)
        {
          if (!second)
          {
            c1 = c;
            second = true;
          }
          else
            c2 = c;

          if (second)
          {
            print(decc(c1, c2));
            second = false;
          }
        }
      }
    }
  }

  println();

  return SUCCESS();
}