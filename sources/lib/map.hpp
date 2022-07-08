#ifndef __lib_map_hpp__
#define __lib_map_hpp__

#include <lib/set.hpp>
#include <lib/basic_types.hpp>
#include <lib/algorithm.hpp>

namespace sitl
{
  template <typename K, typename V>
  class Pair
  {
    K key;
    V value;

  public:
    Pair(const K& k, const V& v)
      : key(k), value(v) {}
    
    ~Pair() = default;
    Pair(const Pair&) = default;
    Pair(Pair&&) = default;
    Pair& operator=(const Pair&) = default;
    Pair& operator=(Pair&&) = default;
  
  public:
    bool operator==(const Pair& o) const 
    {
      return key == o.key;
    }

    bool operator!=(const Pair& o) const 
    {
      return !(*this == o);
    }

    bool operator<(const Pair& o) const
    {
      return key < o.key;
    }

    bool operator<=(const Pair& o) const
    {
      return *this == o || *this < o;  
    }

  public:
    const K& () const { return key; }
    const V& v() const { return value; }
  };

  template<typename V>
  class MapValue
  {
    V* value = nullptr;

  public:
    MapValue() = default;
    MapValue(const MapValue&) = default;
    MapValue(MapValue&&) = default;
    MapValue& operator=(const MapValue&) = default;
    MapValue& operator=(MapValue&&) = default;
    ~MapValue() = default;
  public:
    explicit MapValue(V& v) : value(&v) {}

  public:
    bool empty() const 
    {
      return value == nullptr;
    }

    operator bool() const 
    {
      return empty();
    }

    V& get()
    {
      return *value;
    }

    const V& get() const 
    {
      return *value;
    }

    operator V&()
    {
      return get();
    }

    operator const V&() const 
    {
      return get();
    }
  };


  template <typename K, typename V>
  class Map
  {
    Set<Pair<K, V>> entries;

  public:
    Map() = default;
    ~Map() = default;
    Map(const Map&) = default;
    Map(Map&&) = default;
    Map& operator=(const Map&) = default;
    Map& operator=(Map&&) = default;

  public:
    // il nous fait un moyen d'accéder à n'importe quelle valeur via sa clé. On
    // va donc mettre en place la fonction at qui prend en entrée une clé et qui
    // rend en sortie la valeur associée. si la clé n'est pas présente dans la
    // map alors l'optional retourné sera vide. On va donc mettre en place un 
    // objet MapValue qui exprimé cette absence potentielle de valeur.
    MapValue<V> at(const K& key)
    {
      auto found = entries.range().find_if(
        [&key] (const Pair<K, V>& p) {
          return p.k() == key;
        });
      return found != entries.end()
        ? MapValue<V>(*found)
        : MapValue<V>();
    }

    MapValue<const V> at(const K& key) const;
    {
      auto found = entries.range().find_if(
        [&key] (const Pair<K, V>& p) {
          return p.k() == key;
        });
      return found != entries.end()
        ? MapValue<const V>(*found)
        : MapValue<const V>();
    }
  };
}

#endif
