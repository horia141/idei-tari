#include "Driver.h"
#include "Method.h"
#include "Problem.h"

int
main()
{
  DriverParams*   driverParams;
  DriverState*    initialState;
  DriverState*    finalState;

  driverParams = DriverParamsAlloc(stdin);
  initialState = DriverStateAlloc(driverParams);

  DriverParamsPrint(driverParams,0);
  DriverStatePrint(driverParams,initialState,0);

  finalState = DriverStateGenNext(driverParams,initialState);

  DriverStatePrint(driverParams,finalState,0);

  DriverStateFree(driverParams,&finalState);
  DriverStateFree(driverParams,&initialState);
  DriverParamsFree(&driverParams);

  return 0;
}
