#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h >
#include <math.h>
#include "structures.h"

void FullofPoison (Stack* sstack, int start, int ennd)
{
    for (int i = start; i < ennd+1; i++)         //+1 ������ ��� ���� ������ ��������� ��� ������ ��� start==end
    {
        sstack->data[i] = POISON;
    }

}

// ����������� �����
void StackCtr (Stack* sstack)
{

    //memset(sstack->data, 0, sizeof(sstack->data)); segfault
    sstack->capacity = MAX_SIZE;
    sstack->data = (int*) calloc (MAX_SIZE + 2 * (sizeof(long long int) / sizeof(int)), sizeof(int));  //������ ������� ��������?
    sstack->ssize = 0;


    //������ ���������

    sstack->canary2 = (long long int*) (sstack->data);
    sstack->data = sstack->data + (sizeof(long long int) / sizeof(int));

    FullofPoison (sstack, 0, MAX_SIZE);

    sstack->canary1 = 0xDED27BED;
    *sstack->canary2 = 0xBED27DED;

    sstack->hash_ = StackHash(sstack);

    if(StackOK(sstack) != 0)
    {
        StackDump(sstack);
        exit(0);
    }
}

void StackResize(Stack *sstack)
{

    int safe_cap = sstack->capacity;
    sstack->capacity += RISE_V_STACK;
    sstack->data = (int*) calloc (sstack->capacity, sizeof(int));

    FullofPoison (sstack, safe_cap, sstack->capacity - 1);

    sstack->canary2 = (long long int*) (sstack->data - sizeof(long long int)/sizeof(int) );

    sstack->canary1 = 0xDED27BED;
    *sstack->canary2 = 0xBED27DED;
}

void StackPush(Stack *sstack, int value)
{
    if(StackOK(sstack) != 0)
    {
        StackDump(sstack);
        exit(0);
    }

    if ( sstack->ssize == sstack->capacity - 1 )
    {
       StackResize(sstack);
    }
    sstack->data[sstack -> ssize] = value;
    sstack->ssize++;
    sstack->hash_ = StackHash(sstack);

}

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

    sstack->hash_ = StackHash(sstack);

    return a;
}

//���������� �����
void StackDtor(Stack* sstack)
{
    assert(sstack);
    memset(sstack -> data, 0xF0, sstack -> ssize);
    free (sstack -> data);
    free (sstack -> canary2);
    sstack -> ssize = -1;
    sstack->canary1 = 0;
}

//������� ������ ������
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

        case HASH_DAMAGE: printf("ERROR: Stack's hash value has been changed\n\n");
                          break;
        default: break;
    }

}

//������� ������ ��������� � �����
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

//����������� �����
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

    if (StackHash (sstack) != sstack->hash_)
    {
        return HASH_DAMAGE;
    }
    return 0;
}

//������� �������� ���� �����
long long int StackHash (Stack *sstack)
{
    long long int hassh = 0;
    for (int i = 0; i < sstack->ssize; i++)
    {
         hassh += sstack->data[i] * (long long int) pow(HASH_CONST, i);
    }

    return hassh;
}

