#include <stdio.h>
#include <stdlib.h>

#include "api.h"
#include "model.h"

void sitl_fparse_error()
{
  step_state_t state = process.prssstate;

  if (state == STEP_FAILURE)
  {
    switch (process.prserr)
    {
    case PERR_SRCNOTOPENED:
      break;
    case PERR_TKSNOTOPENED:
      break;
    case PERR_INVALIDLINES:
      for (int i = 0; i < process.prsnblines; ++i)
        ;
      break;
    case PERR_NOTHING:
      break;
    default:
      break;
    }
  }
}

void sitl_fcheckstx_error()
{
}

void sitl_fchecksem_error()
{
}

void sitl_ftranslate_error()
{
}
