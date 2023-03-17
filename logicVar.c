#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "logicVar.h"
#include "arraysStrings.h"

int opsG3(STACK *s, char *token, VARS *arr)
{
    return isEqual(s, token) || negate(s, token) || shortcutAnd(s, token) || shortcutOr(s, token) || ifThenElse(s, token) ||
           isHigher(s, token) || isLower(s, token) || putLower(s, token) || putHigher(s, token) || variable(s, token, arr);
}

_Bool truthValue(STACK_ELEM x)
{
    bool r = true;
    if (x.t == LONG)
    {
        if (x.elem.l == 0)
            r = false;
        else
            r = true;
    }
    if (x.t == DOUBLE)
    {
        if (x.elem.d == 0)
            r = false;
        else
            r = true;
    }
    if (x.t == CHAR)
    {
        if (x.elem.c == 0)
            r = false;
        else
            r = true;
    }
    if (x.t == STRING)
    {
        if (x.elem.str[0] == '\0')
            r = false;
        else
            r = true;
    }
    if (x.t == ARRAY)
    {
        if (isEmpty(x.elem.arr))
            r = false;
        else
            r = true;
    }
    return r;
}

int equalLong(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == LONG && b.t == LONG)
    {
        STACK_ELEM x;
        x.t = LONG;
        x.elem.l = 0;
        if (a.elem.l == b.elem.l)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == DOUBLE && b.t == LONG)
    {
        STACK_ELEM x;
        x.t = LONG;
        x.elem.l = 0;
        if (a.elem.d == b.elem.l)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == CHAR && b.t == LONG)
    {
        STACK_ELEM x;
        x.t = LONG;
        x.elem.l = 0;
        if (a.elem.c == b.elem.l)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    return r;
}

int equalDouble(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == LONG && b.t == DOUBLE)
    {
        STACK_ELEM x;
        x.t = LONG;
        x.elem.l = 0;
        if (a.elem.l == b.elem.d)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }

    if (a.t == DOUBLE && b.t == DOUBLE)
    {
        STACK_ELEM x;
        x.t = LONG;
        x.elem.l = 0;
        if (a.elem.d == b.elem.d)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == CHAR && b.t == DOUBLE)
    {
        STACK_ELEM x;
        x.t = LONG;
        x.elem.l = 0;
        if (a.elem.c == b.elem.d)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    return r;
}

int equalChar(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == DOUBLE && b.t == CHAR)
    {
        STACK_ELEM x;
        x.t = LONG;
        x.elem.l = 0;
        if (a.elem.d == b.elem.c)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == CHAR && b.t == CHAR)
    {
        STACK_ELEM x;
        x.t = LONG;
        x.elem.l = 0;
        if (a.elem.c == b.elem.c)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == LONG && b.t == CHAR)
    {
        STACK_ELEM x;
        x.t = LONG;
        x.elem.l = 0;
        if (a.elem.l == b.elem.c)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    return r;
}

int isEqual(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "=") == 0)
    {
        STACK_ELEM a = pop(s);
        STACK_ELEM b = pop(s);
        equalLong(s, a, b);
        equalDouble(s, a, b);
        equalChar(s, a, b);
        if (a.t == STRING && b.t == STRING)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = 0;
            if (strcmp(a.elem.str, b.elem.str) == 0)
                x.elem.l = 1;
            push(s, x);
            r = 1;
        }
        valueByIndex(s, a, b);
    }
    return r;
}

int negate(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "!") == 0)
    {
        STACK_ELEM x = pop(s);
        STACK_ELEM y;
        y.t = LONG;
        y.elem.l = 1;
        if (truthValue(x) == true)
            y.elem.l = 0;
        push(s, y);
    }
    return r;
}

int shortcutAnd(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "e&") == 0)
    {
        STACK_ELEM a = pop(s);
        STACK_ELEM b = pop(s);
        if (truthValue(a) == false)
            push(s, a);
        else if (truthValue(b) == false)
            push(s, b);
        else
            push(s, a);
        r = 1;
    }
    return r;
}

int shortcutOr(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "e|") == 0)
    {
        STACK_ELEM a = pop(s);
        STACK_ELEM b = pop(s);
        if (truthValue(b) == true)
            push(s, b);
        else
            push(s, a);
        r = 1;
    }
    return r;
}

int ifThenElse(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "?") == 0)
    {
        STACK_ELEM a = pop(s);
        STACK_ELEM b = pop(s);
        STACK_ELEM c = pop(s);
        if (truthValue(c) == true)
            push(s, b);
        else
            push(s, a);
        r = 1;
    }
    return r;
}

