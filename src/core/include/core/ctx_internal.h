#ifndef CTX_INTERNAL_H_
#define CTX_INTERNAL_H_

#include "core/coro_def_internal.h"

void SetupCtx(Coro* coro);
void SwapCtx(CoroCtx* other);

#endif // CTX_INTERNAL_H_
