#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "Bfs/Driver.h"

struct DriverParams
{
  int             StatePrintInterval;
  ProblemParams*  ProblemParams;
};

DriverParams*
DriverParamsAlloc(
  FILE* fin,
  const char* name)
{
  DriverParams*  driverParams;

  driverParams = malloc(sizeof(DriverParams));

  fscanf(fin," %*s [ SingleThreadedParams ] :");
  fscanf(fin," StatePrintInterval : %d",&driverParams->StatePrintInterval);
  driverParams->ProblemParams = ProblemParamsAlloc(fin,"ProblemParams");

  return driverParams;
}

void
DriverParamsFree(
  DriverParams** driverParams)
{
  assert(driverParams != NULL && DriverParamsIsValid(*driverParams));

  (*driverParams)->StatePrintInterval = 0;
  ProblemParamsFree(&(*driverParams)->ProblemParams);

  free(*driverParams);
  *driverParams = NULL;
}

void
DriverParamsPrint(
  const DriverParams* driverParams,
  const char* name,
  int indentLevel)
{
  assert(DriverParamsIsValid(driverParams));
  assert(indentLevel >= 0);

  char*  indent;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%s%s[SingleThreadedParams]:\n",indent,name);
  printf("%s  StatePrintInterval: %d\n",indent,driverParams->StatePrintInterval);
  ProblemParamsPrint(driverParams->ProblemParams,"ProblemParams",indentLevel + 1);

  free(indent);
}

int
DriverParamsIsValid(
  const DriverParams* driverParams)
{
  if (driverParams == NULL) {
    return 0;
  }

  if (driverParams->StatePrintInterval < 1) {
    return 0;
  }

  if (!ProblemParamsIsValid(driverParams->ProblemParams)) {
    return 0;
  }

  return 1;
}


struct DriverState
{
  int            Iteration;
  ProblemState*  Current;
  ProblemState*  Best;
};

DriverState*
DriverStateAlloc(
  const DriverParams* driverParams)
{
  assert(DriverParamsIsValid(driverParams));

  DriverState*  driverState;

  driverState = malloc(sizeof(DriverState));

  driverState->Iteration = 0;
  driverState->Current = ProblemStateFirst(driverParams->ProblemParams);
  driverState->Best = ProblemStateCopy(driverParams->ProblemParams,driverState->Current);

  return driverState;
}

DriverState*
DriverStateGenNext(
  const DriverParams* driverParams,
  const DriverState* initState)
{
  assert(DriverParamsIsValid(driverParams));
  assert(DriverStateIsValid(driverParams,initState));

  DriverState*   currentState;
  ProblemState*  nextProblemState;

  currentState = malloc(sizeof(DriverState));

  currentState->Iteration = initState->Iteration;
  currentState->Current = ProblemStateCopy(driverParams->ProblemParams,initState->Current);
  currentState->Best = ProblemStateCopy(driverParams->ProblemParams,initState->Best);

  do {
    nextProblemState = ProblemStateWalk(driverParams->ProblemParams,currentState->Current);

    if (nextProblemState != NULL) {
      ProblemStateFree(driverParams->ProblemParams,&currentState->Current);
      currentState->Current = nextProblemState;

      if (ProblemStateCost(driverParams->ProblemParams,currentState->Current) < 
	  ProblemStateCost(driverParams->ProblemParams,currentState->Best)) {
	ProblemStateFree(driverParams->ProblemParams,&currentState->Best);
	currentState->Best = ProblemStateCopy(driverParams->ProblemParams,currentState->Current);
      }

      currentState->Iteration += 1;

      if (currentState->Iteration % driverParams->StatePrintInterval == 0) {
	DriverStatePrint(driverParams,currentState,"currentState",0);
      }
    }
  } while (nextProblemState != NULL);

  return currentState;
}

void
DriverStateFree(
  const DriverParams* driverParams,
  DriverState** driverState)
{
  assert(DriverParamsIsValid(driverParams));
  assert(driverState != NULL && DriverStateIsValid(driverParams,*driverState));

  (*driverState)->Iteration = -1;
  ProblemStateFree(driverParams->ProblemParams,&(*driverState)->Current);
  ProblemStateFree(driverParams->ProblemParams,&(*driverState)->Best);

  free(*driverState);
  *driverState = NULL;
}

void
DriverStatePrint(
  const DriverParams* driverParams,
  const DriverState* driverState,
  const char* name,
  int indentLevel)
{
  assert(DriverParamsIsValid(driverParams));
  assert(DriverStateIsValid(driverParams,driverState));
  assert(indentLevel >= 0);

  char*  indent;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%s%s[SingleThreadedState]:\n",indent,name);
  printf("%s  Iteration: %d\n",indent,driverState->Iteration);
  ProblemStatePrint(driverParams->ProblemParams,driverState->Current,"Current",indentLevel + 1);
  ProblemStatePrint(driverParams->ProblemParams,driverState->Best,"Best",indentLevel + 1);

  free(indent);
}


int
DriverStateIsValid(
  const DriverParams* driverParams,
  const DriverState* driverState)
{
  assert(DriverParamsIsValid(driverParams));

  if (driverState == NULL) {
    return 0;
  }

  if (driverState->Iteration < 0) {
    return 0;
  }

  if (!ProblemStateIsValid(driverParams->ProblemParams,driverState->Current)) {
    return 0;
  }

  if (!ProblemStateIsValid(driverParams->ProblemParams,driverState->Best)) {
    return 0;
  }

  return 1;
}