int higherLong(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == LONG && b.t == LONG)
    {
        STACK_ELEM x;
        x.t = LONG;
        x.elem.l = 0;
        if (a.elem.l < b.elem.l)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == DOUBLE && b.t == LONG)
    {
        STACK_ELEM y, x;
        x.t = LONG;
        x.elem.l = 0;
        y.t = DOUBLE;
        y.elem.d = b.elem.l;
        if (a.elem.d < y.elem.d)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == CHAR && b.t == LONG)
    {
        STACK_ELEM y, x;
        x.t = LONG;
        x.elem.l = 0;
        y.t = LONG;
        y.elem.l = a.elem.c;
        if (y.elem.l < b.elem.l)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    return r;
}

int higherDouble(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == DOUBLE && b.t == DOUBLE)
    {
        STACK_ELEM x;
        x.t = LONG;
        x.elem.l = 0;
        if (a.elem.d < b.elem.d)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == LONG && b.t == DOUBLE)
    {
        STACK_ELEM y, x;
        x.t = LONG;
        x.elem.l = 0;
        y.t = DOUBLE;
        y.elem.d = a.elem.l;
        if (y.elem.d < b.elem.d)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == CHAR && b.t == DOUBLE)
    {
        STACK_ELEM y, x;
        x.t = LONG;
        x.elem.l = 0;
        y.t = DOUBLE;
        y.elem.d = a.elem.c;
        if (y.elem.d < b.elem.d)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    return r;
}

int higherChar(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == LONG && b.t == CHAR)
    {
        STACK_ELEM y, x;
        x.t = LONG;
        x.elem.l = 0;
        y.t = LONG;
        y.elem.l = b.elem.c;
        if (a.elem.l < y.elem.l)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == DOUBLE && b.t == CHAR)
    {
        STACK_ELEM y, x;
        x.t = LONG;
        x.elem.l = 0;
        y.t = DOUBLE;
        y.elem.d = b.elem.c;
        if (a.elem.d < y.elem.d)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == CHAR && b.t == CHAR)
    {
        STACK_ELEM x;
        x.t = LONG;
        x.elem.l = 0;
        if (a.elem.c < b.elem.c)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    return r;
}

int isHigher(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, ">") == 0)
    {
        STACK_ELEM a = pop(s);
        STACK_ELEM b = pop(s);
        higherLong(s, a, b);
        higherDouble(s, a, b);
        higherChar(s, a, b);
        if (a.t == STRING && b.t == STRING)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = 0;
            if (strcmp(b.elem.str, a.elem.str) > 0)
                x.elem.l = 1;
            push(s, x);
            r = 1;
        }
        elemFinal(s, a, b);
    }
    return r;
}

int lowerLong(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == LONG && b.t == LONG)
    {
        STACK_ELEM x;
        x.t = LONG;
        x.elem.l = 0;
        if (a.elem.l < b.elem.l)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == DOUBLE && b.t == LONG)
    {
        STACK_ELEM y, x;
        x.t = LONG;
        x.elem.l = 0;
        y.t = DOUBLE;
        y.elem.d = b.elem.l;
        if (a.elem.d < y.elem.d)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == CHAR && b.t == LONG)
    {
        STACK_ELEM y, x;
        x.t = LONG;
        x.elem.l = 0;
        y.t = LONG;
        y.elem.l = a.elem.c;
        if (y.elem.l < b.elem.l)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    return r;
}

int lowerDouble(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == DOUBLE && b.t == DOUBLE)
    {
        STACK_ELEM x;
        x.t = LONG;
        x.elem.l = 0;
        if (a.elem.d > b.elem.d)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == LONG && b.t == DOUBLE)
    {
        STACK_ELEM y, x;
        x.t = LONG;
        x.elem.l = 0;
        y.t = DOUBLE;
        y.elem.d = a.elem.l;
        if (y.elem.d > b.elem.d)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == CHAR && b.t == DOUBLE)
    {
        STACK_ELEM y, x;
        x.t = LONG;
        x.elem.l = 0;
        y.t = DOUBLE;
        y.elem.d = a.elem.c;
        if (y.elem.d > b.elem.d)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    return r;
}

int lowerChar(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == LONG && b.t == CHAR)
    {
        STACK_ELEM y, x;
        x.t = LONG;
        x.elem.l = 0;
        y.t = LONG;
        y.elem.l = b.elem.c;
        if (a.elem.l > y.elem.l)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == DOUBLE && b.t == CHAR)
    {
        STACK_ELEM y, x;
        x.t = LONG;
        x.elem.l = 0;
        y.t = DOUBLE;
        y.elem.d = b.elem.c;
        if (a.elem.d > y.elem.d)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    if (a.t == CHAR && b.t == CHAR)
    {
        STACK_ELEM x;
        x.t = LONG;
        x.elem.l = 0;
        if (a.elem.c > b.elem.c)
            x.elem.l = 1;
        push(s, x);
        r = 1;
    }
    return r;
}

