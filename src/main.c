#include <stdio.h>
#include <assert.h>

#include <core/coro.h>

void GenerateNumbers(Coro* coro, void* data) {
    assert(coro != NULL);
    assert(data != NULL);

    int counter = 0;

    while (!CoroDone(coro)) {
        *(int*)data = counter;
        counter++;
        CoroYield(coro);
    }
}

void PrintNumbers(Coro* coro, void* data) {
    assert(coro != NULL);
    assert(data != NULL);

    while (!CoroDone(coro)) {
        int val = *(int*)data;
        printf("Cur value: %d\n", val);
        CoroYield(coro);
    }
}

int main() {
    int counter = 0;

    Coro* count_coro = CoroCreate(GenerateNumbers, &counter);
    Coro* print_coro = CoroCreate(PrintNumbers, &counter);
    while (counter < 5) {
        CoroResume(count_coro);
        CoroResume(print_coro);
    }

    CoroDestory(count_coro);
    CoroDestory(print_coro);
}
