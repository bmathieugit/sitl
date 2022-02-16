#ifndef __sitl_tokens_h__
#define __sitl_tokens_h__

#include <stdbool.h>
#include "model.h"

#define CLEARTEXT

extern process_t process;

char* sitl_argsfind(
  int argc, 
  char** argv, 
  const char* arg);

bool
sitl_initprocess(
    const char *srcname,
    FILE* ferr);

void sitl_wreport();
void sitl_rreport();

void sitl_rtksl(tline_t *tl, FILE* ftks);
void sitl_wtksl(tline_t *tl, FILE* ftks);

void sitl_fparse();
void sitl_fcheckstx();
void sitl_fchecksem();
void sitl_ftranslate();

void sitl_fparse_error();
void sitl_fcheckstx_error();
void sitl_fchecksem_error();
void sitl_ftranslate_error();

#endif