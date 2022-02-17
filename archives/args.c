#include "api.h"
#include "ctools.h"

char* sitl_argsfind(
  int argc, 
  char** argv, 
  const char* arg)
{
  char *found = NULL;

  for (int i = 0; i < argc; ++i)
  {
    if (strstarts(argv[i], arg))
    {
      char *eql = strchr(argv[i], '=');

      if (eql != NULL)
        found = eql + 1;
    }
  }

  return found;
}