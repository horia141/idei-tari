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
  FILE* fin)
{
  ProblemParams*  problemParams;
  int             minDownPortsNr;
  int             maxUpPortsNr;
  double          a;
  double          r;
  int             i;
    
  problemParams = malloc(sizeof(ProblemParams));

  fscanf(fin," AccessNetworkParams :");
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
    
  return problemParams;
}

void
ProblemParamsFree(
  ProblemParams** problemParams)
{
  assert(problemParams != NULL);
  assert(ProblemParamsIsValid(*problemParams));

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
  int indentLevel)
{
  assert(ProblemParamsIsValid(problemParams));
  assert(indentLevel >= 0);

  char*  indent;
  int    i;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sAccessNetworkParams:\n",indent);
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
  char*  TextDiff;
};

static void    _ProblemStateFix(
                 ProblemState* problemState,
                 const ProblemParams* problemParams);
static int     _ProblemStateFindFit(
                 const ProblemState* problemState,
                 const ProblemParams* problemParams,
                 int portAllocationMatrixCnt,
                 const Speed** portAllocationMatrix,
                 int currLevel,
                 int currLevelUser,
                 int currLevelUserCnt,
                 Speed* nodeSpeed);

ProblemState*
ProblemStateAlloc(
  const ProblemParams* problemParams)
{
  assert(ProblemParamsIsValid(problemParams));

  ProblemState*  problemState;
  int            i;

  problemState = malloc(sizeof(ProblemState));

  problemState->NodeIdsUsedCnt = 0;
  problemState->NodeIdsCnt = problemParams->MaxNetworkNodes;
  problemState->NodeIds = malloc(sizeof(int) * problemState->NodeIdsCnt);
  problemState->Cost = 0;
  problemState->TextDiff = strdup("");

  for (i = 0; i < problemState->NodeIdsCnt; i++) {
    problemState->NodeIds[i] = -1;
  }

  _ProblemStateFix(problemState,problemParams);

  return problemState;
}

ProblemState*
ProblemStateCopy(
  const ProblemState* sourceState)
{
  assert(ProblemStateIsValid(sourceState));

  ProblemState*  problemState;
  int            i;
    
  problemState = malloc(sizeof(ProblemState));

  problemState->NodeIdsUsedCnt = sourceState->NodeIdsUsedCnt;
  problemState->NodeIdsCnt = sourceState->NodeIdsCnt;
  problemState->NodeIds = malloc(sizeof(int) * problemState->NodeIdsCnt);
  problemState->Cost = sourceState->Cost;
  problemState->TextDiff = strdup(sourceState->TextDiff);

  for (i = 0; i < problemState->NodeIdsCnt; i++) {
    problemState->NodeIds[i] = sourceState->NodeIds[i];
  }

  return problemState;
}

ProblemState*
ProblemStateGenNext(
  const ProblemState* previousState,
  const ProblemParams* problemParams)
{
  assert(ProblemStateIsValid(previousState));
  assert(ProblemParamsIsValid(problemParams));

  ProblemState*  problemState;
  char           tempBuff[2048];
  int            tempBuffSize;
  float          operation;
  int            index;
  int            oldType;
  int            changeNode;
  int            i;
  int            j;

  problemState = ProblemStateCopy(previousState);

  operation = rand() / (float)RAND_MAX;
  index = rand() % problemState->NodeIdsUsedCnt;

  free(problemState->TextDiff);

  memset(tempBuff,'\0',2048);
  tempBuffSize = 0;

  tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"INIT            : ");

  for (i = 0; i < problemState->NodeIdsUsedCnt; i++) {
    tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problemParams->Nodes[problemState->NodeIds[i]].Name);
  }

  if (operation < 0.20 && problemState->NodeIdsUsedCnt < problemState->NodeIdsCnt) {
    for (i = problemState->NodeIdsUsedCnt; i > index; i--) {
      problemState->NodeIds[i] = problemState->NodeIds[i-1];
    }

    problemState->NodeIds[index] = rand() % problemParams->NodesCnt;
    problemState->NodeIdsUsedCnt += 1;

    tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,";ADD %3d [%s] : ",index+1,problemParams->Nodes[problemState->NodeIds[index]].Name);

    for (j = 0; j < problemState->NodeIdsUsedCnt; j++) {
      tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problemParams->Nodes[problemState->NodeIds[j]].Name);
    }
  } else if (operation < 0.40 && problemState->NodeIdsUsedCnt > 1) {
    oldType = problemState->NodeIds[index];

    for (i = index; i < problemState->NodeIdsUsedCnt - 1; i++) {
      problemState->NodeIds[i] = problemState->NodeIds[i+1];
    }

    problemState->NodeIds[problemState->NodeIdsUsedCnt-1] = -1;
    problemState->NodeIdsUsedCnt -= 1;

    tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,";REM %3d         : ",index+1);

    for (j = 0; j < problemState->NodeIdsUsedCnt; j++) {
      tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problemParams->Nodes[problemState->NodeIds[j]].Name);
    }
  } else {
    do {
      changeNode = rand() % problemParams->NodesCnt;
    } while (changeNode == problemState->NodeIds[index]);

    problemState->NodeIds[index] = changeNode;

    tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,";CHG %3d [%s] : ",index+1,problemParams->Nodes[problemState->NodeIds[index]].Name);

    for (j = 0; j < problemState->NodeIdsUsedCnt; j++) {
      tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problemParams->Nodes[problemState->NodeIds[j]].Name);
    }
  }

  problemState->TextDiff = strdup(tempBuff);

  _ProblemStateFix(problemState,problemParams);

  return problemState;
}

