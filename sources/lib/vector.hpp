#ifndef __lib_vector_hpp__
#define __lib_vector_hpp__

#include <lib/basic_types.hpp>
#include <lib/range.hpp>
#include <lib/strong.hpp>
#include <lib/utility.hpp>

namespace sitl
{
  template <typename T>
  class Vector
  {
    Size lgth = 0;
    Size max = 0;
    Strong<T[]> storage;

  public:
    constexpr Vector() noexcept = default;

    explicit constexpr Vector(Size _max) noexcept
        : lgth(0),
          max(_max),
          storage{new T[max]}
    {
    }

    template <typename IT>
    constexpr Vector(IT b, IT e) noexcept
        : Vector()
    {
      append(b, e);
    }

    template <Rangeable R>
    constexpr Vector(R r) noexcept
        : Vector(r.size())
    {
      lappend(r);
    }

    constexpr Vector(const Vector &o) noexcept
        : Vector(o.max)
    {
      lappend(o.begin(), o.end());
    }

    constexpr Vector(Vector &&o) noexcept
        : lgth(o.lgth),
          max(o.max),
          storage(move(o.storage))
    {
      o.lgth = 0;
      o.max = 0;
    }

    constexpr ~Vector() noexcept = default;

    constexpr Vector &operator=(const Vector &o) noexcept
    {
      if (this != &o)
      {
        lgth = 0;
        max = o.max;
        storage = new T[max];
        lappend(o.begin(), o.end());
      }

      return *this;
    }

    constexpr Vector &operator=(Vector &&o) noexcept
    {
      if (this != &o)
      {
        lgth = o.lgth;
        max = o.max;
        storage = move(o.storage);
        o.lgth = 0;
        o.max = 0;
      }

      return *this;
    }

  public:
    constexpr operator Range<T *>() noexcept
    {
      return range();
    }

    constexpr operator Range<const T *>() const noexcept
    {
      return range();
    }

    constexpr auto range() noexcept
    {
      return sitl::range(*this);
    }

    constexpr auto range() const noexcept
    {
      return sitl::range(*this);
    }

    constexpr Size size() const noexcept
    {
      return lgth;
    }

    constexpr Size capacity() const noexcept
    {
      return max;
    }

    constexpr bool empty() const noexcept
    {
      return lgth == 0;
    }

    constexpr T *data() noexcept
    {
      return storage;
    }

    constexpr const T *data() const noexcept
    {
      return storage;
    }

  public:
    constexpr void increase(Size more) noexcept
    {
      if (more == 0)
        return;

      Strong<T[]> nstorage = new T[max + more];

      for (Size i = 0; i < lgth; ++i)
        nstorage[i] = move(storage[i]);

      storage = move(nstorage);
      max = max + more;
    }

    constexpr void clear() noexcept
    {
      lgth = 0;
    }

  public:
    constexpr void lpush(const T &t) noexcept
    {
      if (lgth < max)
      {
        storage[lgth] = t;
        ++lgth;
      }
    }

    constexpr void lpush(T &&t) noexcept
    {
      if (lgth < max)
      {
        storage[lgth] = move(t);
        ++lgth;
      }
    }

    constexpr void push(const T &t) noexcept
    {
      if (lgth >= max)
        increase(max == 0 ? 10 : max * 2);

      storage[lgth] = t;
      lgth = lgth + 1;
    }

    constexpr void push(T &&t) noexcept
    {
      if (lgth >= max)
        increase(max == 0 ? 10 : max * 2);

      storage[lgth] = move(t);
      lgth = lgth + 1;
    }

    constexpr void lappend(Range<T *> sp) noexcept
    {
      lappend(sp.begin(), sp.end());
    }

    constexpr void lappend(Range<const T *> sp) noexcept
    {
      lappend(sp.begin(), sp.end());
    }

    constexpr void lappend(const Vector &o) noexcept
    {
      for (const T &t : o)
        lpush(t);
    }

    constexpr void lappend(Vector &&o) noexcept
    {
      for (T &&t : o)
        lpush(move(t));
    }

    template <typename IT>
    constexpr void lappend(IT b, IT e) noexcept
    {
      while (b != e)
      {
        lpush(*b);
        ++b;
      }
    }

    constexpr void append(Range<T *> sp) noexcept
    {
      append(sp.begin(), sp.end());
    }

    constexpr void append(Range<const T *> sp) noexcept
    {
      append(sp.begin(), sp.end());
    }

    constexpr void append(const Vector &o) noexcept
    {
      for (const T &t : o)
        push(t);
    }

    constexpr void append(Vector &&o) noexcept
    {
      for (T &&t : o)
        push(move(t));
    }

    template <typename IT>
    constexpr void append(IT b, IT e) noexcept
    {
      while (b != e)
      {
        push(*b);
        ++b;
      }
    }

    constexpr T &operator[](Size i) noexcept
    {
      return storage[i];
    }

    const T &operator[](Size i) const noexcept
    {
      return storage[i];
    }

    constexpr T &back() noexcept
    {
      return storage[size() - 1];
    }

    constexpr const T &back() const noexcept
    {
      return storage[size() - 1];
    }

  public:
    constexpr T *begin() noexcept
    {
      return storage;
    }

    constexpr T *end() noexcept
    {
      return static_cast<T *>(storage) + lgth;
    }

    constexpr const T *begin() const noexcept
    {
      return storage;
    }

    constexpr const T *end() const noexcept
    {
      return static_cast<const T *>(storage) + lgth;
    }
  };

  template <typename T>
  using VectorRange = Range<T *>;

  template <typename T>
  using VectorCRange = Range<const T *>;
}

#endif