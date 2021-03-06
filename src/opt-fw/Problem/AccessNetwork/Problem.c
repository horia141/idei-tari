#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>
#include <limits.h>
#include <math.h>

#include "Problem.h"

struct Speed;
struct Node;
struct User;

typedef struct Speed Speed;
typedef struct Node Node;
typedef struct User User;

struct Speed
{
  double  Download;
  double  Upload;
};

struct Node
{
  char*   Name;
  double  Cost;
  int     DownPortsNr;
  Speed   DownPort;
  int     UpPortsNr;
  Speed   UpPort;
};

struct User
{
  char*  Name;
  Speed  Speed;
};

struct ProblemParams
{
  char*  Name;
  int    NodesCnt;
  Node*  Nodes;
  int    UsersCnt;
  User*  Users;
  int    MaxNetworkLevels;
  int    MaxNetworkNodes;
};

static double  _debug_log(
		 double x);
static double  _debug_pow(
                 double x,
		 double y);
static double _debug_ceil(
		 double x);

ProblemParams*
ProblemParamsAlloc(
  FILE* fin,
  const char* name)
{
  ProblemParams*  problemParams;
  int             minDownPortsNr;
  int             maxUpPortsNr;
  double          a;
  double          r;
  int             i;
    
  problemParams = malloc(sizeof(ProblemParams));

  fscanf(fin," %*s AccessNetworkParams :");
  fscanf(fin," Name : %as",&problemParams->Name);
  fscanf(fin," NodesCnt : %d",&problemParams->NodesCnt);
  fscanf(fin," Nodes :");
  problemParams->Nodes = malloc(sizeof(Node) * problemParams->NodesCnt);

  for (i = 0; i < problemParams->NodesCnt; i++) {
    fscanf(fin," Node :");
    fscanf(fin," Name : %as",&problemParams->Nodes[i].Name);
    fscanf(fin," Cost : %lf",&problemParams->Nodes[i].Cost);
    fscanf(fin," DownPortsNr : %d",&problemParams->Nodes[i].DownPortsNr);
    fscanf(fin," DownPort : %lf %lf",&problemParams->Nodes[i].DownPort.Download,&problemParams->Nodes[i].DownPort.Upload);
    fscanf(fin," UpPortsNr : %d",&problemParams->Nodes[i].UpPortsNr);
    fscanf(fin," UpPort : %lf %lf",&problemParams->Nodes[i].UpPort.Download,&problemParams->Nodes[i].UpPort.Upload);
  }

  fscanf(fin," UsersCnt : %d",&problemParams->UsersCnt);
  fscanf(fin," Users:");
  problemParams->Users = malloc(sizeof(User) * problemParams->UsersCnt);

  for (i = 0; i < problemParams->UsersCnt; i++) {
    fscanf(fin," User :");
    fscanf(fin," Name : %as",&problemParams->Users[i].Name);
    fscanf(fin," Speed : %lf %lf",&problemParams->Users[i].Speed.Download,&problemParams->Users[i].Speed.Upload);
  }

  minDownPortsNr = INT_MAX;
  maxUpPortsNr = INT_MIN;

  for (i = 0; i < problemParams->NodesCnt; i++) {
    if (problemParams->Nodes[i].DownPortsNr < minDownPortsNr) {
      minDownPortsNr = problemParams->Nodes[i].DownPortsNr;
    }

    if (problemParams->Nodes[i].UpPortsNr > maxUpPortsNr) {
      maxUpPortsNr = problemParams->Nodes[i].UpPortsNr;
    }
  }

  if (minDownPortsNr == maxUpPortsNr) {
    maxUpPortsNr -= 1;
  }

  a = (double)problemParams->UsersCnt / (double)minDownPortsNr;
  r = (double)maxUpPortsNr / (double)minDownPortsNr;

  /* We compute MaxNetworkLevels and MaxNetworkNodes according to the rules
     in the presentation, taking into account how the number of nodes
     per level decreased as we reach "root". The formula for MaxNeworkLevel is
     extracted from the condition that the number of nodes in the last layer
     is one (there is a small error, we assume a t is a t-1 in the computation,
     but it just yields one or two nodes which will never be used). The formula
     for MaxNetworkNodes is obtained from treating the sum of all the nodes
     on each level as a geometric series, and summing accordingly.
     Also, the "-1 *" in front of the formula for MaxNetworkLevels comes from
     the last "_debug_log(r)" call. It used to be "_debug_log(1/r)", but, taking
     advantage of the laws of the logarithm, I passed "-1" in front : we gain
     some precision with this. */

  problemParams->MaxNetworkLevels = (int)_debug_ceil(-1 * _debug_log(problemParams->UsersCnt) / _debug_log(r));
  problemParams->MaxNetworkNodes = (int)_debug_ceil(a * (1 - _debug_pow(r,problemParams->MaxNetworkLevels)) / (1 - r));

#ifdef HACK
  /* This is a massive HACK. We employ it here for ProblemStateWalk which,
     when generating larger solutions, causes _ProblemStateFix to acces
     it's portAllocationMatrix array out of bounds. This is because, with
     larger networks, all users are handled by the first nodes, while the
     last just form a linear structure. This structure is very long and
     tends to be larger than MaxNetworkLevels. */

  problemParams->MaxNetworkLevels *= 4;
#endif

  return problemParams;
}

