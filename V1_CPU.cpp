#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

//while spec symb: scanf command

int command_compare(char *data1, int length1, char *data2, int length2)
{
    int spec = 0;
    if (length1 == length2)
    {
        for (int i = 0; i < length1; i++)
        {

            if (data1[i] == data2[i])
            {
                spec++;
            }

            else
            {
                break;
            }
        }

        if (spec==length1)
        {
            return 1;
        }

        else
        {
            return 0;
        }
    }

    else
    {
        return 0;
    }
}

int inf_proc (Stack *S, char user_ch)    //считываем сюда команду, закидываем в массив и проверяем с командами
{
    char PUSH_command[4] = {'P','u','s','h'};
    int len_push = 4;

    char POP_command[] = {'P','o','p'};
    int len_pop = 3;

    char ADD_command[] = {'A','d','d'};
    int len_add = 3;

    char MUL_command[] = {'M','u','l'};
    int len_mul = 3;

    char SUB_command[] = {'S','u','b'};
    int len_sub = 3;

    int i = 0;


    /*if (user_ch == '!')
    {
        return 0;
    } */

    //char *user_data = (char*) calloc (30, sizeof(char));  //TODO^ проверять размер массива!!!
    char user_data[30]={};
    user_data[0] = user_ch;

    while (user_ch != '\n')
    {
        i++;
        scanf("%c", &user_ch);
        if (user_ch == '\n')
        {
            break;
        }
        user_data[i] = user_ch;
    }

    int user_number = 0;
    //теперь вызовем сами команды

    if ( command_compare (user_data, i, PUSH_command, 4) )
    {
        printf ("Enter the number: ");

        scanf("%d", &user_number);

        CPU(0, user_number, S);
    }

    else if ( command_compare (user_data, i, POP_command, 3) )
    {
        CPU(1, user_number, S);
    }

    else if ( command_compare (user_data, i, ADD_command, 3) )
    {
        CPU(2, user_number, S);
    }

    else if ( command_compare (user_data, i, MUL_command, 3) )
    {
        CPU(3, user_number, S);
    }

    else if ( command_compare (user_data, i, SUB_command, 3) )
    {
        CPU(4, user_number, S);
    }

    else
    {
        printf("\nYour command is NOT DEFINED. Please press ENTER to continue\n");
        scanf("%c", &user_ch);//считали \n
    }

}

void CPU (int COMMAND_NUM, int user_number, Stack *S) // вызываем сами команды    называется ИНТЕРПРЕТАТОР
{

    switch (COMMAND_NUM)
    {
        case 0: StackPush(S, user_number);
                break;

        case 1: printf("%d\n", StackPop(S));
                break;

        case 2: StackPush(S, StackPop(S) + StackPop(S));
                break;

        case 3: StackPush(S, StackPop(S) * StackPop(S));
                break;

        case 4: StackPush(S, StackPop(S) - StackPop(S));
                break;
    }
}

void User_Work(Stack *S) //здесь по циклу вызываем CPU и inf_proc
{
    printf("\nPlease, enter your commands\nIf you want to finish programm, enter !\n");
    printf ("Enter the command: ");
    char user_ch;
    scanf("%c", &user_ch);
    while (user_ch != '!')
    {
       inf_proc(S, user_ch);
       scanf("%c", &user_ch);//считали \n

       printf ("Enter the command: ");
       scanf("%c", &user_ch);
    }
}
