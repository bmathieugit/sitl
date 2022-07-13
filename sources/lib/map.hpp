#ifndef __lib_map_hpp__
#define __lib_map_hpp__

#include <lib/vector.hpp>
#include <lib/basic_types.hpp>

namespace sitl
{
  template <typename K, typename V>
  struct Pair 
  {
    K k;
    V v;
  };

  template <typename K, typename V>
  bool operator == (const Pair<K, V>& p,
                    const Pair<K, V>& p2) noexcept
  {
    return p.k == p2.k;
  }

  template <typename K, typename V>
  bool operator == (const Pair<K, V>& p, 
                    const K& k) noexcept
  {
    return p.k == k;
  }

  template <typename V> 
  struct MapValue
  {
    V* v = nullptr;

    operator bool () const noexcept
    {
      return v != nullptr;
    }

    V& get() noexcept { return *v; }
    const V& get() const noexcept { return *v; }
  };

  template <typename K, typename V>
  class Map
  {
    Vector<Pair<K, V>> entries;
 
  public:
    Size size() const noexcept
    {
      return entries.size();
    }

    bool empty() const noexcept
    {
      return entries.empty();
    }

  public:
    MapValue<V> at(const K& key) noexcept
    {
      auto it = entries.range().find(key);
      
      return MapValue<V> {
        it != entries.end()
          ? &(*it).v
          : nullptr
      };
    }

    MapValue<const V> at(const K& key) const noexcept
    {
      auto it = entries.range().find(key);
      
      return MapValue<const V> {
        it != entries.end()
          ? &(*it).v
          : nullptr
      };
    }
   
    void push(const K& key, V&& value) noexcept
    {
      auto found = at(key);

      if (found)
        found.get() = move(value);
      else 
        entries.push(Pair<K, V>(key, move(value)));
    }
  
    void push(const K& key, const V& value) noexcept
    {
      push(move(V(value)));
    }

  public:
    auto begin() noexcept { return entries.begin(); }
    auto end() noexcept { return entries.end(); }
    auto begin() const noexcept { return entries.begin(); }
    auto end() const noexcept { return entries.end(); }
  };
}

#endif
