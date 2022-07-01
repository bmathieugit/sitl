#ifndef __lib_range_hpp__
#define __lib_range_hpp__

#include <lib/meta.hpp>
#include <lib/basic_types.hpp>
#include <lib/utility.hpp>

namespace sitl
{
  template <typename T>
  concept Iterator = requires(T t)
  {
    t++;
    ++t;
    t + 1;
    t - t;
    *t;
    t[0];
    t == t;
    t != t;
  };
}

namespace op
{
  constexpr auto Not = [](auto &&pred) noexcept
  {
    return [&](auto &&o)
    {
      return !pred(o);
    };
  };

  constexpr auto Equals = [](const auto &t) noexcept
  {
    return [&](auto &&o)
    {
      return o == t;
    };
  };

  constexpr auto NotEquals = [](const auto &t) noexcept
  {
    return Not(Equals(t));
  };

  constexpr auto Less = [](const auto &t) noexcept
  {
    return [&](auto &&o)
    {
      return o < t;
    };
  };

  constexpr auto LessEquals = [](const auto &t) noexcept
  {
    return [&](auto &&o)
    {
      return o <= t;
    };
  };

  constexpr auto Greater = [](const auto &t) noexcept
  {
    return [&](auto &&o)
    {
      return o > t;
    };
  };

  constexpr auto GreaterEquals = [](const auto &t) noexcept
  {
    return [&](auto &&o)
    {
      return o >= t;
    };
  };
}

namespace sitl
{

  struct FindIfAlgorithm
  {
    template <Iterator IT, typename P>
    constexpr IT operator()(IT b, IT e, P pred) const noexcept
    {
      while (b != e)
        if (pred(*b))
          return b;
        else
          ++b;

      return b;
    }
  };

  struct FindAlgorithm
  {
    template <Iterator IT, typename T>
    constexpr IT operator()(IT b, IT e, const T &t) const noexcept
    {
      return FindIfAlgorithm()(b, e, op::Equals(t));
    }
  };

  struct FindIfNotAlgorithm
  {
    template <Iterator IT, typename P>
    constexpr IT operator()(IT b, IT e, P pred) const noexcept
    {
      while (b != e)
        if (!pred(*b))
          return b;
        else
          ++b;

      return b;
    }
  };

  struct AfterIfAlgorithm
  {
    template <Iterator IT, typename P>
    constexpr IT operator()(IT b, IT e, P pred) const noexcept
    {
      auto tmp = FindIfAlgorithm()(b, e, pred);
      return tmp == e ? e : ++tmp;
    }
  };

  struct AfterAlgorithm
  {
    template <Iterator IT, typename T>
    constexpr IT operator()(IT b, IT e, const T &t) const noexcept
    {
      return AfterIfAlgorithm()(b, e, op::Equals(t));
    }
  };

  struct BeforeIfAlgorithm
  {
    template <Iterator IT, typename P>
    constexpr IT operator()(IT b, IT e, P pred) const noexcept
    {
      auto tmp = FindIfAlgorithm()(b, e, pred);
      return tmp == b ? b : tmp--;
    }
  };

  struct BeforeAlgorithm
  {
    template <Iterator IT, typename T>
    constexpr IT operator()(IT b, IT e, const T &t) const noexcept
    {
      return BeforeIfAlgorithm()(b, e, op::Equals(t));
    }
  };

  template <typename R>
  struct AroundIfAlgorithm
  {
    struct AroundResult
    {
      R before;
      R after;
    };

    template <Iterator IT, typename P>
    constexpr AroundResult operator()(IT b, IT e, P pred) const noexcept
    {
      IT fit = FindIfAlgorithm()(b, e, pred);
      return AroundResult{
          R(b, fit), R(fit != e ? ++fit : e, e)};
    }
  };

  template <typename R>
  struct AroundAlgorithm
  {
    template <Iterator IT, typename T>
    constexpr decltype(auto) operator()(IT b, IT e, const T &t) const noexcept
    {
      return AroundIfAlgorithm<R>()(b, e, op::Equals(t));
    }
  };

