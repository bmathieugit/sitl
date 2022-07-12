#ifndef __lib_map_hpp__
#define __lib_map_hpp__

#include <lib/vector.hpp>
#include <lib/basic_types.hpp>
#include <lib/logger.hpp>

namespace sitl
{
  template <typename K, typename V>
  struct Pair 
  {
    K k;
    V v;
  };

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
     for (Pair<K, V>& p : entries)
        if (p.k == key)
          return MapValue<V>{&p.v};

      return MapValue<V>{};
    }

    const V* at(const K& key) const
    {
      for (const Pair<K, V>& p : entries)
        if (p.k == key)
          return &p.v;
      
      return nullptr;
    }
   
    void push(const K& key, const V& value)
    {
      auto found = at(key);

      if (found)
        found.get() = value;
      else 
        entries.push(Pair<K, V>(key, value));
    }

    void push(const K& key, V&& value)
    {
      auto found = at(key);

      if (found)
        found.get() = move(value);
      else 
        entries.push(Pair<K, V>(key, move(value)));
     }
  };
}

#endif
