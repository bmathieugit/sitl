#ifndef __lib_result_hpp__
#define __lib_result_hpp__

#include "utility.hpp"

namespace lib
{
  template <
      typename type_t,
      typename unexpected_t>
  class result
  {
    union
    {
      type_t val;
      unexpected_t unexp;
    };

    bool has_val;

  public:
    constexpr explicit result(
        const type_t &_val)
        : val(_val), has_val(true) {}

    constexpr explicit result(
        type_t &&_val)
        : val(move(_val)), has_val(true) {}

    constexpr explicit result(
        const unexpected_t &_unexp)
        : unexp(_unexp), has_val(false) {}

    constexpr explicit result(
        unexpected_t &&_unexp)
        : unexp(move(_unexp)), has_val(false) {}

    ~result()
    {
      if (has_val)
        val.~type_t();
      else
        unexp.~unexpected_t();
    }

    constexpr result(
        const result &o)
    {
      has_val = o.has_val;

      if (has_val)
        val = o.val;
      else
        unexp = o.unexp;
    }

    constexpr result(result &&o)
    {
      has_val = o.has_val;

      if (has_val)
        val = move(o.val);
      else
        unexp = move(o.unexp);
    }

    constexpr result &operator=(
        const result &o)
    {
      if (this != &o)
      {
        has_val = o.has_val;

        if (has_val)
          val = o.val;
        else
          unexp = o.unexp;
      }

      return *this;
    }

    constexpr result &operator=(
        result &&o)
    {
      if (this != &o)
      {
        has_val = o.has_val;

        if (has_val)
          val = move(o.val);
        else
          unexp = move(o.unexp);
      }

      return *this;
    }

    constexpr result &operator=(
        const type_t &o)
    {
      val = o;
      has_val = true;
      return *this;
    }

    constexpr result &operator=(
        type_t &&o)
    {
      val = move(o);
      has_val = true;
      return *this;
    }

    constexpr result &operator=(
        const unexpected_t &o)
    {
      unexp = o;
      has_val = false;
      return *this;
    }

    constexpr result &operator=(
        unexpected_t &&o)
    {
      unexp = move(o);
      has_val = false;
      return *this;
    }

  public:
    constexpr const type_t &value() const
    {
      return val;
    }

    constexpr type_t &value()
    {
      return val;
    }

    constexpr type_t &operator*()
    {
      return value();
    }

    constexpr const type_t &operator*() const
    {
      return value();
    }

    constexpr const unexpected_t &error() const
    {
      return unexp;
    }

    constexpr unexpected_t &error()
    {
      return unexp;
    }

    constexpr operator bool() const
    {
      return has_val;
    }

    constexpr operator type_t &() &
    {
      return val; 
    }


    constexpr operator const type_t &() const &
    {
      return val; 
    }

    constexpr operator type_t &&() &&
    {
      return val; 
    }

    constexpr operator const type_t &&() const &&
    {
      return val; 
    }
  };

}

#endif
