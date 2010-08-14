#ifndef _METHOD_H
#define _METHOD_H

#include <stdio.h>

#include "Problem.h"

struct MethodParams;
typedef struct MethodParams MethodParams;

MethodParams*  MethodParamsAlloc(
                 FILE* fin);
void           MethodParamsFree(
                 MethodParams** methodParams);
void           MethodParamsPrint(
                 const MethodParams* methodParams,
                 int indentLevel);
int            MethodParamsIsValid(
                 const MethodParams* methodParams);

struct MethodState;
typedef struct MethodState MethodState;

MethodState*   MethodStateAlloc(
                 const MethodParams* methodParams,
                 const ProblemParams* problemParams);
MethodState*   MethodStateGenNext(
                 const MethodState* previousState,
                 const MethodParams* methodParams,
                 const ProblemParams* problemParams,
                 int iteration);
void           MethodStateFree(
                 MethodState** methodState);
void           MethodStatePrint(
                 const MethodState* methodState,
                 int indentLevel);
int            MethodStateIsValid(
                 const MethodState* methodState);
ProblemState*  MethodStateGetBest(
                 const MethodState* methodState,
                 const ProblemState* currBest);

#endif
