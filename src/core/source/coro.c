#include "core/coro.h"

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "core/coro_def_internal.h"
#include "core/ctx_internal.h"

static size_t CoroGetNextId() {
    static size_t id_counter = 0;
    return id_counter++;
}

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

// should not be placed in include
void CoroFuncTrampoline(CoroCtx* ctx) {
    Coro* coro = container_of(ctx, Coro, ctx_buffer);   

    coro->coro_func(coro, coro->data);

    // assert(!"Should not reach this point");
}

// should not be placed in include
void CoroExit(Coro* coro) {
#if defined (CORO_SOFT_FALL)
    CoroYield(coro);
#else 
    (void)coro;
    fprintf(stderr, "Coroutine execution reached %s\n", __func__);
    abort();
#endif // CORO_SOFT_FALL
}

Coro* CoroCreate(CoroFunc coro_func, void* data) {
    Coro* coro = calloc(1, sizeof(Coro));
    if (coro == NULL) { return NULL; }

    coro->call_stack = calloc(1, kStackFixedSize);
    if (coro->call_stack == NULL) {
        free(coro);

        return NULL;
    }
    memset(&coro->ctx_buffer, 0, sizeof(coro->ctx_buffer));

    coro->coro_func = coro_func;
    coro->data = data;

    coro->id = CoroGetNextId();
    coro->state = kCoroStateSuspended;

    SetupCtx(coro);

    return coro;
}

void CoroDestory(Coro* coro) {
    assert(coro != NULL);

    free(coro->call_stack);
    free(coro);
}

void CoroYield(Coro* coro) {
    assert(coro != NULL);

    coro->state = kCoroStateSuspended;

    SwapCxt(&coro->ctx_buffer);
}

void CoroResume(Coro* coro) {
    assert(coro != NULL);

    coro->state = kCoroStateRunning;

    SwapCxt(&coro->ctx_buffer);
}

CoroState CoroCurrentState(Coro* coro) { return coro->state; }
_Bool CoroDone(Coro* coro) { return coro->state == kCoroStateFinished; }
void CoroStop(Coro* coro) { coro->state = kCoroStateFinished; }
size_t CoroId(Coro* coro) { return coro->id; }
