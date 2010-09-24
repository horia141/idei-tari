#ifndef _CROSSOVER_H
#define _CROSSOVER_H

#include <stdio.h>

struct CrossOverParams;
typedef struct CrossOverParams CrossOverParams;

CrossOverParams*  CrossOverParamsAlloc(
                    FILE* fin,
                    const char* name);
void              CrossOverParamsFree(
                    CrossOverParams** crossOverParams);
void              CrossOverParamsPrint(
                    const CrossOverParams* crossOverParams,
                    const char* name,
                    int indentLevel);
int               CrossOverParamsIsValid(
                    const CrossOverParams* crossOverParams);

void              GenerateCrossOverMask(
                    const CrossOverParams* crossOverParams,
                    int crossOverMaskCnt,
                    int* crossOverMask);

#endif
