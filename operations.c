#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "operations.h"
#include "arraysStrings.h"
#include "convStackmanip.h"
#include "blocos.h"

int opsg11(STACK *s, char *token, VARS *arr)
{
    return add(s, token) || sub(s, token) || mult(s, token, arr) || divis(s, token) || increment(s, token) || decrement(s, token) || mod(s, token, arr) ||
           expon(s, token);
}

int opsg12(STACK *s, char *token, VARS *arr)
{
    return bitwiseAnd(s, token) || bitwiseNot(s, token, arr) || bitwiseXor(s, token) || bitwiseOr(s, token);
}

STACK_ELEM convertorString(STACK_ELEM x)
{
    STACK_ELEM y;
    y.t = STRING;
    if (x.t == LONG)
    {
        y.elem.str = malloc(BUFSIZ * sizeof(char));
        snprintf(y.elem.str, BUFSIZ, "%ld", x.elem.l);
    }
    if (x.t == DOUBLE)
    {
        STACK_ELEM y;
        y.t = STRING;
        y.elem.str = malloc(BUFSIZ * sizeof(char));
        snprintf(y.elem.str, BUFSIZ, "%g", x.elem.d);
    }
    if (x.t == CHAR)
    {
        STACK_ELEM y;
        y.t = STRING;
        y.elem.str = malloc(2 * sizeof(char));
        y.elem.str[0] = x.elem.c;
        y.elem.str[1] = '\0';
    }
    return y;
}

int add(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "+") == 0)
    {
        STACK_ELEM a, b;
        a = pop(s);
        b = pop(s);
        if (a.t == LONG && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l + b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == DOUBLE && b.t == DOUBLE)
        {
            STACK_ELEM x;
            x.t = DOUBLE;
            x.elem.d = a.elem.d + b.elem.d;
            push(s, x);
            r = 1;
        }
        if (a.t == DOUBLE && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = DOUBLE;
            x.elem.d = a.elem.d + b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == LONG && b.t == DOUBLE)
        {
            STACK_ELEM x;
            x.t = DOUBLE;
            x.elem.d = a.elem.l + b.elem.d;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = CHAR;
            x.elem.c = a.elem.c + b.elem.c;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.c + b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == LONG && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l + b.elem.c;
            push(s, x);
            r = 1;
        }
        else
            concat(s, a, b);
    }
    return r;
}

int sub(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "-") == 0)
    {
        STACK_ELEM a, b;
        b = pop(s);
        a = pop(s);
        if (a.t == LONG && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l - b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == DOUBLE && b.t == DOUBLE)
        {
            STACK_ELEM x;
            x.t = DOUBLE;
            x.elem.d = a.elem.d - b.elem.d;
            push(s, x);
            r = 1;
        }
        if (a.t == DOUBLE && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = DOUBLE;
            x.elem.d = a.elem.d - b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == LONG && b.t == DOUBLE)
        {
            STACK_ELEM x;
            x.t = DOUBLE;
            x.elem.d = a.elem.l - b.elem.d;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = CHAR;
            x.elem.c = a.elem.c - b.elem.c;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.c - b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == LONG && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l - b.elem.c;
            push(s, x);
            r = 1;
        }
    }
    return r;
}

int mult(STACK *s, char *token, VARS *arr)
{
    int r = 0;
    if (strcmp(token, "*") == 0)
    {
        STACK_ELEM a, b;
        a = pop(s);
        b = pop(s);
        if (a.t == LONG && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l * b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == DOUBLE && b.t == DOUBLE)
        {
            STACK_ELEM x;
            x.t = DOUBLE;
            x.elem.d = a.elem.d * b.elem.d;
            push(s, x);
            r = 1;
        }
        if (a.t == DOUBLE && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = DOUBLE;
            x.elem.d = a.elem.d * b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == LONG && b.t == DOUBLE)
        {
            STACK_ELEM x;
            x.t = DOUBLE;
            x.elem.d = a.elem.l * b.elem.d;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = CHAR;
            x.elem.c = a.elem.c * b.elem.c;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.c * b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == LONG && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l * b.elem.c;
            push(s, x);
            r = 1;
        }
        concatenateMult(s, a, b);
        fold(s, a, b, arr);
    }
    return r;
}

int divis(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "/") == 0)
    {
        STACK_ELEM a, b;
        b = pop(s);
        a = pop(s);
        if (a.t == LONG && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l / b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == DOUBLE && b.t == DOUBLE)
        {
            STACK_ELEM x;
            x.t = DOUBLE;
            x.elem.d = a.elem.d / b.elem.d;
            push(s, x);
            r = 1;
        }
        if (a.t == DOUBLE && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = DOUBLE;
            x.elem.d = a.elem.d / b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == LONG && b.t == DOUBLE)
        {
            STACK_ELEM x;
            x.t = DOUBLE;
            x.elem.d = a.elem.l / b.elem.d;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = CHAR;
            x.elem.c = a.elem.c / b.elem.c;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.c / b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == LONG && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l / b.elem.c;
            push(s, x);
            r = 1;
        }
        separateBySubstr(s, b, a);
    }
    return r;
}

