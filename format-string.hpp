#include <string>
#include <string_view>

template <typename char_t>
constexpr std::basic_string_view<char_t>
view_of(const std::basic_string<char_t> &s)
{
  return std::basic_string_view<char_t>(
      s.begin(), s.end());
}

template <typename char_t, size_t n>
constexpr std::basic_string_view<char_t>
view_of(const char_t (&v)[n])
{
  return std::basic_string_view<char_t>(v, n);
}

template <typename char_t>
constexpr void format_of(
    std::basic_string<char_t> &buff,
    const std::basic_string_view<char_t> &v)
{
  buff.append(v.begin(), v.end());
}

template <typename char_t>
constexpr size_t length_of(
    const std::basic_string_view<char_t> &v)
{
  return v.size();
}

template <typename char_t>
constexpr void format_of(
    std::basic_string<char_t> &buff,
    const std::basic_string<char_t> &s)
{
  format_of(buff, view_of(s));
}

template <typename char_t>
constexpr size_t length_of(
    const std::basic_string<char_t> &s)
{
  return length_of(view_of(s));
}

template <typename char_t, size_t n>
constexpr void format_of(
    std::basic_string<char_t> &buff,
    const char_t (&v)[n])
{
  format_of(buff, view_of(v));
}

template <typename char_t, size_t n>
constexpr size_t length_of(
    const char_t (&v)[n])
{
  return length_of(view_of(v));
}