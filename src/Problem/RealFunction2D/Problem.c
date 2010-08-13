#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#include "Problem.h"

struct ProblemParams
{
    double  IntervalStartX;
    double  IntervalStartY;
    double  IntervalEndX;
    double  IntervalEndY;
};

static double  _ProblemFunction(
                 double x, 
                 double y);

ProblemParams*
ProblemParamsAlloc(
  FILE* fin)
{
    ProblemParams*  problemParams;

    problemParams = malloc(sizeof(ProblemParams));

    fscanf(fin," RealFunction2DParams :");
    fscanf(fin," IntervalStartX : %lf",&problemParams->IntervalStartX);
    fscanf(fin," IntervalStartY : %lf",&problemParams->IntervalStartY);
    fscanf(fin," IntervalEndX : %lf",&problemParams->IntervalEndX);
    fscanf(fin," IntervalEndY : %lf",&problemParams->IntervalEndY);

    return problemParams;
}

void
ProblemParamsFree(
  ProblemParams** problemParams)
{
    assert(problemParams != NULL);
    assert(ProblemParamsIsValid(*problemParams));

    (*problemParams)->IntervalStartX = 0.0;
    (*problemParams)->IntervalStartY = 0.0;
    (*problemParams)->IntervalEndX = 0.0;
    (*problemParams)->IntervalEndY = 0.0;

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

    printf("%sRealFunction2D Params\n",indent);
    printf("%s  IntervalStart: (%f,%f)\n",indent,problemParams->IntervalStartX,problemParams->IntervalStartY);
    printf("%s  IntervalEnd: (%f,%f)\n",indent,problemParams->IntervalEndX,problemParams->IntervalEndY);

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

    return 1;
}

static double
_ProblemFunction(
  double x,
  double y)
{
    return x * x + y * y;
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
  const ProblemState* sourceState)
{
    assert(ProblemStateIsValid(sourceState));

    ProblemState*  problemState;

    problemState = malloc(sizeof(ProblemState));

    problemState->PositionX = sourceState->PositionX;
    problemState->PositionY = sourceState->PositionY;
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

void
ProblemStateFree(
  ProblemState** problemState)
{
    assert(problemState != NULL);
    assert(ProblemStateIsValid(*problemState));

    (*problemState)->PositionX = 0.0;
    (*problemState)->PositionY = 0.0;
    (*problemState)->Cost = 0.0;

    free(*problemState);
    *problemState = NULL;
}

void
ProblemStatePrint(
  const ProblemState* problemState,
  int indentLevel)
{
    assert(ProblemStateIsValid(problemState));
    assert(indentLevel >= 0);

    char*  indent;

    indent = malloc(sizeof(char) * (2 * indentLevel + 1));

    memset(indent,' ',2 * indentLevel);
    indent[2 * indentLevel] = '\0';

    printf("%sRealFunction2D State:\n",indent);
    printf("%s  Position: (%f,%f)\n",indent,problemState->PositionX,problemState->PositionY);
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

    return sizeof(problemState->PositionX) * 8 + sizeof(problemState->PositionY) * 8;
}
