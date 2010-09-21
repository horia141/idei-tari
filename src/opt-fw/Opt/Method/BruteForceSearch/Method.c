#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>

#include "Method.h"

struct MethodParams
{
  ProblemParams*  ProblemParams;
};

MethodParams*
MethodParamsAlloc(
  FILE* fin)
{
  MethodParams*  methodParams;

  methodParams = malloc(sizeof(MethodParams));

  fscanf(fin," BruteForceSearchParams : ");
  methodParams->ProblemParams = ProblemParamsAlloc(fin);

  return methodParams;
}

void
MethodParamsFree(
  MethodParams** methodParams)
{
  assert(methodParams != NULL && MethodParamsIsValid(*methodParams));

  ProblemParamsFree(&(*methodParams)->ProblemParams);

  free(*methodParams);
  *methodParams = NULL;
}

void
MethodParamsPrint(
  const MethodParams* methodParams,
  int indentLevel)
{
  assert(MethodParamsIsValid(methodParams));
  assert(indentLevel >= 0);

  char*  indent;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sBruteForceSearchParams:\n",indent);
  ProblemParamsPrint(methodParams->ProblemParams,indentLevel + 1);

  free(indent);
}

int
MethodParamsIsValid(
  const MethodParams* methodParams)
{
  if (methodParams == NULL) {
    return 0;
  }

  if (!ProblemParamsIsValid(methodParams->ProblemParams)) {
    return 0;
  }

  return 1;
}

const ProblemParams*
MethodParamsProblemParams(
  const MethodParams* methodParams)
{
  assert(MethodParamsIsValid(methodParams));

  return methodParams->ProblemParams;
}


struct MethodState
{
  ProblemState*  ProblemState;
};

MethodState*
MethodStateAlloc(
  const MethodParams* methodParams)
{
  assert(MethodParamsIsValid(methodParams));

  MethodState*  methodState;

  methodState = malloc(sizeof(MethodState));

  methodState->ProblemState = ProblemStateFirst(methodParams->ProblemParams);

  return methodState;
}

MethodState*
MethodStateGenNext(
  const MethodParams* methodParams,
  const MethodState* previousState)
{
  assert(MethodParamsIsValid(methodParams));
  assert(MethodStateIsValid(methodParams,previousState));

  MethodState*  methodState;

  methodState = malloc(sizeof(MethodState));

  methodState->ProblemState = ProblemStateWalk(methodParams->ProblemParams,previousState->ProblemState);

  return methodState;
}

void
MethodStateFree(
  const MethodParams* methodParams,
  MethodState** methodState)
{
  assert(MethodParamsIsValid(methodParams));
  assert(methodState != NULL && MethodStateIsValid(methodParams,*methodState));

  ProblemStateFree(methodParams->ProblemParams,&(*methodState)->ProblemState);

  free(*methodState);
  *methodState = NULL;
}

void
MethodStatePrint(
  const MethodParams* methodParams,
  const MethodState* methodState,
  int indentLevel)
{
  assert(MethodParamsIsValid(methodParams));
  assert(MethodStateIsValid(methodParams,methodState));
  assert(indentLevel >= 0);

  char*  indent;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sBruteForceSearchState:\n",indent);
  printf("%s  ProblemStatesCnt: 1\n",indent);
  printf("%s  ProblemStates: \n",indent);
  ProblemStatePrint(methodParams->ProblemParams,methodState->ProblemState,indentLevel + 2);

  free(indent);
}

int
MethodStateIsValid(
  const MethodParams* methodParams,
  const MethodState* methodState)
{
  assert(MethodParamsIsValid(methodParams));

  if (methodState == NULL) {
    return 0;
  }

  if (!ProblemStateIsValid(methodParams->ProblemParams,methodState->ProblemState)) {
    return 0;
  }

  return 1;
}

ProblemState*
MethodStateGetBest(
  const MethodParams* methodParams,
  const MethodState* methodState,
  const ProblemState* currBest)
{
  assert(MethodParamsIsValid(methodParams));
  assert(MethodStateIsValid(methodParams,methodState));
  assert(currBest == NULL || ProblemStateIsValid(methodParams->ProblemParams,currBest));

  const ProblemState*  best;
  double               bestCost;

  best = methodState->ProblemState;
  bestCost = ProblemStateCost(methodParams->ProblemParams,best);

  if (currBest != NULL && ProblemStateCost(methodParams->ProblemParams,currBest) < bestCost) {
    return ProblemStateCopy(methodParams->ProblemParams,currBest);
  } else {
    return ProblemStateCopy(methodParams->ProblemParams,best);
  }
}
