#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
// DO NOT USE ABORT/EXIT

int main()
{
    stack_t stk = {};

    StackElem_t pop_value = 0;

    StackInit(&stk, 8 ON_DEBUG(, "stk", __FILE__, __LINE__));
    StackDump(stk);
    int idx = 0;
    int* point = 0;
    for (idx = 1; idx < 70; idx++)
    {
        StackPush(&stk, idx*2.0);
    }

    for (idx = 0; idx < 30; idx++)
    {
        StackPop(&stk, &pop_value);
    }

    *((int*)&stk) = 5252;
    for (idx = 53; idx > 3; idx--)
        StackPush(&stk, idx*4.9);
    StackDestroy(&stk);
    return 0;
}

