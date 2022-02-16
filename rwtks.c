#include <stdio.h>
#include <stdlib.h>

#include "api.h"

#ifndef CLEARTEXT

void sitl_rtksl(
    tline_t *tl,
    FILE* ftks)
{
  int sz1 = sizeof(tl->rnum);
  int sz2 = sizeof(tl->state);
  int sz3 = sizeof(tl->idx);
  int sz4 = sizeof(tl->offset);
  int nbtk = sizeof(tl->tks) /
             sizeof(tl->tks[0]);

  for (int i = 0; i < nbtk; ++i)
    tl->tks[i].type = TT_UNDEF;

  fread(&tl->rnum, sz1, 1, ftks);
  fread(&tl->state, sz2, 1, ftks);
  fread(&tl->idx, sz3, 1, ftks);
  fread(&tl->offset, sz4, 1, ftks);

  for (int i = 0; i < tl->idx; ++i)
  {
    token_t *tk = &tl->tks[i];

    int sz5 = sizeof(tk->type);
    int sz6 = sizeof(tk->size);
    int sz7 = sizeof(tk->val[0]);

    fread(&tk->type, sz5, 1, ftks);
    fread(&tk->size, sz6, 1, ftks);

    if (tk->size > 0)
      fread(&tk->val, sz7, tk->size, ftks);
    else
      tk->val[0] = EOS;
  }
}

void sitl_wtksl(
    tline_t *tl,
    FILE* ftks)
{
  int sz1 = sizeof(tl->rnum);
  int sz2 = sizeof(tl->state);
  int sz3 = sizeof(tl->idx);
  int sz4 = sizeof(tl->offset);

  fwrite(&tl->rnum, sz1, 1, ftks);
  fwrite(&tl->state, sz2, 1, ftks);
  fwrite(&tl->idx, sz3, 1, ftks);
  fwrite(&tl->offset, sz4, 1, ftks);

  for (int i = 0; i < tl->idx; ++i)
  {
    token_t *tk = &tl->tks[i];

    int sz5 = sizeof(tk->type);
    int sz6 = sizeof(tk->size);
    int sz7 = sizeof(tk->val[0]);

    fwrite(&tk->type, sz5, 1, ftks);
    fwrite(&tk->size, sz6, 1, ftks);

    if (tk->size > 0)
      fwrite(&tk->val, sz7, tk->size, ftks);
  }
}

#else

void sitl_rtksl(
    tline_t *tl,
    FILE* ftks)
{
  fscanf(ftks, "%d;%d;%d;%d\n",
         (int *)&tl->rnum,
         (int *)&tl->state,
         (int *)&tl->idx,
         (int *)&tl->offset);

  for (int i = 0; i < tl->idx; ++i)
  {
    token_t *tk = &tl->tks[i];

    fscanf(ftks, "  %d;%d;%s\n",
           (int *)&tk->type,
           (int *)&tk->size,
           (char *)tk->val);
  }
}

void sitl_wtksl(
    tline_t *tl,
    FILE* ftks)
{
  fprintf(ftks, "%d;%d;%d;%d\n",
          (int)tl->rnum,
          (int)tl->state,
          (int)tl->idx,
          (int)tl->offset);

  for (int i = 0; i < tl->idx; ++i)
  {
    token_t *tk = &tl->tks[i];

    fprintf(ftks, "  %d;%d;%s\n",
            (int)tk->type,
            (int)tk->size,
            (char *)tk->val);
  }
}

#endif