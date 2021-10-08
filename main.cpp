#include <stdio.h>
#include "structures.h"

int main()
{
    int k = 10;
    Stack S;
    StackCtr(&S, 10);
    for (int i=0; i<150; i++)
    {
        StackPush(&S, i);
    }

    printf("%d", StackPop(&S) );
    return 0;
}
