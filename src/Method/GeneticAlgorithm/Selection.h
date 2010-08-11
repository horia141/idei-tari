#ifndef _SELECTION_H
#define _SELECTION_H

#include "Problem.h"

struct SelectionParams;
typedef struct SelectionParams SelectionParams;

SelectionParams*  SelectionParamsAlloc();
void              SelectionParamsFree(
                    SelectionParams** selectionParams);
void              SelectionParamsPrint(
                    const SelectionParams* selectionParams,
                    int indentLevel);
int               SelectionParamsIsValid(
                    const SelectionParams* selectionParams);
const char*       SelectionParamsName(
                    const SelectionParams* selectionParams);

void              GenerateSelectedStates(
                    int selectedStatesCnt,
                    const ProblemState** selectedStates,
                    int previousStatesCnt,
                    ProblemState** previousStates,
                    const SelectionParams* selectionParams);

#endif
