#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>

#include "Selection.h"

struct SelectionParams
{
  int    TournamentSize;
};

SelectionParams*
SelectionParamsAlloc(
  FILE* fin)
{
  SelectionParams*  selectionParams;

  selectionParams = malloc(sizeof(SelectionParams));

  fscanf(fin," TournamentSelectionParams :");
  fscanf(fin," TournamentSize : %d",&selectionParams->TournamentSize);

  return selectionParams;
}

void
SelectionParamsFree(
  SelectionParams** selectionParams)
{
  assert(selectionParams != NULL);
  assert(SelectionParamsIsValid(*selectionParams));

  (*selectionParams)->TournamentSize = 0;

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

  printf("%sTournamentSelectionParams:\n",indent);
  printf("%s  TournamentSize: %d\n",indent,selectionParams->TournamentSize);

  free(indent);
}

int
SelectionParamsIsValid(
  const SelectionParams* selectionParams)
{
  if (selectionParams == NULL) {
    return 0;
  }

  if (selectionParams->TournamentSize < 1) {
    return 0;
  }

  return 1;
}


void
GenerateSelectedStates(
  const SelectionParams* selectionParams,
  const ProblemParams* problemParams,
  int selectedStatesCnt,
  const ProblemState** selectedStates,
  int previousStatesCnt,
  ProblemState** previousStates)
{
  assert(SelectionParamsIsValid(selectionParams));
  assert(ProblemParamsIsValid(problemParams));
  assert(selectedStatesCnt > 0);
  assert(selectedStates != NULL);
  assert(previousStatesCnt > 0);
  assert(previousStates != NULL);
  assert(selectedStatesCnt == previousStatesCnt);

  const ProblemState*  tournamentBest;
  double               tournamentBestCost;
  int                  tournamentIndex;
  int                  i;
  int                  j;

  for (i = 0; i < previousStatesCnt; i++) {
    assert(ProblemStateIsValid(problemParams,previousStates[i]));
  }

  for (i = 0; i < selectedStatesCnt; i++) {
    tournamentBest = NULL;
    tournamentBestCost = DBL_MAX;

    for (j = 0; j < selectionParams->TournamentSize; j++) {
      tournamentIndex = rand () % previousStatesCnt;

      if (ProblemStateCost(problemParams,previousStates[tournamentIndex]) < tournamentBestCost) {
	tournamentBest = previousStates[tournamentIndex];
	tournamentBestCost = ProblemStateCost(problemParams,previousStates[tournamentIndex]);
      }
    }

    selectedStates[i] = tournamentBest;
  }
}
