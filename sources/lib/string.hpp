#ifndef __lib_string_hpp__
#define __lib_string_hpp__

#include <lib/vector.hpp>
#include <lib/basic_types.hpp>
#include <lib/utility.hpp>
#include <lib/range.hpp>

namespace sitl
{
  template <IsCharacter C>
  using BasicStringRange = Range<C *>;

  template <IsCharacter C>
  using BasicStringCRange = Range<const C *>;

  using StringRange = BasicStringRange<char>;
  using StringCRange = BasicStringCRange<char>;

  template <IsCharacter C>
  class BasicString
  {
  private:
    Vector<C> storage;

  public:
    BasicString() noexcept = default;

    explicit constexpr BasicString(Size max) noexcept
        : storage(max)
    {
    }

    constexpr BasicString(BasicStringCRange<C> s) noexcept
        : BasicString(s.size())
    {
      lappend(s);
    }

    constexpr BasicString(const C *o) noexcept
        : BasicString(BasicStringCRange<C>(o, o + StrLen<C>()(o)))
    {
    }

    template <typename IT>
    constexpr BasicString(IT b, IT e) noexcept
        : storage(b, e) {}

    constexpr BasicString(const BasicString<C> &) noexcept = default;
    constexpr BasicString(BasicString &&) noexcept = default;
    constexpr ~BasicString() noexcept = default;
    constexpr BasicString<C> &operator=(const BasicString<C> &) noexcept = default;
    constexpr BasicString<C> &operator=(BasicString<C> &&) noexcept = default;

  public:
    constexpr auto range() noexcept
    {
      return range(*this);
    }

    constexpr auto range() const noexcept
    {
      return range(*this);
    }

    constexpr Size size() const noexcept
    {
      return storage.size();
    }

    constexpr Size capacity() const noexcept
    {
      return storage.capacity();
    }

    constexpr bool empty() const noexcept
    {
      return storage.empty();
    }

    constexpr C *data() noexcept
    {
      return storage.data();
    }

    constexpr const C *data() const noexcept
    {
      return storage.data();
    }

  public:
    constexpr void increase(Size more) noexcept
    {
      storage.increase(more);
    }

    constexpr void clear() noexcept
    {
      storage.clear();
    }

  public:
    constexpr void lpush(C c) noexcept
    {
      storage.lpush(c);
    }

    constexpr void push(C c) noexcept
    {
      storage.push(c);
    }

    template <typename IT>
    constexpr void lappend(IT b, IT e) noexcept
    {
      storage.lappend(b, e);
    }

    constexpr void lappend(const BasicString &o) noexcept
    {
      storage.lappend(o.storage());
    }

    constexpr void lappend(BasicString &&o) noexcept
    {
      storage.lappend(move(o.storage()));
    }

    constexpr void lappend(BasicStringCRange<C> o) noexcept
    {
      storage.lappend(o);
    }

    constexpr void lappend(BasicStringRange<C> o) noexcept
    {
      storage.lappend(o);
    }

    constexpr void lappend(const C *o) noexcept
    {
      storage.lappend(o, o + StrLen<C>()(o));
    }

    template <typename IT>
    constexpr void append(IT b, IT e) noexcept
    {
      storage.append(b, e);
    }

    constexpr void append(const BasicString &o) noexcept
    {
      storage.append(o.storage);
    }

    constexpr void append(BasicString &&o) noexcept
    {
      storage.append(move(o.storage));
    }

    constexpr void append(BasicStringCRange<C> o) noexcept
    {
      storage.append(o);
    }

    constexpr void append(BasicStringRange<C> o) noexcept
    {
      storage.append(o);
    }

    constexpr void append(const C *o) noexcept
    {
      storage.append(o, o + StrLen<C>()(o));
    }

  public:
    constexpr operator BasicStringCRange<C>() const noexcept
    {
      return BasicStringCRange<C>(data(), size());
    }

    constexpr operator BasicStringRange<C>() noexcept
    {
      return BasicStringRange<C>(data(), size());
    }

    constexpr C &operator[](Size i) noexcept
    {
      return storage[i];
    }

    constexpr const C &operator[](Size i) const noexcept
    {
      return storage[i];
    }

  public:
    constexpr C *begin() noexcept
    {
      return storage.begin();
    }

    constexpr C *end() noexcept
    {
      return storage.end();
    }

    constexpr const C *begin() const noexcept
    {
      return storage.begin();
    }

    constexpr const C *end() const noexcept
    {
      return storage.end();
    }
  };

  using String = BasicString<char>;
}

namespace sitl
{
  template <Size n>
  constexpr StringCRange sr(const char (&s)[n]) noexcept
  {
    return Range<const char *>(s, n - 1);
  }

  constexpr StringCRange sr(const char *s) noexcept
  {
    return Range<const char *>(s, s + StrLen<char>()(s));
  }
}

namespace sitl
{
  template <typename C>
  class BasicChar
  {
  private:
    C c;

  public:
    constexpr BasicChar(C _c) noexcept : c(_c) {}
    constexpr BasicChar() = delete;
    constexpr BasicChar(const BasicChar &c) noexcept = default;
    constexpr BasicChar(BasicChar &&c) noexcept = default;
    constexpr ~BasicChar() noexcept = default;
    constexpr BasicChar &operator=(const BasicChar &c) noexcept = default;
    constexpr BasicChar &operator=(BasicChar &&c) noexcept = default;

  public:
    constexpr bool between(C b, C e) const noexcept
    {
      return b <= c && c <= e;
    }

    template <Size n>
    constexpr bool in(const C (&s)[n]) const noexcept
    {
      return BasicStringCRange<C>(s, s + n).contains(c);
    }

    constexpr bool operator==(C o) const noexcept
    {
      return c == o;
    }

    constexpr bool operator!=(C o) const noexcept
    {
      return c != o;
    }
  };

  using Char = BasicChar<char>;
}

#endif
