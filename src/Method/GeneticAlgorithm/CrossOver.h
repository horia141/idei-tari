#ifndef _CROSSOVER_H
#define _CROSSOVER_H

#include <stdio.h>

struct CrossOverParams;
typedef struct CrossOverParams CrossOverParams;

CrossOverParams*  CrossOverParamsAlloc(
                    FILE* fin);
void              CrossOverParamsFree(
                    CrossOverParams** crossOverParams);
void              CrossOverParamsPrint(
                    const CrossOverParams* crossOverParams,
                    int indentLevel);
int               CrossOverParamsIsValid(
                    const CrossOverParams* crossOverParams);

void              GenerateCrossOverMask(
                    int crossOverMaskCnt,
                    int* crossOverMask,
                    const CrossOverParams* crossOverParams);

#endif
