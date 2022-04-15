#include <lib/buffer.hpp>
#include <lib/vector.hpp>

#include <cstdio>

int main()
{ 
  lib::Size nsucceed = 0;
  lib::Size ntotal = 11;

  lib::Buffer<int> ints(12);

  nsucceed += ints.size() == 0 ? 1 : 0;
  nsucceed += ints.empty() ? 1 : 0;
  nsucceed += ints.capacity() == 12 ? 1 : 0;

  ints.push_back(1);

  nsucceed += ints.size() == 1 ? 1 : 0;
  nsucceed += !ints.empty() ? 1 : 0;
  nsucceed += ints.capacity() == 12 ? 1 : 0;

  lib::FlushedBuffer<int> fb = ints.flush();

  nsucceed += ints.size() == 0 ? 1 : 0;
  nsucceed += ints.empty() ? 1 : 0;
  nsucceed += ints.capacity() == 0 ? 1 : 0;
  nsucceed += fb.lgth == 1 ? 1 : 0;
  nsucceed += fb.max == 12 ? 1 : 0;

  delete[] fb.buff;

  std::printf("test OK %d/%d\n", nsucceed, ntotal);
}