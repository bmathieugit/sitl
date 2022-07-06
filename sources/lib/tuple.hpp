#ifndef __sitl_tuple_hpp__
#define __sitl_tuple_hpp__

#include <lib/utility.hpp>

namespace sitl
{
  /**
   * @brief Représente une localisation
   * d'un élément dans un Tuple.
   */
  using TupleIndex = unsigned int;

  /**
   * @brief Un TupleSequence est une suite
   * d'index TupleIndex permettant de fournir
   * un moyen de localisation de chaque
   * TupleElement d'un tuple
   *
   * @tparam i liste des index.
   */
  template <TupleIndex... i>
  struct TupleSequence
  {
  };

  /**
   * @brief Construit un TupleSequence à
   * partir d'un TupleIndex maximal. Par
   * effet d'héritage/décalage, on obtient
   * un TupleSequence de 0 à max
   *
   * @tparam max TupleIndex max
   * @tparam i next TupleIndex
   */
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

  /**
   * @brief Un TupleElement va stocker et
   * localiser un élément dans un Tuple par
   * son index et son type.
   *
   * @tparam T type de l'élément contenu
   * @tparam i index de l'élément dans le tuple
   */
  template <typename T, TupleIndex i>
  struct TupleElement
  {
    T elem;
  };

  /**
   * @brief Retourne une référence sur
   * l'élément contenu dans le TupleElement
   *
   * @tparam i index dans le tuple
   * @tparam T type de l'objet contenu
   * @param te TupleElement dont on souhaite l'élément
   * @return constexpr T& référence sur l'élément
   * contenu dans te
   */
  template <TupleIndex i, typename T>
  constexpr T &get(TupleElement<T, i> &te)
  {
    return te.elem;
  }

  /**
   * @brief Retourne une référence constante sur
   * l'élément contenu dans le TupleElement
   *
   * @tparam i index dans le tuple
   * @tparam T type de l'objet contenu
   * @param te TupleElement dont on souhaite l'élément
   * @return constexpr const T& référence sur l'élément
   * contenu dans te
   */
  template <TupleIndex i, typename T>
  constexpr const T &get(const TupleElement<T, i> &te)
  {
    return te.elem;
  }

  /**
   * @brief Retourne une référence rvalue sur
   * l'élément contenu dans le TupleElement
   *
   * @tparam i index dans le tuple
   * @tparam T type de l'objet contenu
   * @param te TupleElement dont on souhaite l'élément
   * @return constexpr T&& référence sur l'élément
   * contenu dans te
   */
  template <TupleIndex i, typename T>
  constexpr T &&get(TupleElement<T, i> &&te)
  {
    return move(te.elem);
  }

  /**
   * @brief
   *
   * @tparam SEQ
   * @tparam T
   */
  template <typename SEQ, typename... T>
  struct TupleElements;

  template <TupleIndex... i, typename... T>
  struct TupleElements<TupleSequence<i...>, T...>
      : public TupleElement<T, i>...
  {
    template <typename... O>
    constexpr explicit TupleElements(O &&...o)
        : TupleElement<T, i>(forward<O>(o))...
    {
    }

    constexpr TupleElements() = default;
    constexpr ~TupleElements() = default;
    constexpr TupleElements(const TupleElements &) = default;
    constexpr TupleElements(TupleElements &&) = default;
    constexpr TupleElements &operator=(const TupleElements &) = default;
    constexpr TupleElements &operator=(TupleElements &&) = default;
  };

  /**
   * @brief Un Tuple est une collection d'objet de type
   * différent.
   *
   * @tparam T Liste des types contenus dans le Tuple
   */
  template <typename... T>
  struct Tuple
  {
    TupleElements<MakeTupleSequenceType<sizeof...(T)>, T...> elems;

  public:
    constexpr Tuple() = default;
    constexpr ~Tuple() = default;
    constexpr Tuple(const Tuple &) = default;
    constexpr Tuple(Tuple &&) = default;
    constexpr Tuple &operator=(const Tuple &) = default;
    constexpr Tuple &operator=(Tuple &&) = default;

  public:
    template <typename... O>
    constexpr explicit Tuple(O &&...o)
        : elems(forward<O>(o)...)
    {
    }

    template <TupleIndex i>
    constexpr auto get() & -> decltype(auto)
    {
      return sitl::get<i>(elems);
    }

    template <TupleIndex i>
    constexpr auto get() && -> decltype(auto)
    {
      return sitl::get<i>(move(elems));
    }

    template <TupleIndex i>
    constexpr auto get() const & -> decltype(auto)
    {
      return sitl::get<i>(elems);
    }
  };
}

#endif