#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h >
#include "structures.h"

int StackPop(Stack *sstack)
{
    assert(sstack);
    sstack->ssize--;
    return sstack->data[sstack->ssize];
}
