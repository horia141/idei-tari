#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>

#include "Method.h"

struct MethodParams
{
  int  ExplorationFactor;
  int  ProblemStatesCnt;
};

MethodParams*
MethodParamsAlloc(
  FILE* fin)
{
  MethodParams*  methodParams;

  methodParams = malloc(sizeof(MethodParams));

  fscanf(fin," HillClimbingParams :");
  fscanf(fin," ExplorationFactor : %d",&methodParams->ExplorationFactor);
  fscanf(fin," ProblemStatesCnt : %d",&methodParams->ProblemStatesCnt);

  return methodParams;
}

void
MethodParamsFree(
  MethodParams** methodParams)
{
  assert(methodParams != NULL);
  assert(MethodParamsIsValid(*methodParams));

  (*methodParams)->ExplorationFactor = 0;
  (*methodParams)->ProblemStatesCnt = 0;

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

  printf("%sHillClimbing Params:\n",indent);
  printf("%s  ExplorationFactor: %d\n",indent,methodParams->ExplorationFactor);
  printf("%s  ProblemStatesCnt: %d\n",indent,methodParams->ProblemStatesCnt);

  free(indent);
}

int
MethodParamsIsValid(
  const MethodParams* methodParams)
{
  if (methodParams == NULL) {
    return 0;
  }

  if (methodParams->ExplorationFactor < 1) {
    return 0;
  }

  if (methodParams->ProblemStatesCnt < 1) {
    return 0;
  }

  return 1;
}


struct MethodState
{
  int             Iteration;
  int             ProblemStatesCnt;
  ProblemState**  ProblemStates;
};

MethodState*
MethodStateAlloc(
  const MethodParams* methodParams,
  const ProblemParams* problemParams)
{
  assert(MethodParamsIsValid(methodParams));
  assert(ProblemParamsIsValid(problemParams));

  MethodState*  methodState;
  int           i;

  methodState = malloc(sizeof(MethodState));

  methodState->Iteration = 0;
  methodState->ProblemStatesCnt = methodParams->ProblemStatesCnt;
  methodState->ProblemStates = malloc(sizeof(ProblemState*) * methodState->ProblemStatesCnt);

  for (i = 0; i < methodState->ProblemStatesCnt; i++) {
    methodState->ProblemStates[i] = ProblemStateAlloc(problemParams);
  }

  return methodState;
}

MethodState*
MethodStateGenNext(
  const MethodState* previousState,
  const MethodParams* methodParams,
  const ProblemParams* problemParams,
  int iteration)
{
  assert(MethodStateIsValid(previousState));
  assert(MethodParamsIsValid(methodParams));
  assert(ProblemParamsIsValid(problemParams));
  assert(previousState->ProblemStatesCnt == methodParams->ProblemStatesCnt);

  MethodState*   methodState;
  ProblemState*  nextBest;
  double         nextBestCost;
  ProblemState*  nextTryBest;
  double         nextTryBestCost;
  int            i;
  int            j;
  
  methodState = malloc(sizeof(MethodState));

  methodState->Iteration = iteration;
  methodState->ProblemStatesCnt = previousState->ProblemStatesCnt;
  methodState->ProblemStates = malloc(sizeof(ProblemState*) * methodState->ProblemStatesCnt);

  for (i = 0; i < methodState->ProblemStatesCnt; i++) {
    nextBest = ProblemStateGenNext(previousState->ProblemStates[i],problemParams);
    nextBestCost = ProblemStateCost(nextBest);

    for (j = 1; j < methodParams->ExplorationFactor; j++) {
      nextTryBest = ProblemStateGenNext(previousState->ProblemStates[i],problemParams);
      nextTryBestCost = ProblemStateCost(nextTryBest);

      if (nextTryBestCost < nextBestCost) {
	ProblemStateFree(&nextBest);

	nextBest = nextTryBest;
	nextBestCost = nextTryBestCost;
      } else {
	ProblemStateFree(&nextTryBest);
      }
    }

    methodState->ProblemStates[i] = nextBest;
  }

  return methodState;
}

void
MethodStateFree(
  MethodState** methodState)
{
  assert(methodState != NULL);
  assert(MethodStateIsValid(*methodState));

  int  i;

  for (i = 0; i < (*methodState)->ProblemStatesCnt; i++) {
    ProblemStateFree(&(*methodState)->ProblemStates[i]);
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
  const MethodState* methodState,
  int indentLevel)
{
  assert(MethodStateIsValid(methodState));
  assert(indentLevel >= 0);

  char*  indent;
  int    i;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sHillClimbing State:\n",indent);
  printf("%s  Iteration: %d\n",indent,methodState->Iteration);
  printf("%s  ProblemStatesCnt: %d\n",indent,methodState->ProblemStatesCnt);
  printf("%s  ProblemStates:\n",indent);

  for (i = 0; i < methodState->ProblemStatesCnt; i++) {
    ProblemStatePrint(methodState->ProblemStates[i],indentLevel + 2);
  }

  free(indent);
}

int
MethodStateIsValid(
  const MethodState* methodState)
{
  int  i;

  if (methodState == NULL) {
    return 0;
  }

  if (methodState->Iteration < 0) {
    return 0;
  }

  if (methodState->ProblemStatesCnt < 1) {
    return 0;
  }

  if (methodState->ProblemStates == NULL) {
    return 0;
  }

  for (i = 0; i < methodState->ProblemStatesCnt; i++) {
    if (!ProblemStateIsValid(methodState->ProblemStates[i])) {
      return 0;
    }
  }

  return 1;
}

ProblemState*
MethodStateGetBest(
  const MethodState* methodState,
  const ProblemState* currBest)
{
  assert(MethodStateIsValid(methodState));
  assert(currBest == NULL || ProblemStateIsValid(currBest));

  const ProblemState*  best;
  double               bestCost;
  double               currCost;
  int                  i;

  best = NULL;
  bestCost = DBL_MAX;

  for (i = 0; i < methodState->ProblemStatesCnt; i++) {
    currCost = ProblemStateCost(methodState->ProblemStates[i]);

    if (currCost < bestCost) {
      best = methodState->ProblemStates[i];
      bestCost = currCost;
    }
  }

  assert (best != NULL);

  if (currBest != NULL && ProblemStateCost(currBest) < bestCost) {
    return ProblemStateCopy(currBest);
  } else {
    return ProblemStateCopy(best);
  }
}
