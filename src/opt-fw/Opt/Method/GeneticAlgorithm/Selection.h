#ifndef _SELECTION_H
#define _SELECTION_H

#include <stdio.h>

#include "Problem.h"

struct SelectionParams;
typedef struct SelectionParams SelectionParams;

SelectionParams*  SelectionParamsAlloc(
                    FILE* fin,
                    const char* name);
void              SelectionParamsFree(
                    SelectionParams** selectionParams);
void              SelectionParamsPrint(
                    const SelectionParams* selectionParams,
                    const char* name,
                    int indentLevel);
int               SelectionParamsIsValid(
                    const SelectionParams* selectionParams);

void              GenerateSelectedStates(
		    const SelectionParams* selectionParams,
		    const ProblemParams* problemParams,
                    int selectedStatesCnt,
                    const ProblemState** selectedStates,
                    int previousStatesCnt,
                    ProblemState** previousStates);

#endif
