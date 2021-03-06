#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <math.h>

#include "Problem.h"

struct ProblemParams
{
  double  IntervalStartX;
  double  IntervalStartY;
  double  IntervalEndX;
  double  IntervalEndY;
  double  IntervalStep;
};

static double  _ProblemFunction(
                 double x, 
                 double y);

ProblemParams*
ProblemParamsAlloc(
  FILE* fin,
  const char* name)
{
  ProblemParams*  problemParams;

  problemParams = malloc(sizeof(ProblemParams));

  fscanf(fin," %*s [ RealFunction2DParams ] :");
  fscanf(fin," Function : %*[^\n] ");
  fscanf(fin," IntervalStart : ( %lf , %lf )",&problemParams->IntervalStartX,&problemParams->IntervalStartY);
  fscanf(fin," IntervalEnd : ( %lf , %lf )",&problemParams->IntervalEndX,&problemParams->IntervalEndY);
  fscanf(fin," IntervalStep : %lf",&problemParams->IntervalStep);

  return problemParams;
}

void
ProblemParamsFree(
  ProblemParams** problemParams)
{
  assert(problemParams != NULL && ProblemParamsIsValid(*problemParams));

  (*problemParams)->IntervalStartX = 0.0;
  (*problemParams)->IntervalStartY = 0.0;
  (*problemParams)->IntervalEndX = 0.0;
  (*problemParams)->IntervalEndY = 0.0;
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

  printf("%s%s[RealFunction2DParams]:\n",indent,name);
  printf("%s  Function: 1/4 * sqrt(30 * (30 - x) * (30 - y) * (x + y))\n",indent);
  printf("%s  IntervalStart: (%f,%f)\n",indent,problemParams->IntervalStartX,problemParams->IntervalStartY);
  printf("%s  IntervalEnd: (%f,%f)\n",indent,problemParams->IntervalEndX,problemParams->IntervalEndY);
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

  if (problemParams->IntervalEndX <= problemParams->IntervalStartX) {
    return 0;
  }

  if (problemParams->IntervalEndY <= problemParams->IntervalStartY) {
    return 0;
  }

  if (problemParams->IntervalStep < 0 ||
      problemParams->IntervalStep > problemParams->IntervalEndX - problemParams->IntervalStartX ||
      problemParams->IntervalStep > problemParams->IntervalEndY - problemParams->IntervalStartY) {
    return 0;
  }

  return 1;
}

static double
_ProblemFunction(
  double x,
  double y)
{
  return 1/4 * sqrt(30 * (30 - x) * (30 - y) * (x + y));
}


struct ProblemState
{
  double  PositionX;
  double  PositionY;
  double  Cost;
};

