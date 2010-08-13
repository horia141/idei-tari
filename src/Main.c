#include <stdlib.h>

#include "Problem.h"
#include "Method.h"

int
main()
{
  MethodParams*   methodParams;
  ProblemParams*  problemParams;
  MethodState*    currMethodState;
  ProblemState*   currBest;
  MethodState*    nextMethodState;
  ProblemState*   nextBest;
  int             i;

  methodParams = MethodParamsAlloc(stdin);
  problemParams = ProblemParamsAlloc(stdin);
  currMethodState = MethodStateAlloc(methodParams,problemParams);
  currBest = MethodStateGetBest(currMethodState,NULL);

  MethodParamsPrint(methodParams,0);
  ProblemParamsPrint(problemParams,0);
  MethodStatePrint(currMethodState,0);
  ProblemStatePrint(currBest,0);

  for (i = 0; i < 4; i++) {
    nextMethodState = MethodStateGenNext(currMethodState,methodParams,problemParams,i + 1);
    nextBest = MethodStateGetBest(nextMethodState,currBest);

    MethodStatePrint(nextMethodState,0);
    ProblemStatePrint(nextBest,0);

    MethodStateFree(&currMethodState);
    ProblemStateFree(&currBest);

    currMethodState = nextMethodState;
    currBest = nextBest;
  }

  MethodParamsFree(&methodParams);
  ProblemParamsFree(&problemParams);
  MethodStateFree(&currMethodState);
  ProblemStateFree(&currBest);

  return 0;
}
