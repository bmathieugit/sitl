#ifndef __sitl_token_hpp__
#define __sitl_token_hpp__

#include <lib/string.hpp>
#include <model/tokentype.hpp>

namespace sitl
{
  /**
   * @brief A token encapsulate a portion
   * of text with a token type
   */
  struct Token
  {
    /**
     * @brief Type ot the token
     */
    TokenType type;

    /**
     * @brief Portion of text
     */
    StringCRange value;
  };
}

#endif