ProblemState*
ProblemStateAlloc(
  const ProblemParams* problemParams)
{
  assert(ProblemParamsIsValid(problemParams));

  ProblemState*  problemState;

  problemState = malloc(sizeof(ProblemState));

  problemState->PositionX = (((double)rand()) / RAND_MAX) * (problemParams->IntervalEndX - problemParams->IntervalStartX) + problemParams->IntervalStartX;
  problemState->PositionY = (((double)rand()) / RAND_MAX) * (problemParams->IntervalEndY - problemParams->IntervalStartY) + problemParams->IntervalStartY;
  problemState->Cost = _ProblemFunction(problemState->PositionX,problemState->PositionY);

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

  problemState->PositionX = sourceState->PositionX;
  problemState->PositionY = sourceState->PositionY;
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
  double         newPositionX;
  double         newPositionY;
  double         intervalX;
  double         intervalY;
  double         offsetX;
  double         offsetY;

  intervalX = 0.1 * (problemParams->IntervalEndX - problemParams->IntervalStartX);
  intervalY = 0.1 * (problemParams->IntervalEndY - problemParams->IntervalStartY);
  offsetX = ((double)rand() / RAND_MAX) * intervalX - intervalX / 2;
  offsetY = ((double)rand() / RAND_MAX) * intervalY - intervalY / 2;
  newPositionX = previousState->PositionX + offsetX;
  newPositionY = previousState->PositionY + offsetY;

  if (newPositionX < problemParams->IntervalStartX) {
    newPositionX = problemParams->IntervalStartX;
  } else if (newPositionX > problemParams->IntervalEndX) {
    newPositionX = problemParams->IntervalEndX;
  }

  if (newPositionY < problemParams->IntervalStartY) {
    newPositionY = problemParams->IntervalStartY;
  } else if (newPositionY > problemParams->IntervalEndY) {
    newPositionY = problemParams->IntervalEndY;
  }

  problemState = malloc(sizeof(ProblemState));

  problemState->PositionX = newPositionX;
  problemState->PositionY = newPositionY;
  problemState->Cost = _ProblemFunction(problemState->PositionX,problemState->PositionY);

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
  double         newPositionX;
  double         newPositionY;
  uint64_t       value0X;
  uint64_t       value0Y;
  uint64_t       value0MaskedX;
  uint64_t       value0MaskedY;
  uint64_t       value1X;
  uint64_t       value1Y;
  uint64_t       value1MaskedX;
  uint64_t       value1MaskedY;
  uint64_t       valueFinalX;
  uint64_t       valueFinalY;
  uint64_t       bitFlipMaskX;
  uint64_t       bitFlipMaskY;
  int            i;

  newPositionX = parentState0->PositionX;
  bitFlipMaskX = 1;

  for (i = crossOverMaskCnt - 1; i >= crossOverMaskCnt / 2; i--) {
    if (crossOverMask[i] == 1) {
      value0X = *((uint64_t*)&newPositionX);
      value1X = *((uint64_t*)&parentState1->PositionX);

      value0MaskedX = value0X & ~bitFlipMaskX;
      value1MaskedX = value1X & bitFlipMaskX;

      valueFinalX = value0MaskedX | value1MaskedX;

      newPositionX = *((double*)&valueFinalX);
    }

    bitFlipMaskX <<= 1;
  }

  newPositionY = parentState0->PositionY;
  bitFlipMaskY = 1;

  for (i = crossOverMaskCnt / 2 - 1; i >= 0; i--) {
    if (crossOverMask[i] == 1) {
      value0Y = *((uint64_t*)&newPositionY);
      value1Y = *((uint64_t*)&parentState1->PositionY);

      value0MaskedY = value0Y & ~bitFlipMaskY;
      value1MaskedY = value1Y & bitFlipMaskY;

      valueFinalY = value0MaskedY | value1MaskedY;

      newPositionY = *((double*)&valueFinalY);
    }

    bitFlipMaskY <<= 1;
  }

  if (newPositionX < problemParams->IntervalStartX) {
    newPositionX = problemParams->IntervalStartX;
  } else if (newPositionX > problemParams->IntervalEndX) {
    newPositionX = problemParams->IntervalEndX;
  }

  if (newPositionY < problemParams->IntervalStartY) {
    newPositionY = problemParams->IntervalStartY;
  } else if (newPositionY > problemParams->IntervalEndY) {
    newPositionY = problemParams->IntervalEndY;
  }

  problemState = malloc(sizeof(ProblemState));

  problemState->PositionX = newPositionX;
  problemState->PositionY = newPositionY;
  problemState->Cost = _ProblemFunction(problemState->PositionX,problemState->PositionY);

  return problemState;
}

ProblemState*
ProblemStateFirst(
  const ProblemParams* problemParams)
{
  assert(ProblemParamsIsValid(problemParams));

  ProblemState*  problemState;

  problemState = malloc(sizeof(ProblemState));

  problemState->PositionX = problemParams->IntervalStartX;
  problemState->PositionY = problemParams->IntervalStartY;
  problemState->Cost = _ProblemFunction(problemState->PositionX,problemState->PositionY);

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

  problemState->PositionX = previousState->PositionX + problemParams->IntervalStep;
  problemState->PositionY = previousState->PositionY;

  if (problemState->PositionX > problemParams->IntervalEndX) {
    problemState->PositionX = problemParams->IntervalStartX;
    problemState->PositionY = previousState->PositionY + problemParams->IntervalStep;

    if (problemState->PositionY > problemParams->IntervalEndY) {
      free(problemState);
      return NULL;
    }
  }

  problemState->Cost = _ProblemFunction(problemState->PositionX,problemState->PositionY);

  return problemState;
}

void
ProblemStateFree(
  const ProblemParams* problemParams,
  ProblemState** problemState)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(problemState != NULL && ProblemStateIsValid(problemParams,*problemState));

  (*problemState)->PositionX = 0.0;
  (*problemState)->PositionY = 0.0;
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

  printf("%s%s[RealFunction2DState]:\n",indent,name);
  printf("%s  Position: (%f,%f)\n",indent,problemState->PositionX,problemState->PositionY);
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

  if (problemState->PositionX < problemParams->IntervalStartX ||
      problemState->PositionX > problemParams->IntervalEndX) {
    return 0;
  }

  if (problemState->PositionY < problemParams->IntervalStartY ||
      problemState->PositionY > problemParams->IntervalEndY) {
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

  return sizeof(problemState->PositionX) * 8 + sizeof(problemState->PositionY) * 8;
}
