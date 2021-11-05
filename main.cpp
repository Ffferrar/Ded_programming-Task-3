#include <stdio.h>
#include "structures.h"

int main()
{
    /*int k = 10;
    Stack S;
    StackCtr(&S, 10);
    for (int i=0; i<150; i++)
    {
        StackPush(&S, i);
    }

    printf("%d", StackPop(&S) ); */
    int Start_Var = 0;
    printf("\nKozhanov Gleb, B05-120\n");
    printf("\nThe Stack & CPU project\n\n");

    printf("If You want to work with CPU, ENTER 1\nElse ENTER 0: ");
    scanf("%d", &Start_Var);
    char trash;          //TODO инициализировать переменные
    scanf("%c", &trash);

    Stack S = {};
    Stack f = {};
    switch (Start_Var)
    {
        case 0: StackCtr(&S);
                //printf("%d %d\n", S.canary2, S.data);

                for (int i=0;i<12;i++){
                    StackPush(&S, 10);
                }
                //printf("%d %d\n", S.canary2, S.data);
                for (int i=0;i<12;i++){
                    printf("%d\n", StackPop(&S));
                }

                //StackDtor(&S);
                /*StackPush(&S, 10);
                S.data[0] = 1;
                StackPop(&S);
                StackDtor(&S);*/
                break;

        case 1: StackCtr(&S); //вызываю функцию для реализации всякого

                User_Work(&S);
                break;

        default: printf("main(): ERROR: Start_Var = %d\n", Start_Var);
                return 1;
    }
    return 0;
}
