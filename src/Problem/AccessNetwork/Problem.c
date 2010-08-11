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
  int    MaxNetworkNodes;
  int    MaxNetworkLevels;
};

static int  _ProblemParamsMaxNetworkNodes(
              const ProblemParams* problemParams);
static int  _ProblemParamsMaxNetworkLevels(
              const ProblemParams* problemParams);

ProblemParams*
ProblemParamsAlloc()
{
  ProblemParams*  problemParams;
    
  problemParams = malloc(sizeof(ProblemParams));

  problemParams->Name = strdup("Test Problem");
  problemParams->NodesCnt = 4;
  problemParams->Nodes = malloc(sizeof(Node)*problemParams->NodesCnt);
  problemParams->Nodes[0].Name = strdup("SW 01");
  problemParams->Nodes[0].Cost = 100.0;
  problemParams->Nodes[0].DownPortsNr = 4;
  problemParams->Nodes[0].DownPort.Download = 10.0;
  problemParams->Nodes[0].DownPort.Upload = 2.0;
  problemParams->Nodes[0].UpPortsNr = 1;
  problemParams->Nodes[0].UpPort.Download = 20.0;
  problemParams->Nodes[0].UpPort.Upload = 2.0;
  problemParams->Nodes[1].Name = strdup("SW 02");
  problemParams->Nodes[1].Cost = 40.0;
  problemParams->Nodes[1].DownPortsNr = 2;
  problemParams->Nodes[1].DownPort.Download = 10.0;
  problemParams->Nodes[1].DownPort.Upload = 4.0;
  problemParams->Nodes[1].UpPortsNr = 1;
  problemParams->Nodes[1].UpPort.Download = 20.0;
  problemParams->Nodes[1].UpPort.Upload = 2.0;
  problemParams->Nodes[2].Name = strdup("SW 03");
  problemParams->Nodes[2].Cost = 150.0;
  problemParams->Nodes[2].DownPortsNr = 8;
  problemParams->Nodes[2].DownPort.Download = 10.0;
  problemParams->Nodes[2].DownPort.Upload = 1.0;
  problemParams->Nodes[2].UpPortsNr = 2;
  problemParams->Nodes[2].UpPort.Download = 100.0;
  problemParams->Nodes[2].UpPort.Upload = 10.0;
  problemParams->Nodes[3].Name = strdup("SW 04");
  problemParams->Nodes[3].Cost = 180.0;
  problemParams->Nodes[3].DownPortsNr = 4;
  problemParams->Nodes[3].DownPort.Download = 12.0;
  problemParams->Nodes[3].DownPort.Upload = 4.0;
  problemParams->Nodes[3].UpPortsNr = 1;
  problemParams->Nodes[3].UpPort.Download = 40.0;
  problemParams->Nodes[3].UpPort.Upload = 10.0;
  problemParams->UsersCnt = 12;
  problemParams->Users = malloc(sizeof(User)*problemParams->UsersCnt);
  problemParams->Users[0].Name = strdup("User 00");
  problemParams->Users[0].Speed.Download = 1.024;
  problemParams->Users[0].Speed.Upload = 0.128;
  problemParams->Users[1].Name = strdup("User 01");
  problemParams->Users[1].Speed.Download = 0.512;
  problemParams->Users[1].Speed.Upload = 0.128;
  problemParams->Users[2].Name = strdup("User 02");
  problemParams->Users[2].Speed.Download = 0.512;
  problemParams->Users[2].Speed.Upload = 0.064;
  problemParams->Users[3].Name = strdup("User 03");
  problemParams->Users[3].Speed.Download = 1.024;
  problemParams->Users[3].Speed.Upload = 0.256;
  problemParams->Users[4].Name = strdup("User 04");
  problemParams->Users[4].Speed.Download = 2.048;
  problemParams->Users[4].Speed.Upload = 1.024;
  problemParams->Users[5].Name = strdup("User 05");
  problemParams->Users[5].Speed.Download = 0.512;
  problemParams->Users[5].Speed.Upload = 0.128;
  problemParams->Users[6].Name = strdup("User 06");
  problemParams->Users[6].Speed.Download = 0.512;
  problemParams->Users[6].Speed.Upload = 0.256;
  problemParams->Users[7].Name = strdup("User 07");
  problemParams->Users[7].Speed.Download = 1.024;
  problemParams->Users[7].Speed.Upload = 0.256;
  problemParams->Users[8].Name = strdup("User 08");
  problemParams->Users[8].Speed.Download = 1.024;
  problemParams->Users[8].Speed.Upload = 0.128;
  problemParams->Users[9].Name = strdup("User 09");
  problemParams->Users[9].Speed.Download = 0.512;
  problemParams->Users[9].Speed.Upload = 0.512;
  problemParams->Users[10].Name = strdup("User 10");
  problemParams->Users[10].Speed.Download = 0.128;
  problemParams->Users[10].Speed.Upload = 0.064;
  problemParams->Users[11].Name = strdup("User 11");
  problemParams->Users[11].Speed.Download = 0.256;
  problemParams->Users[11].Speed.Upload = 0.128;
  problemParams->cMaxNetworkNodes = _ProblemParamsMaxNetworkNodes(problemParams);
  problemParams->cMaxNetworkLevels = _ProblemParamsMaxNetworkLevels(problemParams);

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
  (*problemParams)->MaxNetworkNodes = 0;
  (*problemParams)->MaxNetworkLevels = 0;

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

  printf("%sAccessNetwork Params:\n",indent);
  printf("%s  Name: %s\n",indent,problemParams->Name);
  printf("%s  Nodes:\n",indent);
  
  for (i = 0; i < NodesCnt; i++) {
    printf("%s    %s:\n",indent,problemParams->Nodes[i].Name);
    printf("%s      Cost: %f\n",indent,problemParams->Nodes[i].Cost);
    printf("%s      DownPortsNr: %d\n",indent,problemParams->Nodes[i].DownPortsNr);
    printf("%s      DownPort: %.3f %.3f\n",indent,problemParams->Nodes[i].DownPort.Download,problemParams->Nodes[i].DownPort.Upload);
    printf("%s      UpPortsNr: %d\n",indent,problemParams->Nodes[i].UpPortsCnt);
    printf("%s      UpPort: %.3f %.3f\n",indent,problemParams->Nodes[i].UpPort.Download,problemParams->Nodes[i].UpPort.Upload);
  }
  
  printf("%s  Users:\n",indent);

  for (i = 0; i < UsersCnt; i++) {
    printf("%s    %s:\n",indent,problemParams->Users[i].Name);
    printf("%s      Speed: %.3f %.3f\n",indent,problemParams->Users[i].Speed.Download,problemParams->Users[i].Speed.Upload);
  }

  printf("%s  MaxNetworkNodes: %d\n",indent,problemParams->MaxNetworkNodes);
  printf("%s  MaxNetworkLevels: %d\n",indent,problemParams->MaxNetworkLevels);

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

    if (problemParams->Users[i].UpPort.Download <= 0.0) {
      return 0;
    }

    if (problemParams->Users[i].UpPort.Upload <= 0.0) {
      return 0;
    }
  }

  if (problemParams->MaxNetworkNodes <= 0) {
    return 0;
  }

  if (problemParams->MaxNetworkLevels <= 0) {
    return 0;
  }

  return 1;
}

