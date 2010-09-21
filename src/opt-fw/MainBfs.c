#include "Bfs/Driver.h"
#include "Problem.h"

int
main()
{
  DriverParams*  driverParams;
  DriverState*   initialState;
  DriverState*   finalState;

  driverParams = DriverParamsAlloc(stdin,"driverParams");
  initialState = DriverStateAlloc(driverParams);

  DriverParamsPrint(driverParams,"driverParams",0);
  DriverStatePrint(driverParams,initialState,"initialState",0);

  finalState = DriverStateGenNext(driverParams,initialState);

  DriverStatePrint(driverParams,finalState,"finalState",0);

  DriverStateFree(driverParams,&finalState);
  DriverStateFree(driverParams,&initialState);
  DriverParamsFree(&driverParams);

  return 0;
}
