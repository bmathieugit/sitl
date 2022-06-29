#ifndef __lib_array_hpp__
#define __lib_array_hpp__

#include <lib/basic_types.hpp>
#include <lib/range.hpp>

namespace sitl
{
  /**
   * @brief structure that can encapsulate a
   * native fixed size array
   *
   * @tparam T type contained in array
   * @tparam n fixed size of the array
   */
  template <typename T, Size n>
  struct Array
  {
    T b[n];

  public:
    /**
     * @brief Create a range on this array
     *
     * @return constexpr auto range that encapsulate this array
     */
    constexpr auto range() noexcept
    {
      return sitl::range(*this);
    }

    /**
     * @brief Create a constant range on this array
     *
     * @return constexpr auto constant range that
     * encapsulate this array
     */
    constexpr auto range() const noexcept
    {
      return sitl::range(*this);
    }

    /**
     * @brief Get the size of the fixed size array
     * (template parameter n)
     *
     * @return constexpr Size return n (template parameter) value
     */
    constexpr Size size() const noexcept
    {
      return n;
    }

    /**
     * @brief Tells that if the fixed size array is empty
     *
     * @return true never because 0 sized array is forbidden
     * @return false allways (fixed size array never empty)
     */
    constexpr bool empty() const noexcept
    {
      return false;
    }

    /**
     * @brief return a pointer on the first element of the array
     *
     * @return T* pointer to the first element
     */
    constexpr T *data() noexcept
    {
      return b;
    }

    /**
     * @brief return a constant pointer on the first element of the array
     *
     * @return const T* constant pointer to the first element
     */
    constexpr const T *data() const noexcept
    {
      return b;
    }

    T &operator[](Size i) &noexcept
    {
      return b[i];
    }

    constexpr const T &operator[](Size i) const &noexcept
    {
      return b[i];
    }

    constexpr T &&operator[](Size i) &&noexcept
    {
      return b[i];
    }

    constexpr const T &&operator[](Size i) const &&noexcept
    {
      return b[i];
    }

    constexpr operator Range<const T *>() const noexcept
    {
      return Range<const T *>(this->data(), this->size());
    }

    constexpr operator Range<T *>() noexcept
    {
      return Range<T *>(this->data(), this->size());
    }

  public:
    /**
     * @brief create an iterator on the first element
     * of the array
     *
     * @return T* ierator on the first element of the array
     */
    constexpr T *begin() noexcept
    {
      return b;
    }

    /**
     * @brief create an iterator on after the last element
     * of the array
     *
     * @return T* ierator on after the last element of the array
     */
    constexpr T *end() noexcept
    {
      return b + n;
    }

    /**
     * @brief create an iterator on the first element
     * of the array
     *
     * @return T* ierator on the first element of the array
     */
    constexpr const T *begin() const noexcept
    {
      return b;
    }

    /**
     * @brief create an iterator on after the last element
     * of the array
     *
     * @return T* ierator on after the last element of the array
     */
    constexpr const T *end() const noexcept
    {
      return b + n;
    }
  };
}

#endif