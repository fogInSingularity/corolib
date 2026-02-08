#ifndef CORO_DEF_H_
#define CORO_DEF_H_

typedef struct Coro Coro;

typedef enum {
    kCoroStateRunning,
    kCoroStateFinished,
    kCoroStateSuspended,
} CoroState;

typedef void (*CoroFunc) (Coro* coro, void* data);

#endif // CORO_DEF_H_
