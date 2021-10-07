#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

void StackCtr (Stack *sstack, int capacity)
{
    //memset(sstack->data, 0, sizeof(sstack->data)); segfault
    sstack->data = (int*) calloc (capacity, sizeof(int));
    sstack->ssize = 0;
    sstack->capacity = capacity;
}
