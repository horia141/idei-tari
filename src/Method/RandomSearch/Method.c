#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "Method.h"
#include "ProblemVector.h"

struct MethodParams
{
  int  ProblemStatesCnt;
};

MethodParams*
MethodParamsAlloc()
{
  MethodParams*  methodParams;

  methodParams = malloc(sizeof(MethodParams));

  methodParams->ProblemStatesCnt = 2;

  return methodParams;
}

void
MethodParamsFree(
  MethodParams** methodParams)
{
  assert(methodParams != NULL);
  assert(MethodParamsIsValid(*methodParams));

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

  printf("%sRandomSearch Params:\n",indent);
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

  if (methodParams->ProblemStatesCnt < 1) {
    return 0;
  }

  return 1;
}


struct MethodState
{
  int             Iteration;
  ProblemVector*  ProblemStates;
};

MethodState*
MethodStateAlloc(
  const MethodParams* methodParams,
  const ProblemParams* problemParams)
{
  assert(MethodParamsIsValid(methodParams));
  assert(ProblemParamsIsValid(problemParams));

  MethodState*  methodState;

  methodState = malloc(sizeof(MethodState));

  methodState->Iteration = 0;
  methodState->ProblemStates = ProblemVectorAlloc(methodParams->ProblemStatesCnt,problemParams);

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
  assert(ProblemVectorCnt(previousState->ProblemStates) == methodParams->ProblemStatesCnt);

  MethodState*  methodState;

  methodState = MethodStateAlloc(methodParams,problemParams);

  methodState->Iteration = iteration;

  return methodState;
}

void
MethodStateFree(
  MethodState** methodState)
{
  assert(methodState != NULL);
  assert(MethodStateIsValid(*methodState));

  (*methodState)->Iteration = -1;
  ProblemVectorFree(&(*methodState)->ProblemStates);

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

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sRandomSearch State:\n",indent);
  printf("%s  Iteration: %d\n",indent,methodState->Iteration);
  
  ProblemVectorPrint(methodState->ProblemStates,indentLevel + 1);

  free(indent);
}

int
MethodStateIsValid(
  const MethodState* methodState)
{
  if (methodState == NULL) {
    return 0;
  }

  if (methodState->Iteration < 0) {
    return 0;
  }

  if (!ProblemVectorIsValid(methodState->ProblemStates)) {
    return 0;
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

  best = ProblemVectorSelectBest(methodState->ProblemStates);

  if (currBest != NULL && ProblemStateCost(currBest) < ProblemStateCost(best)) {
    return ProblemStateCopy(currBest);
  } else {
    return ProblemStateCopy(best);
  }
}