int increment(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, ")") == 0)
    {
        STACK_ELEM x = pop(s);
        if (x.t == LONG)
        {
            x.elem.l += 1;
            push(s, x);
            r = 1;
        }
        if (x.t == DOUBLE)
        {
            x.elem.d += 1;
            push(s, x);
            r = 1;
        }
        if (x.t == CHAR)
        {
            x.elem.c += 1;
            push(s, x);
            r = 1;
        }
        removeLast(s, x);
    }
    return r;
}

int decrement(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "(") == 0)
    {
        STACK_ELEM x = pop(s);
        if (x.t == LONG)
        {
            x.elem.l -= 1;
            push(s, x);
            r = 1;
        }
        if (x.t == DOUBLE)
        {
            x.elem.d -= 1;
            push(s, x);
            r = 1;
        }
        if (x.t == CHAR)
        {
            x.elem.c -= 1;
            push(s, x);
            r = 1;
        }
        removeFirst(s, x);
    }
    return r;
}

int mod(STACK *s, char *token, VARS *arr)
{

    int r = 0;
    if (strcmp(token, "%") == 0)
    {
        STACK_ELEM a, b;
        b = pop(s);
        a = pop(s);
        if (a.t == LONG && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l % b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = CHAR;
            x.elem.c = a.elem.c % b.elem.c;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.c % b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == LONG && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l % b.elem.c;
            push(s, x);
            r = 1;
        }
        applyBlock(s, b, a, arr);
    }
    return r;
}

int expon(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "#") == 0)
    {
        STACK_ELEM a, b;
        b = pop(s);
        a = pop(s);
        if (a.t == LONG && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = pow(a.elem.l, b.elem.l);
            push(s, x);
            r = 1;
        }
        if (a.t == DOUBLE && b.t == DOUBLE)
        {
            STACK_ELEM x;
            x.t = DOUBLE;
            x.elem.d = pow(a.elem.d, b.elem.d);
            push(s, x);
            r = 1;
        }
        if (a.t == DOUBLE && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = DOUBLE;
            x.elem.d = pow(a.elem.d, b.elem.l);
            push(s, x);
            r = 1;
        }
        if (a.t == LONG && b.t == DOUBLE)
        {
            STACK_ELEM x;
            x.t = DOUBLE;
            x.elem.d = pow(a.elem.l, b.elem.d);
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = CHAR;
            x.elem.c = pow(a.elem.c, b.elem.c);
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = pow(a.elem.c, b.elem.l);
            push(s, x);
            r = 1;
        }
        if (a.t == LONG && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = pow(a.elem.l, b.elem.c);
            push(s, x);
            r = 1;
        }
        findSubstring(s, b, a);
    }
    return r;
}

int bitwiseAnd(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "&") == 0)
    {
        STACK_ELEM a, b;
        a = pop(s);
        b = pop(s);
        if (a.t == LONG && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l & b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = CHAR;
            x.elem.c = a.elem.c & b.elem.c;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.c & b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == LONG && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l & b.elem.c;
            push(s, x);
            r = 1;
        }
    }
    return r;
}

int bitwiseOr(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "|") == 0)
    {
        STACK_ELEM a, b;
        a = pop(s);
        b = pop(s);
        if (a.t == LONG && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l | b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = CHAR;
            x.elem.c = a.elem.c | b.elem.c;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.c | b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == LONG && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l | b.elem.c;
            push(s, x);
            r = 1;
        }
    }
    return r;
}

int bitwiseXor(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "^") == 0)
    {
        STACK_ELEM a, b;
        a = pop(s);
        b = pop(s);
        if (a.t == LONG && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l ^ b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = CHAR;
            x.elem.c = a.elem.c ^ b.elem.c;
            push(s, x);
            r = 1;
        }
        if (a.t == CHAR && b.t == LONG)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.c ^ b.elem.l;
            push(s, x);
            r = 1;
        }
        if (a.t == LONG && b.t == CHAR)
        {
            STACK_ELEM x;
            x.t = LONG;
            x.elem.l = a.elem.l ^ b.elem.c;
            push(s, x);
            r = 1;
        }
    }
    return r;
}

int bitwiseNot(STACK *s, char *token, VARS *arr)
{
    int r = 0;
    if (strcmp(token, "~") == 0)
    {
        STACK_ELEM x = pop(s);
        if (x.t == LONG)
        {
            STACK_ELEM y;
            y.t = LONG;
            y.elem.l = ~x.elem.l;
            push(s, y);
            r = 1;
        }
        if (x.t == CHAR)
        {
            STACK_ELEM y;
            y.t = CHAR;
            y.elem.c = ~x.elem.c;
            push(s, y);
            r = 1;
        }
        putInStack(s, x);
        execBlock(s, x, arr);
    }
    return r;
}