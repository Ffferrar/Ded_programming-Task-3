#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h >
#include "structures.h"

void StackDctor(Stack* sstack)
{
    assert(sstack);
    memset(sstack -> data, 0xF0, sstack -> ssize);
    free (sstack -> data);
    sstack -> ssize = -1;

}
