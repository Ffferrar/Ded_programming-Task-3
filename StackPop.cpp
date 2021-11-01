#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h >
#include "structures.h"

int StackPop(Stack *sstack)
{
    assert(sstack);
    sstack->ssize--;
    if(StackOK(sstack) != 0)
    {
        StackDump(sstack);
        exit(0);
    }
    int a = sstack->data[sstack->ssize];
    FullofPoison (sstack, sstack->ssize, sstack->ssize);

    return a;
}
