#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "Driver.h"

struct DriverParams
{
  int             IterationsNr;
  int             StatePrintInterval;
  MethodParams*   MethodParams;
  ProblemParams*  ProblemParams;
};

DriverParams*
DriverParamsAlloc(
  FILE* fin)
{
  DriverParams*  driverParams;

  driverParams = malloc(sizeof(DriverParams));

  fscanf(fin," SingleThreadedParams :");
  fscanf(fin," IterationsNr : %d",&driverParams->IterationsNr);
  fscanf(fin," StatePrintInterval : %d",&driverParams->StatePrintInterval);
  driverParams->MethodParams = MethodParamsAlloc(fin);
  driverParams->ProblemParams = ProblemParamsAlloc(fin);

  return driverParams;
}

void
DriverParamsFree(
  DriverParams** driverParams)
{
  assert(driverParams != NULL);
  assert(DriverParamsIsValid(*driverParams));

  (*driverParams)->IterationsNr = 0;
  (*driverParams)->StatePrintInterval = 0;
  MethodParamsFree(&(*driverParams)->MethodParams);
  ProblemParamsFree(&(*driverParams)->ProblemParams);

  free(*driverParams);
  *driverParams = NULL;
}

void
DriverParamsPrint(
  const DriverParams* driverParams,
  int indentLevel)
{
  assert(DriverParamsIsValid(driverParams));
  assert(indentLevel >= 0);

  char*  indent;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sSingleThreadedParams:\n",indent);
  printf("%s  IterationsNr: %d\n",indent,driverParams->IterationsNr);
  printf("%s  StatePrintInterval: %d\n",indent,driverParams->StatePrintInterval);
  MethodParamsPrint(driverParams->MethodParams,indentLevel + 1);
  ProblemParamsPrint(driverParams->ProblemParams,indentLevel + 1);

  free(indent);
}

int
DriverParamsIsValid(
  const DriverParams* driverParams)
{
  if (driverParams == NULL) {
    return 0;
  }

  if (driverParams->IterationsNr < 1) {
    return 0;
  }

  if (driverParams->StatePrintInterval < 1) {
    return 0;
  }

  if (driverParams->StatePrintInterval >= driverParams->IterationsNr) {
    return 0;
  }

  if (!MethodParamsIsValid(driverParams->MethodParams)) {
    return 0;
  }

  if (!ProblemParamsIsValid(driverParams->ProblemParams)) {
    return 0;
  }

  return 1;
}


struct DriverState
{
  int                   Iteration;
  MethodState*          MethodState;
  ProblemState*         Best;
};

DriverState*
DriverStateAlloc(
  const DriverParams* driverParams)
{
  DriverState*  driverState;

  driverState = malloc(sizeof(DriverState));

  driverState->Iteration = 0;
  driverState->MethodState = MethodStateAlloc(driverParams->MethodParams,driverParams->ProblemParams);
  driverState->Best = MethodStateGetBest(driverState->MethodState,NULL);

  return driverState;
}

DriverState*
DriverStateRun(
  const DriverState* initState,
  const DriverParams* driverParams)
{
  assert(DriverStateIsValid(initState));
  assert(DriverParamsIsValid(driverParams));

  DriverState*   driverState;
  MethodState*   nextMethodState;
  ProblemState*  nextBest;
  
  driverState = malloc(sizeof(DriverState));

  driverState->Iteration = 1;
  driverState->MethodState = MethodStateGenNext(initState->MethodState,driverParams->MethodParams,driverParams->ProblemParams,driverState->Iteration);
  driverState->Best = MethodStateGetBest(driverState->MethodState,initState->Best);
  
  for (driverState->Iteration = 1; driverState->Iteration < driverParams->IterationsNr; driverState->Iteration++) {
    if (driverState->Iteration % driverParams->StatePrintInterval == 0) {
      DriverStatePrint(driverState,0);
    }

    nextMethodState = MethodStateGenNext(driverState->MethodState,driverParams->MethodParams,driverParams->ProblemParams,driverState->Iteration);
    nextBest = MethodStateGetBest(nextMethodState,driverState->Best);

    MethodStateFree(&driverState->MethodState);
    ProblemStateFree(&driverState->Best);

    driverState->MethodState = nextMethodState;
    driverState->Best = nextBest;
  }

  return driverState;
}

void
DriverStateFree(
  DriverState** driverState)
{
  assert(driverState != NULL);
  assert(DriverStateIsValid(*driverState));

  (*driverState)->Iteration = -1;
  MethodStateFree(&(*driverState)->MethodState);
  ProblemStateFree(&(*driverState)->Best);

  free(*driverState);
  *driverState = NULL;
}

void
DriverStatePrint(
  const DriverState* driverState,
  int indentLevel)
{
  assert(DriverStateIsValid(driverState));
  assert(indentLevel >= 0);

  char*  indent;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sSingleThreadedState:\n",indent);
  printf("%s  Iteration: %d\n",indent,driverState->Iteration);
  MethodStatePrint(driverState->MethodState,indentLevel + 1);
  ProblemStatePrint(driverState->Best,indentLevel + 1);

  free(indent);
}

int
DriverStateIsValid(
  const DriverState* driverState)
{
  if (driverState == NULL) {
    return 0;
  }

  if (driverState->Iteration < 0) {
    return 0;
  }

  if (!MethodStateIsValid(driverState->MethodState)) {
    return 0;
  }

  if (!ProblemStateIsValid(driverState->Best)) {
    return 0;
  }

  return 1;
}
