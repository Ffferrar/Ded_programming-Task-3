#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "structures.h"

void StackResize(Stack *sstack)
{
    int safe_cap = sstack->capacity;
    sstack->capacity += RISE_V_STACK;
    sstack->data = (int*) calloc (sstack->capacity, sizeof(int));

    FullofPoison (sstack, safe_cap, sstack->capacity - 1);

    sstack->canary1 = (long long int*) (sstack->data);
    sstack->canary2 = (long long int*) (sstack->data + sizeof(long long int) / sizeof(int) + sstack->capacity);

    *sstack->canary1 = 0xDED27BED;
    *sstack->canary2 = 0xBED27DED;
}

void StackPush(Stack *sstack, int value)
{
    assert(sstack);
    if ( sstack->ssize == sstack->capacity - 1 )
    {
       StackResize(sstack);
    }
    sstack->data[sstack -> ssize] = value;
    sstack->ssize++;
}
