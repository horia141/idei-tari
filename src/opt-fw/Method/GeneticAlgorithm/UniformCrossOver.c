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

  fscanf(fin," UniformCrossOverParams :");

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

  printf("%sUniformCrossOverParams:\n",indent);

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

  int  i;

  for (i = 0; i < crossOverMaskCnt; i++) {
    crossOverMask[i] = rand() % 2;
  }
}
