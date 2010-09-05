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

  fscanf(fin," TwoPointCrossOverParams :");

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

  printf("%sTwoPointCrossOverParams:\n",indent);

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
  assert(crossOverMaskCnt > 1); // separate test because this is TPC

  int  crossOverPoint0;
  int  crossOverPoint1;
  int  i;

  crossOverPoint0 = rand() % (crossOverMaskCnt - 2) + 1;
  crossOverPoint1 = rand() % (crossOverMaskCnt - crossOverPoint0) + crossOverPoint0;

  for (i = 0; i < crossOverPoint0; i++) {
    crossOverMask[i] = 0;
  }

  for (i = crossOverPoint0; i < crossOverPoint1; i++) {
    crossOverMask[i] = 1;
  }

  for (i = crossOverPoint1; i < crossOverMaskCnt; i++) {
    crossOverMask[i] = 0;
  }
}
