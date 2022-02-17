#ifndef __lib_span_hpp__
#define __lib_span_hpp__

#include "utility.hpp"
#include "algorithm.hpp"

namespace lib
{
  struct normal_limit
  {
    constexpr size_t
    sized(
        size_t n)
    {
      return n;
    }
  };

  template <
      typename T,
      typename limit = normal_limit>
  class span
  {

    T *b = nullptr;
    T *e = nullptr;

  public:
    constexpr span() noexcept = default;

    constexpr span(
        const span &s) noexcept = default;

    span &operator=(
        const span &s) noexcept = default;

    ~span() = default;

    constexpr explicit span(
        T *_begin,
        T *_end)
        : b(_begin),
          e(_end) {}

    constexpr explicit span(
        T *_begin,
        size_t _length)
        : span(_begin,
               _begin + _length) {}

    template <size_t n>
    constexpr span(
        const T (&_begin)[n])
        : span(_begin, limit{}.sized(n)) {}


  public:
    constexpr T *
    begin()
    {
      return b;
    }

    constexpr T *
    end()
    {
      return e;
    }

    constexpr const T *
    begin() const
    {
      return b;
    }

    constexpr const T *
    end() const
    {
      return e;
    }

    constexpr const T *
    data() const
    {
      return b;
    }

    constexpr const T &
    operator[](
        size_t i) const
    {
      return *(b + i);
    }

    constexpr T &
    operator[](
        size_t i)
    {
      return *(b + i);
    }

    constexpr size_t
    size() const
    {
      return e - b;
    }

    constexpr bool
    empty() const
    {
      return size() == 0;
    }
  };

  template<typename T>
  span<T> span_of(T* t, size_t n)
  {
    return span<T>(t, n);
  }

  template <
      typename T1, typename lim1,
      typename T2, typename lim2>
  bool equals(
      const span<T1, lim1> s1,
      const span<T2, lim2> s2)
  {
    return lib::equals(
        s1.begin(), s1.end(),
        s2.begin(), s2.end());
  }
}

#endif