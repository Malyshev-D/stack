#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
// DO NOT USE ABORT/EXIT

int main()
{
    stack_t stk = {};

    if (&stk == nullptr)
    {
        printf("sth wrong\n");
        return 0;
    }
    StackElem_t pop_value = 0;

    StackInit(&stk, 8 ON_DEBUG(, "stk", __FILE__, __LINE__));
    for (int i = 1; i < 70; i++)
    {
        StackPush(&stk, i*2.5);
    }
    StackDump(stk);

    for (int j = 0; j< 30; j++)
    {
        StackPop(&stk, &pop_value);
    }
    StackDestroy(&stk);
    return 0;
}

