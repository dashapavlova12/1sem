#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef double elem_t;
const int signal = 0xBEDABEDA;
const int INITIAL_STACK_CAPACITY = 10;
const elem_t POISON = -666;
const int STACK_OK = 0;
const elem_t CANARY = 42.42;

struct Stack;

int StackPush (struct Stack * stc, elem_t val);

struct Stack * init_stack();

int StackPop (struct Stack * stc, elem_t * val);

int IncreaseStack (struct Stack * stc);

int StackDump (struct Stack * stc);

int StackOk (struct Stack * stc);

int StackDestruct (struct Stack * stc);
