#include "format.hpp"
#include "format-ansi.hpp"
#include "ios.hpp"

int main()
{
  lib::printfln("rpouthis is the ans wer #", lib::cleft | lib::cleft | lib::bold | 42);
}
