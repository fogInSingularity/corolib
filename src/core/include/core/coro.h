#ifndef CORO_H_
#define CORO_H_

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#include <stddef.h>

#include "core/coro_def.h"

Coro* CoroCreate(CoroFunc coro_func, void* data);
void CoroDestory(Coro* coro);

void CoroYield(Coro* coro);
void CoroResume(Coro* coro);

CoroState CoroCurrentState(Coro* coro);
_Bool CoroDone(Coro* coro);
void CoroStop(Coro* coro);
size_t CoroId(Coro* coro);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // CORO_H_