  template <typename R>
  struct InsideAlgorithm
  {
    template <Iterator IT, typename T>
    constexpr R operator()(IT b, IT e, const T &t1, const T &t2) const noexcept
    {
      IT it1 = FindAlgorithm()(b, e, t1);

      if (it1 == e)
        return R(e, e);

      IT it2 = FindAlgorithm()(it1 + 1, e, t2);

      return it2 == e ? R(e, e) : R(it1, it2 + 1);
    }
  };

  template <typename R>
  struct OutsideAlgorithm
  {
    struct OutsideResult
    {
      R before;
      R after;
    };

    template <Iterator IT, typename T>
    constexpr OutsideResult operator()(IT b, IT e, const T &bt, const T &et) const noexcept
    {
      R inside = InsideAlgorithm<R>()(b, e, bt, et);
      return {
          R(b, inside.begin()),
          R(inside.end(), e)};
    }
  };

  struct CountIfAlgorithm
  {
    template <Iterator IT, typename P>
    constexpr Size operator()(IT b, IT e, P pred) const noexcept
    {
      Size cnt = 0;

      while (b != e)
      {
        if (pred(*b))
          ++cnt;

        ++b;
      }

      return cnt;
    }
  };

  struct CountAlgorithm
  {
    template <Iterator IT, typename T>
    constexpr Size operator()(IT b, IT e, const T &t) const noexcept
    {
      return CountIfAlgorithm()(b, e, op::Equals(t));
    }
  };

  struct MismatchAlgorithm
  {
    template <Iterator IT, Iterator IT2>
    struct Pair
    {
      IT first;
      IT2 second;
    };

    template <Iterator IT, Iterator IT2>
    constexpr MismatchAlgorithm::Pair<IT, IT2> operator()(
        IT b, IT e, IT2 b2, IT2 e2) const noexcept
    {
      while (b != e && b2 != e2)
        if (*b == *b2)
        {
          ++b;
          ++b2;
        }
        else
          break;

      return {b, b2};
    }
  };

  struct EqualsAlgorithm
  {
    template <Iterator IT, Iterator IT2>
    constexpr bool operator()(IT b, IT e, IT2 b2, IT2 e2) const noexcept
    {
      auto &&[r1, r2] = MismatchAlgorithm()(b, e, b2, e2);
      return r1 == e && r2 == e2;
    }
  };

  struct StartsWithAlgorithm
  {
    template <Iterator IT, Iterator IT2>
    constexpr bool operator()(IT b, IT e, IT2 b2, IT2 e2) const noexcept
    {
      return MismatchAlgorithm()(b, e, b2, e2).second == e2;
    }
  };

  struct AllOfAlgorithm
  {
    template <Iterator IT, typename P>
    constexpr bool operator()(IT b, IT e, P pred) const noexcept
    {
      return FindIfNotAlgorithm()(b, e, pred) == e;
    }
  };

  struct AnyOfAlgorithm
  {
    template <Iterator IT, typename P>
    constexpr bool operator()(IT b, IT e, P pred) const noexcept
    {
      return FindIfAlgorithm()(b, e, pred) != e;
    }
  };

  struct NoneOfAlgorithm
  {
    template <Iterator IT, typename P>
    constexpr bool operator()(IT b, IT e, P pred) const noexcept
    {
      return FindIfAlgorithm()(b, e, pred) == e;
    }
  };
}

namespace sitl
{
  template <typename T>
  concept Rangeable = requires(const T &t, T &t2, T &&t3)
  {
    t.begin();
    t.end();
    t.size();
    t2.begin();
    t2.end();
    t2.size();
    t3.begin();
    t3.end();
    t3.size();
  };

  template <Iterator I>
  struct DefaultIteratorValue;

  template <typename T>
  struct DefaultIteratorValue<T *>
  {
    static constexpr T *value = nullptr;
  };

