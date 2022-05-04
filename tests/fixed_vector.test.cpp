#include <lib/fixed_vector.hpp>
#include <cstdio>

int main()
{
  lib::Size nsucceed = 0;
  lib::Size ntotal = 0;

  lib::FixedVector<int> ints(12);
  for (lib::Size i = 0; i < 12; ++i)
    ints.push_back(i);

  (++ntotal, nsucceed += ints.size() == 12 ? 1 : 0);
  (++ntotal, nsucceed += ints.capacity() == 12 ? 1 : 0);

  lib::FixedVector<int> ints2(lib::FixedVector<int>::from(1, 2, 3));

  (++ntotal, nsucceed += ints2.size() == 3 ? 1 : 0);
  (++ntotal, nsucceed += ints2.capacity() == 3 ? 1 : 0);

  ints2.push_back(4);

  (++ntotal, nsucceed += ints2.size() == 3 ? 1 : 0);
  (++ntotal, nsucceed += ints2.capacity() == 3 ? 1 : 0);

  (++ntotal, nsucceed += ints2[0] == 1 ? 1 : 0);
  (++ntotal, nsucceed += ints2[1] == 2 ? 1 : 0);
  (++ntotal, nsucceed += ints2[2] == 3 ? 1 : 0);

  ints2.clear();

  (++ntotal, nsucceed += ints2.size() == 0 ? 1 : 0);
  (++ntotal, nsucceed += ints2.capacity() == 3 ? 1 : 0);

  auto ints3 = lib::FixedVector<int>::from(1, 2, 3, 4, 5);
  auto ints4 = lib::FixedVector<int>::from(1, 2, 3, 4, 5);

  (++ntotal, nsucceed += ints3 == ints4 ? 1 : 0);

  std::printf("test OK %d/%d\n", nsucceed, ntotal);
}