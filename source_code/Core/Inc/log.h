#ifndef __LOG_H__
#define __LOG_H__

#include "main.h"
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

void Log_Init(void);
int8_t Log_Printf(char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
