#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#include "Problem.h"

struct ProblemParams
{
  double  IntervalStart;
  double  IntervalEnd;
  double  IntervalStep;
};

static double  _ProblemFunction(
                 double x);

ProblemParams*
ProblemParamsAlloc(
  FILE* fin,
  const char* name)
{
  ProblemParams*  problemParams;

  problemParams = malloc(sizeof(ProblemParams));

  fscanf(fin," %*s [ RealFunction1DParams ] :");
  fscanf(fin," Function : %*[^\n] ");
  fscanf(fin," IntervalStart : %lf",&problemParams->IntervalStart);
  fscanf(fin," IntervalEnd : %lf",&problemParams->IntervalEnd);
  fscanf(fin," IntervalStep : %lf",&problemParams->IntervalStep);

  return problemParams;
}

void
ProblemParamsFree(
  ProblemParams** problemParams)
{
  assert(problemParams != NULL && ProblemParamsIsValid(*problemParams));

  (*problemParams)->IntervalStart = 0.0;
  (*problemParams)->IntervalEnd = 0.0;
  (*problemParams)->IntervalStep = 0.0;

  free(*problemParams);
  *problemParams = NULL;
}

void
ProblemParamsPrint(
  const ProblemParams* problemParams,
  const char* name,
  int indentLevel)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(indentLevel >= 0);

  char*  indent;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%s%s[RealFunction1DParams]:\n",indent,name);
  printf("%s  Function: x * x\n",indent);
  printf("%s  IntervalStart: %f\n",indent,problemParams->IntervalStart);
  printf("%s  IntervalEnd: %f\n",indent,problemParams->IntervalEnd);
  printf("%s  IntervalStep: %f\n",indent,problemParams->IntervalStep);

  free(indent);
}

int
ProblemParamsIsValid(
  const ProblemParams* problemParams)
{
  if (problemParams == NULL) {
    return 0;
  }

  if (problemParams->IntervalEnd <= problemParams->IntervalStart) {
    return 0;
  }
  
  if (problemParams->IntervalStep < 0 || 
      problemParams->IntervalStep > problemParams->IntervalEnd - problemParams->IntervalStart) {
    return 0;
  }

  return 1;
}

static double
_ProblemFunction(
  double x)
{
  return x * x;
}


struct ProblemState
{
  double  Position;
  double  Cost;
};

ProblemState*
ProblemStateAlloc(
  const ProblemParams* problemParams)
{
  assert(ProblemParamsIsValid(problemParams));

  ProblemState*  problemState;

  problemState = malloc(sizeof(ProblemState));

  problemState->Position = (((double)rand()) / RAND_MAX) * (problemParams->IntervalEnd - problemParams->IntervalStart) + problemParams->IntervalStart;
  problemState->Cost = _ProblemFunction(problemState->Position);

  return problemState;
}

ProblemState*
ProblemStateCopy(
  const ProblemParams* problemParams,
  const ProblemState* sourceState)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,sourceState));

  ProblemState*  problemState;

  problemState = malloc(sizeof(ProblemState));

  problemState->Position = sourceState->Position;
  problemState->Cost = sourceState->Cost;

  return problemState;
}

ProblemState*
ProblemStateGenNext(
  const ProblemParams* problemParams,
  const ProblemState* previousState)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,previousState));

  ProblemState*  problemState;
  double         newPosition;
  double         interval;
  double         offset;

  interval = 0.1 * (problemParams->IntervalEnd - problemParams->IntervalStart);
  offset = ((double)rand() / RAND_MAX) * interval - interval / 2;
  newPosition = previousState->Position + offset;

  if (newPosition < problemParams->IntervalStart) {
    newPosition = problemParams->IntervalStart;
  } else if (newPosition > problemParams->IntervalEnd) {
    newPosition = problemParams->IntervalEnd;
  }

  problemState = malloc(sizeof(ProblemState));

  problemState->Position = newPosition;
  problemState->Cost = _ProblemFunction(problemState->Position);

  return problemState;
}

