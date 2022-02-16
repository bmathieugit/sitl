
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ctools.h"
#include "model.h"
#include "api.h"

static inline bool
__iseo(int c)
{
  return (
      c == EOS or
      c == EOF or
      c == EOL);
}

static inline bool
__isdigit(int c)
{
  return chin(c, '0', '9');
}

static inline bool
__isblank(int c)
{
  return (
      c == ' ' or
      c == '\r' or
      c == '\v' or
      c == '\f');
}

static inline bool
__isalpha(int c)
{
  return (
      chin(c, 'a', 'z') or
      chin(c, 'A', 'Z') or
      c == '_');
}

static inline char *
__offset(char *l)
{
  while (*l == ' ')
    ++l;

  return l;
}

static inline char *
__number(
    char *val,
    char *l)
{
  while (__isdigit(*l))
  {
    *val = *l;
    ++l;
    ++val;
  }

  *val = EOS;

  return l;
}

static inline char *
__string(
    char *val,
    char *l)
{
  char *vinit = val;
  char *linit = l;

  if (*l != '"')
    *vinit = EOS;
  else
  {
    ++l;

    while (*l != EOS and
           *l != '"')
    {
      *val = *l;
      ++l;
      ++val;
    }

    if (*l == '"')
    {
      *val = '"';
      *(val + 1) = EOS;
      return l + 1;
    }
    else
    {
      *vinit = EOS;
      l = linit;
    }
  }

  return l;
}

static inline ttype_t
__string_type(char *val)
{
  if (streq(val, ""))
    return TT_UNKNOWN;
  else
    return TT_STR;
}

static inline char *
__id(
    char *val,
    char *l)
{
  if (__isalpha(*l))
  {
    *val = *l;
    ++l;
    ++val;
  }

  while (__isalpha(*l) or
         __isdigit(*l))
  {
    *val = *l;
    ++l;
    ++val;
  }

  *val = EOS;

  return l;
}

static inline ttype_t
__id_type(char *val)
{
  if (streq(val, "attr"))
    return TT_ATTR;
  else if (streq(val, "const"))
    return TT_CONST;
  else if (streq(val, "call"))
    return TT_CALL;
  else if (streq(val, "copy"))
    return TT_COPY;
  else if (streq(val, "move"))
    return TT_MOVE;
  else if (streq(val, "del"))
    return TT_DEL;
  else if (streq(val, "let"))
    return TT_LET;
  else if (streq(val, "return"))
    return TT_RETRN;
  else if (streq(val, "type"))
    return TT_TYPE;
  else if (streq(val, "function"))
    return TT_FCT;
  else if (streq(val, "if"))
    return TT_IF;
  else if (streq(val, "while"))
    return TT_WHILE;
  else if (streq(val, "param"))
    return TT_PARAM;
  else
    return TT_ID;
}

static inline char *
__eo(char *val, char *l)
{
  *val = EOS;
  return l;
}

static inline void
__nextl(
    tline_t *tl,
    char *l)
{
  char *le;

  token_t tk;
  ttype_t type;

  int offset = __offset(l) - l;
  int idx = 0;
  tl_state_t state = TLS_VALID;

  l += offset;

  bool no_eol = true;

  while (no_eol)
  {
    while (__isblank(*l))
      ++l;

    if (__isalpha(*l))
    {
      le = __id(tk.val, l);
      type = __id_type(tk.val);
    }
    else if (__isdigit(*l))
    {
      le = __number(tk.val, l);
      type = TT_NUM;
    }
    else if (*l == '"')
    {
      le = __string(tk.val, l);
      type = __string_type(tk.val);
    }
    else if (__iseo(*l))
    {
      le = __eo(tk.val, l);
      type = TT_EOL;
    }
    else
    {
      le = l;
      type = TT_UNKNOWN;
    }

    if (type == TT_EOL)
    {
      if (idx == 0)
        state = TLS_EMPTY;

      no_eol = false;
    }
    else if (type == TT_UNKNOWN)
    {
      state = TLS_INVALID;
      no_eol = false;
    }

    tk.size = le - l;
    tk.type = type;

    l = le;

    int sz = sizeof(tl->tks);
    int szi = sizeof(tl->tks[0]);

    if (idx >= (sz / szi))
      state = TLS_OVERFLW;
    else
    {
      tl->tks[idx] = tk;
      ++idx;
    }
  }

  tl->idx = idx;
  tl->offset = offset;
  tl->state = state;
}

static inline void
__lastl(tline_t *tl)
{
  tl->state = TLS_LAST;
  tl->idx = 0;
  tl->offset = 0;
}

void sitl_fparse()
{
  if (process.prssstate != STEP_NOTDONE)
    return;

  FILE* fsrc = fopen(process.srcname, "r");

  if (fsrc == NULL)
  {
    process.prssstate = STEP_FAILURE;
    process.prserr = PERR_SRCNOTOPENED;
    return;
  }

  FILE* ftks = fopen(process.tksname, "w");

  if (ftks == NULL)
  {
    process.prssstate = STEP_FAILURE;
    process.prserr = PERR_TKSNOTOPENED;
    return;
  }

  tline_t tl;
  tl.rnum = 1;
  char l[LINESIZE];
  int lsz = sizeof(l);
  int nbc = 0;
  bool invalidl = false;

  do
  {
    nbc = freadl(l, lsz, fsrc);

    if (nbc == -1)
    {
      fescapel(fsrc);
      ++tl.rnum;
      continue;
    }

    if (nbc == 0)
      break;

    __nextl(&tl, l);

    switch (tl.state)
    {
    case TLS_INVALID:
      invalidl = true;
    case TLS_VALID:
      sitl_wtksl(&tl, ftks);
      break;

    case TLS_OVERFLW:
      invalidl = true;

    case TLS_EMPTY:
    default:
      break;
    }

    ++tl.rnum;

  } while (nbc > 0);

  __lastl(&tl);
  sitl_wtksl(&tl, ftks);

  fclose(fsrc);
  fclose(ftks);

  if (invalidl)
  {
    process.prssstate = STEP_FAILURE;
    process.prserr = PERR_INVALIDLINES;
  }
  else
  {
    process.prssstate = STEP_SUCCESS;
    process.prserr = PERR_NOTHING;
  }
}
