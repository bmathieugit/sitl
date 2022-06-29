#ifndef __sitl_nsomeanalyser_hpp__
#define __sitl_nsomeanalyser_hpp__

namespace sitl
{
  template <Size n, TokenType type>
  struct NSomeAnalyser
  {
    static constexpr Size S = n;
    constexpr bool operator()(VectorCRange<Token> tline, Position pos) const noexcept
    {
      for (int i = pos; i < n; i++)
        if (tline[i].type != type)
          return false;
      return true;
    }
  };

  template <Size n, TokenType type>
  using NSome = NSomeAnalyser<n, type>;
}

#endif