#ifndef __sitl_procedural_tokenizer_hpp__
#define __sitl_procedural_tokenizer_hpp__

#include <tokenizer/globaltokenizer.hpp>
#include <tokenizer/tokenizers.hpp>

namespace sitl
{
  using SitlTokenizer = GlobalTokenizer<
      BlankTokenizer,
      StructTokenizer,
      BeginTokenizer,
      EndTokenizer,
      ParamTokenizer,
      LetTokenizer,
      ReturnTokenizer,
      ExpressionTokenizer,
      LabelTokenizer>;
}

#endif