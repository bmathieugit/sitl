#ifndef __silt_test_hpp__
#define __silt_test_hpp__

#include <vector>
#include <string>
#include <string_view>
#include <exception>

namespace sitl::test
{
  namespace constraints
  {
    template <typename exception_t>
    struct will_throw
    {
    };

    template <typename exception_t>
    struct wont_throw
    {
    };

    struct succeed
    {
    };
    
    struct failure
    {
    };
  }

  namespace check
  {
    template <typename action_t,
              typename constraint_t>
    void that(const action_t &a, const constraint_t &c)
    {
    }
  }

  namespace assert
  {
    template <typename action_t,
              typename constraint_t>
    void that(const action_t &a,
              const constraint_t &c)
    {
    }

    template <typename T, typename O>
    void equals(const T &t, const O &o)
    {
    }

  }

  struct test
  {
    std::string descr;
    void (*t)();
  };

  class fixture
  {
    std::string descr;
    std::vector<test> tests;

  public:
    template <typename... test_t>
    explicit fixture(std::string_view descr,
                     const test_t &...ts)
        : tests({ts...})
    {
    }

  public:
    void run_all()
    {
      for (const test t : tests)
      {
        t.t();
      }
    }
  };
}

sitl::test::test test(std::string_view descr, void (*t)())
{
  return sitl::test::test{descr, t};
}

sitl::test::fixture describe(
    "test dsl",
    test(" is a good idea")
        .that([]
              { assert::that([]
                             { throw std::exception(); },
                             will_throw<std::exception>{}); }));

#endif