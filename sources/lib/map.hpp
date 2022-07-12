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
                    const Pair<K, V>& p2)
  {
    return p.k == p2.k;
  }

  template <typename K, typename V>
  bool operator == (const Pair<K, V>& p, 
                    const K& k)
  {
    return p.k == k;
  }

  template <typename V> 
  struct MapValue
  {
    V* v = nullptr;

    operator bool () const 
    {
      return v != nullptr;
    }

    V& get() { return *v; }
    const V& get() const { return *v; }
  };

  template <typename K, typename V>
  class Map
  {
    Vector<Pair<K, V>> entries;
 
  public:
    Size size() const 
    {
      return entries.size();
    }

    bool empty() const 
    {
      return entries.empty();
    }

  public:
    MapValue<V> at(const K& key)
    {
      auto it = entries.range().find(key);
      
      return MapValue<V> {
        it != entries.end()
          ? &(*it).v
          : nullptr
      };
    }

    MapValue<const V> at(const K& key) const
    {
      auto it = entries.range().find(key);
      
      return MapValue<const V> {
        it != entries.end()
          ? &(*it).v
          : nullptr
      };
    }
   
    void push(const K& key, V&& value)
    {
      auto found = at(key);

      if (found)
        found.get() = move(value);
      else 
        entries.push(Pair<K, V>(key, move(value)));
    }
  
    void push(const K& key, const V& value)
    {
      push(move(V(value)));
    }
  };
}

#endif