int isLower(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "<") == 0)
    {
        STACK_ELEM a = pop(s);
        STACK_ELEM b = pop(s);
        lowerLong(s, a, b);
        lowerDouble(s, a, b);
        lowerChar(s, a, b);
        if (a.t == STRING && b.t == STRING)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = 0;
            if (strcmp(b.elem.str, a.elem.str) < 0)
                x.elem.l = 1;
            push(s, x);
        }
        elemInic(s, a, b);
    }
    return r;
}

int putLowerLong(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == LONG && b.t == LONG)
    {
        if (a.elem.l < b.elem.l)
            push(s, a);
        else
            push(s, b);
        r = 1;
    }
    if (a.t == DOUBLE && b.t == LONG)
    {
        STACK_ELEM y;
        y.t = DOUBLE;
        y.elem.d = b.elem.l;
        if (a.elem.d < y.elem.d)
            push(s, a);
        else
            push(s, y);
        r = 1;
    }
    if (a.t == CHAR && b.t == LONG)
    {
        STACK_ELEM y;
        y.t = LONG;
        y.elem.l = a.elem.c;
        if (y.elem.l < b.elem.l)
            push(s, a);
        else
            push(s, b);
        r = 1;
    }
    return r;
}

int putLowerDouble(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == DOUBLE && b.t == DOUBLE)
    {
        if (a.elem.d < b.elem.d)
            push(s, a);
        else
            push(s, b);
        r = 1;
    }
    if (a.t == LONG && b.t == DOUBLE)
    {
        STACK_ELEM y;
        y.t = DOUBLE;
        y.elem.d = a.elem.l;
        if (y.elem.d < b.elem.d)
            push(s, y);
        else
            push(s, b);
        r = 1;
    }
    if (a.t == CHAR && b.t == DOUBLE)
    {
        STACK_ELEM y;
        y.t = DOUBLE;
        y.elem.d = a.elem.c;
        if (y.elem.d < b.elem.d)
            push(s, a);
        else
            push(s, b);
        r = 1;
    }
    return r;
}

int putLowerChar(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == CHAR && b.t == CHAR)
    {
        if (a.elem.c < (b.elem.c))
            push(s, a);
        else
            push(s, b);
        r = 1;
    }

    if (a.t == LONG && b.t == CHAR)
    {
        STACK_ELEM y;
        y.t = LONG;
        y.elem.l = b.elem.c;
        if (a.elem.l < y.elem.l)
            push(s, a);
        else
            push(s, b);
        r = 1;
    }

    if (a.t == DOUBLE && b.t == CHAR)
    {
        STACK_ELEM y;
        y.t = DOUBLE;
        y.elem.d = b.elem.c;
        if (a.elem.d < y.elem.d)
            push(s, a);
        else
            push(s, b);
        r = 1;
    }
    return r;
}

int putLower(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "e<") == 0)
    {
        STACK_ELEM a = pop(s);
        STACK_ELEM b = pop(s);
        putLowerLong(s, a, b);
        putLowerDouble(s, a, b);
        putLowerChar(s, a, b);
        if (a.t == STRING && b.t == STRING)
        {
            STACK_ELEM y;
            y.t = STRING;
            y.elem.str = malloc(BUFSIZ * sizeof(char));
            if (strcmp(b.elem.str, a.elem.str) < 0)
                strcpy(y.elem.str, b.elem.str);
            else
                strcpy(y.elem.str, a.elem.str);
            push(s, y);
            r = 1;
            free(a.elem.str);
            free(b.elem.str);
        }
    }
    return r;
}

int putHigherLong(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == LONG && b.t == LONG)
    {
        if (a.elem.l > b.elem.l)
            push(s, a);
        else
            push(s, b);
        r = 1;
    }
    if (a.t == DOUBLE && b.t == LONG)
    {
        STACK_ELEM y;
        y.t = DOUBLE;
        y.elem.d = b.elem.l;
        if (a.elem.d > y.elem.d)
            push(s, a);
        else
            push(s, y);
        r = 1;
    }
    if (a.t == CHAR && b.t == LONG)
    {
        STACK_ELEM y;
        y.t = LONG;
        y.elem.l = a.elem.c;
        if (y.elem.l > b.elem.l)
            push(s, a);
        else
            push(s, b);
        r = 1;
    }
    return r;
}

