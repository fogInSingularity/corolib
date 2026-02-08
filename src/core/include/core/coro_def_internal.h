#ifndef CORO_DEF_INTERNAL_H_
#define CORO_DEF_INTERNAL_H_

#include <stddef.h>
#include <stdint.h>

#include "core/coro_def.h"

// rbx, rsp, rbp, r12-r15
// 7 regs
enum { kNSavedRegs = 7 };
typedef struct {
    int64_t saved_regs[kNSavedRegs];
} CoroCtx;

typedef struct Coro {
    CoroFunc coro_func;
    void* data;

    size_t id;
    CoroState state;

    void* call_stack; // NOTE: fixed size
    CoroCtx ctx_buffer;
} Coro;

extern const size_t kStackFixedSize;

extern const size_t kCoroFuncOffset;
extern const size_t kDataOffset;
extern const size_t kStackOffset;
extern const size_t kContextOffset;

#endif // CORO_DEF_INTERNAL_H_
