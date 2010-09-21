#ifndef _PROBLEM_H
#define _PROBLEM_H

#include <stdio.h>

struct ProblemParams;
typedef struct ProblemParams ProblemParams;

ProblemParams*  ProblemParamsAlloc(
		  FILE* fin,
		  const char* name);
void            ProblemParamsFree(
                  ProblemParams** problemParams);
void            ProblemParamsPrint(
                  const ProblemParams* problemParams,
		  const char* name,
                  int indentLevel);
int             ProblemParamsIsValid(
                  const ProblemParams* problemParams);

struct ProblemState;
typedef struct ProblemState ProblemState;

ProblemState*   ProblemStateAlloc(
                  const ProblemParams* problemParams);
ProblemState*   ProblemStateCopy(
                  const ProblemParams* problemParams,
                  const ProblemState* sourceState);
ProblemState*   ProblemStateGenNext(
                  const ProblemParams* problemParams,
                  const ProblemState* previousState);
ProblemState*   ProblemStateCrossOver(
                  const ProblemParams* problemParams,
                  const ProblemState* parentState0,
                  const ProblemState* parentState1,
                  int crossOverMaskCnt,
                  const int* crossOverMask);
ProblemState*   ProblemStateFirst(
                  const ProblemParams* problemParams);
ProblemState*   ProblemStateWalk(
                  const ProblemParams* problemParams,
                  const ProblemState* previousState);
void            ProblemStateFree(
                  const ProblemParams* problemParams,
                  ProblemState** problemState);
void            ProblemStatePrint(
                  const ProblemParams* problemParams,
                  const ProblemState* problemState,
		  const char* name,
                  int indentLevel);
int             ProblemStateIsValid(
                  const ProblemParams* problemParams,
                  const ProblemState* problemState);
int             ProblemStateCompare(
                  const ProblemParams* problemParams,
                  const ProblemState* problemState0,
                  const ProblemState* problemState1);
double          ProblemStateCost(
                  const ProblemParams* problemParams,
                  const ProblemState* problemState);
int             ProblemStateGenomeSize(
                  const ProblemParams* problemParams,
                  const ProblemState* problemState);

#endif
