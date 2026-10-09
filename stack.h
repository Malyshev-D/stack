#ifndef MEOW
#define MEOW

#ifdef STACK_DEBUG
#define ON_DEBUG(...) __VA_ARGS__
#else
#define ON_DEBUG(...)
#endif

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef double StackElem_t;
const size_t elem_size = sizeof(StackElem_t);
enum error_value {empty, zerostack, zerodata, negsize, negcapacity, overflow};

struct stack_t
{
    ON_DEBUG(
    const char*      name;
    const char*      file;
    int              line;
    enum error_value error;)

    StackElem_t* data;
    int          size;
    int          capacity;
};

enum error_value StackInit   (stack_t* stk, int          capacity ON_DEBUG(,const char* name, const char* file, int line));
enum error_value StackPush   (stack_t* stk, StackElem_t  value);// возвращает код ошибки, если неверно (в не дебаг моде)
enum error_value StackPop    (stack_t* stk, StackElem_t* value);
void             StackDestroy(stack_t* stk);
void             StackDump   (stack_t  stk);
ON_DEBUG(
enum error_value StackVerify (stack_t* stk);)


#endif