void
ProblemParamsFree(
  ProblemParams** problemParams)
{
  assert(problemParams != NULL && ProblemParamsIsValid(*problemParams));

  int  i;

  for (i = 0; i < (*problemParams)->NodesCnt; i++) {
    free((*problemParams)->Nodes[i].Name);

    (*problemParams)->Nodes[i].Name = NULL;
    (*problemParams)->Nodes[i].Cost = 0.0f;
    (*problemParams)->Nodes[i].DownPortsNr = 0;
    (*problemParams)->Nodes[i].DownPort.Download = 0;
    (*problemParams)->Nodes[i].DownPort.Upload = 0;
    (*problemParams)->Nodes[i].UpPortsNr = 0;
    (*problemParams)->Nodes[i].UpPort.Download = 0;
    (*problemParams)->Nodes[i].UpPort.Upload = 0;
  }

  for (i = 0; i < (*problemParams)->UsersCnt; i++) {
    free((*problemParams)->Users[i].Name);

    (*problemParams)->Users[i].Name = NULL;
    (*problemParams)->Users[i].Speed.Download = 0;
    (*problemParams)->Users[i].Speed.Upload = 0;
  }

  free((*problemParams)->Name);
  free((*problemParams)->Nodes);
  free((*problemParams)->Users);

  (*problemParams)->Name = NULL;
  (*problemParams)->NodesCnt = 0;
  (*problemParams)->Nodes = NULL;
  (*problemParams)->UsersCnt = 0;
  (*problemParams)->Users = NULL;
  (*problemParams)->MaxNetworkLevels = 0;
  (*problemParams)->MaxNetworkNodes = 0;

  free(*problemParams);
  *problemParams = NULL;
}

void
ProblemParamsPrint(
  const ProblemParams* problemParams,
  const char* name,
  int indentLevel)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(indentLevel >= 0);

  char*  indent;
  int    i;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%s%s[AccessNetworkParams]:\n",indent,name);
  printf("%s  Name: %s\n",indent,problemParams->Name);
  printf("%s  NodesCnt: %d\n",indent,problemParams->NodesCnt);
  printf("%s  Nodes:\n",indent);
  
  for (i = 0; i < problemParams->NodesCnt; i++) {
    printf("%s    Node:\n",indent);
    printf("%s      Name: %s\n",indent,problemParams->Nodes[i].Name);
    printf("%s      Cost: %.3lf\n",indent,problemParams->Nodes[i].Cost);
    printf("%s      DownPortsNr: %d\n",indent,problemParams->Nodes[i].DownPortsNr);
    printf("%s      DownPort: %.3lf %.3lf\n",indent,problemParams->Nodes[i].DownPort.Download,problemParams->Nodes[i].DownPort.Upload);
    printf("%s      UpPortsNr: %d\n",indent,problemParams->Nodes[i].UpPortsNr);
    printf("%s      UpPort: %.3lf %.3lf\n",indent,problemParams->Nodes[i].UpPort.Download,problemParams->Nodes[i].UpPort.Upload);
  }

  printf("%s  UsersCnt: %d\n",indent,problemParams->UsersCnt);
  printf("%s  Users:\n",indent);

  for (i = 0; i < problemParams->UsersCnt; i++) {
    printf("%s    User:\n",indent);
    printf("%s      Name: %s\n",indent,problemParams->Users[i].Name);
    printf("%s      Speed: %.3lf %.3lf\n",indent,problemParams->Users[i].Speed.Download,problemParams->Users[i].Speed.Upload);
  }

  printf("%s  MaxNetworkLevels: %d\n",indent,problemParams->MaxNetworkLevels);
  printf("%s  MaxNetworkNodes: %d\n",indent,problemParams->MaxNetworkNodes);

  free(indent);
}

