#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h >
#include "structures.h"

int StackOK (Stack *sstack)
{
    if (sstack == 0)
    {
        return NULL_STACK_POINTER;
    }

    if (sstack->ssize < 0)
    {
        return STACK_UNDERFLOW;
    }

    if (sstack->capacity <0)
    {
        return NEGATIVE_CAPACITY;
    }

    if (sstack->capacity < sstack->ssize)
    {
        return STACK_OVERFLOW;
        //throw ("ERROR: Size > Capacity);
    }

    if (sstack->data == 0)
    {
        return NULL_DATA_POINTER;
    }

    if (sstack->canary2 == 0)
    {
        return NULL_CANARI_POINTER;
    }

    if (sstack->canary1 != 0xDED27BED)
    {
        return CANARY1_DAMAGE;
    }

    if (*sstack->canary2 != 0xBED27DED)
    {
        return CANARY2_DAMAGE;
    }
    return 0;
}
