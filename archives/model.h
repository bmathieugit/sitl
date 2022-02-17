#ifndef __sitl_model_h__
#define __sitl_model_h__

#include <stdio.h>

#define LINESIZE 300
#define LTKSSIZE 6
#define MAXERRORS 50


// OBJECT MODEL


typedef enum
{
  TT_ATTR,
  TT_LET,
  TT_DEL,
  TT_CALL,
  TT_CONST,
  TT_COPY,
  TT_MOVE,
  TT_WHILE,
  TT_FOR,
  TT_IF,
  TT_FCT,
  TT_STR,
  TT_PARAM,
  TT_NUM,
  TT_ID,
  TT_TYPE,
  TT_RETRN,

  TT_OFFSET,
  TT_BOL,
  TT_EOL,
  TT_UNKNOWN,
  TT_UNDEF

} ttype_t;

typedef struct
{
  char val[LINESIZE];
  ttype_t type;
  int size;

} token_t;

typedef enum
{
  TLS_VALID,
  TLS_INVALID,
  TLS_EMPTY,
  TLS_OVERFLW,
  TLS_LAST

} tl_state_t;

typedef struct
{
  token_t tks[LTKSSIZE];
  int idx;
  int offset;
  int rnum;
  tl_state_t state;

} tline_t;


typedef struct 
{
  size_t hash;
  char* val;

} type_index_t;


// PROCESS MODEL


typedef enum
{
  STEP_NOTDONE,
  STEP_SUCCESS,
  STEP_FAILURE

} step_state_t;

typedef enum
{
  PERR_NOTHING,
  PERR_SRCNOTOPENED,
  PERR_TKSNOTOPENED,
  PERR_INVALIDLINES

} prsstep_error_t;

typedef enum
{
  STXERR_NOTHING,
  STXERR_TKSNOTOPENED,
  STXERR_INVALIDL

} stxstep_error_t;

typedef enum
{
  SEMERR_NOTHING,
  SEMERR_FAILURE

} semstep_error_t;

typedef struct
{
  int line;

} prs_invalidl_t;

typedef struct
{
  int line;

} stx_invalidl_t;

typedef struct
{
  int line;

} sem_invalidl_t;

typedef struct
{
  char srcname[200];
  char tksname[256];
  char astname[256];
  char repname[256];

  FILE *ferr;

  step_state_t prssstate;
  prsstep_error_t prserr;
  int prsnblines;
  prs_invalidl_t prslines[MAXERRORS];

  step_state_t stxsstate;
  stxstep_error_t stxerr;
  int stxnblines;
  stx_invalidl_t stxlines[MAXERRORS];

  step_state_t semsstate;
  semstep_error_t semerr;
  int semnblines;
  sem_invalidl_t semlines[MAXERRORS];

} process_t;

#endif
