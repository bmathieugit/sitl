#include <lib/format.hpp>
#include <lib/basic_types.hpp>
#include <cstdio>

int main()
{
  lib::Size nbsucceed = 0;
  lib::Size nbtotal = 0;
  
  (nbtotal++, nbsucceed += lib::fmt::format("#"_sv, 12).size() == 2 ? 1 : 0);
  (nbtotal++, nbsucceed += "# #!"_fmt("hello", "world").size() == 12 ? 1 : 0);
  (nbtotal++, nbsucceed += "# #!"_fmt("hello", "world").size() == 12 ? 1 : 0);
  (nbtotal++, nbsucceed += "#"_fmt(12).size() == 2 ? 1 : 0);
  (nbtotal++, nbsucceed += "#"_fmt('a').size() == 1 ? 1 : 0);
  (nbtotal++, nbsucceed += "#"_fmt('a').size() == 1 ? 1 : 0);
  (nbtotal++, nbsucceed += "#"_fmt('a').size() == 1 ? 1 : 0);

  std::printf("test OK %d/%d\n", nbsucceed, nbtotal);

  return 0;
}