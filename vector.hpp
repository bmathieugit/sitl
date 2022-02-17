#ifndef __lib_vector_hpp__
#define __lib_vector_hpp__

#include "utility.hpp"
#include "algorithm.hpp"
#include "span.hpp"

namespace lib
{
  template <typename T>
  class vector
  {
    size_t lgth = 0;
    size_t max = 10;
    T *data = nullptr;

  public:
    explicit vector(size_t _max = 10)
        : max(_max),
          data(new T[_max])
    {
    }

    template <typename iterator>
    explicit vector(iterator b, iterator e)
        : vector(e - b)
    {
      for (; b != e; b++)
        push_back(*b);
    }

    template <typename O>
    explicit vector(span<O> sp)
        : vector(sp.begin(), sp.end())
    {
    }

    vector(const vector<T> &v)
        : vector(v.max)
    {
      for (const T &it : v)
        push_back(it);
    }

    vector(vector<T> &&v)
        : lgth(v.lgth),
          max(v.max),
          data(v.data)
    {
      v.max = 0;
      v.lgth = 0;
      v.data = nullptr;
    }

    ~vector()
    {
      delete[] data;
      data = nullptr;
      max = 0;
      lgth = 0;
    }

    vector<T> &operator=(const vector<T> &v)
    {
      if (this != &v)
      {
        delete[] data;
        data = new T[v.max];
        copy_all(v.begin(), v.end(), begin());
        lgth = v.lgth;
      }

      return *this;
    }

    vector<T> &operator=(vector<T> &&v)
    {
      if (this != &v)
      {
        data = v.data;
        lgth = v.lgth;
        max = v.max;
        v.data = nullptr;
        v.lgth = 0;
        v.max = 0;
      }

      return *this;
    };

    size_t size() const
    {
      return lgth;
    }

    bool empty() const
    {
      return lgth == 0;
    }

    size_t capacity() const
    {
      return max;
    }

    T &operator[](size_t i)
    {
      return data[i];
    }

    const T &operator[](size_t i) const
    {
      return data[i];
    }

    void push_back(const T &t)
    {
      if (lgth == max)
      {
        size_t nmax = max * 2;
        T *tmp = data;
        data = new T[nmax];

        for (size_t i = 0; i < max; ++i)
          data[i] = move(tmp[i]);

        max = nmax;
        delete[] tmp;
      }

      data[lgth] = t;
      ++lgth;
    }

    void push_back(T &&t)
    {
      if (lgth == max)
      {
        size_t nmax = max * 2;
        T *tmp = data;
        data = new T[nmax];

        for (size_t i = 0; i < max; ++i)
          data[i] = move(tmp[i]);

        max = nmax;
        delete[] tmp;
      }

      data[lgth] = static_cast<T &&>(t);
      ++lgth;
    }

    T *begin()
    {
      return data;
    }

    T *end()
    {
      return data + lgth;
    }

    const T *begin() const
    {
      return data;
    }

    const T *end() const
    {
      return data + lgth;
    }

    size_t front_index() const
    {
      return 0;
    }

    size_t back_index() const
    {
      return lgth;
    }

    const T &front() const
    {
      return *begin();
    }

    const T &back() const
    {
      return *(end() - 1);
    }

    T &front()
    {
      return *begin();
    }

    T &back()
    {
      return *(end() - 1);
    }
  };

}

#endif
