#ifndef _DRIVER_H
#define _DRIVER_H

#include <stdio.h>

#include "Problem.h"
#include "Method.h"

struct DriverParams;
typedef struct DriverParams DriverParams;

DriverParams*  DriverParamsAlloc(
                 FILE* fin);
void           DriverParamsFree(
                 DriverParams** driverParams);
void           DriverParamsPrint(
                 const DriverParams* driverParams,
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
                 int indentLevel);
int            DriverStateIsValid(
                 const DriverParams* driverParams,
                 const DriverState* driverState);

#endif
