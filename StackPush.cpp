#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "structures.h"

#define RISE_V_STACK 2

void StackResize(Stack *sstack)
{
    sstack->capacity *= RISE_V_STACK;
    sstack->data = (int*) calloc (sstack->capacity, sizeof(int));
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
