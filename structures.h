#define MAX_SIZE 10
#define RISE_V_STACK 10
#define POISON 1984
struct Stack        //Стэк собственной персоной
{
    int capacity;
    int *data;
    int ssize;
    long long int *canary1;
    long long int *canary2;
};

//основные функции для стэка

void StackCtr (Stack *sstack);

void StackPush(Stack *sstack, int value);

int StackPop(Stack *sstack);

void StackDctor(Stack* sstack);

//защита стэка

int StackOK (Stack *sstack);
void StackDump (Stack *sstack, int mistake);
void FullofPoison (Stack* sstack, int start, int ennd);

//для V1 of CPU

int command_compare(char *data1, int length1, char *data2, int length2);

int inf_proc (Stack *S, char user_ch);

void CPU (int COMMAND_NUM, int user_number, Stack *S);

void User_Work(Stack *S);
