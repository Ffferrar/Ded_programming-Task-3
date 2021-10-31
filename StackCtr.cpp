#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

void FullofPoison (Stack* sstack, int start, int ennd)
{
    for (int i = start; i < ennd; i++)
    {
        sstack->data[i] = POISON;
    }
}

void StackCtr (Stack* sstack)
{
    //memset(sstack->data, 0, sizeof(sstack->data)); segfault
    sstack->data = (int*) calloc (MAX_SIZE + 2 * (sizeof(long long int) / sizeof(int)), sizeof(int));  //почему столько выделяем?
    sstack->capacity = MAX_SIZE;
    sstack->ssize = 0;

    FullofPoison (sstack, 0, MAX_SIZE - 1);

    //ставим канарейки

    sstack->canary1 = (long long int*) (sstack->data);
    sstack->canary2 = (long long int*) (sstack->data + sizeof(long long int) / sizeof(int) + MAX_SIZE); // TODO!!!

    *sstack->canary1 = 0xDED27BED;
    *sstack->canary2 = 0xBED27DED;
}
