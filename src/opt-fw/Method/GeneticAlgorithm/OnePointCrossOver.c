#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "CrossOver.h"

struct CrossOverParams
{
};

CrossOverParams*
CrossOverParamsAlloc(
  FILE* fin)
{
  CrossOverParams*  crossOverParams;

  crossOverParams = malloc(sizeof(CrossOverParams));

  fscanf(fin," OnePointCrossOverParams :");

  return crossOverParams;
}

void
CrossOverParamsFree(
  CrossOverParams** crossOverParams)
{
  assert(crossOverParams != NULL);
  assert(CrossOverParamsIsValid(*crossOverParams));

  free(*crossOverParams);
  *crossOverParams = NULL;
}

void
CrossOverParamsPrint(
  const CrossOverParams* crossOverParams,
  int indentLevel)
{
  assert(CrossOverParamsIsValid(crossOverParams));
  assert(indentLevel >= 0);

  char*  indent;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sOnePointCrossOverParams:\n",indent);

  free(indent);
}

int
CrossOverParamsIsValid(
  const CrossOverParams* crossOverParams)
{
  if (crossOverParams == NULL) {
    return 0;
  }

  return 1;
}


void
GenerateCrossOverMask(
  const CrossOverParams* crossOverParams,
  int crossOverMaskCnt,
  int* crossOverMask)
{
  assert(CrossOverParamsIsValid(crossOverParams));
  assert(crossOverMaskCnt > 0);
  assert(crossOverMask != NULL);

  int  crossOverPoint;
  int  i;

  crossOverPoint = rand() % (crossOverMaskCnt - 1) + 1;

  for (i = 0; i < crossOverPoint; i++) {
    crossOverMask[i] = 0;
  }

  for (i = crossOverPoint; i < crossOverMaskCnt; i++) {
    crossOverMask[i] = 1;
  }
}
