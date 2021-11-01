#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h >
#include "structures.h"

void ErrorPrint(int ERROR)
{
    switch (ERROR)
    {
        case NULL_STACK_POINTER: printf("ERROR: Pointer of stack structure is NULL\n\n");
                                 break;

        case STACK_UNDERFLOW: printf("ERROR: Size of stack is negative\n\n");
                              break;

        case NEGATIVE_CAPACITY: printf("ERROR: Capacity of stack is negative\n\n");
                                break;

        case STACK_OVERFLOW: printf("ERROR: Size of stack > Capacity of stack\n\n");
                             break;

        case NULL_DATA_POINTER: printf("ERROR: Pointer of data is NULL\n\n");
                                break;

        case NULL_CANARI_POINTER: printf("ERROR: Pointer of canary2 is NULL\n\n");
                                  break;

        case CANARY1_DAMAGE: printf("ERROR: Main stack information is damaged. Canary ALLERT\n\n");
                             break;

        case CANARY2_DAMAGE: printf("ERROR: Data of stack is damaged. Canary ALLERT\n\n");
                             break;
    }

}

void StackPrint(Stack *sstack)
{
    Stack sstack_copy;
    StackCtr(&sstack_copy);
    sstack_copy = *sstack;
    printf("Stack data is printed...\n");
    for (int i = 0; i < sstack_copy.ssize; i++)
    {
        printf("data[%d]: %d\n", i, sstack_copy.data[i]);
    }
}

void StackDump (Stack *sstack)
{
    printf("\nDump was called. Please, check your actions:\n");
    printf("Current stack:\n\tStack size %d\n\tStack capacity %d\n\n", sstack->ssize, sstack->capacity);

    StackPrint(sstack);
    ErrorPrint( StackOK(sstack) );
}

