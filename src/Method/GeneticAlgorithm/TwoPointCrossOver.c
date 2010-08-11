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

  crossOverParams->Name = strdup("TwoPointCrossOver");

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

  printf("%sTwoPointCrossOver Params:\n",indent);

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
  assert(crossOverMaskCnt > 1);

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
