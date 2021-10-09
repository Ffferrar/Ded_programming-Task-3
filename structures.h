
struct Stack
{
    int capacity;
    int *data;
    int ssize;
};

void StackCtr (Stack *sstack, int capacity);

void StackPush(Stack *sstack, int value);

int StackPop(Stack *sstack);

void StackDctor();

int command_compare(char *data1, int length1, char *data2, int length2);

int inf_proc (Stack *S, char user_ch);

void CPU (int COMMAND_NUM, int user_number, Stack *S);

void User_Work(Stack *S);
