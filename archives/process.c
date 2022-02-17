#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "api.h"
#include "model.h"
#include "ctools.h"

process_t process;

bool sitl_initprocess(
    const char *srcname,
    FILE *ferr)
{
  process.ferr = NULL;

  process.srcname[0] = EOS;
  process.tksname[0] = EOS;
  process.astname[0] = EOS;
  process.repname[0] = EOS;

  process.prssstate = STEP_NOTDONE;
  process.stxsstate = STEP_NOTDONE;
  process.semsstate = STEP_NOTDONE;

  process.prserr = PERR_NOTHING;
  process.stxerr = STXERR_NOTHING;
  process.semerr = SEMERR_NOTHING;

  process.prsnblines = 0;
  process.stxnblines = 0;
  process.semnblines = 0;

  for (int i = 0; i < MAXERRORS; ++i)
  {
    process.prslines[i].line = -1;
    process.stxlines[i].line = -1;
    process.semlines[i].line = -1;
  }

  if (ferr == NULL or
      srcname == NULL or
      strlen(srcname) > 199)
    return false;

  process.ferr = ferr;

  strcpy(process.srcname, srcname);

  strcat(process.tksname, srcname);
  strcat(process.tksname, ".tks");

  strcat(process.astname, srcname);
  strcat(process.astname, ".ast");

  strcat(process.repname, srcname);
  strcat(process.repname, ".report");

  return true;
}