  template <typename T>
  struct DefaultIteratorValue<const T *>
  {
    static constexpr const T *value = nullptr;
  };

  template <typename M, typename IT>
  concept Mapper = requires(M &&m, IT &&it)
  {
    m(*it);
  };

  template <Iterator I, Mapper<I> M>
  class MapIterator
  {
    M mapper;
    I it;

  public:
    constexpr MapIterator(I _it, M _mapper) noexcept
        : it(_it),
          mapper(_mapper) {}

    constexpr MapIterator() noexcept = delete;
    constexpr ~MapIterator() noexcept = default;
    constexpr MapIterator(const MapIterator &) noexcept = default;
    constexpr MapIterator(MapIterator &&) noexcept = default;
    constexpr MapIterator &operator=(const MapIterator &) noexcept = default;
    constexpr MapIterator &operator=(MapIterator &&) noexcept = default;

  public:
    constexpr MapIterator &operator++() noexcept
    {
      ++it;
      return *this;
    }

    constexpr MapIterator operator++(int) noexcept
    {
      auto tmp = *this;
      ++(*this);
      return tmp;
    }

    constexpr MapIterator operator+(int offset) const noexcept
    {
      return MapIterator(it + offset, mapper);
    }

    constexpr auto operator-(const MapIterator &o) const noexcept
    {
      return it - o.it;
      ;
    }

    constexpr decltype(mapper(*it)) operator*() noexcept
    {
      return mapper(*it);
    }

    constexpr bool operator==(const MapIterator &o) const noexcept
    {
      return it == o.it;
    }

    constexpr bool operator!=(const MapIterator &o) const noexcept
    {
      return it != o.it;
    }

    constexpr decltype(auto) operator[](Size i) noexcept
    {
      return it[i];
    }

    constexpr decltype(auto) operator[](Size i) const noexcept
    {
      return it[i];
    }
  };

  template <Iterator IT>
  struct Range
  {
    IT b;
    IT e;

  public:
    constexpr Range() noexcept
        : b(DefaultIteratorValue<IT>::value),
          e(DefaultIteratorValue<IT>::value) {}
    template <Rangeable R>
    constexpr Range(R &r) noexcept
        : b(r.begin()), e(r.end()) {}
    constexpr Range(IT _b, IT _e) noexcept
        : b(_b), e(_e) {}
    constexpr Range(const Range &) noexcept = default;
    constexpr Range(Range &&) noexcept = default;
    constexpr ~Range() noexcept = default;
    constexpr Range &operator=(const Range &) noexcept = default;
    constexpr Range &operator=(Range &&) noexcept = default;

  public:
    constexpr auto operator[](Size i) const noexcept
        -> decltype(*(b + 1))
    {
      return *(b + i);
    }

    constexpr bool empty() const noexcept
    {
      return b == e;
    }

    constexpr Size size() const noexcept
    {
      return e - b;
    }

    constexpr auto begin() noexcept
    {
      return b;
    }

    constexpr auto end() noexcept
    {
      return e;
    }

    constexpr auto begin() const noexcept
    {
      return b;
    }

    constexpr auto end() const noexcept
    {
      return e;
    }

  public:
    constexpr Range sub(Size i) noexcept
    {
      return Range(i < size() ? b + i : e, e);
    }

    constexpr const Range sub(Size i) const noexcept
    {
      return Range(i < size() ? b + i : e, e);
    }

    constexpr Range sub(Size i, Size ei) noexcept
    {
      return Range(i < size() ? b + i : e, ei < size() ? b + ei : e);
    }

    constexpr const Range sub(Size i, Size ei) const noexcept
    {
      return Range(i < size() ? b + i : e, ei < size() ? b + ei : e);
    }

  public:
    template <Mapper<IT> M>
    constexpr Range<MapIterator<IT, M>> map(M &&mapper) noexcept
    {
      return Range<MapIterator<IT, M>>(
          MapIterator<IT, M>(b, mapper),
          MapIterator<IT, M>(e, mapper));
    }

