#ifndef __sitl_tuple_hpp__
#define __sitl_tuple_hpp__

#include <lib/utility.hpp>

namespace sitl
{
  using TupleIndex = unsigned int;
  
  template <TupleIndex... i> struct TupleSequence{};
  
  template <TupleIndex first, TupleIndex ... next>
  consteval auto makeSequenceImpl()
  {
    if constexpr (first == 0)
      return TupleSequence<first, next...>();
    else 
       return makeSequenceImpl<first - 1, first, next...>();
  }

  template <TupleIndex max>
  consteval auto makeSequence()
  {
    return makeSequenceImpl<max>();
  }
  
  template <typename ... T>
  using MakeSequence = decltype(makeSequence<sizeof...(T)-1>());

  template <typename T, TupleIndex i>
  struct TupleElement
  {
    T elem;
  };

  template <TupleIndex i, typename T>
  constexpr T &get(TupleElement<T, i> &te)
  {
    return te.elem;
  }

  template <TupleIndex i, typename T>
  constexpr const T &get(const TupleElement<T, i> &te)
  {
    return te.elem;
  }

  template <TupleIndex i, typename T>
  constexpr T &&get(TupleElement<T, i> &&te)
  {
    return move(te.elem);
  }

  template <typename SEQ, typename... T>
  struct TupleElements;

  template <TupleIndex... i, typename... T>
  struct TupleElements<TupleSequence<i...>, T...>
      : public TupleElement<T, i>...
  {
  };

  template <typename... T>
  using TupleStorage = TupleElements<MakeSequence<T...>, T...>;

  template <typename... T>
  class Tuple : public TupleStorage<T...>
  {
  public:
    constexpr Tuple() = default;
    constexpr ~Tuple() = default;
    constexpr Tuple(const Tuple &) = default;
    constexpr Tuple(Tuple &&) = default;
    constexpr Tuple &operator=(const Tuple &) = default;
    constexpr Tuple &operator=(Tuple &&) = default;

  private:
    template <typename... O, TupleIndex... i>
    constexpr Tuple(const Tuple<O...> &o, TupleSequence<i...>)
        : TupleStorage<T...>{get<i>(o)...}
    {
    }

    template <typename... O, TupleIndex... i>
    constexpr Tuple(Tuple<O...> &&o, TupleSequence<i...>)
        : TupleStorage<T...>{get<i>(o)...}
    {
    }

  public:
    template <typename... O>
    constexpr explicit Tuple(O &&...o)
        : TupleStorage<T...>{forward<O>(o)...}
    {
    }

    template <typename... O>
    constexpr Tuple(const Tuple<O...> &o)
        : Tuple(o, MakeSequence<T...>())
    {
    }

    template <typename... O>
    constexpr Tuple(Tuple<O...> &&o)
        : Tuple(move(o), MakeSequence<T...>())
    {
    }

  public:
    template <typename... O>
    constexpr Tuple &operator=(const Tuple<O...> &o)
    {
      static_cast<TupleStorage<T...> &>(*this) = static_cast<TupleStorage<O...>>(o);
      return *this;
    }

    template <typename... O>
    constexpr Tuple &operator=(Tuple<O...> &&o)
    {
      static_cast<TupleStorage<T...> &>(*this) = static_cast<TupleStorage<O...> &&>(o);
      return *this;
    }
  };

  template <>
  class Tuple<> {};
}

#endif
