#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>

#include "Opt/Method.h"

struct MethodParams
{
  int             ExplorationFactor;
  int             ProblemStatesCnt;
  ProblemParams*  ProblemParams;
};

MethodParams*
MethodParamsAlloc(
  FILE* fin,
  const char* name)
{
  MethodParams*  methodParams;

  methodParams = malloc(sizeof(MethodParams));

  fscanf(fin," %*s [ HillClimbingParams ] :");
  fscanf(fin," ExplorationFactor : %d",&methodParams->ExplorationFactor);
  fscanf(fin," ProblemStatesCnt : %d",&methodParams->ProblemStatesCnt);
  methodParams->ProblemParams = ProblemParamsAlloc(fin,"ProblemParams");

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
  ProblemParamsFree(&(*methodParams)->ProblemParams);

  free(*methodParams);
  *methodParams = NULL;
}

void
MethodParamsPrint(
  const MethodParams* methodParams,
  const char* name,
  int indentLevel)
{
  assert(MethodParamsIsValid(methodParams));
  assert(indentLevel >= 0);

  char*  indent;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%s%s[HillClimbingParams]:\n",indent,name);
  printf("%s  ExplorationFactor: %d\n",indent,methodParams->ExplorationFactor);
  printf("%s  ProblemStatesCnt: %d\n",indent,methodParams->ProblemStatesCnt);
  ProblemParamsPrint(methodParams->ProblemParams,"ProblemParams",indentLevel + 1);

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
  const MethodState* previousState)
{
  assert(MethodParamsIsValid(methodParams));
  assert(MethodStateIsValid(methodParams,previousState));

  MethodState*   methodState;
  ProblemState*  nextBest;
  double         nextBestCost;
  ProblemState*  nextTryBest;
  double         nextTryBestCost;
  int            i;
  int            j;
  
  methodState = malloc(sizeof(MethodState));

  methodState->ProblemStatesCnt = previousState->ProblemStatesCnt;
  methodState->ProblemStates = malloc(sizeof(ProblemState*) * methodState->ProblemStatesCnt);

  for (i = 0; i < methodState->ProblemStatesCnt; i++) {
    nextBest = ProblemStateGenNext(methodParams->ProblemParams,previousState->ProblemStates[i]);
    nextBestCost = ProblemStateCost(methodParams->ProblemParams,nextBest);

    for (j = 1; j < methodParams->ExplorationFactor; j++) {
      nextTryBest = ProblemStateGenNext(methodParams->ProblemParams,previousState->ProblemStates[i]);
      nextTryBestCost = ProblemStateCost(methodParams->ProblemParams,nextTryBest);

      if (nextTryBestCost < nextBestCost) {
	ProblemStateFree(methodParams->ProblemParams,&nextBest);

	nextBest = nextTryBest;
	nextBestCost = nextTryBestCost;
      } else {
	ProblemStateFree(methodParams->ProblemParams,&nextTryBest);
      }
    }

    methodState->ProblemStates[i] = nextBest;
  }

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

  (*methodState)->ProblemStatesCnt = 0;
  (*methodState)->ProblemStates = NULL;

  free(*methodState);
  *methodState = NULL;
}

void
MethodStatePrint(
  const MethodParams* methodParams,
  const MethodState* methodState,
  const char* name,
  int indentLevel)
{
  assert(MethodParamsIsValid(methodParams));
  assert(MethodStateIsValid(methodParams,methodState));
  assert(indentLevel >= 0);

  char*  indent;
  int    nameBufferCnt;
  char*  nameBuffer;
  int    i;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));
  nameBufferCnt = strlen("ProblemStates") + sizeof(methodState->ProblemStatesCnt) * 4 + 1;
  nameBuffer = malloc(sizeof(char) * nameBufferCnt);

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%s%s[HillClimbingState]:\n",indent,name);
  printf("%s  ProblemStatesCnt: %d\n",indent,methodState->ProblemStatesCnt);
  printf("%s  ProblemStates:\n",indent);

  for (i = 0; i < methodState->ProblemStatesCnt; i++) {
    snprintf(nameBuffer,nameBufferCnt,"ProblemState%d",i);
    ProblemStatePrint(methodParams->ProblemParams,methodState->ProblemStates[i],nameBuffer,indentLevel + 2);
  }

  free(indent);
  free(nameBuffer);
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
