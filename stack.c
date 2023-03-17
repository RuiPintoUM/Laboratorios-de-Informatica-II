#include <stdio.h>
#include <string.h>
#include "stack.h"

STACK *newstack()
{
    STACK *s = malloc(sizeof(STACK));
    s->size = 100;
    s->sp = 0;
    s->values = calloc(100, sizeof(STACK_ELEM));
    return s;
}

void push(STACK *s, STACK_ELEM elem)
{
    if (s->sp == s->size)
    {
        increaseS(s);
    }
    s->values[s->sp] = elem;
    s->sp++;
}

int increaseS(STACK *s)
{
    STACK_ELEM *temp = calloc(s->size * 2, sizeof(STACK_ELEM));
    memcpy(temp, s->values, s->size * sizeof(STACK_ELEM));
    s->size *= 2;
    s->values = temp;
    return 0;
}

STACK_ELEM pop(STACK *s)
{
    if (s->sp == 0)
    {
        fprintf(stderr, "Stack Vazia\n");
        exit(1);
    }
    s->sp--;
    return s->values[s->sp];
}

int isEmpty(STACK *s)
{
    return (s->sp == 0);
}

STACK_ELEM peek(STACK *s)
{
    if (s->sp == 0)
    {
        fprintf(stderr, "Stack Vazia\n");
        exit(1);
    }
    return s->values[s->sp - 1];
}

int debugStack(STACK *s, char *token)
{
    if (strcmp(token, "debugStack") == 0)
    {
        while (!isEmpty(s))
        {
            STACK_ELEM x = pop(s);
            if (x.t == LONG)
            {
                printf("Tipo: Long      Elem: %ld", x.elem.l);
                printf("\n");
            }
            if (x.t == DOUBLE)
            {
                printf("Tipo: Double    Elem: %g", x.elem.d);
                printf("\n");
            }
            if (x.t == CHAR)
            {
                printf("Tipo: Char      Elem: %c", x.elem.c);
                printf("\n");
            }
            if (x.t == STRING)
            {
                printf("Tipo: String    Elem: %s", x.elem.str);
                printf("\n");
            }
            if (x.t == ARRAY)
            {
                printf("Array:");
                printf("\n");
                debugStack(x.elem.arr, token);
            }
        }
    }
    return 0;
}

VARS *initVars()
{
    VARS *arr = malloc(27 * sizeof(STACK_ELEM));
    arr->var[0].t = LONG;
    arr->var[0].elem.l = 10;
    arr->var[1].t = LONG;
    arr->var[1].elem.l = 11;
    arr->var[2].t = LONG;
    arr->var[2].elem.l = 12;
    arr->var[3].t = LONG;
    arr->var[3].elem.l = 13;
    arr->var[4].t = LONG;
    arr->var[4].elem.l = 14;
    arr->var[5].t = LONG;
    arr->var[5].elem.l = 15;
    arr->var[13].t = CHAR;
    arr->var[13].elem.c = '\n';
    arr->var[18].t = CHAR;
    arr->var[18].elem.c = ' ';
    arr->var[23].t = LONG;
    arr->var[23].elem.l = 0;
    arr->var[24].t = LONG;
    arr->var[24].elem.l = 1;
    arr->var[25].t = LONG;
    arr->var[25].elem.l = 2;
    return arr;
}