    template <Mapper<IT> M>
    constexpr Range<MapIterator<IT, M>> map(M &&mapper) const noexcept
    {
      return Range<MapIterator<IT, M>>(
          MapIterator<IT, M>(b, mapper),
          MapIterator<IT, M>(e, mapper));
    }

  public:
    template <Rangeable R>
    constexpr R as() noexcept
    {
      return R(begin(), end());
    }

    template <Rangeable R>
    constexpr const R as() const noexcept
    {
      return R(begin(), end());
    }

  public:
    constexpr decltype(auto) apply(auto &&algorithm, auto &&...args) noexcept
    {
      return algorithm(begin(), end(), forward<decltype(args) &&>(args)...);
    }

    constexpr decltype(auto) apply(auto &&algorithm, auto &&...args) const noexcept
    {
      return algorithm(begin(), end(), forward<decltype(args) &&>(args)...);
    }

  public:
    constexpr Size count() const noexcept
    {
      return apply(CountIfAlgorithm(),
                   [](const RemoveReference<decltype(*declval<IT>())> &)
                   { return true; });
    }

    constexpr Size count(const RemoveReference<decltype(*declval<IT>())> &t) const noexcept
    {
      return apply(CountAlgorithm(), t);
    }

    constexpr Size count_if(auto &&pred) const noexcept
    {
      return apply(CountIfAlgorithm(), pred);
    }

    constexpr auto find(const RemoveReference<decltype(*declval<IT>())> &t) noexcept
    {
      return apply(FindAlgorithm(), t);
    }

    constexpr auto find(const RemoveReference<decltype(*declval<IT>())> &t) const noexcept
    {
      return apply(FindAlgorithm(), t);
    }

    constexpr bool contains(const RemoveReference<decltype(*declval<IT>())> &t) const noexcept
    {
      return find(t) != end();
    }

    constexpr bool contains_if(auto &&pred) const noexcept
    {
      return find_if(pred) != end();
    }

    constexpr auto find_if(auto &&pred) noexcept
    {
      return apply(FindIfAlgorithm(), pred);
    }

    constexpr auto find_if(auto &&pred) const noexcept
    {
      return apply(FindIfAlgorithm(), pred);
    }

    constexpr auto find_if_not(auto &&pred) noexcept
    {
      return apply(FindIfNotAlgorithm(), pred);
    }

    constexpr auto find_if_not(auto &&pred) const noexcept
    {
      return apply(FindIfNotAlgorithm(), pred);
    }

    constexpr bool starts_with(const Rangeable auto &o) const noexcept
    {
      return apply(StartsWithAlgorithm(), o.begin(), o.end());
    }

    constexpr Range after_if(auto &&pred) noexcept
    {
      return Range(apply(AfterIfAlgorithm(), pred), end());
    }

    constexpr const Range after_if(auto &&pred) const noexcept
    {
      return Range(apply(AfterIfAlgorithm(), pred), end());
    }

    constexpr Range before_if(auto &&pred) noexcept
    {
      return Range(begin(), apply(BeforeIfAlgorithm(), pred));
    }

    constexpr const Range before_if(auto &&pred) const noexcept
    {
      return Range(begin(), apply(BeforeIfAlgorithm(), pred));
    }

    constexpr decltype(auto) around_if(auto &&pred) noexcept
    {
      return apply(AroundIfAlgorithm<Range>(), pred);
    }

    constexpr decltype(auto) around_if(auto &&pred) const noexcept
    {
      return apply(AroundIfAlgorithm<const Range>(), pred);
    }

    constexpr Range after(const RemoveReference<decltype(*declval<IT>())> &t) noexcept
    {
      return Range(apply(AfterAlgorithm(), t), end());
    }

    constexpr const Range after(const RemoveReference<decltype(*declval<IT>())> &t) const noexcept
    {
      return Range(apply(AfterAlgorithm(), t), end());
    }

    constexpr Range before(const RemoveReference<decltype(*declval<IT>())> &t) noexcept
    {
      return Range(begin(), apply(BeforeAlgorithm(), t));
    }

