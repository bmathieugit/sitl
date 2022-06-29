#ifndef __sitl_expression_tokenizer_hpp__
#define __sitl_expression_tokenizer_hpp__

#include <tokenizer/globaltokenizer.hpp>
#include <tokenizer/tokenizers.hpp>

namespace sitl
{
  using ExpressionTokenizer = GlobalTokenizer<
      NumberTokenizer,
      StringTokenizer,
      LabelTokenizer,
      LParTokenizer,
      RParTokenizer,
      BlankTokenizer>;
}

#endif