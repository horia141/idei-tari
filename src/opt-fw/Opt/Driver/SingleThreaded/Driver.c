#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "Opt/Driver.h"

struct DriverParams
{
  int             IterationsNr;
  int             StatePrintInterval;
  MethodParams*   MethodParams;
};

DriverParams*
DriverParamsAlloc(
  FILE* fin,
  const char* name)
{
  DriverParams*  driverParams;

  driverParams = malloc(sizeof(DriverParams));

  fscanf(fin," %*s [ SingleThreadedParams ] :");
  fscanf(fin," IterationsNr : %d",&driverParams->IterationsNr);
  fscanf(fin," StatePrintInterval : %d",&driverParams->StatePrintInterval);
  driverParams->MethodParams = MethodParamsAlloc(fin,"MethodParams");

  return driverParams;
}

void
DriverParamsFree(
  DriverParams** driverParams)
{
  assert(driverParams != NULL && DriverParamsIsValid(*driverParams));

  (*driverParams)->IterationsNr = 0;
  (*driverParams)->StatePrintInterval = 0;
  MethodParamsFree(&(*driverParams)->MethodParams);

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
  printf("%s  IterationsNr: %d\n",indent,driverParams->IterationsNr);
  printf("%s  StatePrintInterval: %d\n",indent,driverParams->StatePrintInterval);
  MethodParamsPrint(driverParams->MethodParams,"MethodParams",indentLevel + 1);

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
  assert(DriverParamsIsValid(driverParams));

  DriverState*  driverState;

  driverState = malloc(sizeof(DriverState));

  driverState->Iteration = 0;
  driverState->MethodState = MethodStateAlloc(driverParams->MethodParams);
  driverState->Best = MethodStateGetBest(driverParams->MethodParams,driverState->MethodState,NULL);

  return driverState;
}

DriverState*
DriverStateGenNext(
  const DriverParams* driverParams,
  const DriverState* initState)
{
  assert(DriverParamsIsValid(driverParams));
  assert(DriverStateIsValid(driverParams,initState));

  DriverState*   driverState;
  MethodState*   nextMethodState;
  ProblemState*  nextBest;
  
  driverState = malloc(sizeof(DriverState));

  driverState->Iteration = 1;
  driverState->MethodState = MethodStateGenNext(driverParams->MethodParams,initState->MethodState);
  driverState->Best = MethodStateGetBest(driverParams->MethodParams,driverState->MethodState,initState->Best);
  
  for (driverState->Iteration = 1; driverState->Iteration < driverParams->IterationsNr; driverState->Iteration++) {
    if (driverState->Iteration % driverParams->StatePrintInterval == 0) {
      DriverStatePrint(driverParams,driverState,"currentState",0);
    }

    nextMethodState = MethodStateGenNext(driverParams->MethodParams,driverState->MethodState);
    nextBest = MethodStateGetBest(driverParams->MethodParams,nextMethodState,driverState->Best);

    MethodStateFree(driverParams->MethodParams,&driverState->MethodState);
    ProblemStateFree(MethodParamsProblemParams(driverParams->MethodParams),&driverState->Best);

    driverState->MethodState = nextMethodState;
    driverState->Best = nextBest;
  }

  return driverState;
}

void
DriverStateFree(
  const DriverParams* driverParams,
  DriverState** driverState)
{
  assert(DriverParamsIsValid(driverParams));
  assert(driverState != NULL && DriverStateIsValid(driverParams,*driverState));

  (*driverState)->Iteration = -1;
  MethodStateFree(driverParams->MethodParams,&(*driverState)->MethodState);
  ProblemStateFree(MethodParamsProblemParams(driverParams->MethodParams),&(*driverState)->Best);

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
  MethodStatePrint(driverParams->MethodParams,driverState->MethodState,"MethodState",indentLevel + 1);
  ProblemStatePrint(MethodParamsProblemParams(driverParams->MethodParams),driverState->Best,"Best",indentLevel + 1);

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

  if (!MethodStateIsValid(driverParams->MethodParams,driverState->MethodState)) {
    return 0;
  }

  if (!ProblemStateIsValid(MethodParamsProblemParams(driverParams->MethodParams),driverState->Best)) {
    return 0;
  }

  return 1;
}
