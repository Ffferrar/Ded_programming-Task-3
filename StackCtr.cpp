#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h >
#include <math.h>
#include "structures.h"

#define CANARY2_ADRESS sstack->data
#define CANARY22_ADRESS sstack->data + sstack->capacity

#define CANARY1_VALUE 0xDED27BEDDED27BED
#define CANARY12_VALUE 0xBAD19DEDBAD19DED
#define CANARY2_VALUE 0xBED27DEDBED27DED
#define CANARY22_VALUE 0xBAD19DEDBAD19DED

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
    if (sstack == nullptr)
    {
        StackDump(sstack);
    }
    //TODO DONE ��������� �� ������� ���������
    //TODO �������� �������� ������

    sstack->capacity = MAX_SIZE;
    sstack->data = (size_stack*) calloc (MAX_SIZE + 2*CAN_PLACE, sizeof(size_stack));  //������ ������� ��������?
    sstack->ssize = 0;

    //������ ���������

    sstack->canary2 = (size_canary*) (CANARY2_ADRESS);
    sstack->data += CAN_PLACE;
    sstack->canary22 = (size_canary*) (CANARY22_ADRESS);

    FullofPoison (sstack, 0, MAX_SIZE);

    sstack->canary1 = CANARY1_VALUE;   //TODO NOT DONE ������� �������� �������� � ���������
    sstack->canary12 = CANARY12_VALUE;

    *sstack->canary2 = CANARY2_VALUE;  //TODO DONE ��������� �������� ��������� � 2 ����
    *sstack->canary22 = CANARY22_VALUE;
    //TODO ��������� ����� ���������

    sstack->hash_ = StackHash(sstack);
    sstack->hash_head = StackHashHead (sstack);

    if(StackOK(sstack) != 0)
    {
        StackDump(sstack); //TODO DONE ������� ��� exit
    }
}

void StackResize(Stack *sstack)
{
    sstack->capacity += RISE_V_STACK;

    size_stack* resize_data = (size_stack*) calloc (sstack->capacity + 2 * CAN_PLACE, sizeof(size_stack));
    memmove((size_stack*) resize_data + CAN_PLACE, (size_stack*) sstack->data, sstack->capacity*sizeof(size_stack) );
    sstack->data = resize_data + CAN_PLACE;

    /*sstack->data = (int*) calloc (sstack->capacity + 2 * (sizeof(long long int) / sizeof(int)), sizeof(int));*/ //TODO DONE ����� ������������� ���������

    FullofPoison (sstack, sstack->ssize, sstack->capacity);

    sstack->canary2 = (size_canary*) (resize_data);     //TODO �������� ������ ��� canary2, DONE ������� ��� ������.
    sstack->canary22 = (size_canary*) (CANARY22_ADRESS);

    *sstack->canary2 = CANARY2_VALUE;
    *sstack->canary22 = CANARY22_VALUE;

    sstack->hash_head = StackHashHead (sstack);

}

void StackPush(Stack *sstack, size_stack value)
{
    if(StackOK(sstack) != 0)
    {
        StackDump(sstack);

    }

    if ( sstack->ssize == sstack->capacity - 1 )
    {
       StackResize(sstack);
    }
    sstack->data[sstack -> ssize] = value;
    sstack->ssize++;
    sstack->hash_ = StackHash(sstack);
    sstack->hash_head = StackHashHead(sstack);

}

size_stack StackPop(Stack *sstack)
{
    size_stack verificator = StackOK(sstack);
    if(verificator != 0)
    {
        StackDump(sstack);
        ErrorPrint(verificator);   //���� ����� , ���� � ����� ��� ����� ����������
        return verificator;
    }
    sstack->ssize--;
    int a = sstack->data[sstack->ssize];
    FullofPoison (sstack, sstack->ssize, sstack->ssize);

    sstack->hash_ = StackHash(sstack);
    sstack->hash_head = StackHashHead(sstack);
    return a;
}

//���������� �����
void StackDtor(Stack* sstack)
{
    assert(sstack);
    memset(sstack -> data, 0xF0, sstack -> ssize);
    free (sstack -> canary2); //�������� ��� �������
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

        case STACK_OVERFLOW: printf("ERROR: Size of stack > Capacity of stack\n\n");
                             break;

        case NULL_DATA_POINTER: printf("ERROR: Pointer to data is NULL\n\n");
                                break;

        case NULL_CANARI_POINTER: printf("ERROR: Pointer to canary2 is NULL\n\n");
                                  break;

        case CANARY1_DAMAGE: printf("ERROR: Main stack information is damaged. Canary ALLERT\n\n");
                             break;

        case CANARY2_DAMAGE: printf("ERROR: Stack data is damaged. Canary ALLERT\n\n");
                             break;

        case HASH_DAMAGE: printf("ERROR: Stack hash value has been changed\n\n");
                          break;

        case HASH_HEAD_DAMAGE: printf("ERROR: Stack head hash value has been changed\n\n");
                          break;

        default: break;
    }

}

//������� ������ ��������� � �����
void StackPrint(Stack *sstack)
{
    printf("Stack data is printed...\n");
    for (size_t i = 0; i < sstack->ssize; i++)
    {
        printf("data[%d]: %d\n", i, sstack->data[i]);
    }
}                                                                //TODO DONE (��� �������) ��� ���� � ����� � ���� �������

void StackDump (Stack *sstack)
{
    printf("\nDump was called. Please, check your actions:\n");
    printf("Current stack:\n\tStack size %d\n\tStack capacity %d\n\n", sstack->ssize, sstack->capacity);

    if (sstack->data != nullptr && sstack->canary1 == 0xDED27BEDDED27BED && *sstack->canary2 == 0xBED27DEDBED27DED)
    {
        StackPrint(sstack);             //TODO DONE �������� ������ � ��� ������, ���� ��������� ���� � ��������� �� data �� ����� ����
    }

    ErrorPrint( StackOK(sstack) );
}

//����������� �����
size_stack StackOK (Stack *sstack)
{
    if (sstack == 0)
    {
        return NULL_STACK_POINTER;
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

    if (sstack->canary1 != 0xDED27BEDDED27BED || sstack->canary12 != 0xBAD19DEDBAD19DED)
    {
        return CANARY1_DAMAGE;
    }

    if (*sstack->canary2 != 0xBED27DEDBED27DED || *sstack->canary22 != 0xBAD19DEDBAD19DED)
    {
        return CANARY2_DAMAGE;
    }

    if (StackHash (sstack) != sstack->hash_)
    {
        return HASH_DAMAGE;
    }

    if (StackHashHead(sstack) != sstack->hash_head)
    {
        return HASH_HEAD_DAMAGE;
    }
    return 0;
}

//������� �������� ���� �����
size_canary StackHash (Stack *sstack)    //TODO DONE ������� ��� ��� ������, �������� ��� ����� ������� � ������
{
    long long int hassh = 0;
    for (int i = 0; i < sstack->ssize; i++)
    {
         hassh += sstack->data[i] * (long long int) pow(HASH_CONST, i);
    }

    return hassh;
}


size_canary StackHashHead (Stack *sstack)
{
    size_canary hassh = 0;
    hassh = sstack->ssize + sstack->capacity + sstack->canary1 + sstack->canary12 + (size_canary) sstack->data + sstack->hash_;
    return hassh;
}

