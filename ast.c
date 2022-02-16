#include <stdio.h>
#include <stdlib.h>

#include "ctools.h"
#include "api.h"
#include "model.h"

void sitl_typesindex()
{
  FILE *ftks = fopen(process.tksname, "r");

  if (ftks == NULL)
  {
    // TODO: une erreur est survenue à l'ouverture du fichier
  }

  tline_t tl;
  size_t nbtype = 0;

  do
  {
    sitl_rtksl(&tl, ftks);

    if (tl.state == TLS_VALID)
      if (tl.tks[0].type == TT_TYPE)
        ++nbtype;

    printf("coucou\n");

  } while (tl.state != TLS_LAST);

  printf("nb type %llu\n", nbtype);
}