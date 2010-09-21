#ifndef _METHOD_H
#define _METHOD_H

#include <stdio.h>

#include "Problem.h"

struct MethodParams;
typedef struct MethodParams MethodParams;

MethodParams*         MethodParamsAlloc(
                        FILE* fin);
void                  MethodParamsFree(
                        MethodParams** methodParams);
void                  MethodParamsPrint(
                        const MethodParams* methodParams,
                        int indentLevel);
int                   MethodParamsIsValid(
                        const MethodParams* methodParams);
const ProblemParams*  MethodParamsProblemParams(
		        const MethodParams* methodParams);

struct MethodState;
typedef struct MethodState MethodState;

MethodState*          MethodStateAlloc(
                        const MethodParams* methodParams);
MethodState*          MethodStateGenNext(
                        const MethodParams* methodParams,
                        const MethodState* previousState);
void                  MethodStateFree(
                        const MethodParams* methodParams,
                        MethodState** methodState);
void                  MethodStatePrint(
                        const MethodParams* methodParams,
                        const MethodState* methodState,
                        int indentLevel);
int                   MethodStateIsValid(
                        const MethodParams* methodParams,
                        const MethodState* methodState);
ProblemState*         MethodStateGetBest(
                        const MethodParams* methodParams,
                        const MethodState* methodState,
                        const ProblemState* currBest);

#endif
