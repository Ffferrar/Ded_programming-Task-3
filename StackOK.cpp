#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h >
#include "structures.h"

int StackOK (Stack *sstack)
{
    if (sstack == 0)
    {
        throw ("ERROR: Stack pointer is NULL");
    }

    if (sstack->ssize < 0)
    {
        throw ("ERROR: Size of stack is negative");
    }

    if (sstack->capacity <0)
    {
        throw ("ERROR: Capacity of stack is negative");
    }

    if (sstack->capacity < sstack->ssize)
    {
        throw ("ERROR: Size < Capacity);
    }

    if (sstack->data == 0)
    {
        throw ("ERROR: Data pointer is NULL");
    }

    if (sstack->canary2 == 0)
    {
        throw ("ERROR: Canary2 pointer is NULL");
    }

    if (sstack->canary1 != 0xDED27BED)
    {
        throw ("ERROR: Main stack information is damaged. Canary ALLERT");
    }

    if (*sstack->canary2 != 0xBED27DED)
    {
        throw ("ERROR: Data of stack is damaged. Canary ALLERT");
    }
}