    constexpr const Range before(const RemoveReference<decltype(*declval<IT>())> &t) const noexcept
    {
      return Range(begin(), apply(BeforeAlgorithm(), t));
    }

    constexpr decltype(auto) around(const RemoveReference<decltype(*declval<IT>())> &t) noexcept
    {
      return apply(AroundAlgorithm<Range>(), t);
    }

    constexpr decltype(auto) around(const RemoveReference<decltype(*declval<IT>())> &t) const noexcept
    {
      return apply(AroundAlgorithm<const Range>(), t);
    }

    constexpr decltype(auto) go_after(const RemoveReference<decltype(*declval<IT>())> &t) noexcept
    {
      auto [bf, af] = around(t);
      *this = af;
      return bf;
    }

    constexpr decltype(auto) go_after_if(auto &&pred) noexcept
    {
      auto [bf, af] = around_if(pred);
      *this = af;
      return bf;
    }

    constexpr Range inside(const RemoveReference<decltype(*declval<IT>())> &t1,
                           const RemoveReference<decltype(*declval<IT>())> &t2) noexcept
    {
      return apply(InsideAlgorithm<Range>(), t1, t2);
    }

    constexpr Range inside(const RemoveReference<decltype(*declval<IT>())> &t1,
                           const RemoveReference<decltype(*declval<IT>())> &t2) const noexcept
    {
      return apply(InsideAlgorithm<Range>(), t1, t2);
    }

    constexpr decltype(auto) outside(const RemoveReference<decltype(*declval<IT>())> &t1,
                                     const RemoveReference<decltype(*declval<IT>())> &t2) noexcept
    {
      return apply(OutsideAlgorithm<Range>(), t1, t2);
    }

    constexpr decltype(auto) outside(const RemoveReference<decltype(*declval<IT>())> &t1,
                                     const RemoveReference<decltype(*declval<IT>())> &t2) const noexcept
    {
      return apply(OutsideAlgorithm<Range>(), t1, t2);
    }

    constexpr bool all_of(auto &&pred) const noexcept
    {
      return apply(AllOfAlgorithm(), pred);
    }

    constexpr bool any_of(auto &&pred) const noexcept
    {
      return apply(AnyOfAlgorithm(), pred);
    }

    constexpr bool none_of(auto &&pred) const noexcept
    {
      return apply(NoneOfAlgorithm(), pred);
    }
  };

  template <Rangeable C>
  constexpr auto range(C &c) noexcept
      -> Range<decltype(declval<C>().begin())>
  {
    return {c};
  }

  template <Rangeable C>
  constexpr auto range(const C &c) noexcept
      -> Range<decltype(declval<const C>().begin())>
  {
    return {c};
  }

  template <typename T, Size n>
  constexpr const Range<T *> range(T (&o)[n]) noexcept
  {
    return {o, o + n};
  }

  template <typename T, Size n>
  constexpr const Range<const T *> range(const T (&o)[n]) noexcept
  {
    return {o, o + n};
  }

  template <typename T>
  constexpr Range<T *> range(T *o, Size n) noexcept
  {
    return {o, o + n};
  }

  template <typename T>
  constexpr const Range<const T *> range(const T *o, Size n) noexcept
  {
    return {o, o + n};
  }

  constexpr bool operator==(const Rangeable auto &r, const Rangeable auto &o) noexcept
  {
    return EqualsAlgorithm()(r.begin(), r.end(), o.begin(), o.end());
  }

  template <typename T, Size n>
  constexpr bool operator==(const Rangeable auto &r, const T (&o)[n]) noexcept
  {
    return r == range(o);
  }

  constexpr bool operator!=(const Rangeable auto &r, const Rangeable auto &o) noexcept
  {
    return !(r == o);
  }

  template <typename T, Size n>
  constexpr bool operator!=(const Rangeable auto &r, const T (&o)[n]) noexcept
  {
    return !(r == range(o));
  }
}

#endif