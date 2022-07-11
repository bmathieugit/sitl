#ifndef __lib_map_hpp__
#define __lib_map_hpp__

#include <lib/set.hpp>
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

  template <typename K, typename V>
  bool operator == (
    const Pair<K, V>& p1, 
    const Pair<K, V>& p2)
  {
    return p1.k == p2.k;
  }

  template <typename K, typename V>
  bool operator != (
    const Pair<K, V>& p1, 
    const Pair<K, V>& p2)
  {
    return p1.k != p2.k;
  }

  template <typename K, typename V>
  bool operator < (
    const Pair<K, V>& p1, 
    const Pair<K, V>& p2)
  {
    return p1.k < p2.k;
  }

  template <typename K, typename V>
  bool operator <= (
    const Pair<K, V>& p1, 
    const Pair<K, V>& p2)
  {
    return p1.k <= p2.k;
  }

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

  public:
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
      auto found = entries.range().find_if(
        [&key] (const Pair<K, V>& p) {
          return p.k == key;
        });
     
     return found != entries.end()
        ? MapValue<V>((*found).v)
        : MapValue<V>();
    }

    MapValue<const V> at(const K& key) const
    {
      auto found = entries.range().find_if(
        [&key] (const Pair<K, V>& p) {
          return p.k == key;
        });
     
     return found != entries.end()
        ? MapValue<const V>((*found).v)
        : MapValue<const V>();
    }
   
    void push(const K& key, const V& value)
    {
      entries.fpush(Pair<K, V>{key, value});
    }

    void push(const K& key, V&& value)
    {
      entries.fpush(Pair<K, V>{key, move(value)});
    }
  };
}

#endif
