#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>

#include "Selection.h"

struct SelectionParams
{
    int    TournamentSize;
    char*  Name;
};

SelectionParams*
SelectionParamsAlloc()
{
    SelectionParams*  selectionParams;

    selectionParams = malloc(sizeof(SelectionParams));

    selectionParams->TournamentSize = 2;
    selectionParams->Name = strdup("TournamentSelection");

    return selectionParams;
}

void
SelectionParamsFree(
  SelectionParams** selectionParams)
{
    assert(selectionParams != NULL);
    assert(SelectionParamsIsValid(*selectionParams));

    (*selectionParams)->TournamentSize = 0;
    free((*selectionParams)->Name);
    (*selectionParams)->Name = NULL;

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

    printf("%sRandomSelection Params:\n",indent);
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

    if (selectionParams->Name == NULL) {
        return 0;
    }

    if (strlen(selectionParams->Name) == 0) {
        return 0;
    }

    return 1;
}

const char*
SelectionParamsName(
  const SelectionParams* selectionParams)
{
    assert(SelectionParamsIsValid(selectionParams));

    return selectionParams->Name;
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

    const ProblemState*  tournamentBest;
    double               tournamentBestCost;
    int                  tournamentIndex;
    int                  i;
    int                  j;

    for (i = 0; i < previousStatesCnt; i++) {
        assert(ProblemStateIsValid(previousStates[i]));
    }

    for (i = 0; i < selectedStatesCnt; i++) {
        tournamentBest = NULL;
        tournamentBestCost = DBL_MAX;

        for (j = 0; j < selectionParams->TournamentSize; j++) {
            tournamentIndex = rand () % previousStatesCnt;

            if (ProblemStateCost(previousStates[tournamentIndex]) < tournamentBestCost) {
                tournamentBest = previousStates[tournamentIndex];
                tournamentBestCost = ProblemStateCost(previousStates[tournamentIndex]);
            }
        }

        selectedStates[i] = tournamentBest;
    }
}
