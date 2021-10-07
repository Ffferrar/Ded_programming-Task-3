#include <stdio.h>
#include <assert.h>
#include "structures.h"

void StackPush(Stack *sstack, int value)
{
    assert(sstack);
    sstack->data[sstack -> ssize] = value;
    sstack->ssize++;
}
