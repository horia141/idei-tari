#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "Selection.h"

struct SelectionParams
{
  char*  Name;
};

SelectionParams*
SelectionParamsAlloc()
{
  SelectionParams*  selectionParams;

  selectionParams = malloc(sizeof(SelectionParams));

  selectionParams->Name = strdup("FitnessProportionateSelection");

  return selectionParams;
}

void
SelectionParamsFree(SelectionParams** selectionParams)
{
  assert(selectionParams != NULL);
  assert(SelectionParamsIsValid(*selectionParams));

  free((*selectionParams)->Name);
  (*selectionParams)->Name = NULL;

  free(*selectionParams);
  *selectionParams = NULL;
}

void
SelectionParamsPrint(const SelectionParams* selectionParams, int indentLevel)
{
  assert(SelectionParamsIsValid(selectionParams));
  assert(indentLevel >= 0);

  char*  indent;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sFitnessProportionateSelection Params:\n",indent);

  free(indent);
}

int
SelectionParamsIsValid(const SelectionParams* selectionParams)
{
  if (selectionParams == NULL) {
    return 0;
  }

  if (selectionParams->Name == NULL) {
    return 0;
  }

  if (strlen(selectionParams->Name) == 0) {
    return 0;
  }

  return 1;
}

const char*
SelectionParamsName(const SelectionParams* selectionParams)
{
  assert(SelectionParamsIsValid(selectionParams));

  return selectionParams->Name;
}


void
GenerateSelectedStates(int selectedStatesCnt, const ProblemState** selectedStates, int previousStatesCnt,  ProblemState** previousStates, const SelectionParams* selectionParams)
{
  assert(selectedStatesCnt > 0);
  assert(selectedStates != NULL);
  assert(previousStatesCnt > 0);
  assert(previousStates != NULL);
  assert(SelectionParamsIsValid(selectionParams));
  assert(selectedStatesCnt == previousStatesCnt);

  double  totalCost;
  double  selectCost;
  double  selectCheckCost;
  int     selectIndex;
  int     i;
  int     j;

  for (i = 0; i < previousStatesCnt; i++) {
    assert(ProblemStateIsValid(previousStates[i]));
  }

  totalCost = 0.0;

  for (i = 0; i < previousStatesCnt; i++) {
    totalCost += ProblemStateCost(previousStates[i]);
  }

  for (i = 0; i < selectedStatesCnt; i++) {
    selectCost = ((double)rand() / RAND_MAX) * totalCost;
    selectCheckCost = 0.0;
    selectIndex = previousStatesCnt - 1;

    for (j = 0; j < previousStatesCnt; j++) {
      if (selectCheckCost > selectCost) {
	selectIndex = j - 1;
	break;
      } else {
	selectCheckCost += ProblemStateCost(previousStates[j]);
      }
    }

    selectedStates[i] = previousStates[selectIndex];
  }
}
