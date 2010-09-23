#ifndef _DRIVER_H
#define _DRIVER_H

#include <stdio.h>

#include "Opt/Method.h"
#include "Problem.h"

struct DriverParams;
typedef struct DriverParams DriverParams;

DriverParams*  DriverParamsAlloc(
		 FILE* fin,
		 const char* name);
void           DriverParamsFree(
                 DriverParams** driverParams);
void           DriverParamsPrint(
                 const DriverParams* driverParams,
		 const char* name,
                 int indentLevel);
int            DriverParamsIsValid(
                 const DriverParams* driverParams);

struct DriverState;
typedef struct DriverState DriverState;

DriverState*   DriverStateAlloc(
                 const DriverParams* driverState);
DriverState*   DriverStateGenNext(
                 const DriverParams* driverParams,
                 const DriverState* initState);
void           DriverStateFree(
                 const DriverParams* driverParams,
                 DriverState** driverState);
void           DriverStatePrint(
                 const DriverParams* driverParams,
                 const DriverState* driverState,
		 const char* name,
                 int indentLevel);
int            DriverStateIsValid(
                 const DriverParams* driverParams,
                 const DriverState* driverState);

#endif
