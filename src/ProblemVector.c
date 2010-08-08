#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>

#include "ProblemVector.h"

struct ProblemVector
{
  int             ProblemStatesCnt;
  ProblemState**  ProblemStates;
};

ProblemVector*
ProblemVectorAlloc(int problemStatesCnt, const ProblemParams* problemParams)
{
  assert(problemStatesCnt > 0);
  assert(ProblemParamsIsValid(problemParams));

  ProblemVector*  problemVector;
  int             i;

  problemVector = malloc(sizeof(ProblemVector));

  problemVector->ProblemStatesCnt = problemStatesCnt;
  problemVector->ProblemStates = malloc(sizeof(ProblemState*) * problemVector->ProblemStatesCnt);

  for (i = 0; i < problemVector->ProblemStatesCnt; i++) {
    problemVector->ProblemStates[i] = ProblemStateAlloc(problemParams);
  }

  return problemVector;
}

ProblemVector*
ProblemVectorCopy(const ProblemVector* sourceVector)
{
  assert(ProblemVectorIsValid(sourceVector));

  ProblemVector*  problemVector;
  int             i;

  problemVector = malloc(sizeof(ProblemVector));

  problemVector->ProblemStatesCnt = sourceVector->ProblemStatesCnt;
  problemVector->ProblemStates = malloc(sizeof(ProblemState*) * problemVector->ProblemStatesCnt);

  for (i = 0; i < problemVector->ProblemStatesCnt; i++) {
    problemVector->ProblemStates[i] = ProblemStateCopy(sourceVector->ProblemStates[i]);
  }

  return problemVector;
}

ProblemVector*
ProblemVectorGenNext(int problemStatesCnt, const ProblemState* problemState, const ProblemParams* problemParams)
{
  assert(problemStatesCnt > 0);
  assert(ProblemStateIsValid(problemState));
  assert(ProblemParamsIsValid(problemParams));

  ProblemVector*  problemVector;
  int             i;

  problemVector = malloc(sizeof(ProblemVector));

  problemVector->ProblemStatesCnt = problemStatesCnt;
  problemVector->ProblemStates = malloc(sizeof(ProblemState*) * problemVector->ProblemStatesCnt);

  for (i = 0; i < problemVector->ProblemStatesCnt; i++) {
    problemVector->ProblemStates[i] = ProblemStateGenNext(problemState,problemParams);
  }

  return problemVector;
}

void
ProblemVectorFree(ProblemVector** problemVector)
{
  assert(problemVector != NULL);
  assert(ProblemVectorIsValid(*problemVector));

  int  i;

  for (i = 0; i < (*problemVector)->ProblemStatesCnt; i++) {
    ProblemStateFree(&((*problemVector)->ProblemStates[i]));
  }

  free((*problemVector)->ProblemStates);

  (*problemVector)->ProblemStatesCnt = 0;
  (*problemVector)->ProblemStates = NULL;

  free(*problemVector);
  *problemVector = NULL;
}

void
ProblemVectorPrint(const ProblemVector* problemVector, int indentLevel)
{
  assert(ProblemVectorIsValid(problemVector));
  assert(indentLevel >= 0);

  char*  indent;
  int    i;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sProblemVector:\n",indent);
  printf("%s  ProblemStatesCnt: %d\n",indent,problemVector->ProblemStatesCnt);
  printf("%s  ProblemStates:\n",indent);

  for (i = 0; i < problemVector->ProblemStatesCnt; i++) {
    ProblemStatePrint(problemVector->ProblemStates[i],indentLevel + 2);
  }

  free(indent);
}

int
ProblemVectorIsValid(const ProblemVector* problemVector)
{
  int  i;

  if (problemVector == NULL) {
    return 0;
  }

  if (problemVector->ProblemStatesCnt < 1) {
    return 0;
  }

  if (problemVector->ProblemStates == NULL) {
    return 0;
  }

  for (i = 0; i < problemVector->ProblemStatesCnt; i++) {
    if (!ProblemStateIsValid(problemVector->ProblemStates[i])) {
      return 0;
    }
  }

  return 1;
}

int
ProblemVectorCnt(const ProblemVector* problemVector)
{
  assert(ProblemVectorIsValid(problemVector));

  return problemVector->ProblemStatesCnt;
}

const ProblemState*
ProblemVectorSelectBest(const ProblemVector* problemVector)
{
  assert(ProblemVectorIsValid(problemVector));

  const ProblemState*  best;
  double               bestCost;
  int                  i;

  best = NULL;
  bestCost = DBL_MAX;

  for (i = 0; i < problemVector->ProblemStatesCnt; i++) {
    if (ProblemStateCost(problemVector->ProblemStates[i]) < bestCost) {
      best = problemVector->ProblemStates[i];
      bestCost = ProblemStateCost(problemVector->ProblemStates[i]);
    }
  }

  assert(best != NULL);

  return best;
}

const ProblemState*
ProblemVectorGet(const ProblemVector* problemVector, int index)
{
  assert(ProblemVectorIsValid(problemVector));
  assert(index >= 0 && index < ProblemVectorCnt(problemVector));

  return problemVector->ProblemStates[index];
}

void
ProblemVectorSet(ProblemVector* problemVector, int index, const ProblemState* problemState)
{
  assert(ProblemVectorIsValid(problemVector));
  assert(index >= 0 && index < ProblemVectorCnt(problemVector));
  assert(ProblemStateIsValid(problemState));

  ProblemStateFree(&(problemVector->ProblemStates[index]));
  problemVector->ProblemStates[index] = ProblemStateCopy(problemState);
}

ProblemState**
ProblemVectorTempView(const ProblemVector* problemVector)
{
  assert(ProblemVectorIsValid(problemVector));

  return problemVector->ProblemStates;
}
