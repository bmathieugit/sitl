#include <lib/rsv/repository.hpp>

#include <vector>
#include <iostream>

class myrepo : public lib::rsv::repository<int>
{
  std::vector<int> ints;

public:
  explicit myrepo(std::vector<int> &&is) : ints{is} {}

public:
  virtual int insert(const int &i)
  {
    ints.push_back(i);
    return 1;
  }

  virtual int insert(int &&i)
  {
    ints.push_back(i);
    return 1;
  }

  virtual int update(const int &t, lib::rsv::predicate<int> pred)
  {
    int cpt = 0;

    for (auto &i : ints)
      if (pred(i))
      {
        i = t;
        cpt++;
      }

    return cpt;
  }

  virtual int remove(lib::rsv::predicate<int> pred)
  {
    return std::erase_if(ints, pred);
  }

  virtual lib::rsv::one<int> select_one(lib::rsv::predicate<int> pred, size_t offset = 0)
  {
    size_t off = 0;

    for (size_t i = 0; i < ints.size(); ++i)
      if (pred(ints[i]))
      {
        if (off == offset)
          return ints[i];
        else
          off++;
      }

    return std::nullopt;
  }

  virtual lib::rsv::cursor<int> select_many(lib::rsv::predicate<int> pred)
  {
    return lib::rsv::cursor<int>{this, pred};
  }
};

int main()
{
  myrepo mr(std::vector<int>{1, 2, 3, 4, 5});
  lib::rsv::repository<int> &repo = mr;

  for (int &i : repo.select_many([](const int &i) -> bool
                                 { return i > 0; }))
  {
    std::cout << i << '\n';
  };
}