int
ProblemParamsIsValid(
  const ProblemParams* problemParams)
{
  int  i;

  if (problemParams == NULL) {
    return 0;
  }

  if (problemParams->Name == NULL) {
    return 0;
  }

  if (strlen(problemParams->Name) == 0) {
    return 0;
  }

  if (problemParams->NodesCnt < 1) {
    return 0;
  }

  if (problemParams->Nodes == NULL) {
    return 0;
  }

  for (i = 0; i < problemParams->NodesCnt; i++) {
    if (problemParams->Nodes[i].Name == NULL) {
      return 0;
    }

    if (strlen(problemParams->Nodes[i].Name) == 0) {
      return 0;
    }

    if (problemParams->Nodes[i].Cost <= 0.0) {
      return 0;
    }

    if (problemParams->Nodes[i].DownPortsNr < 1) {
      return 0;
    }

    if (problemParams->Nodes[i].DownPort.Download <= 0.0) {
      return 0;
    }

    if (problemParams->Nodes[i].DownPort.Upload <= 0.0) {
      return 0;
    }

    if (problemParams->Nodes[i].UpPortsNr < 1) {
      return 0;
    }

    if (problemParams->Nodes[i].UpPort.Download <= 0.0) {
      return 0;
    }

    if (problemParams->Nodes[i].UpPort.Upload <= 0.0) {
      return 0;
    }

    if (problemParams->Nodes[i].UpPortsNr >= problemParams->Nodes[i].DownPortsNr) {
      return 0;
    }
  }

  if (problemParams->UsersCnt < 1) {
    return 0;
  }

  if (problemParams->Users == NULL) {
    return 0;
  }

  for (i = 0; i < problemParams->UsersCnt; i++) {
    if (problemParams->Users[i].Name == NULL) {
      return 0;
    }

    if (strlen(problemParams->Users[i].Name) == 0) {
      return 0;
    }

    if (problemParams->Users[i].Speed.Download <= 0.0) {
      return 0;
    }

    if (problemParams->Users[i].Speed.Upload <= 0.0) {
      return 0;
    }
  }

  if (problemParams->MaxNetworkLevels <= 0) {
    return 0;
  }

  if (problemParams->MaxNetworkNodes <= 0) {
    return 0;
  }

  return 1;
}

static double
_debug_log(
  double x)
{
  return log(x);
}

static double
_debug_pow(
  double x,
  double y)
{
  return pow(x,y);
}

static double
_debug_ceil(
  double x)
{
  return ceil(x);
}

struct ProblemState
{
  int    NodeIdsUsedCnt;
  int    NodeIdsCnt;
  int*   NodeIds;
  float  Cost;
};

static void          _ProblemStateFix(
                       ProblemState* problemState,
                       const ProblemParams* problemParams);
static int           _ProblemStateFindFit(
                       const ProblemState* problemState,
		       const ProblemParams* problemParams,
		       int portAllocationMatrixCnt,
		       const Speed** portAllocationMatrix,
		       int currLevel,
		       int currLevelUser,
		       int currLevelUserCnt,
		       Speed* nodeSpeed);
static void          _ProblemStateEmpty(
   		       ProblemState* problemState,
		       const ProblemParams* problemParams);
static ProblemState* _ProblemStateWalkToValid(
		       ProblemState* problemState,
		       const ProblemParams* problemParams);
static double        _ProblemStateCalcCost(
		       ProblemState* problemState,
		       const ProblemParams* problemParams);

ProblemState*
ProblemStateAlloc(
  const ProblemParams* problemParams)
{
  assert(ProblemParamsIsValid(problemParams));

  ProblemState*  problemState;

  problemState = malloc(sizeof(ProblemState));

  _ProblemStateEmpty(problemState,problemParams);
  _ProblemStateFix(problemState,problemParams);

  return problemState;
}

ProblemState*
ProblemStateCopy(
  const ProblemParams* problemParams,
  const ProblemState* sourceState)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,sourceState));

  ProblemState*  problemState;
  int            i;
    
  problemState = malloc(sizeof(ProblemState));

  problemState->NodeIdsUsedCnt = sourceState->NodeIdsUsedCnt;
  problemState->NodeIdsCnt = sourceState->NodeIdsCnt;
  problemState->NodeIds = malloc(sizeof(int) * problemState->NodeIdsCnt);
  problemState->Cost = sourceState->Cost;

  for (i = 0; i < problemState->NodeIdsCnt; i++) {
    problemState->NodeIds[i] = sourceState->NodeIds[i];
  }

  return problemState;
}

ProblemState*
ProblemStateGenNext(
  const ProblemParams* problemParams,
  const ProblemState* previousState)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,previousState));

  ProblemState*  problemState;
  float          operation;
  int            index;
  int            oldType;
  int            changeNode;
  int            i;

  problemState = ProblemStateCopy(problemParams,previousState);

  operation = rand() / (float)RAND_MAX;
  index = rand() % problemState->NodeIdsUsedCnt;

  if (operation < 0.20 && problemState->NodeIdsUsedCnt < problemState->NodeIdsCnt) {
    for (i = problemState->NodeIdsUsedCnt; i > index; i--) {
      problemState->NodeIds[i] = problemState->NodeIds[i-1];
    }

    problemState->NodeIds[index] = rand() % problemParams->NodesCnt;
    problemState->NodeIdsUsedCnt += 1;
  } else if (operation < 0.40 && problemState->NodeIdsUsedCnt > 1) {
    oldType = problemState->NodeIds[index];

    for (i = index; i < problemState->NodeIdsUsedCnt - 1; i++) {
      problemState->NodeIds[i] = problemState->NodeIds[i+1];
    }

    problemState->NodeIds[problemState->NodeIdsUsedCnt-1] = -1;
    problemState->NodeIdsUsedCnt -= 1;
  } else {
    do {
      changeNode = rand() % problemParams->NodesCnt;
    } while (changeNode == problemState->NodeIds[index]);

    problemState->NodeIds[index] = changeNode;
  }

  _ProblemStateFix(problemState,problemParams);

  return problemState;
}

