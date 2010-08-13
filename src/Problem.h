#ifndef _PROBLEM_H
#define _PROBLEM_H

#include <stdio.h>

struct ProblemParams;
typedef struct ProblemParams ProblemParams;

ProblemParams*  ProblemParamsAlloc(
                  FILE* fin);
void            ProblemParamsFree(
                  ProblemParams** problemParams);
void            ProblemParamsPrint(
		  const ProblemParams* problemParams, int indentLevel);
int             ProblemParamsIsValid(
		  const ProblemParams* problemParams);

struct ProblemState;
typedef struct ProblemState ProblemState;

ProblemState*   ProblemStateAlloc(
                  const ProblemParams* problemParams);
ProblemState*   ProblemStateCopy(
                  const ProblemState* sourceState);
ProblemState*   ProblemStateGenNext(
                  const ProblemState* previousState,
                  const ProblemParams* problemParams);
ProblemState*   ProblemStateCrossOver(
                  const ProblemState* parentState0,
                  const ProblemState* parentState1,
                  const ProblemParams* problemParams,
                  int crossOverMaskCnt,
                  const int* crossOverMask);
void            ProblemStateFree(
                  ProblemState** problemState);
void            ProblemStatePrint(
                  const ProblemState* problemState,
                  int indentLevel);
int             ProblemStateIsValid(
                  const ProblemState* problemState);
int             ProblemStateCompare(
                  const ProblemState** problemState0,
                  const ProblemState** problemState1);
double          ProblemStateCost(
                  const ProblemState* problemState);
int             ProblemStateGenomeSize(
                  const ProblemState* problemState);

#endif
