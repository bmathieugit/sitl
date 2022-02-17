#ifndef __sitl_ctools_h__
#define __sitl_ctools_h__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define not !
#define and &&
#define or ||
#define EOL '\n'
#define EOS '\0'

static inline bool
chin(
    int c,
    int b,
    int e)
{
  return b <= c and
         c <= e;
}

static inline bool
strstarts(
    const char *s,
    const char *pfx)
{
  return strncmp(s, pfx, strlen(pfx)) == 0;
}

static inline bool
streq(
    const char *s1,
    const char *s2)
{
  return strcmp(s1, s2) == 0;
}

static inline size_t
strhash(const char *s)
{
  unsigned long hash = 5381;
  int c;

  while ((c = *s++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

static inline bool
isdquote(const int c)
{
  return c == '"';
}

static inline long
fsize(const char *fname)
{
  FILE *f = fopen(fname, "r");

  if (f == NULL)
  {
    fprintf(stderr, "file not found\n");
    return -1;
  }

  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  rewind(f);
  fclose(f);

  return size;
}

static inline int
freadl(
    char *buff,
    int limit,
    FILE *f)
{
  int c = fgetc(f);
  int i = 0;

  if (c == EOF)
    return 0;

  while (c != EOF and
         c != EOL and
         i < limit - 3)
  {
    buff[i] = c;
    i += 1;
    c = fgetc(f);
  }

  if (c == EOF or
      c == EOL)
  {
    buff[i] = EOL;
    buff[i + 1] = EOS;
  }
  else
  {
    buff[0] = EOS;
    return -1;
  }

  return i + 1;
}

static inline void
fescapel(FILE *f)
{
  int c;

  do
  {
    c = fgetc(f);
    printf("%d", c);

  } while (c != EOF and
           c != '\n');

  if (c == '\n')
    fgetc(f);
}

static inline int
freadall(
    const char *fname,
    char *ctnt,
    int fsz)
{
  FILE *f = fopen(fname, "r");

  if (f == NULL)
  {
    printf("file not found\n");
    return -1;
  }

  int ctntsize = fread(ctnt, 1, fsz, f);
  ctnt[ctntsize] = '\0';
  fclose(f);
  return ctntsize;
}

#endif
