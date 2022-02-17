#ifndef __lib_utility_hpp__
#define __lib_utility_hpp__

#include "meta.hpp"
#include "result.hpp"
#include <stdlib.h>

#define rcast reinterpret_cast

namespace lib
{
  using size_t = long unsigned;
  using byte_t = char unsigned;

  template <typename type_t>
  using ptr = type_t *;

  template <typename type_t>
  using cptr = type_t *const;

  template <typename type_t>
  constexpr remove_reference<type_t> &&
  move(type_t &&t)
  {
    return static_cast<remove_reference<type_t> &&>(t);
  }


  template <typename type_t, 
            typename type_t2>
  constexpr void move(
    type_t &dest,
    type_t2 &&src) 
  {
    dest = move(src);
  } 

  template <typename type_t, 
            typename type_t2, 
            typename type_t3>
  constexpr void move(
    type_t &dest,
    type_t2 &&src, 
    type_t3 &&null) 
  {
    dest = move(src);
    src = move(null);
  } 

  template <typename type_t, typename type_t2>
  constexpr void copy(
    type_t &dest,
    type_t2 &&src) 
  {
    dest = src;
  } 

  template <typename type_t>
  const type_t &const_me(type_t &t)
  {
    return t;
  }

  template <typename type_t>
  type_t &unconst_me(const type_t &t)
  {
    return const_cast<type_t &>(t);
  }

  template <typename type_t>
  constexpr void memcpy(
      const type_t *bsrc,
      const type_t *esrc,
      type_t *dest)
  {
    constexpr size_t cpualign = sizeof(size_t);
    constexpr size_t typealign = sizeof(type_t);

    const size_t allbytes = (esrc - bsrc) * typealign;
    size_t alignedbytes = allbytes / cpualign;

    const size_t *bsrcs = rcast<const size_t *>(bsrc);
    size_t *dests = rcast<size_t *>(dest);

    while (alignedbytes--)
      *dests++ = *bsrcs++;

    const byte_t *bsrcb = rcast<const byte_t *>(bsrcs);
    byte_t *destb = rcast<byte_t *>(dests);
    size_t tailbytes = allbytes % cpualign;

    while (tailbytes--)
      *destb++ = *bsrcb++;
  }

  template <
      size_t i,
      typename arg_t,
      typename... args_t>
  constexpr auto &get(
      const arg_t &arg,
      const args_t &...args)
  {
    static_assert(i <= sizeof...(args));

    if constexpr (i == 0)
      return arg;
    else
      return get<i - 1>(args...);
  }

  struct alloc_error
  {
  };

  template <
      typename type_t,
      typename... args_t>
  ptr<type_t>
  malloc(
      args_t &&...args) noexcept
  {
    ptr<type_t> p = std::malloc(sizeof(type_t));

    *p = type_t(args...);

    return p;
  }

  template <typename type_t, typename... args_t>
  ptr<type_t>
  mallocs(size_t nb, args_t &&...args) noexcept
  {
    
    ptr<type_t> p = static_cast<ptr<type_t>>(std::malloc(nb * sizeof(type_t)));
    auto init = p;
    auto pend = p + nb;

    while (p != pend)
      *(p++) = type_t(args...);

    return init;
  }

  template <typename type_t>
  void free(ptr<type_t> p) noexcept
  {
    if (not p)
      return;

    p->~type_t();
    std::free(p);
  }

  template <typename type_t>
  void frees(ptr<type_t> p, size_t nb) noexcept
  {
    if (p == nullptr)
      return;

    auto pend = p + nb;
    auto init = p; 

    while (p != pend)
      (*(p++)).~type_t();

    std::free(init);
  }

}

#endif
