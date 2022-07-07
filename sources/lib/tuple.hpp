#ifndef __sitl_tuple_hpp__
#define __sitl_tuple_hpp__

#include <lib/utility.hpp>

namespace sitl
{
  using TupleIndex = unsigned int;

  template <TupleIndex... i>
  struct TupleSequence
  {
  };

  template <TupleIndex max, TupleIndex... i>
  struct MakeTupleSequence
      : public MakeTupleSequence<max - 1, max - 1, i...>
  {
  };

  template <TupleIndex... i>
  struct MakeTupleSequence<0, i...>
  {
    using type = TupleSequence<i...>;
  };

  template <TupleIndex N>
  using MakeTupleSequenceType = typename MakeTupleSequence<N>::type;

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
  using TupleStorage = TupleElements<MakeTupleSequenceType<sizeof...(T)>, T...>;

  template <typename... T>
  struct Tuple : TupleStorage<T...>
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
    constexpr Tuple(const Tuple<O...> &o,
                    TupleSequence<i...>)
        : TupleStorage<T...>{forward<O>(o.template get<i>())...}
    {
    }

    template <typename... O, TupleIndex... i>
    constexpr Tuple(Tuple<O...> &&o,
                    TupleSequence<i...>)
        : TupleStorage<T...>{move(o.template get<i>())...}
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
        : Tuple(o, MakeTupleSequenceType<sizeof...(T)>())
    {
    }

    template <typename... O>
    constexpr Tuple(Tuple<O...> &&o)
        : Tuple(move(o), MakeTupleSequenceType<sizeof...(T)>())
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
}

#endif