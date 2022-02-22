#include <string>
#include <string_view>

template <typename C>
constexpr std::basic_string_view<C>
view_of(const std::basic_string<C> &s)
{
  return std::basic_string_view<C>(
      s.begin(), s.end());
}

template <typename C, size_t n>
constexpr std::basic_string_view<C>
view_of(const C (&v)[n])
{
  return std::basic_string_view<C>(v, n);
}

template <typename C>
constexpr void format_of(
    std::basic_string<C> &buff,
    const std::basic_string_view<C> &v)
{
  buff.append(v.begin(), v.end());
}

template <typename C>
constexpr size_t length_of(
    const std::basic_string_view<C> &v)
{
  return v.size();
}

template <typename C>
constexpr void format_of(
    std::basic_string<C> &buff,
    const std::basic_string<C> &s)
{
  format_of(buff, view_of(s));
}

template <typename C>
constexpr size_t length_of(
    const std::basic_string<C> &s)
{
  return length_of(view_of(s));
}

template <typename C, size_t n>
constexpr void format_of(
    std::basic_string<C> &buff,
    const C (&v)[n])
{
  format_of(buff, view_of(v));
}

template <typename C, size_t n>
constexpr size_t length_of(
    const C (&v)[n])
{
  return length_of(view_of(v));
}