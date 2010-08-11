#ifndef _CROSSOVER_H
#define _CROSSOVER_H

struct CrossOverParams;
typedef struct CrossOverParams CrossOverParams;

CrossOverParams*  CrossOverParamsAlloc();
void              CrossOverParamsFree(
                    CrossOverParams** crossOverParams);
void              CrossOverParamsPrint(
                    const CrossOverParams* crossOverParams,
                    int indentLevel);
int               CrossOverParamsIsValid(
                    const CrossOverParams* crossOverParams);
const char*       CrossOverParamsName(
                    const CrossOverParams* crossOverParams);

void              GenerateCrossOverMask(
                    int crossOverMaskCnt,
                    int* crossOverMask,
                    const CrossOverParams* crossOverParams);

#endif