ProblemState*
ProblemStateCrossOver(
  const ProblemParams* problemParams,
  const ProblemState* parentState0,
  const ProblemState* parentState1,
  int crossOverMaskCnt,
  const int* crossOverMask)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,parentState0));
  assert(ProblemStateIsValid(problemParams,parentState1));
  assert(crossOverMaskCnt > 0);
  assert(crossOverMask != NULL);
  assert((crossOverMaskCnt == ProblemStateGenomeSize(problemParams,parentState0) && 
	  crossOverMaskCnt >= ProblemStateGenomeSize(problemParams,parentState1)) ||
     	 (crossOverMaskCnt == ProblemStateGenomeSize(problemParams,parentState1) && 
	  crossOverMaskCnt >= ProblemStateGenomeSize(problemParams,parentState0)));

  ProblemState*  problemState;
  int            i;

  problemState = ProblemStateCopy(problemParams,parentState0);

  for (i = 0; i < crossOverMaskCnt; i++) {
    if (crossOverMask[i] == 1) {
      problemState->NodeIds[i] = parentState1->NodeIds[i];
    }
  }

  problemState->NodeIdsUsedCnt = 0;

  for (i = 0; i < problemState->NodeIdsCnt; i++) {
    if (problemState->NodeIds[i] != -1) {
      problemState->NodeIds[problemState->NodeIdsUsedCnt] = problemState->NodeIds[i];
      problemState->NodeIdsUsedCnt += 1;
    }
  }

  for (i = problemState->NodeIdsUsedCnt; i < problemState->NodeIdsCnt; i++) {
    problemState->NodeIds[i] = -1;
  }

  _ProblemStateFix(problemState,problemParams);

  return problemState;
}

ProblemState*
ProblemStateFirst(
  const ProblemParams* problemParams)
{
  assert(ProblemParamsIsValid(problemParams));

  ProblemState*  problemState;

  problemState = malloc(sizeof(ProblemState));
  
  _ProblemStateEmpty(problemState,problemParams);
  problemState = _ProblemStateWalkToValid(problemState,problemParams);

  return problemState;
}

ProblemState*
ProblemStateWalk(
  const ProblemParams* problemParams,
  const ProblemState* previousState)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,previousState));

  ProblemState*  problemState;

  problemState = ProblemStateCopy(problemParams,previousState);
  problemState = _ProblemStateWalkToValid(problemState,problemParams);

  return problemState;
}

void
ProblemStateFree(
  const ProblemParams* problemParams,
  ProblemState** problemState)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(problemState != NULL && ProblemStateIsValid(problemParams,*problemState));

  free((*problemState)->NodeIds);

  (*problemState)->NodeIdsUsedCnt = 0;
  (*problemState)->NodeIdsCnt = 0;
  (*problemState)->NodeIds = NULL;
  (*problemState)->Cost = 0.0;

  free(*problemState);
  *problemState = NULL;
}

void
ProblemStatePrint(
  const ProblemParams* problemParams,
  const ProblemState* problemState,
  const char* name,
  int indentLevel)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,problemState));
  assert(indentLevel >= 0);

  char*  indent;
  int    i;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%s%s[AccessNetworkState]:\n",indent,name);
  printf("%s  NodeIdsUsedCnt: %d\n",indent,problemState->NodeIdsUsedCnt);
  printf("%s  NodeIdsCnt: %d\n",indent,problemState->NodeIdsCnt);
  printf("%s  NodesIds: ",indent);

  for (i = 0; i < problemState->NodeIdsUsedCnt; i++) {
    printf("%d ", problemState->NodeIds[i]);
  }

  printf("\n");
  printf("%s  Cost: %.3lf\n",indent,problemState->Cost);

  free(indent);
}

