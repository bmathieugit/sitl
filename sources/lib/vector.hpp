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
    Size max  = 0;
    Strong<T[]> store;

  public:
    Vector()  = default;

    explicit Vector(Size _max) 
        : lgth(0), max(_max), store{new T[max]}
    {
    }

    template <Iterator IT>
    Vector(IT b, IT e) 
      : Vector(e - b)
    {
      lappend(b, e);
    }

    template <Iterator IT>
    Vector(Range<IT> r) 
      : Vector(r.begin(), r.end())
    {}

    Vector(const Vector &o) 
      : Vector(o.begin(), o.end())
    {}

    Vector(Vector &&o) 
        : lgth(o.lgth),
          max(o.max),
          store(move(o.store))
    {
      o.lgth = 0;
      o.max = 0;
    }

    ~Vector() = default;

    Vector& operator=(const Vector &o) 
    {
      if (this != &o)
      {
        lgth  = 0;
        max   = o.max;
        store = new T[max];
        
        lappend(o.begin(), o.end());
      }

      return *this;
    }

    Vector& operator=(Vector &&o) 
    {
      if (this != &o)
      {
        lgth = o.lgth;
        max = o.max;
        store = move(o.store);
        o.lgth = 0;
        o.max = 0;
      }

      return *this;
    }

  public:
    operator Range<T*>() 
    {
      return range();
    }

    operator Range<const T*>() const 
    {
      return range();
    }

    operator Range<MoveIterator<T*>>() &&
    {
      return Range<MoveIterator<T*>>(
        MoveIterator<T*>(begin()), 
        MoveIterator<T*>(end()));
    }

    auto range() 
    {
      return sitl::range(*this);
    }

    auto range() const 
    {
      return sitl::range(*this);
    }

    Size size() const 
    {
      return lgth;
    }

    Size capacity() const 
    {
      return max;
    }

    bool empty() const 
    {
      return lgth == 0;
    }

    T* data() 
    {
      return store;
    }

    const T* data() const 
    {
      return store;
    }

  public:
    void increase(Size more) 
    {
      if (more == 0)
        return;

      Strong<T[]> nstore = new T[max + more];

      for (Size i = 0; i < lgth; ++i)
        nstore[i] = move(store[i]);

      store = move(nstore);
      max = max + more;
    }

    void clear() 
    {
      lgth = 0;
    }

  public:
    void lpush(const T &t) 
    {
      if (lgth < max)
      {
        store[lgth] = t;
        ++lgth;
      }
    }

    void lpush(T &&t) 
    {
      if (lgth < max)
      {
        store[lgth] = move(t);
        ++lgth;
      }
    }

    void push(const T &t) 
    {
      if (lgth >= max)
        increase(max == 0 ? 10 : max * 2);

      store[lgth] = t;
      lgth = lgth + 1;
    }

    void push(T &&t) 
    {
      if (lgth >= max)
        increase(max == 0 ? 10 : max * 2);

      store[lgth] = move(t);
      lgth = lgth + 1;
    }
    
    template <Iterator IT>
    void lappend(Range<IT> sp) 
    {
      lappend(sp.begin(), sp.end());
    }

    template <typename IT>
    void lappend(IT b, IT e) 
    {
      while (b != e)
      {
        lpush(*b);
        ++b;
      }
    }

    template <typename IT>
    void append(Range<IT> sp) 
    {
      append(sp.begin(), sp.end());
    }

    template <typename IT>
    void append(IT b, IT e) 
    {
      while (b != e)
      {
        push(*b);
        ++b;
      }
    }

    T &operator[](Size i) 
    {
      return store[i];
    }

    const T &operator[](Size i) const 
    {
      return store[i];
    }

    T &back() 
    {
      return store[size() - 1];
    }

    const T &back() const 
    {
      return store[size() - 1];
    }

  public:
    T *begin() 
    {
      return store;
    }

    T *end() 
    {
      return static_cast<T *>(store) + lgth;
    }

    const T *begin() const 
    {
      return store;
    }

    const T *end() const 
    {
      return static_cast<const T *>(store) + lgth;
    }
  };

  template <typename T>
  using VectorRange = Range<T *>;

  template <typename T>
  using VectorCRange = Range<const T *>;
}

#endif
