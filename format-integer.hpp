#include <string>
#include <concepts>

#include "meta.hpp"
#include "format-core.hpp"

namespace fmt
{
  namespace
  {
    template <typename C>
    class stack_array
    {
      C data[40];
      int i = -1;

    public:
      void push(C c) { data[++i] = c; }
      C pop() { return data[i--]; }
      bool empty() { return i == -1; }
    };
  }

  template <is_integer T>
  struct formatter<T>
  {
    template <typename C>
    void operator()(
        std::basic_string<C> &buff,
        T t)
    {
      bool neg = t < 0;
      auto _abs = [](int i)
      { return i < 0 ? -i : i; };

      stack_array<C> tbuff;

      if (t == 0)
        tbuff.push('0');
      else
        while (t != 0)
        {
          tbuff.push("0123456789"[_abs(t % 10)]);
          t /= 10;
        }

      if (neg)
        tbuff.push('-');

      while (not tbuff.empty())
        buff.push_back(tbuff.pop());
    }
  };

}