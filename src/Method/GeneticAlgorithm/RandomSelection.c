#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "Selection.h"

struct SelectionParams
{
};

SelectionParams*
SelectionParamsAlloc(
  FILE* fin)
{
  SelectionParams*  selectionParams;

  selectionParams = malloc(sizeof(SelectionParams));

  fscanf(fin," RandomSelectionParams :");

  return selectionParams;
}

void
SelectionParamsFree(
  SelectionParams** selectionParams)
{
  assert(selectionParams != NULL);
  assert(SelectionParamsIsValid(*selectionParams));

  free(*selectionParams);
  *selectionParams = NULL;
}

void
SelectionParamsPrint(
  const SelectionParams* selectionParams,
  int indentLevel)
{
  assert(SelectionParamsIsValid(selectionParams));
  assert(indentLevel >= 0);

  char*  indent;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sRandomSelectionParams:\n",indent);

  free(indent);
}

int
SelectionParamsIsValid(
  const SelectionParams* selectionParams)
{
  if (selectionParams == NULL) {
    return 0;
  }

  return 1;
}


void
GenerateSelectedStates(
  int selectedStatesCnt,
  const ProblemState** selectedStates,
  int previousStatesCnt,
  ProblemState** previousStates,
  const SelectionParams* selectionParams)
{
  assert(selectedStatesCnt > 0);
  assert(selectedStates != NULL);
  assert(previousStatesCnt > 0);
  assert(previousStates != NULL);
  assert(SelectionParamsIsValid(selectionParams));
  assert(selectedStatesCnt == previousStatesCnt);

  int  selectIndex;
  int  i;

  for (i = 0; i < previousStatesCnt; i++) {
    assert(ProblemStateIsValid(previousStates[i]));
  }

  for (i = 0; i < selectedStatesCnt; i++) {
    selectIndex = rand() % previousStatesCnt;
    selectedStates[i] = previousStates[selectIndex];
  }
}