int
ProblemStateIsValid(
  const ProblemParams* problemParams,
  const ProblemState* problemState)
{
  assert(ProblemParamsIsValid(problemParams));

#ifdef NOHACK
  int      portAllocationMatrixCnt;
  Speed**  portAllocationMatrix;
  int      currLevel;
  int      currLevelUser;
  int      currLevelUsersCnt;
  int      nextLevelUsersCnt;
  int      nextLevelNodesAdded;
  int      savedNodesAdded;
  Speed    nodeSpeed;
#endif
  int      i;
#ifdef NOHACK
  int      j;
  int      k;
  int      l;
#endif

  if (problemState == NULL) {
    return 0;
  }

  if (problemState->NodeIdsUsedCnt < 1 || 
      problemState->NodeIdsUsedCnt > problemState->NodeIdsCnt) {
    return 0;
  }

  if (problemState->NodeIdsCnt < 1 || 
      problemState->NodeIdsCnt > problemParams->MaxNetworkNodes) {
    return 0;
  }

  if (problemState->NodeIds == NULL) {
    return 0;
  }

  for (i = 0; i < problemState->NodeIdsUsedCnt; i++) {
    if (problemState->NodeIds[i] < 0 ||
	problemState->NodeIds[i] > problemParams->NodesCnt) {
      return 0;
    }
  }

  for (i = problemState->NodeIdsUsedCnt; i < problemState->NodeIdsCnt; i++) {
    if (problemState->NodeIds[i] != -1) {
      return 0;
    }
  }

  if (problemState->Cost <= 0.0) {
      return 0;
  }

#ifdef HACK
  {
    /* SHORT HACK */
    ProblemState*  fixedState;
    int            i;

    fixedState = malloc(sizeof(ProblemState));

    fixedState->NodeIdsUsedCnt = problemState->NodeIdsUsedCnt;
    fixedState->NodeIdsCnt = problemState->NodeIdsCnt;
    fixedState->NodeIds = malloc(sizeof(int) * fixedState->NodeIdsCnt);
    fixedState->Cost = problemState->Cost;

    for (i = 0; i < fixedState->NodeIdsCnt; i++) {
      fixedState->NodeIds[i] = problemState->NodeIds[i];
    }

    _ProblemStateFix(fixedState,problemParams);

    if (problemState->NodeIdsUsedCnt != fixedState->NodeIdsUsedCnt) {
      free(fixedState->NodeIds);
      free(fixedState);
      return 0;
    }

    for (i = 0; i < problemState->NodeIdsUsedCnt; i++) {
      if (problemState->NodeIds[i] != fixedState->NodeIds[i]) {
	free(fixedState->NodeIds);
	free(fixedState);
	return 0;
      }
    }

    free(fixedState->NodeIds);
    free(fixedState);
  }
#endif

#ifdef NOHACK
  /* TEMPORARY REMOVED */
  portAllocationMatrixCnt = problemParams->MaxNetworkLevels;
  portAllocationMatrix = malloc(sizeof(Speed*) * portAllocationMatrixCnt);

  for (i = 0; i < portAllocationMatrixCnt; i++) {
    portAllocationMatrix[i] = malloc(sizeof(Speed) * problemParams->UsersCnt);
  }

  for (i = 0; i < problemParams->UsersCnt; i++) {
    portAllocationMatrix[0][i] = problemParams->Users[i].Speed;
  }

  currLevel = 0;
  currLevelUser = 0;
  currLevelUsersCnt = problemParams->UsersCnt;
  nextLevelUsersCnt = 0;
  nextLevelNodesAdded = 0;
  savedNodesAdded = 0;

  for (i = 0; i < problemState->NodeIdsUsedCnt; i++) {
    nodeSpeed.Download = 0;
    nodeSpeed.Upload = 0;

    for (j = currLevelUser, k = 0;
	 j < currLevelUsersCnt && k < problemParams->Nodes[problemState->NodeIds[i]].DownPortsNr;
	 j++, k++) {
      if (problemParams->Nodes[problemState->NodeIds[i]].DownPort.Download < portAllocationMatrix[currLevel][j].Download ||
	  problemParams->Nodes[problemState->NodeIds[i]].DownPort.Upload < portAllocationMatrix[currLevel][j].Upload) {

	for (l = 0; l < portAllocationMatrixCnt; l++) {
	  free(portAllocationMatrix[l]);
	}

	free(portAllocationMatrix);

	return 0;
      }

      nodeSpeed.Download += portAllocationMatrix[currLevel][j].Download;
      nodeSpeed.Upload += portAllocationMatrix[currLevel][j].Upload;
    }

    if (nodeSpeed.Download >= problemParams->Nodes[problemState->NodeIds[i]].UpPortsNr * 
	                      problemParams->Nodes[problemState->NodeIds[i]].UpPort.Download ||
	nodeSpeed.Upload >= problemParams->Nodes[problemState->NodeIds[i]].UpPortsNr *
	                    problemParams->Nodes[problemState->NodeIds[i]].UpPort.Upload) {
      for (l = 0; l < portAllocationMatrixCnt; l++) {
	free(portAllocationMatrix[l]);
      }

      free(portAllocationMatrix);

      return 0;
    }

    for (j = 0; j < problemParams->Nodes[problemState->NodeIds[i]].UpPortsNr; j++) {
      portAllocationMatrix[currLevel+1][nextLevelUsersCnt+j].Download = nodeSpeed.Download / problemParams->Nodes[problemState->NodeIds[i]].UpPortsNr;
      portAllocationMatrix[currLevel+1][nextLevelUsersCnt+j].Upload = nodeSpeed.Upload / problemParams->Nodes[problemState->NodeIds[i]].UpPortsNr;
    }

    currLevelUser += problemParams->Nodes[problemState->NodeIds[i]].DownPortsNr;
    nextLevelUsersCnt += problemParams->Nodes[problemState->NodeIds[i]].UpPortsNr;

    nextLevelNodesAdded += 1;

    if (currLevelUser >= currLevelUsersCnt) {
      currLevel += 1;
      currLevelUser = 0;
      currLevelUsersCnt = nextLevelUsersCnt;
      nextLevelUsersCnt = 0;

      savedNodesAdded = nextLevelNodesAdded;
      nextLevelNodesAdded = 0;
    }

    if (savedNodesAdded == 1 && i + 1 < problemState->NodeIdsUsedCnt) {
      /* More nodes than needed */
      for (l = 0; l < portAllocationMatrixCnt; l++) {
	free(portAllocationMatrix[l]);
      }

      free(portAllocationMatrix);

      return 0;
    }
  }

  for (l = 0; l < portAllocationMatrixCnt; l++) {
    free(portAllocationMatrix[l]);
  }

  free(portAllocationMatrix);

  /* Check this thing. Does it do what it says it does? */

  if (nextLevelNodesAdded != 1 && nextLevelNodesAdded != 0) {
    /* Fewer nodes than needed */
    return 0;
  }
#endif

  return 1;
}

