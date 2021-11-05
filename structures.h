typedef long long int size_canary;
typedef int size_stack;

#define MAX_SIZE 10
#define RISE_V_STACK 10
#define POISON 1984
#define HASH_CONST 7           //TODO DONE добавить два typedefа

const int CAN_PLACE  (sizeof (size_canary)/ sizeof (size_stack));

struct Stack        //Стэк собственной персоной
{
    size_canary canary1 = 0;
    size_canary* canary2 = nullptr;
    size_canary* canary22 = nullptr;

    size_t capacity = 0;      //TODO DONE заменить size capacity на sizet
    size_t ssize = 0;         //TODO сделать название size
    size_stack *data = nullptr;
    size_canary hash_ = 0; //TODO DONE две канарейки
    size_canary hash_head = 0;

    size_canary canary12 = 0;

};

//основные функции для стэка

void StackCtr (Stack* sstack);

void StackPush(Stack *sstack, int value);

int StackPop(Stack *sstack);

void StackDtor(Stack* sstack);

void StackResize(Stack *sstack);

//защита стэка

enum ERRORS_NAMES
{
    NULL_STACK_POINTER = 1,
    STACK_OVERFLOW = 2,
    NULL_DATA_POINTER = 3,     //TODO DONE вручную пронумеровать
    NULL_CANARI_POINTER = 4,
    CANARY1_DAMAGE = 5,
    CANARY2_DAMAGE = 6,
    HASH_DAMAGE = 7,
    HASH_HEAD_DAMAGE = 8
};

int StackOK (Stack *sstack);
void StackDump (Stack *sstack);
void ErrorPrint(int ERROR);
void StackPrint(Stack *sstack);

void FullofPoison (Stack* sstack, int start, int ennd);

size_canary StackHash (Stack *sstack);
size_canary StackHashHead (Stack *sstack);



//для V1 of CPU

int command_compare(char *data1, int length1, char *data2, int length2);

int inf_proc (Stack *S, char user_ch);

void CPU (int COMMAND_NUM, int user_number, Stack *S);

void User_Work(Stack *S);