ProblemState*
ProblemStateCrossOver(
  const ProblemState* parentState0,
  const ProblemState* parentState1,
  const ProblemParams* problemParams,
  int crossOverMaskCnt,
  const int* crossOverMask)
{
  assert(ProblemStateIsValid(parentState0));
  assert(ProblemStateIsValid(parentState1));
  assert(ProblemParamsIsValid(problemParams));
  assert(crossOverMaskCnt > 0);
  assert(crossOverMask != NULL);
  assert((crossOverMaskCnt == ProblemStateGenomeSize(parentState0) && crossOverMaskCnt >= ProblemStateGenomeSize(parentState1)) ||
     	 (crossOverMaskCnt == ProblemStateGenomeSize(parentState1) && crossOverMaskCnt >= ProblemStateGenomeSize(parentState0)));

  ProblemState*  problemState;
  char           tempBuff[2048];
  int            tempBuffSize;
  int            i;

  problemState = ProblemStateCopy(parentState0);

  free(problemState->TextDiff);

  memset(tempBuff,'\0',2048);
  tempBuffSize = 0;

  tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"PARENTS         : ");

  for (i = 0; i < parentState0->NodeIdsUsedCnt; i++) {
    tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problemParams->Nodes[parentState0->NodeIds[i]].Name);
  }

  tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,",                  ");

  for (i = 0; i < parentState1->NodeIdsUsedCnt; i++) {
    tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problemParams->Nodes[parentState1->NodeIds[i]].Name);
  }

  tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,";CROSSOVER MASK  : ");

  for (i = 0; i < crossOverMaskCnt; i++) {
    if (crossOverMask[i] == 1) {
      tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[CROSS] ");
    } else {
      tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[LEAVE] ");
    }
  }

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

  tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,";RESULT CHILD    : ");

  for (i = 0; i < problemState->NodeIdsUsedCnt; i++) {
    tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problemParams->Nodes[problemState->NodeIds[i]].Name);
  }
  
  problemState->TextDiff = strdup(tempBuff);

  _ProblemStateFix(problemState,problemParams);

  return problemState;
}

void
ProblemStateFree(
  ProblemState** problemState)
{
  assert(problemState != NULL);
  assert(ProblemStateIsValid(*problemState));

  free((*problemState)->NodeIds);
  free((*problemState)->TextDiff);

  (*problemState)->NodeIdsUsedCnt = 0;
  (*problemState)->NodeIdsCnt = 0;
  (*problemState)->NodeIds = NULL;
  (*problemState)->Cost = 0.0;
  (*problemState)->TextDiff = NULL;

  free(*problemState);
  *problemState = NULL;
}

