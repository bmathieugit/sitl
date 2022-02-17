#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ctools.h"
#include "model.h"
#include "api.h"

void sitl_wreport()
{
  FILE *rep = fopen(process.repname, "wb+");
  fwrite(&process,
         sizeof(process),
         1, rep);
  fclose(rep);
}

void sitl_rreport()
{
  FILE *rep = fopen(process.repname, "rb+");
  fread(&process,
        sizeof(process),
        1, rep);
  fclose(rep);
}
