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
    char trash;
    scanf("%c", &trash);
    switch (Start_Var)
    {
        case 0: break;

        case 1: Stack S;
                StackCtr(&S, 10); //������� ������� ��� ���������� �������

                User_Work(&S);
                break;

        default: printf("main(): ERROR: Start_Var = %d/n", Start_Var);
                return 1;
    }
    return 0;
}
