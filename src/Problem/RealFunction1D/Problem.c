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
};

static double  _ProblemFunction(
                 double x);

ProblemParams*
ProblemParamsAlloc(
  FILE* fin)
{
  ProblemParams*  problemParams;

  problemParams = malloc(sizeof(ProblemParams));

  fscanf(fin," RealFunction1DParams :");
  fscanf(fin," IntervalStart : %lf",&problemParams->IntervalStart);
  fscanf(fin," IntervalEnd : %lf",&problemParams->IntervalEnd);

  return problemParams;
}

void
ProblemParamsFree(
  ProblemParams** problemParams)
{
  assert(problemParams != NULL);
  assert(ProblemParamsIsValid(*problemParams));

  (*problemParams)->IntervalStart = 0.0;
  (*problemParams)->IntervalEnd = 0.0;

  free(*problemParams);
  *problemParams = NULL;
}

void
ProblemParamsPrint(
  const ProblemParams* problemParams,
  int indentLevel)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(indentLevel >= 0);

  char*  indent;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sRealFunction1D Params\n",indent);
  printf("%s  IntervalStart: %f\n",indent,problemParams->IntervalStart);
  printf("%s  IntervalEnd: %f\n",indent,problemParams->IntervalEnd);

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
  const ProblemState* sourceState)
{
  assert(ProblemStateIsValid(sourceState));

  ProblemState*  problemState;

  problemState = malloc(sizeof(ProblemState));

  problemState->Position = sourceState->Position;
  problemState->Cost = sourceState->Cost;

  return problemState;
}

ProblemState*
ProblemStateGenNext(
  const ProblemState* previousState,
  const ProblemParams* problemParams)
{
  assert(ProblemStateIsValid(previousState));
  assert(ProblemParamsIsValid(problemParams));

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
  const ProblemState* parentState0,
  const ProblemState* parentState1,
  const ProblemParams* problemParams,
  int crossOverMaskCnt,
  const int* crossOverMask)
{
  assert(ProblemStateIsValid(parentState0));
  assert(ProblemStateIsValid(parentState1));
  assert(ProblemParamsIsValid(problemParams));
  assert(crossOverMaskCnt > 0);
  assert(crossOverMask != NULL);
  assert(crossOverMaskCnt == ProblemStateGenomeSize(parentState0));
  assert(crossOverMaskCnt == ProblemStateGenomeSize(parentState1));

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

void
ProblemStateFree(
  ProblemState** problemState)
{
  assert(problemState != NULL);
  assert(ProblemStateIsValid(*problemState));

  (*problemState)->Position = 0.0;
  (*problemState)->Cost = 0.0;

  free(*problemState);
  *problemState = NULL;
}

void
ProblemStatePrint(
  const ProblemState* problemState, int indentLevel)
{
  assert(ProblemStateIsValid(problemState));
  assert(indentLevel >= 0);

  char*  indent;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sRealFunction1D State:\n",indent);
  printf("%s  Position: %f\n",indent,problemState->Position);
  printf("%s  Cost: %f\n",indent,problemState->Cost);

  free(indent);
}

int
ProblemStateIsValid(
  const ProblemState* problemState)
{
  if (problemState == NULL) {
    return 0;
  }

  return 1;
}

int
ProblemStateCompare(
  const ProblemState** problemState0,
  const ProblemState** problemState1)
{
  assert(problemState0 != NULL);
  assert(problemState1 != NULL);
  assert(ProblemStateIsValid(*problemState0));
  assert(ProblemStateIsValid(*problemState1));

  if ((*problemState0)->Cost < (*problemState1)->Cost) {
    return -1;
  } else if ((*problemState0)->Cost > (*problemState1)->Cost) {
    return 1;
  } else {
    return 0;
  }
}

double
ProblemStateCost(
  const ProblemState* problemState)
{
  assert(ProblemStateIsValid(problemState));

  return problemState->Cost;
}

int
ProblemStateGenomeSize(
  const ProblemState* problemState)
{
  assert(ProblemStateIsValid(problemState));

  return sizeof(problemState->Position) * 8;
}