int
ProblemStateCompare(
  const ProblemParams* problemParams,
  const ProblemState* problemState0,
  const ProblemState* problemState1)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,problemState0));
  assert(ProblemStateIsValid(problemParams,problemState1));

  if (problemState0->Cost < problemState1->Cost) {
    return -1;
  } else if (problemState0->Cost > problemState1->Cost) {
    return 1;
  } else {
    return 0;
  }
}

double
ProblemStateCost(
  const ProblemParams* problemParams,
  const ProblemState* problemState)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,problemState));

  return problemState->Cost;
}

int
ProblemStateGenomeSize(
  const ProblemParams* problemParams,
  const ProblemState* problemState)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(ProblemStateIsValid(problemParams,problemState));

  return problemState->NodeIdsUsedCnt;
}

static void
_ProblemStateFix(
  ProblemState* problemState,
  const ProblemParams* problemParams)
{
  int      portAllocationMatrixCnt;
  Speed**  portAllocationMatrix;
  int      currLevel;
  int      currLevelUser;
  int      currLevelUsersCnt;
  int      nextLevelUsersCnt;
  int      nextLevelNodesAdded;
  int      savedNodesAdded;
  int      nextNodeId;
  Speed    nextNodeSpeed;
  int      nodeGood;
  Speed    nodeSpeed;
  int      i;
  int      j;
  int      k;

  portAllocationMatrixCnt = problemParams->MaxNetworkLevels;
  portAllocationMatrix = malloc(sizeof(Speed*) * portAllocationMatrixCnt);

  for (i = 0; i < portAllocationMatrixCnt; i++) {
    portAllocationMatrix[i] = malloc(sizeof(Speed) * problemParams->UsersCnt);
  }

  for (i = 0; i < problemParams->UsersCnt; i++) {
    portAllocationMatrix[0][i] = problemParams->Users[i].Speed;
  }

  currLevel = 0;
  currLevelUser = 0;
  currLevelUsersCnt = problemParams->UsersCnt;
  nextLevelUsersCnt = 0;
  nextLevelNodesAdded = 0;
  savedNodesAdded = 0;

  for (i = 0; i < problemState->NodeIdsUsedCnt; i++) {
    nodeGood = 1;
    nodeSpeed.Download = 0;
    nodeSpeed.Upload = 0;

    /* Extract this large "for" as a function */

    for (j = currLevelUser, k = 0;
	 j < currLevelUsersCnt && k < problemParams->Nodes[problemState->NodeIds[i]].DownPortsNr && nodeGood;
	 j++, k++) {
      if (problemParams->Nodes[problemState->NodeIds[i]].DownPort.Download < portAllocationMatrix[currLevel][j].Download ||
	  problemParams->Nodes[problemState->NodeIds[i]].DownPort.Upload < portAllocationMatrix[currLevel][j].Upload) {
	nodeGood = 0;
      }

      nodeSpeed.Download += portAllocationMatrix[currLevel][j].Download;
      nodeSpeed.Upload += portAllocationMatrix[currLevel][j].Upload;
    }

    if (nodeGood &&
	nodeSpeed.Download <= problemParams->Nodes[problemState->NodeIds[i]].UpPortsNr * problemParams->Nodes[problemState->NodeIds[i]].UpPort.Download &&
	nodeSpeed.Upload <= problemParams->Nodes[problemState->NodeIds[i]].UpPortsNr * problemParams->Nodes[problemState->NodeIds[i]].UpPort.Upload) {
      for (j = 0; j < problemParams->Nodes[problemState->NodeIds[i]].UpPortsNr; j++) {
	portAllocationMatrix[currLevel+1][nextLevelUsersCnt+j].Download = nodeSpeed.Download / problemParams->Nodes[problemState->NodeIds[i]].UpPortsNr;
	portAllocationMatrix[currLevel+1][nextLevelUsersCnt+j].Upload = nodeSpeed.Upload / problemParams->Nodes[problemState->NodeIds[i]].UpPortsNr;
      }

      currLevelUser += problemParams->Nodes[problemState->NodeIds[i]].DownPortsNr;
      nextLevelUsersCnt += problemParams->Nodes[problemState->NodeIds[i]].UpPortsNr;
    } else {
      nextNodeId = _ProblemStateFindFit(problemState,problemParams,portAllocationMatrixCnt,(const Speed**)portAllocationMatrix,currLevel,currLevelUser,currLevelUsersCnt,&nextNodeSpeed);

      for (j = 0; j < problemParams->Nodes[nextNodeId].UpPortsNr; j++) {
	portAllocationMatrix[currLevel+1][nextLevelUsersCnt+j].Download = nextNodeSpeed.Download / problemParams->Nodes[nextNodeId].UpPortsNr;
	portAllocationMatrix[currLevel+1][nextLevelUsersCnt+j].Upload = nextNodeSpeed.Upload / problemParams->Nodes[nextNodeId].UpPortsNr;
      }

      currLevelUser += problemParams->Nodes[nextNodeId].DownPortsNr;
      nextLevelUsersCnt += problemParams->Nodes[nextNodeId].UpPortsNr;

      problemState->NodeIds[i] = nextNodeId;
    }

    nextLevelNodesAdded += 1;

    if (currLevelUser >= currLevelUsersCnt) {
      currLevel += 1;
      currLevelUser = 0;
      currLevelUsersCnt = nextLevelUsersCnt;
      nextLevelUsersCnt = 0;

      savedNodesAdded = nextLevelNodesAdded;
      nextLevelNodesAdded = 0;
    }

    if (savedNodesAdded == 1 && i + 1 < problemState->NodeIdsUsedCnt) {
      /* More nodes than needed */
      for (j = i + 1; j < problemState->NodeIdsUsedCnt; j++) {
	problemState->NodeIds[j] = -1;
      }

      problemState->NodeIdsUsedCnt = i + 1;

      break;
    }
  }

  if (nextLevelNodesAdded != 1 || savedNodesAdded != 1) {
    /* Fewer nodes than needed */
    while (savedNodesAdded != 1) {
      nextNodeId = _ProblemStateFindFit(problemState,problemParams,portAllocationMatrixCnt,(const Speed**)portAllocationMatrix,currLevel,currLevelUser,currLevelUsersCnt,&nextNodeSpeed);

      for (i = 0; i < problemParams->Nodes[nextNodeId].UpPortsNr; i++) {
	portAllocationMatrix[currLevel+1][nextLevelUsersCnt+i].Download = nextNodeSpeed.Download / problemParams->Nodes[nextNodeId].UpPortsNr;
	portAllocationMatrix[currLevel+1][nextLevelUsersCnt+i].Upload = nextNodeSpeed.Upload / problemParams->Nodes[nextNodeId].UpPortsNr;
      }

      currLevelUser += problemParams->Nodes[nextNodeId].DownPortsNr;
      nextLevelUsersCnt += problemParams->Nodes[nextNodeId].UpPortsNr;
      nextLevelNodesAdded += 1;

      problemState->NodeIds[problemState->NodeIdsUsedCnt] = nextNodeId;
      problemState->NodeIdsUsedCnt += 1;

      if (currLevelUser >= currLevelUsersCnt) {
	currLevel += 1;
	currLevelUser = 0;
	currLevelUsersCnt = nextLevelUsersCnt;
	nextLevelUsersCnt = 0;

	savedNodesAdded = nextLevelNodesAdded;
	nextLevelNodesAdded = 0;
      }
    }
  }

  problemState->Cost = _ProblemStateCalcCost(problemState,problemParams);

  for (i = 0; i < portAllocationMatrixCnt; i++) {
    free(portAllocationMatrix[i]);
  }

  free(portAllocationMatrix);
}

