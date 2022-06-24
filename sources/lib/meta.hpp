#ifndef __lib_meta_hpp__
#define __lib_meta_hpp__

#include <lib/basic_types.hpp>

namespace meta
{
  template <typename T>
  struct NotConst
  {
    static constexpr bool value = true;
  };

  template <typename T>
  struct NotConst<const T>
  {
    static constexpr bool value = false;
  };
}

template <typename T>
concept NotConst = meta::NotConst<T>::value;

namespace meta
{
  template <typename T>
  struct NativeArray
  {
    static constexpr bool value = false;
  };

  template <typename T>
  struct NativeArray<T[]>
  {
    static constexpr bool value = true;
  };
}

template <typename T>
concept NativeArray = meta::NativeArray<T>::value;

template <typename T, typename U>
struct same_type
{
  static constexpr bool value = false;
};

template <typename T>
struct same_type<T, T>
{
  static constexpr bool value = true;
};

template <typename T, typename O>
concept same_as = same_type<T, O>::value && same_type<O, T>::value;

template <typename T, typename... O>
concept is_any_of = (same_as<T, O> || ...);

template <typename T>
concept IsInteger = is_any_of<
    T,
    short, unsigned short, const short, const unsigned short,
    int, unsigned int, const int, const unsigned int,
    long, unsigned long, const long, const unsigned long,
    long long, unsigned long long, const long long, const unsigned long long>;

template <typename T>
concept IsUnsignedInteger = is_any_of<
    T,
    unsigned short, const unsigned short,
    unsigned int, const unsigned int,
    unsigned long, const unsigned long,
    unsigned long long, const unsigned long long>;

template <typename T>
concept IsSignedInteger = IsInteger<T> && !IsUnsignedInteger<T>;

template <typename T>
concept IsBoolean = same_as<T, bool>;

template <typename T>
concept IsCharacter = is_any_of<T, char, wchar_t>;

namespace meta
{

  template <typename T>
  struct RemoveReference
  {
    using type = T;
  };

  template <typename T>
  struct RemoveReference<T &>
  {
    using type = T;
  };

  template <typename T>
  struct RemoveReference<T &&>
  {
    using type = T;
  };

  template <typename T>
  struct RemoveConstVolatile
  {
    using type = T;
  };

  template <typename T>
  struct RemoveConstVolatile<const T>
  {
    using type = T;
  };

  template <typename T>
  struct RemoveConstVolatile<volatile T>
  {
    using type = T;
  };

  template <typename T>
  struct RemoveConstVolatile<const volatile T>
  {
    using type = T;
  };
}

template <typename T>
using RemoveConstVolatile = typename meta::RemoveConstVolatile<T>::type;

template <typename T>
using RemoveReference = typename meta::RemoveReference<T>::type;

template <typename T>
using RemoveConstVolatilReference = RemoveConstVolatile<RemoveReference<T>>;

#endif
