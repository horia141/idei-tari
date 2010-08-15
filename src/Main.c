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
  DriverStatePrint(initialState,0);

  finalState = DriverStateRun(initialState,driverParams);

  DriverStatePrint(finalState,0);

  DriverParamsFree(&driverParams);
  DriverStateFree(&initialState);
  DriverStateFree(&finalState);

  return 0;
}