static int
_ProblemStateFindFit(
  const ProblemState* problemState,
  const ProblemParams* problemParams,
  int portAllocationMatrixCnt,
  const Speed** portAllocationMatrix,
  int currLevel,
  int currLevelUser,
  int currLevelUsersCnt,
  Speed* nodeSpeed)
{
  int     validNodeIdsCnt;
  int*    validNodeIds;
  int     validSpeedsCnt;
  Speed*  validSpeeds;
  int     nodeGood;
  Speed   speed;
  int     nextNodeId;
  int     nextNode;
  int     i;
  int     j;
  int     k;

  validNodeIdsCnt = 0;
  validNodeIds = malloc(sizeof(int) * problemParams->NodesCnt);

  validSpeedsCnt = 0;
  validSpeeds = malloc(sizeof(Speed) * problemParams->NodesCnt);

  for (i = 0; i < problemParams->NodesCnt; i++) {
    nodeGood = 1;
    speed.Download = 0;
    speed.Upload = 0;

    for (j = currLevelUser, k = 0;
	 j < currLevelUsersCnt && k < problemParams->Nodes[i].DownPortsNr && nodeGood;
	 j++,k++) {
      if (problemParams->Nodes[i].DownPort.Download < portAllocationMatrix[currLevel][j].Download ||
	  problemParams->Nodes[i].DownPort.Upload < portAllocationMatrix[currLevel][j].Upload) {
	nodeGood = 0;
      }

      speed.Download += portAllocationMatrix[currLevel][j].Download;
      speed.Upload += portAllocationMatrix[currLevel][j].Upload;
    }

    if (nodeGood &&
	speed.Download <= problemParams->Nodes[i].UpPortsNr * problemParams->Nodes[i].UpPort.Download &&
	speed.Upload <= problemParams->Nodes[i].UpPortsNr * problemParams->Nodes[i].UpPort.Upload) {
      validNodeIds[validNodeIdsCnt] = i;
      validNodeIdsCnt += 1;
      validSpeeds[validSpeedsCnt] = speed;
      validSpeedsCnt += 1;
    }
  }

  if (validNodeIdsCnt > 0) {
    nextNodeId = rand() % validNodeIdsCnt;
    nextNode = validNodeIds[nextNodeId];
    *nodeSpeed = validSpeeds[nextNodeId];

    free(validNodeIds);
    free(validSpeeds);

    return nextNode;
  } else {
    /* Could not find even one node which can handle this level's traffic
       requirements. If we're at level 0 (user access level), this should
       prove a fatal condition : no one switch has access ports with
       sufficient bandwith to handle certain users. If we're at upper levels,
       the situation might be recoverable. For example, if at the lower
       level we have big switches which aggregate a lot of users, the resulting
       sumed bandwidth requirement might prove too great to be handled. Some
       backtracking would be needed, though I'm not sure how to go along with
       it. In general, favoring smaller switches at lower levels and bigger ones
       as we go along might mitigate this problem. For now, we abort. */
    free(validNodeIds);
    free(validSpeeds);

    printf("Could not find fit problem state!\n");
    exit(2);
  }
}

