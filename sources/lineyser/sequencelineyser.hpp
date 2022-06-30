#ifndef __sitl_sequence_analyser_hpp__
#define __sitl_sequence_analyser_hpp__

#include <lib/vector.hpp>

namespace sitl
{
  template <TokenType... types>
  struct SequenceLineyser
  {
    static constexpr Size S = sizeof...(types);

    constexpr bool operator()(
        VectorCRange<Token> tline,
        Position pos) const noexcept
    {
      return (true && ... && (tline[pos++].type == types));
    }
  };

  template<TokenType ... types>
  using Sequence = SequenceLineyser<types...>;
}

#endif