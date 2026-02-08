#include "core/coro_def_internal.h"

#include <stddef.h>

#include "core/coro_def.h"

const size_t kStackFixedSize = 2 << 10;

const size_t kCoroFuncOffset = offsetof(Coro, coro_func);
const size_t kDataOffset = offsetof(Coro, data);
const size_t kStackOffset = offsetof(Coro, call_stack);
const size_t kContextOffset = offsetof(Coro, ctx_buffer);
