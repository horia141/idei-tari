#ifndef _SELECTION_H
#define _SELECTION_H

struct SelectionParams;
typedef struct SelectionParams SelectionParams;

SelectionParams*  SelectionParamsAlloc();
void              SelectionParamsFree(SelectionParams** selectionParams);
void              SelectionParamsPrint(const SelectionParams* selectionParams);
int               SelectionParamsIsValid(const SelectionParams* selectionParams);
const char*       SelectionParamsName(const SelectionParams* selectionParams);

void              GenerateSelectedStates(int selectedStatesInt, const ProblemState** selectedStates, const SelectionParams* selectionParams);

#endif

#ifndef _CROSSOVER_H
#define _CROSSOVER_H

struct CrossOverParams;
typedef struct CrossOverParams CrosOverParams;

CrossOverParams*  CrossOverParamsAlloc();
void              CrossOverParamsFree(CrossOverParams** crossOverParams);
void              CrossOverParamsPrint(const CrossOverParams* crossOverParams);
int               CrossOverParamsIsValid(const CrossOverParams* crossOverParams);
const char*       CrossOverParamsName(const CrossOverParams* crossOverParams);

void              GenerateCrossOverMask(int crossOverMaskCnt, int* crossOverMask, const CrossOverParams* crossOverParams);

#endif
