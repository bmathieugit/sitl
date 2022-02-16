#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ctools.h"
#include "model.h"
#include "api.h"

void sitl_fcheckstx()
{
  if (process.stxsstate != STEP_NOTDONE)
    return;

  tline_t tl;
  FILE* ftks = fopen(process.tksname, "r");

  if (ftks == NULL)
  {
    process.stxerr = STXERR_TKSNOTOPENED;
    process.stxsstate = STEP_FAILURE;
    return;
  }

  bool res = true;
  bool invalidl = false;

  do
  {
    sitl_rtksl(&tl, ftks);

    int nbtk = tl.idx;
    int offset = tl.offset;
    // int rnum = tl.rnum;

    tl_state_t st = tl.state;

    ttype_t tp0 = tl.tks[0].type;
    ttype_t tp1 = tl.tks[1].type;
    ttype_t tp2 = tl.tks[2].type;
    ttype_t tp3 = tl.tks[3].type;
    ttype_t tp4 = tl.tks[4].type;
    // ttype_t tp5 = tl.tks[5].type;

    if (st == TLS_EMPTY)
      continue;

    if (st == TLS_LAST)
      break;

    switch (tp0)
    {
    case TT_TYPE:
      res = nbtk == 3 and
            offset == 0 and
            tp0 == TT_TYPE and
            tp1 == TT_ID and
            tp2 == TT_EOL;
      break;
    case TT_ATTR:
      res = nbtk == 4 and
            offset == 1 and
            tp0 == TT_ATTR and
            tp1 == TT_ID and
            tp2 == TT_ID and
            tp3 == TT_EOL;
      break;
    case TT_LET:
      res = nbtk == 5 and
            offset >= 1 and
            tp0 == TT_LET and
            tp1 == TT_ID and
            tp2 == TT_ID and
            (tp3 == TT_ID or
             tp3 == TT_STR or
             tp3 == TT_NUM) and
            tp4 == TT_EOL;
      break;
    case TT_DEL:
      res = nbtk == 3 and
            offset >= 1 and
            tp0 == TT_DEL and
            tp1 == TT_ID and
            tp2 == TT_EOL;
      break;
    case TT_CONST:
      res = nbtk == 5 and
            offset >= 1 and
            tp0 == TT_CONST and
            tp1 == TT_ID and
            tp2 == TT_ID and
            (tp3 == TT_ID or
             tp3 == TT_STR or
             tp3 == TT_NUM) and
            tp4 == TT_EOL;
      break;
    case TT_COPY:
      res = nbtk == 4 and
            offset >= 1 and
            tp0 == TT_COPY and
            tp1 == TT_ID and
            (tp2 == TT_ID or
             tp2 == TT_STR or
             tp2 == TT_NUM) and
            tp3 == TT_EOL;
      break;
    case TT_MOVE:
      res = nbtk == 4 and
            offset >= 1 and
            tp0 == TT_MOVE and
            tp1 == TT_ID and
            (tp2 == TT_ID or
             tp2 == TT_STR or
             tp2 == TT_NUM) and
            tp3 == TT_EOL;
      break;
    case TT_WHILE:
      res = nbtk == 3 and
            offset >= 1 and
            tp0 == TT_WHILE and
            tp1 == TT_ID and
            tp2 == TT_EOL;
      break;
    case TT_IF:
      res = nbtk == 3 and
            offset >= 1 and
            tp0 == TT_IF and
            tp1 == TT_ID and
            tp2 == TT_EOL;
      break;
    case TT_FCT:
      res = nbtk == 4 and
            offset == 0 and
            tp0 == TT_FCT and
            tp1 == TT_ID and
            tp2 == TT_ID and
            tp3 == TT_EOL;
      break;
    case TT_PARAM:
      res = nbtk == 4 and
            offset == 1 and
            tp0 == TT_PARAM and
            tp1 == TT_ID and
            tp2 == TT_ID and
            tp3 == TT_EOL;
      break;
    case TT_RETRN:
      res = nbtk == 3 and
            offset >= 1 and
            tp0 == TT_RETRN and
            (tp1 == TT_ID or
             tp1 == TT_STR or
             tp1 == TT_NUM) and
            tp2 == TT_EOL;
      break;
    default:
      res = false;
      break;
    }

    if (not res)
      invalidl = true;

  } while (tl.state != TLS_LAST);

  if (invalidl)
  {
    process.stxsstate = STEP_FAILURE;
    process.stxerr = STXERR_INVALIDL;
  }
  else
  {
    process.stxsstate = STEP_SUCCESS;
    process.stxerr = STXERR_NOTHING;
  }
}