int putHigherDouble(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == DOUBLE && b.t == DOUBLE)
    {
        if (a.elem.d > b.elem.d)
            push(s, a);
        else
            push(s, b);
        r = 1;
    }
    if (a.t == LONG && b.t == DOUBLE)
    {
        STACK_ELEM y;
        y.t = DOUBLE;
        y.elem.d = a.elem.l;
        if (y.elem.d > b.elem.d)
            push(s, y);
        else
            push(s, b);
        r = 1;
    }
    if (a.t == CHAR && b.t == DOUBLE)
    {
        STACK_ELEM y;
        y.t = DOUBLE;
        y.elem.d = a.elem.c;
        if (y.elem.d > b.elem.d)
            push(s, a);
        else
            push(s, b);
        r = 1;
    }
    return r;
}

int putHigherChar(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == CHAR && b.t == CHAR)
    {
        if (a.elem.c > (b.elem.c))
            push(s, a);
        else
            push(s, b);
        r = 1;
    }

    if (a.t == LONG && b.t == CHAR)
    {
        STACK_ELEM y;
        y.t = LONG;
        y.elem.l = b.elem.c;
        if (a.elem.l > y.elem.l)
            push(s, a);
        else
            push(s, b);
        r = 1;
    }

    if (a.t == DOUBLE && b.t == CHAR)
    {
        STACK_ELEM y;
        y.t = DOUBLE;
        y.elem.d = b.elem.c;
        if (a.elem.d > y.elem.d)
            push(s, a);
        else
            push(s, b);
        r = 1;
    }
    return r;
}

int putHigher(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "e>") == 0)
    {
        STACK_ELEM a = pop(s);
        STACK_ELEM b = pop(s);
        putHigherLong(s, a, b);
        putHigherDouble(s, a, b);
        putHigherChar(s, a, b);
        if (a.t == STRING && b.t == STRING)
        {
            STACK_ELEM y;
            y.t = STRING;
            y.elem.str = malloc(BUFSIZ * sizeof(char));
            if (strcmp(b.elem.str, a.elem.str) > 0)
                strcpy(y.elem.str, b.elem.str);
            else
                strcpy(y.elem.str, a.elem.str);
            push(s, y);
            r = 1;
            free(a.elem.str);
            free(b.elem.str);
        }
    }
    return r;
}

int variable(STACK *s, char *token, VARS *arr)
{
    int r = 0;
    int n;
    if (token[0] == ':')
    {
        n = token[1] - 65;
        STACK_ELEM v = peek(s);

        if (v.t == LONG)
        {
            arr->var[n].t = LONG;
            arr->var[n].elem.l = v.elem.l;
        }
        if (v.t == CHAR)
        {
            arr->var[n].t = CHAR;
            arr->var[n].elem.c = v.elem.c;
        }
        if (v.t == DOUBLE)
        {
            arr->var[n].t = DOUBLE;
            arr->var[n].elem.d = v.elem.d;
        }
        if (v.t == STRING)
        {
            arr->var[n].t = STRING;
            arr->var[n].elem.str = v.elem.str;
        }
        if (v.t == ARRAY)
        {
            arr->var[n].t = ARRAY;
            arr->var[n].elem.arr = v.elem.arr;
        }
        if (v.t == BLOCO)
        {
            arr->var[n].t = BLOCO;
            arr->var[n].elem.bl = v.elem.bl;
        }
        r = 1;
    }

    char *g = token;
    if ((!isalpha(token == 0)) && *g >= 'A' && *g <= 'Z')
    {
        n = token[0] - 65;
        if (arr->var[n].t == LONG)
        {
            STACK_ELEM j;
            j.t = LONG;
            j.elem.l = arr->var[n].elem.l;
            push(s, j);
            r = 1;
        }
        if (arr->var[n].t == DOUBLE)
        {
            STACK_ELEM j;
            j.t = DOUBLE;
            j.elem.d = arr->var[n].elem.d;
            push(s, j);
            r = 1;
        }
        if (arr->var[n].t == CHAR)
        {
            STACK_ELEM j;
            j.t = CHAR;
            j.elem.c = arr->var[n].elem.c;
            push(s, j);
            r = 1;
        }
        if (arr->var[n].t == STRING)
        {
            STACK_ELEM j;
            j.t = STRING;
            j.elem.str = arr->var[n].elem.str;
            push(s, j);
            r = 1;
        }
        if (arr->var[n].t == ARRAY)
        {
            push(s, arr->var[n]);
        }
        if (arr->var[n].t == BLOCO)
        {
            push(s, arr->var[n]);
        }
    }
    return r;
}