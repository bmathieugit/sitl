#include <stdlib.h>

#include "ctools.h"
#include "api.h"
// #include "syntax.h"

int main(
    int argc,
    char **argv)
{
  printf("sitl compiler\n");

  char *fname = sitl_argsfind(argc, argv, "--file");

  if (fname == NULL)
  {
    fprintf(stderr, "fname not found in args line");
    return EXIT_FAILURE;
  }
  else
    fprintf(stdout, "--file : %s\n", fname);

  sitl_initprocess(fname, stderr);

  printf("src : %s\ntks : %s\nast : %s\nrep : %s\n",
         process.srcname,
         process.tksname,
         process.astname,
         process.repname);

  sitl_parse();
  sitl_fparse_error();

  sitl_checkstx();
  sitl_fcheckstx_error();

  // sitl_checksem();
  // sitl_fchecksem_error();

  sitl_wreport();
  sitl_typesindex();

  return EXIT_SUCCESS;
}
