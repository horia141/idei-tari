#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "CrossOver.h"

struct CrossOverParams
{
  char*  Name;
};

CrossOverParams*
CrossOverParamsAlloc()
{
  CrossOverParams*  crossOverParams;

  crossOverParams = malloc(sizeof(CrossOverParams));

  crossOverParams->Name = strdup("UniformCrossOver");

  return crossOverParams;
}

void
CrossOverParamsFree(
  CrossOverParams** crossOverParams)
{
  assert(crossOverParams != NULL);
  assert(CrossOverParamsIsValid(*crossOverParams));

  free((*crossOverParams)->Name);
  (*crossOverParams)->Name = NULL;

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

  printf("%sUniformCrossOver Params:\n",indent);

  free(indent);
}

int
CrossOverParamsIsValid(
  const CrossOverParams* crossOverParams)
{
  if (crossOverParams == NULL) {
    return 0;
  }

  if (crossOverParams->Name == NULL) {
    return 0;
  }

  if (strlen(crossOverParams->Name) == 0) {
    return 0;
  }

  return 1;
}

const char*
CrossOverParamsName(
  const CrossOverParams* crossOverParams)
{
  assert(CrossOverParamsIsValid(crossOverParams));
    
  return crossOverParams->Name;
}


void
GenerateCrossOverMask(
  int crossOverMaskCnt,
  int* crossOverMask,
  const CrossOverParams* crossOverParams)
{
  assert(crossOverMaskCnt > 0);
  assert(crossOverMask != NULL);
  assert(CrossOverParamsIsValid(crossOverParams));

  int  i;

  for (i = 0; i < crossOverMaskCnt; i++) {
    crossOverMask[i] = rand() % 2;
  }
}
