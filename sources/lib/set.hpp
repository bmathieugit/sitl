#ifndef __lib_set_hpp__
#define __lib_set_hpp__

#include <lib/list.hpp>
#include <lib/basic_types.hpp>
#include <lib/range.hpp>

namespace sitl
{
  template <typename T>
  concept LessComparable = requires(const T &t1, const T &t2)
  {
    t1 == t2;
    t1 != t2;
    t1 <= t2;
    t1 < t2;
  };

  template <LessComparable T>
  class Set
  {
    List<T> storage;

  public:
    constexpr Set() noexcept = default;
    constexpr Set(Size _max) noexcept
        : storage(_max)
    {
    }

    template <typename IT>
    constexpr Set(IT b, IT e) noexcept
        : Set()
    {
      append(b, e);
    }

    template <Rangeable R>
    constexpr Set(R r)
        : Set(r.size())
    {
      append(r.begin(), r.end());
    }

    constexpr Set(const Set &) noexcept = default;
    constexpr Set(Set &&) noexcept = default;
    constexpr ~Set() noexcept = default;
    constexpr Set &operator=(const Set &) noexcept = default;
    constexpr Set &operator=(Set &&) noexcept = default;

  public:
    constexpr auto range() noexcept
    {
      return sitl::range(*this);
    }

    constexpr auto range() const noexcept
    {
      return sitl::range(*this);
    }

    Size size() const noexcept
    {
      return storage.size();
    }

    Size capacity() const noexcept
    {
      return storage.capacity();
    }

    bool empty() const noexcept
    {
      return storage.empty();
    }

    void push(T &&t)
    {
      auto it = range().find_if(
          [&t](const T &o) noexcept
          { return t <= o; });

      if (it == end() || *it != t)
        storage.insert(it, static_cast<T &&>(t));
    }

    void push(const T &t) noexcept
    {
      push(static_cast<T &&>(T(t)));
    }

    template <typename IT>
    void append(IT b, IT e) noexcept
    {
      while (b != e)
      {
        push(*b);
        ++b;
      }
    }

  public:
    auto begin() noexcept
    {
      return storage.begin();
    }

    auto end() noexcept
    {
      return storage.end();
    }

    auto begin() const noexcept
    {
      return storage.begin();
    }

    auto end() const noexcept
    {
      return storage.end();
    }
  };
}

#endif