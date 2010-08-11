#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "Method.h"
#include "ProblemVector.h"

struct MethodParams
{
  int  Miu;
  int  Lambda;
};

MethodParams*
MethodParamsAlloc()
{
  MethodParams*  methodParams;

  methodParams = malloc(sizeof(MethodParams));

  methodParams->Miu = 2;
  methodParams->Lambda = 4;

  return methodParams;
}

void
MethodParamsFree(
  MethodParams** methodParams)
{
  assert(methodParams != NULL);
  assert(MethodParamsIsValid(*methodParams));

  (*methodParams)->Miu = 0;
  (*methodParams)->Lambda = 0;

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

  printf("%sEvolutionStrategy (μ,λ) Params:\n",indent);
  printf("%s  Miu: %d\n",indent,methodParams->Miu);
  printf("%s  Lambda: %d\n",indent,methodParams->Lambda);

  free(indent);
}

int
MethodParamsIsValid(
  const MethodParams* methodParams)
{
  if (methodParams == NULL) {
    return 0;
  }

  if (methodParams->Miu < 1) {
    return 0;
  }

  if (methodParams->Lambda < 1) {
    return 0;
  }

  if (methodParams->Lambda % methodParams->Miu != 0) {
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
  methodState->ProblemStates = ProblemVectorAlloc(methodParams->Lambda,problemParams);

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
  assert(ProblemVectorCnt(previousState->ProblemStates) == methodParams->Lambda);

  MethodState*          methodState;
  int                   sortedStatesCnt;
  const ProblemState**  sortedStates;
  int                   bestOffspringCnt;
  ProblemState*         newOffspring;
  int                   i;
  int                   j;

  sortedStatesCnt = ProblemVectorCnt(previousState->ProblemStates);
  sortedStates = malloc(sizeof(const ProblemState*) * sortedStatesCnt);

  memcpy(sortedStates,ProblemVectorTempView(previousState->ProblemStates),sizeof(const ProblemState*) * sortedStatesCnt);
  qsort(sortedStates,sortedStatesCnt,sizeof(const ProblemState*),(__compar_fn_t)ProblemStateCompare);

  methodState = malloc(sizeof(MethodState));
  
  methodState->Iteration = iteration;
  methodState->ProblemStates = ProblemVectorCopy(previousState->ProblemStates);

  bestOffspringCnt = methodParams->Lambda / methodParams->Miu;

  for (i = 0; i < methodParams->Miu; i++) {
    for (j = 0; j < bestOffspringCnt; j++) {
      newOffspring = ProblemStateGenNext(sortedStates[i],problemParams);
      ProblemVectorSet(methodState->ProblemStates,i * bestOffspringCnt + j,newOffspring);
      ProblemStateFree(&newOffspring);
    }
  }

  free(sortedStates);

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

  printf("%sHillClimbing State:\n",indent);
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