static void
_ProblemStateEmpty(
  ProblemState* problemState,
  const ProblemParams* problemParams)
{
  int  i;

  problemState->NodeIdsUsedCnt = 0;
  problemState->NodeIdsCnt = problemParams->MaxNetworkNodes;
  problemState->NodeIds = malloc(sizeof(int) * problemState->NodeIdsCnt);
  problemState->Cost = 0;

  for (i = 0; i < problemState->NodeIdsCnt; i++) {
    problemState->NodeIds[i] = -1;
  }
}

static ProblemState*
_ProblemStateWalkToValid(
  ProblemState* problemState,
  const ProblemParams* problemParams)
{
  int  addIndex;
  int  doIncrement;
  int  lastOne;
  int  i;

  do {
    addIndex = 0;
    doIncrement = 1;

    while (doIncrement && (addIndex < problemState->NodeIdsCnt)) {
      problemState->NodeIds[addIndex] += 1;
      doIncrement = 0;
    
      if (problemState->NodeIds[addIndex] == problemParams->NodesCnt) {
	problemState->NodeIds[addIndex] = 0;
	addIndex += 1;
	doIncrement = 1;
      }
    }

    problemState->NodeIdsUsedCnt += addIndex == problemState->NodeIdsUsedCnt ? 1 : 0;

    lastOne = 1;

    for (i = 0; i < problemState->NodeIdsCnt && lastOne; i++) {
      if (problemState->NodeIds[i] != problemParams->NodesCnt - 1) {
	lastOne = 0;
      }
    }

    if (lastOne) {
      free(problemState->NodeIds);
      free(problemState);

      return NULL;
    }

    problemState->Cost = _ProblemStateCalcCost(problemState,problemParams);
  } while (!ProblemStateIsValid(problemParams,problemState));

  return problemState;
}

static double
_ProblemStateCalcCost(
  ProblemState* problemState,
  const ProblemParams* problemParams)
{
  double  cost;
  int     i;

  cost = 0.0;

  for (i = 0; i < problemState->NodeIdsUsedCnt; i++) {
    cost += problemParams->Nodes[problemState->NodeIds[i]].Cost;
  }

  return cost;
}
