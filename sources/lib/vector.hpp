#ifndef __lib_vector_hpp__
#define __lib_vector_hpp__

#include <lib/basic_types.hpp>
#include <lib/range.hpp>
#include <lib/strong.hpp>
#include <lib/utility.hpp>

namespace sitl
{
  template<typename T>
  struct VectorData
  {
    Size lgth   = 0; 
    Size max    = 0;
    Strong<T[]> = nullptr;
  };

  template <typename P, typename T, typename O>
  concept HasPrepushPolicy = 
  requires (VectorData<T>& vd, const O& o, O&& o2) 
  {
    P::Prepush()(vd, o);
    P::Prepush()(vd, move(o2));
  };

  template <typename P, typename T, typename O>
  concept HasPushPolicy = 
  requires (VectorData<T>& vd, const O& o, O&& o2) 
  {
    P::Push()(vd, o);
    P::Push()(vd, move(o2));
  };

  template <typename P>
  concept HasPostpushPolicy = 
  requires (VectorData<T>& vd, const O& o, O&& o2) 
  {
    P::Postpush()(vd, o);
    P::postpush()(vd, move(o2));
  };

  template <typename T, typename POLICIES>
  class PVector : private VectorData<T>
  { 
  public:
    ~PVector() noexcept = default;

    PVector() noexcept = default;

    explicit PVector(Size _max) noexcept
     : lgth(0), max(_max), store(new T[max]) {}

    template <typename IT>
    PVector(IT b, IT e) noexcept 
    {}

    PVector(const PVector& o) noexcept
    {}

    PVector(PVector&& o) noexcept
    {}

    PVector& operator=(const PVector& o) noexcept
    {}

    PVector& operator=(PVector&& o) noexcept
    {}

  public:
    Size size() const noexcept 
    { return lgth; }

    bool empty() const noexcept
    { return lgth == 0; }

    Size capacity() const noexcept
    { return max; }

  public:
    auto data() noexcept 
    { return store; }

    auto data() const noexcept
    { return store; }

    auto begin() noexcept 
    { return store; }

    auto end() noexcept 
    { return store + size; }

    auto begin() const noexcept
    { return store; }

    auto end() const noexcept
    { return store + size; }

  public:
    template <typename O>
    void push(const O& o) noexcept
    {
      if constexpr (HasPrepushPolicy<POLICIES>)
        POLICIES::Prepush()(*this, o);

      if constexpr (HasPushPolicy<POLICIES>)
        POLICIES::Push()(*this, o);
     
      if constexpr (HasPostpushPolicy<POLICIES>)
        POLICIES::Postpush()(*this, o);
    }

    template <typename O>
    void push(O&& o) noexcept
    {
      if constexpr (HasPrepushPolicy<POLICIES>)
        POLICIES::Prepush()(*this, move(o));

      if constexpr (HasPushPolicy<POLICIES>)
        POLICIES::Push()(*this, move(o));
     
      if constexpr (HasPostpushPolicy<POLICIES>)
        POLICIES::Postpush()(*this, move(o));
    }

    template <typename IT>
    void append(IT b, IT e) noexcept
    {
      if constexpr (HasPreappendPolicy<POLICIES>)
        POLICIES::Preappend()(*this, b, e);
      
      for (auto&& t : Range<IT>(b, e))
        push(t);

      if constexpr (HasPostappendPolicy<POLICIES>)
        POLICIES::Postappend()(*this, b, e);
    }

    
  };
}


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