void
ProblemStatePrint(
  const ProblemState* problemState,
  int indentLevel)
{
  assert(ProblemStateIsValid(problemState));
  assert(indentLevel >= 0);

  char*  indent;
  char*  diffText;
  int    i;
  int    printADiffChar;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sAccessNetworkState:\n",indent);
  printf("%s  NodeIdsUsedCnt: %d\n",indent,problemState->NodeIdsUsedCnt);
  printf("%s  NodeIdsCnt: %d\n",indent,problemState->NodeIdsCnt);
  printf("%s  NodesIds: ",indent);

  for (i = 0; i < problemState->NodeIdsUsedCnt; i++) {
    printf("%d ", problemState->NodeIds[i]);
  }

  printf("\n");
  printf("%s  Cost: %.3lf\n",indent,problemState->Cost);
  printf("%s  TextDiff: ",indent);

  diffText = problemState->TextDiff;
  printADiffChar = 0;

  while (*diffText) {
      switch (*diffText) {
      case ';': if (printADiffChar) printf("\n%s          - ",indent); break;
      case ',': if (printADiffChar) printf("\n%s            ",indent); break;
      default:  printf("%c",*diffText); printADiffChar = 1; break;
      }

      diffText++;
  }

  printf("\n");

  free(indent);
}

int
ProblemStateIsValid(
  const ProblemState* problemState)
{
  int  i;

  if (problemState == NULL) {
    return 0;
  }

  if (problemState->NodeIdsUsedCnt < 1) {
    return 0;
  }

  if (problemState->NodeIdsCnt < 1) {
    return 0;
  }

  if (problemState->NodeIdsUsedCnt > problemState->NodeIdsCnt) {
    return 0;
  }

  if (problemState->NodeIds == NULL) {
    return 0;
  }

  for (i = 0; i < problemState->NodeIdsUsedCnt; i++) {
    if (problemState->NodeIds[i] == -1) {
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

  if (problemState->TextDiff == NULL) {
    return 0;
  }

  return 1;
}

int
ProblemStateCompare(
  const ProblemState** problemState0,
  const ProblemState** problemState1)
{
  assert(problemState0 != NULL);
  assert(problemState1 != NULL);
  assert(ProblemStateIsValid(*problemState0));
  assert(ProblemStateIsValid(*problemState1));

  if ((*problemState0)->Cost < (*problemState1)->Cost) {
    return -1;
  } else if ((*problemState0)->Cost > (*problemState1)->Cost) {
    return 1;
  } else {
    return 0;
  }
}

double
ProblemStateCost(
  const ProblemState* problemState)
{
  assert(ProblemStateIsValid(problemState));

  return problemState->Cost;
}

int
ProblemStateGenomeSize(
  const ProblemState* problemState)
{
  assert(ProblemStateIsValid(problemState));

  return problemState->NodeIdsUsedCnt;
}

void
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
    char*    diffText;
    char     tempBuff[2048];
    int      tempBuffSize;
    int      i;
    int      j;
    int      k;

    portAllocationMatrixCnt = problemParams->MaxNetworkLevels;
    portAllocationMatrix = malloc(sizeof(Speed*) * portAllocationMatrixCnt);

    for (i = 0; i < problemParams->MaxNetworkLevels; i++) {
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

    memset(tempBuff,'\0',2048);
    tempBuffSize = 0;

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

            tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,";CHG %3d [%s] : ",i+1,problemParams->Nodes[nextNodeId].Name);

            for (j = 0; j < problemState->NodeIdsUsedCnt; j++) {
                tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problemParams->Nodes[problemState->NodeIds[j]].Name);
            }
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
            /* more nodes than needed */
            for (j = i + 1; j < problemState->NodeIdsUsedCnt; j++) {
                problemState->NodeIds[j] = -1;
            }

            problemState->NodeIdsUsedCnt = i + 1;

            tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,";RMX %3d         : ",i+2);

            for (j = 0; j < problemState->NodeIdsUsedCnt; j++) {
                tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problemParams->Nodes[problemState->NodeIds[j]].Name);
            }

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

            tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,";APP     [%s] : ",problemParams->Nodes[nextNodeId].Name);

            for (j = 0; j < problemState->NodeIdsUsedCnt; j++) {
                tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problemParams->Nodes[problemState->NodeIds[j]].Name);
            }

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

    problemState->Cost = 0.0;

    for (i = 0; i < problemState->NodeIdsUsedCnt; i++) {
        problemState->Cost = problemState->Cost + problemParams->Nodes[problemState->NodeIds[i]].Cost;
    }

    diffText = problemState->TextDiff;
    asprintf(&problemState->TextDiff,"%s%s",diffText,tempBuff);
    free(diffText);

    for (i = 0; i < problemParams->MaxNetworkLevels; i++) {
        free(portAllocationMatrix[i]);
    }

    free(portAllocationMatrix);
}

int
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
