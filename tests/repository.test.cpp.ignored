#include <lib/rsv/repository.hpp>
#include <lib/rsv/vector_based_repository.hpp>
#include <lib/rsv/list_based_repository.hpp>

#include <vector>
#include <iostream>

class myrepo : public lib::rsv::list_based_repository<int>
{
public:
  explicit myrepo(std::list<int> &&is)
      : lib::rsv::list_based_repository<int>(is) {}

public:
  virtual const int &pk(const int &i)
  {
    return i;
  }
};

int main()
{
  myrepo mr(std::list<int>{1, 2, 3, 4, 5});
  lib::rsv::repository<int> &repo = mr;

  for (int &i : repo.select_many([](const int &i)
                               { return i > 0; }))
    std::cout << i << '\n';
}