int
_ProblemParamsMaxNetworkNodes(
  const ProblemParams* problemParams)
{
  return 6 + 3 + 2 + 1;
}

int
_ProblemParamsMaxNetworkLevels(
  const ProblemParams* problemParams)
{
  return 4;
}


struct ProblemState
{
  int    NodeIdsUsedCnt;
  int    NodeIdsCnt;
  int*   NodeIds;
  float  Cost;
  char*  TextDiff;
};

static void  _ProblemStateFix(
               ProblemState* problemState,
               const ProblemParams* problemParams);
static int   _IndividualFindFit(
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
    
  problemState = malloc(sizeof(ProblemState));

  problemState->NodeIdsUsedCnt = sourceState->NodeIdsUsedCnt;
  problemState->NodeIdsCnt = sourceState->NodeIdsCnt;
  problemState->NodeIds = malloc(sizeof(int) * problemState->NodeIdsCnt);
  problemState->Cost = sourceState->Cost;
  problemState->TextDiff = strdup(source->TextDiff);

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
  assert(PreviousStateIsValid(previousState));
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
  index = rand() % individual->NodeIdsUsedCnt;

  free(individual->TextDiff);

  memset(tempBuff,'\0',2048);
  tempBuffSize = 0;

  tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"INIT            : ");

  for (i = 0; i < individual->NodeIdsUsedCnt; i++) {
    tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problem->Nodes[individual->NodeIds[i]].Name);
  }

  if (operation < 0.20 && individual->NodeIdsUsedCnt < individual->NodeIdsCnt) {
    for (i = individual->NodeIdsUsedCnt; i > index; i--) {
      individual->NodeIds[i] = individual->NodeIds[i-1];
    }

    individual->NodeIds[index] = rand() % problem->NodesCnt;
    individual->NodeIdsUsedCnt += 1;

    tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,";ADD %3d [%s] : ",index+1,problem->Nodes[individual->NodeIds[index]].Name);

    for (j = 0; j < individual->NodeIdsUsedCnt; j++) {
      tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problem->Nodes[individual->NodeIds[j]].Name);
    }
  } else if (operation < 0.40 && individual->NodeIdsUsedCnt > 1) {
    oldType = individual->NodeIds[index];

    for (i = index; i < individual->NodeIdsUsedCnt - 1; i++) {
      individual->NodeIds[i] = individual->NodeIds[i+1];
    }

    individual->NodeIds[individual->NodeIdsUsedCnt-1] = -1;
    individual->NodeIdsUsedCnt -= 1;

    tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,";REM %3d         : ",index+1);

    for (j = 0; j < individual->NodeIdsUsedCnt; j++) {
      tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problem->Nodes[individual->NodeIds[j]].Name);
    }
  } else {
    do {
      changeNode = rand() % problem->NodesCnt;
    } while (changeNode == individual->NodeIds[index]);

    individual->NodeIds[index] = changeNode;

    tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,";CHG %3d [%s] : ",index+1,problem->Nodes[individual->NodeIds[index]].Name);

    for (j = 0; j < individual->NodeIdsUsedCnt; j++) {
      tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problem->Nodes[individual->NodeIds[j]].Name);
    }
  }

  individual->TextDiff = strdup(tempBuff);

  _IndividualFix(individual,problem);
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
  assert((crossOverMaskCnt == ProblemStateGenomeSize(parentState0) && crossOverMaskCnt <= ProblemStateGenomeSize(parentState1)) ||
	 (crossOverMaskCnt == ProblemStateGenomeSize(parentState1) && crossOverMaskCnt <= ProblemStateGenomeSize(parentState0)));

  ProblemState*  problemState;
  char           tempBuff0[2048];
  int            tempBuff0Size;
  char           tempBuff1[2048];
  int            tempBuff1Size;
  int            newNodeIdsUsedCnt;
  int            newNodeIdsCnt;
  int*           newNodeIds;
  int            temp;
  int            i;

  problemState = ProblemStateCopy(parentState0);

  free(problemState->TextDiff);

  memset(tempBuff0,'\0',2048);
  tempBuff0Size = 0;

  tempBuff0Size += snprintf(tempBuff0+tempBuff0Size,2048-tempBuff0Size,"PARENTS         : ");
  tempBuff1Size += snprintf(tempBuff1+tempBuff1Size,2048-tempBuff1Size,"PARENTS         : ");

  for (i = 0; i < parent0->NodeIdsUsedCnt; i++) {
    tempBuff0Size += snprintf(tempBuff0+tempBuff0Size,2048-tempBuff0Size,"[%s] ",problem->Nodes[parent0->NodeIds[i]].Name);
    tempBuff1Size += snprintf(tempBuff1+tempBuff1Size,2048-tempBuff1Size,"[%s] ",problem->Nodes[parent0->NodeIds[i]].Name);
  }

  tempBuff0Size += snprintf(tempBuff0+tempBuff0Size,2048-tempBuff0Size,",                  ");
  tempBuff1Size += snprintf(tempBuff1+tempBuff1Size,2048-tempBuff1Size,",                  ");

  for (i = 0; i < parent1->NodeIdsUsedCnt; i++) {
    tempBuff0Size += snprintf(tempBuff0+tempBuff0Size,2048-tempBuff0Size,"[%s] ",problem->Nodes[parent1->NodeIds[i]].Name);
    tempBuff1Size += snprintf(tempBuff1+tempBuff1Size,2048-tempBuff1Size,"[%s] ",problem->Nodes[parent1->NodeIds[i]].Name);
  }

  tempBuff0Size += snprintf(tempBuff0+tempBuff0Size,2048-tempBuff0Size,";CROSSOVER MASK  : ");
  tempBuff1Size += snprintf(tempBuff1+tempBuff1Size,2048-tempBuff1Size,";CROSSOVER MASK  : ");

  for (i = 0; i < crossOverMaskCnt; i++) {
    if (crossOverMask[i] == 1) {
      tempBuff0Size += snprintf(tempBuff0+tempBuff0Size,2048-tempBuff0Size,"[CROSS] ");
      tempBuff1Size += snprintf(tempBuff1+tempBuff1Size,2048-tempBuff1Size,"[CROSS] ");
    } else {
      tempBuff0Size += snprintf(tempBuff0+tempBuff0Size,2048-tempBuff0Size,"[LEAVE] ");
      tempBuff1Size += snprintf(tempBuff1+tempBuff1Size,2048-tempBuff1Size,"[LEAVE] ");
    }
  }

  for (i = 0; i < crossOverMaskCnt; i++) {
    if (crossOverMask[i] == 1) {
      temp = child0->NodeIds[i];
      child0->NodeIds[i] = child1->NodeIds[i];
      child1->NodeIds[i] = temp;
    }
  }

  newNodeIdsUsedCnt = 0;
  newNodeIdsCnt = problem->cMaxNetworkNodes;
  newNodeIds = malloc(sizeof(int) * newNodeIdsCnt);

  for (i = 0; i < crossOverMaskCnt; i++) {
    if (child0->NodeIds[i] != -1) {
      newNodeIds[newNodeIdsUsedCnt] = child0->NodeIds[i];
      newNodeIdsUsedCnt += 1;
    }
  }

  for (i = newNodeIdsUsedCnt; i < newNodeIdsCnt; i++) {
    newNodeIds[i] = -1;
  }

  free(child0->NodeIds);

  child0->NodeIdsUsedCnt = newNodeIdsUsedCnt;
  child0->NodeIdsCnt = newNodeIdsCnt;
  child0->NodeIds = newNodeIds;

  tempBuff0Size += snprintf(tempBuff0+tempBuff0Size,2048-tempBuff0Size,";FIRST CHILD     : ");

  for (i = 0; i < child0->NodeIdsUsedCnt; i++) {
    tempBuff0Size += snprintf(tempBuff0+tempBuff0Size,2048-tempBuff0Size,"[%s] ",problem->Nodes[child0->NodeIds[i]].Name);
  }
  
  child0->cTextDiff = strdup(tempBuff0);

  newNodeIdsUsedCnt = 0;
  newNodeIdsCnt = problem->cMaxNetworkNodes;
  newNodeIds = malloc(sizeof(int) * newNodeIdsCnt);

  for (i = 0; i < crossOverMaskCnt; i++) {
    if (child1->NodeIds[i] != -1) {
      newNodeIds[newNodeIdsUsedCnt] = child1->NodeIds[i];
      newNodeIdsUsedCnt += 1;
    }
  }

  for (i = newNodeIdsUsedCnt; i < newNodeIdsCnt; i++) {
    newNodeIds[i] = -1;
  }

  free(child1->NodeIds);

  child1->NodeIdsUsedCnt = newNodeIdsUsedCnt;
  child1->NodeIdsCnt = newNodeIdsCnt;
  child1->NodeIds = newNodeIds;

  tempBuff1Size += snprintf(tempBuff1+tempBuff1Size,2048-tempBuff1Size,";SECOND CHILD    : ");

  for (i = 0; i < child1->NodeIdsUsedCnt; i++) {
    tempBuff1Size += snprintf(tempBuff1+tempBuff1Size,2048-tempBuff1Size,"[%s] ",problem->Nodes[child1->NodeIds[i]].Name);
  }

  child1->cTextDiff = strdup(tempBuff1);

  _IndividualFix(child0,problem);
  _IndividualFix(child1,problem);

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
  int    i;

  indent = malloc(sizeof(char) * (2 * indentLevel + 1));

  memset(indent,' ',2 * indentLevel);
  indent[2 * indentLevel] = '\0';

  printf("%sAccessNetwork State:\n",indent);
  printf("%s  Nodes: ");

  for (i = 0; i < problemState->NodeIdsUsedCnt; i++) {
    printf("%d ", problemState->NodeIds[i]);
  }

  printf("\n");
  printf("%s  Cost: %.3f\n",indent,problemState->Cost);
  printf("%s  TextDiff: %s\n",indent,problemState->TextDiff);

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

  if (problemState->Cost <= 0) {
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
_IndividualFix(
  Individual* individual,
  const Problem* problem)
{
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

  portAllocationMatrix = malloc(sizeof(Speed*) * problem->cMaxNetworkLevels);

  for (i = 0; i < problem->cMaxNetworkLevels; i++) {
    portAllocationMatrix[i] = malloc(sizeof(Speed) * problem->UsersCnt);
  }

  for (i = 0; i < problem->UsersCnt; i++) {
    portAllocationMatrix[0][i] = problem->Users[i].Speed;
  }

  currLevel = 0;
  currLevelUser = 0;
  currLevelUsersCnt = problem->UsersCnt;
  nextLevelUsersCnt = 0;
  nextLevelNodesAdded = 0;
  savedNodesAdded = 0;

  memset(tempBuff,'\0',2048);
  tempBuffSize = 0;

  for (i = 0; i < individual->NodeIdsUsedCnt; i++) {
    nodeGood = 1;
    nodeSpeed.Download = 0;
    nodeSpeed.Upload = 0;

    /* Extract this large "for" as a function */

    for (j = currLevelUser, k = 0;
	 j < currLevelUsersCnt && k < problem->Nodes[individual->NodeIds[i]].DownPortsNr && nodeGood;
	 j++, k++) {
      if (problem->Nodes[individual->NodeIds[i]].DownPort.Download < portAllocationMatrix[currLevel][j].Download ||
	  problem->Nodes[individual->NodeIds[i]].DownPort.Upload < portAllocationMatrix[currLevel][j].Upload) {
	nodeGood = 0;
      }

      nodeSpeed.Download += portAllocationMatrix[currLevel][j].Download;
      nodeSpeed.Upload += portAllocationMatrix[currLevel][j].Upload;
    }

    if (nodeGood &&
	nodeSpeed.Download <= problem->Nodes[individual->NodeIds[i]].UpPortsNr * problem->Nodes[individual->NodeIds[i]].UpPort.Download &&
	nodeSpeed.Upload <= problem->Nodes[individual->NodeIds[i]].UpPortsNr * problem->Nodes[individual->NodeIds[i]].UpPort.Upload) {
      for (j = 0; j < problem->Nodes[individual->NodeIds[i]].UpPortsNr; j++) {
	portAllocationMatrix[currLevel+1][nextLevelUsersCnt+j].Download = nodeSpeed.Download / problem->Nodes[individual->NodeIds[i]].UpPortsNr;
	portAllocationMatrix[currLevel+1][nextLevelUsersCnt+j].Upload = nodeSpeed.Upload / problem->Nodes[individual->NodeIds[i]].UpPortsNr;
      }

      currLevelUser += problem->Nodes[individual->NodeIds[i]].DownPortsNr;
      nextLevelUsersCnt += problem->Nodes[individual->NodeIds[i]].UpPortsNr;
    } else {
      nextNodeId = _IndividualFindFit(individual,problem,(const Speed**)portAllocationMatrix,currLevel,currLevelUser,currLevelUsersCnt,&nextNodeSpeed);

      for (j = 0; j < problem->Nodes[nextNodeId].UpPortsNr; j++) {
	portAllocationMatrix[currLevel+1][nextLevelUsersCnt+j].Download = nextNodeSpeed.Download / problem->Nodes[nextNodeId].UpPortsNr;
	portAllocationMatrix[currLevel+1][nextLevelUsersCnt+j].Upload = nextNodeSpeed.Upload / problem->Nodes[nextNodeId].UpPortsNr;
      }

      currLevelUser += problem->Nodes[nextNodeId].DownPortsNr;
      nextLevelUsersCnt += problem->Nodes[nextNodeId].UpPortsNr;

      individual->NodeIds[i] = nextNodeId;

      tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,";CHG %3d [%s] : ",i+1,problem->Nodes[nextNodeId].Name);

      for (j = 0; j < individual->NodeIdsUsedCnt; j++) {
	tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problem->Nodes[individual->NodeIds[j]].Name);
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

    if (savedNodesAdded == 1 && i + 1 < individual->NodeIdsUsedCnt) {
      /* more nodes than needed */
      for (j = i + 1; j < individual->NodeIdsUsedCnt; j++) {
	individual->NodeIds[j] = -1;
      }

      individual->NodeIdsUsedCnt = i + 1;

      tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,";RMX %3d         : ",i+2);

      for (j = 0; j < individual->NodeIdsUsedCnt; j++) {
	tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problem->Nodes[individual->NodeIds[j]].Name);
      }

      break;
    }
  }

  if (nextLevelNodesAdded != 1 || savedNodesAdded != 1) {
    /* Fewer nodes than needed */
    while (savedNodesAdded != 1) {
      nextNodeId = _IndividualFindFit(individual,problem,(const Speed**)portAllocationMatrix,currLevel,currLevelUser,currLevelUsersCnt,&nextNodeSpeed);

      for (i = 0; i < problem->Nodes[nextNodeId].UpPortsNr; i++) {
	portAllocationMatrix[currLevel+1][nextLevelUsersCnt+i].Download = nextNodeSpeed.Download / problem->Nodes[nextNodeId].UpPortsNr;
	portAllocationMatrix[currLevel+1][nextLevelUsersCnt+i].Upload = nextNodeSpeed.Upload / problem->Nodes[nextNodeId].UpPortsNr;
      }

      currLevelUser += problem->Nodes[nextNodeId].DownPortsNr;
      nextLevelUsersCnt += problem->Nodes[nextNodeId].UpPortsNr;
      nextLevelNodesAdded += 1;

      individual->NodeIds[individual->NodeIdsUsedCnt] = nextNodeId;
      individual->NodeIdsUsedCnt += 1;

      tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,";APP     [%s] : ",problem->Nodes[nextNodeId].Name);

      for (j = 0; j < individual->NodeIdsUsedCnt; j++) {
	tempBuffSize += snprintf(tempBuff+tempBuffSize,2048-tempBuffSize,"[%s] ",problem->Nodes[individual->NodeIds[j]].Name);
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

  individual->cCost = _IndividualCost(individual,problem);

  diffText = individual->cTextDiff;
  asprintf(&individual->cTextDiff,"%s%s",diffText,tempBuff);
  free(diffText);

  for (i = 0; i < problem->cMaxNetworkLevels; i++) {
    free(portAllocationMatrix[i]);
  }

  free(portAllocationMatrix);
}

int
_IndividualFindFit(
  const Individual* individual,
  const Problem* problem,
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
  validNodeIds = malloc(sizeof(int) * problem->NodesCnt);

  validSpeedsCnt = 0;
  validSpeeds = malloc(sizeof(Speed) * problem->NodesCnt);

  for (i = 0; i < problem->NodesCnt; i++) {
    nodeGood = 1;
    speed.Download = 0;
    speed.Upload = 0;

    for (j = currLevelUser, k = 0;
	 j < currLevelUsersCnt && k < problem->Nodes[i].DownPortsNr && nodeGood;
	 j++,k++) {
      if (problem->Nodes[i].DownPort.Download < portAllocationMatrix[currLevel][j].Download ||
	  problem->Nodes[i].DownPort.Upload < portAllocationMatrix[currLevel][j].Upload) {
	nodeGood = 0;
      }

      speed.Download += portAllocationMatrix[currLevel][j].Download;
      speed.Upload += portAllocationMatrix[currLevel][j].Upload;
    }

    if (nodeGood &&
	speed.Download <= problem->Nodes[i].UpPortsNr * problem->Nodes[i].UpPort.Download &&
	speed.Upload <= problem->Nodes[i].UpPortsNr * problem->Nodes[i].UpPort.Upload) {
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

    printf("Could not find fit individual!\n");
    exit(2);
  }
}
