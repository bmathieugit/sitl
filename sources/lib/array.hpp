#ifndef __lib_array_hpp__
#define __lib_array_hpp__

#include <lib/basic_types.hpp>
#include <lib/range.hpp>

namespace sitl
{

  template <typename T, Size n>
  struct Array
  {
    T b[n];

  public:
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
      return n;
    }

    constexpr bool empty() const noexcept
    {
      return false;
    }

    constexpr T *data() noexcept
    {
      return b;
    }

    constexpr const T *data() const noexcept
    {
      return b;
    }

    T &operator[](Size i) &noexcept
    {
      return b[i];
    }

    constexpr const T &operator[](Size i) const &noexcept
    {
      return b[i];
    }

    constexpr T &&operator[](Size i) &&noexcept
    {
      return b[i];
    }

    constexpr const T &&operator[](Size i) const &&noexcept
    {
      return b[i];
    }

    constexpr operator Range<const T*>() const noexcept
    {
      return Range<const T*>(this->data(), this->size());
    }

    constexpr operator Range<T*>() noexcept
    {
      return Range<T*>(this->data(), this->size());
    }

  public:
    constexpr T *begin() noexcept
    {
      return b;
    }

    constexpr T *end() noexcept
    {
      return b + n;
    }

    constexpr const T *begin() const noexcept
    {
      return b;
    }

    constexpr const T *end() const noexcept
    {
      return b + n;
    }
  };
}

#endif