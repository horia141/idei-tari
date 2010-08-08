#ifndef _PROBLEM_VECTOR_H
#define _PROBLEM_VECTOR_H

#include "Problem.h"

struct ProblemVector;
typedef struct ProblemVector ProblemVector;

ProblemVector*       ProblemVectorAlloc(int problemStatesCnt, const ProblemParams* problemParams);
ProblemVector*       ProblemVectorCopy(const ProblemVector* sourceVector);
ProblemVector*       ProblemVectorGenNext(int problemStatesCnt, const ProblemState* problemState, const ProblemParams* problemParams);
void                 ProblemVectorFree(ProblemVector** problemVector);
void                 ProblemVectorPrint(const ProblemVector* problemVector, int indentLevel);
int                  ProblemVectorIsValid(const ProblemVector* problemVector);
int                  ProblemVectorCnt(const ProblemVector* problemVector);
const ProblemState*  ProblemVectorSelectBest(const ProblemVector* problemVector);
const ProblemState*  ProblemVectorGet(const ProblemVector* problemVector, int index);
void                 ProblemVectorSet(ProblemVector* problemVector, int index, const ProblemState* problemState);
ProblemState**       ProblemVectorTempView(const ProblemVector* problemVector);

#endif
