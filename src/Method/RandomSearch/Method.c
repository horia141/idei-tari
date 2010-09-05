#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>

#include "Method.h"

struct MethodParams
{
  int             ProblemStatesCnt;
  ProblemParams*  ProblemParams;
};

MethodParams*
MethodParamsAlloc(
  FILE* fin)
{
  MethodParams*  methodParams;

  methodParams = malloc(sizeof(MethodParams));

  fscanf(fin," RandomSearchParams :");
  fscanf(fin," ProblemStatesCnt : %d",&methodParams->ProblemStatesCnt);
  methodParams->ProblemParams = ProblemParamsAlloc(fin);

  return methodParams;
}

void
MethodParamsFree(
  MethodParams** methodParams)
{
  assert(methodParams != NULL && MethodParamsIsValid(*methodParams));

  (*methodParams)->ProblemStatesCnt = 0;
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

  printf("%sRandomSearchParams:\n",indent);
  printf("%s  ProblemStatesCnt: %d\n",indent,methodParams->ProblemStatesCnt);
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

  if (methodParams->ProblemStatesCnt < 1) {
    return 0;
  }

  if (!ProblemParamsIsValid(methodParams->ProblemParams)) {
    return 0;
  }

  return 1;
}

const ProblemParams*
MethodParamsProblemParams(const MethodParams* methodParams)
{
  assert(MethodParamsIsValid(methodParams));

  return methodParams->ProblemParams;
}


struct MethodState
{
  int             Iteration;
  int             ProblemStatesCnt;
  ProblemState**  ProblemStates;
};

MethodState*
MethodStateAlloc(
  const MethodParams* methodParams)
{
  assert(MethodParamsIsValid(methodParams));

  MethodState*  methodState;
  int           i;

  methodState = malloc(sizeof(MethodState));

  methodState->Iteration = 0;
  methodState->ProblemStatesCnt = methodParams->ProblemStatesCnt;
  methodState->ProblemStates = malloc(sizeof(ProblemState*) * methodState->ProblemStatesCnt);

  for (i = 0; i < methodState->ProblemStatesCnt; i++) {
    methodState->ProblemStates[i] = ProblemStateAlloc(methodParams->ProblemParams);
  }

  return methodState;
}

MethodState*
MethodStateGenNext(
  const MethodParams* methodParams,
  const MethodState* previousState,
  int iteration)
{
  assert(MethodParamsIsValid(methodParams));
  assert(MethodStateIsValid(methodParams,previousState));
  assert(iteration >= 0);

  MethodState*  methodState;

  methodState = MethodStateAlloc(methodParams);

  methodState->Iteration = iteration;

  return methodState;
}

void
MethodStateFree(
  const MethodParams* methodParams,
  MethodState** methodState)
{
  assert(MethodParamsIsValid(methodParams));
  assert(methodState != NULL && MethodStateIsValid(methodParams,*methodState));

  int  i;

  for (i = 0; i < (*methodState)->ProblemStatesCnt; i++) {
    ProblemStateFree(methodParams->ProblemParams,&(*methodState)->ProblemStates[i]);
  }

  free((*methodState)->ProblemStates);

  (*methodState)->Iteration = -1;
  (*methodState)->ProblemStatesCnt = 0;
  (*methodState)->ProblemStates = NULL;

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
  int    i;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sRandomSearchState:\n",indent);
  printf("%s  Iteration: %d\n",indent,methodState->Iteration);
  printf("%s  ProblemStatesCnt: %d\n",indent,methodState->ProblemStatesCnt);
  printf("%s  ProblemStates:\n",indent);

  for (i = 0; i < methodState->ProblemStatesCnt; i++) {
    ProblemStatePrint(methodParams->ProblemParams,methodState->ProblemStates[i],indentLevel + 2);
  }

  free(indent);
}

int
MethodStateIsValid(
  const MethodParams* methodParams,
  const MethodState* methodState)
{
  assert(MethodParamsIsValid(methodParams));

  int  i;

  if (methodState == NULL) {
    return 0;
  }

  if (methodState->Iteration < 0) {
    return 0;
  }

  if (methodState->ProblemStatesCnt != methodParams->ProblemStatesCnt) {
    return 0;
  }

  if (methodState->ProblemStates == NULL) {
    return 0;
  }

  for (i = 0; i < methodState->ProblemStatesCnt; i++) {
    if (!ProblemStateIsValid(methodParams->ProblemParams,methodState->ProblemStates[i])) {
      return 0;
    }
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
  double               currCost;
  int                  i;

  best = NULL;
  bestCost = DBL_MAX;

  for (i = 0; i < methodState->ProblemStatesCnt; i++) {
    currCost = ProblemStateCost(methodParams->ProblemParams,methodState->ProblemStates[i]);

    if (currCost < bestCost) {
      best = methodState->ProblemStates[i];
      bestCost = currCost;
    }
  }

  assert (best != NULL);

  if (currBest != NULL && ProblemStateCost(methodParams->ProblemParams,currBest) < bestCost) {
    return ProblemStateCopy(methodParams->ProblemParams,currBest);
  } else {
    return ProblemStateCopy(methodParams->ProblemParams,best);
  }
}
