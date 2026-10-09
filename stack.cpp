#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

enum error_value StackInit (stack_t* stk, int capacity ON_DEBUG(,const char* name, const char* file, int line))
{
    stk->data = (StackElem_t*)calloc(capacity, elem_size);
    stk->capacity = capacity;

    ON_DEBUG(
    stk->name = name;
    stk->file = file;
    stk->line = line;
    stk->error = empty;)

    ON_DEBUG(return StackVerify(stk);)
    return empty;
}

enum error_value StackPush(stack_t* stk, StackElem_t value)
{
    ON_DEBUG(
    if (StackVerify(stk) != empty)
        return stk->error;
    )ц

    if (stk->size == stk->capacity)
    {
        stk->data = (StackElem_t*)realloc((void*)(stk->data), (stk->capacity * 2 * elem_size));
        if (stk->data == nullptr)
            return zerodata;
        stk->capacity *= 2;
    }
    stk->data[stk->size] = value;
    stk->size++;

    ON_DEBUG(return StackVerify(stk);)
    return empty;
}

enum error_value StackPop(stack_t* stk, StackElem_t* value)
{
    ON_DEBUG(
    if (StackVerify(stk) != empty)
        return stk->error;
    )
    stk->size--;
    *value = stk->data[stk->size];
    stk->data[stk->size] = 0;

    if (2 * stk->size < stk->capacity && stk->capacity % 2 == 0)
    {
        stk->data = (StackElem_t*)realloc((void*)(stk->data), (stk->capacity * elem_size) / 2);
        if (stk->data == nullptr)
            return zerodata;
        stk->capacity /= 2;
    }

    ON_DEBUG(return StackVerify(stk);)
    return empty;
}

void StackDestroy(stack_t* stk)
{
    StackDump(*stk);
    if (stk != nullptr && stk->data != nullptr)
    {
        stk->size = stk->capacity = 0;
        free(stk->data);
    }
    StackDump(*stk);
}

ON_DEBUG(
enum error_value StackVerify(stack_t* stk)
{
    // ошибка найдена до вызова
    if (stk->error != empty)
    {
        StackDump(*stk);
        return stk->error;
    }
    // диагностика ошибок
    if (stk == nullptr)
    {
        stk->error = zerostack;
        StackDump(*stk);
        return zerostack;
    }
    if (stk->data == nullptr)
    {
        stk->error = zerodata;
        StackDump(*stk);
        return zerodata;
    }
    if (stk->size < 0)
    {
        stk->error = negsize;
        StackDump(*stk);
        return negsize;
    }
    if (stk->capacity < 0)
    {
        stk->error = negcapacity;
        StackDump(*stk);
        return negcapacity;
    }
    if (stk->size > stk->capacity)
    {
        stk->error = overflow;
        StackDump(*stk);
        return overflow;
    }
    return empty;
})

void StackDump(stack_t stk)
{
    ON_DEBUG(
    printf(ANSI_COLOR_RED);
    switch(stk.error)
    {
        case zerostack:
            printf("STACK POINTER IS NULL\n");
        case zerodata:
            printf("DATA POINTER IS NULL\n");
            break;
        case negsize:
            printf("SIZE IS LESS THAN ZERO\n");
            break;
        case negcapacity:
            printf("CAPACITY IS LESS THAN ZERO\n");
            break;
        case overflow:
            printf("CAPACITY IS LESS THAN SIZE\n");
            break;
    }
    printf(ANSI_COLOR_YELLOW "Stack \"%s\" [%p] created at %s:%d\n" ANSI_COLOR_RESET,
    stk.name, stk.data, stk.file, stk.line);
    )
    // печать стека обычная
    printf("elements:");
    for (int idx = 0; idx < stk.size; idx++)
    {
        if (idx % 10 == 0)
        {
            putchar('\n');
        }
        printf("<%lg> ", stk.data[idx]);
    }
    putchar('\n');
    printf("size: %d\ncapacity: %d\n\n",
    stk.size, stk.capacity);
}
