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
    template <typename... U>
    static constexpr Vector from(U &&...us) noexcept
    {
      return Vector(
          Strong<T[]>(new T[]{forward<U>(us)...}),
          sizeof...(U));
    }

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

    constexpr Vector(Strong<T[]> &&fb, Size lgth) noexcept
        : lgth(lgth),
          max(lgth),
          storage(move(fb)) {}

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
    constexpr auto range() noexcept
    {
      return rangeof(*this);
    }

    constexpr auto range() const noexcept
    {
      return rangeof(*this);
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
    constexpr void lpush_back(const T &t) noexcept
    {
      if (lgth < max)
      {
        storage[lgth] = t;
        ++lgth;
      }
    }

    constexpr void lpush_back(T &&t) noexcept
    {
      if (lgth < max)
      {
        storage[lgth] = move(t);
        ++lgth;
      }
    }

    constexpr void push_back(const T &t) noexcept
    {
      if (lgth >= max)
        increase(max == 0 ? 10 : max * 2);

      storage[lgth] = t;
      lgth = lgth + 1;
    }

    constexpr void push_back(T &&t) noexcept
    {
      if (lgth >= max)
        increase(max == 0 ? 10 : max * 2);

      storage[lgth] = move(t);
      lgth = lgth + 1;
    }

    constexpr void push_front(const T &t) noexcept
    {
      if (lgth >= max)
        increase(max == 0 ? 10 : max * 2);

      for (Size i = lgth; i > 0; --i)
        storage[i] = move(storage[i - 1]);

      storage[0] = t;
      lgth = lgth + 1;
    }

    constexpr void push_front(T &&t) noexcept
    {
      if (lgth >= max)
        increase(max == 0 ? 10 : max * 2);

      for (Size i = lgth; i > 0; --i)
        storage[i] = move(storage[i - 1]);

      storage[0] = move(t);
      lgth = lgth + 1;
    }

    constexpr void lappend(Range<T*> sp) noexcept
    {
      lappend(sp.begin(), sp.end());
    }

    constexpr void lappend(Range<const T*> sp) noexcept
    {
      lappend(sp.begin(), sp.end());
    }

    constexpr void lappend(const Vector &o) noexcept
    {
      for (const T &t : o)
        lpush_back(t);
    }

    constexpr void lappend(Vector &&o) noexcept
    {
      for (T &&t : o)
        lpush_back(move(t));
    }

    template <typename IT>
    constexpr void lappend(IT b, IT e) noexcept
    {
      while (b != e)
      {
        lpush_back(*b);
        ++b;
      }
    }

    constexpr void append(Range<T*> sp) noexcept
    {
      append(sp.begin(), sp.end());
    }

    constexpr void append(Range<const T*> sp) noexcept
    {
      append(sp.begin(), sp.end());
    }

    constexpr void append(const Vector &o) noexcept
    {
      for (const T &t : o)
        push_back(t);
    }

    constexpr void append(Vector &&o) noexcept
    {
      for (T &&t : o)
        push_back(move(t));
    }

    template <typename IT>
    constexpr void append(IT b, IT e) noexcept
    {
      while (b != e)
      {
        push_back(*b);
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
}

#endif