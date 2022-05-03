#include <lib/strong.hpp>

#include <cstdio>

int main()
{
  lib::Size nsucceed = 0;
  lib::Size ntotal = 0;

  lib::Strong<int> i = new int(10);

  (++ntotal, nsucceed += static_cast<bool>(i) ? 1 : 0);
  (++ntotal, nsucceed += *i == 10 ? 1 : 0);
  
  i.destruct();
  
  (++ntotal, nsucceed += !static_cast<bool>(i) ? 1 : 0);

  lib::Strong<int[]> is = new int[10];
  
  for (int i = 0; i < 10; ++i)
    is[i] = i;

  (++ntotal, nsucceed += is[0] == 0 ? 1 : 0);
  (++ntotal, nsucceed += is[1] == 1 ? 1 : 0);
  (++ntotal, nsucceed += is[2] == 2 ? 1 : 0);
  (++ntotal, nsucceed += is[3] == 3 ? 1 : 0);
  (++ntotal, nsucceed += is[4] == 4 ? 1 : 0);
  (++ntotal, nsucceed += is[5] == 5 ? 1 : 0);
  (++ntotal, nsucceed += is[6] == 6 ? 1 : 0);
  (++ntotal, nsucceed += is[7] == 7 ? 1 : 0);
  (++ntotal, nsucceed += is[8] == 8 ? 1 : 0);
  (++ntotal, nsucceed += is[9] == 9 ? 1 : 0);

  is = nullptr;

  (++ntotal, nsucceed += !static_cast<bool>(is) ? 1 : 0);

  std::printf("test OK %d/%d\n", nsucceed, ntotal);
}
