
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
