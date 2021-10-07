#include <stdio.h>
#include "structures.h"

int StackPop(Stack *sstack)
{

    sstack->ssize--;
    return sstack->data[sstack->ssize];

}
