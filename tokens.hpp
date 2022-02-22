#ifndef __sitl_tokens_hpp__
#define __sitl_tokens_hpp__

enum class token_type
{
  kw_type,
  kw_build,
  kw_copy,
  kw_move,
  kw_fun,
  kw_del,
  kw_if,
  kw_while,
  kw_for,
  kw_true,
  kw_false,
  kw_return,
  sm_lbrace,
  sm_rbrace,
  sm_lbracket,
  sm_rbracket,
  sm_lsbracket,
  sm_rsbracket,
  sm_eq,
  sm_mv,
  sm_colon,
  sm_int,
  sm_flt,
  sm_str,
  sm_id
};



#endif