ProblemState*
ProblemStateCrossOver(
  const ProblemParams* problemParams,
  const ProblemState* parentState0,
  const ProblemState* parentState1,
  int crossOverMaskCnt,
  const int* crossOverMask)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,parentState0));
  assert(ProblemStateIsValid(problemParams,parentState1));
  assert(crossOverMaskCnt > 0);
  assert(crossOverMask != NULL);
  assert(crossOverMaskCnt == ProblemStateGenomeSize(problemParams,parentState0));
  assert(crossOverMaskCnt == ProblemStateGenomeSize(problemParams,parentState1));

  ProblemState*  problemState;
  double         newPosition;
  uint64_t       value0;
  uint64_t       value0Masked;
  uint64_t       value1;
  uint64_t       value1Masked;
  uint64_t       valueFinal;
  uint64_t       bitFlipMask;
  int            i;

  newPosition = parentState0->Position;
  bitFlipMask = 1;

  for (i = crossOverMaskCnt - 1; i >= 0; i--) {
    if (crossOverMask[i] == 1) {
      value0 = *((uint64_t*)&newPosition);
      value1 = *((uint64_t*)&parentState1->Position);

      value0Masked = value0 & ~bitFlipMask;
      value1Masked = value1 & bitFlipMask;

      valueFinal = value0Masked | value1Masked;

      newPosition = *((double*)&valueFinal);
    }

    bitFlipMask <<= 1;
  }

  if (newPosition < problemParams->IntervalStart) {
    newPosition = problemParams->IntervalStart;
  } else if (newPosition > problemParams->IntervalEnd) {
    newPosition = problemParams->IntervalEnd;
  }

  problemState = malloc(sizeof(ProblemState));

  problemState->Position = newPosition;
  problemState->Cost = _ProblemFunction(problemState->Position);

  return problemState;
}

ProblemState*
ProblemStateFirst(
  const ProblemParams* problemParams)
{
  assert(ProblemParamsIsValid(problemParams));

  ProblemState*  problemState;

  problemState = malloc(sizeof(ProblemState));

  problemState->Position = problemParams->IntervalStart;
  problemState->Cost = _ProblemFunction(problemState->Position);

  return problemState;
}

ProblemState*
ProblemStateWalk(
  const ProblemParams* problemParams,
  const ProblemState* previousState)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,previousState));

  ProblemState*  problemState;

  problemState = malloc(sizeof(ProblemState));

  problemState->Position = previousState->Position + problemParams->IntervalStep;

  if (problemState->Position > problemParams->IntervalEnd) {
    free(problemState);
    return NULL;
  }
  
  problemState->Cost = _ProblemFunction(problemState->Position);

  return problemState;
}

void
ProblemStateFree(
  const ProblemParams* problemParams,
  ProblemState** problemState)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(problemState != NULL && ProblemStateIsValid(problemParams,*problemState));

  (*problemState)->Position = 0.0;
  (*problemState)->Cost = 0.0;

  free(*problemState);
  *problemState = NULL;
}

void
ProblemStatePrint(
  const ProblemParams* problemParams,
  const ProblemState* problemState,
  const char* name,
  int indentLevel)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,problemState));
  assert(indentLevel >= 0);

  char*  indent;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%s%s[RealFunction1DState]:\n",indent,name);
  printf("%s  Position: %f\n",indent,problemState->Position);
  printf("%s  Cost: %f\n",indent,problemState->Cost);

  free(indent);
}

int
ProblemStateIsValid(
  const ProblemParams* problemParams,
  const ProblemState* problemState)
{
  assert(ProblemParamsIsValid(problemParams));

  if (problemState == NULL) {
    return 0;
  }

  if (problemState->Position < problemParams->IntervalStart ||
      problemState->Position > problemParams->IntervalEnd) {
    return 0;
  }

  return 1;
}

int
ProblemStateCompare(
  const ProblemParams* problemParams,
  const ProblemState* problemState0,
  const ProblemState* problemState1)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,problemState0));
  assert(ProblemStateIsValid(problemParams,problemState1));

  if (problemState0->Cost < problemState1->Cost) {
    return -1;
  } else if (problemState0->Cost > problemState1->Cost) {
    return 1;
  } else {
    return 0;
  }
}

double
ProblemStateCost(
  const ProblemParams* problemParams,
  const ProblemState* problemState)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,problemState));

  return problemState->Cost;
}

int
ProblemStateGenomeSize(
 const ProblemParams* problemParams,
  const ProblemState* problemState)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,problemState));

  return sizeof(problemState->Position) * 8;
}
