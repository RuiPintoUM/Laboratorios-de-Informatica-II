#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "convStackmanip.h"
#include "handler.h"
#include "blocos.h"

int opsG2(STACK *s, char *token, VARS *arr)
{
    return duplicate(s, token) || sacar(s, token) || switchTop(s, token) || rodar(s, token) || toTop(s, token, arr) || convToLong(s, token) || convToChar(s, token) || convToDouble(s, token) ||
           convToString(s, token) || readLine(s, token);
}

int duplicate(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "_") == 0)
    {
        STACK_ELEM x = peek(s);
        push(s, x);
        r = 1;
    }
    return r;
}

int sacar(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, ";") == 0)
    {
        pop(s);
        r = 1;
    }
    return r;
}

int switchTop(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "\\") == 0)
    {
        if (s->sp >= 1)
        {
            STACK_ELEM x = pop(s);
            STACK_ELEM y = pop(s);
            push(s, x);
            push(s, y);
            r = 1;
        }
    }
    return r;
}

int rodar(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "@") == 0)
    {
        STACK_ELEM x, y, z;

        x = pop(s);
        y = pop(s);
        z = pop(s);

        push(s, y);
        push(s, x);
        push(s, z);
        r = 1;
    }
    return r;
}

int toTop(STACK *s, char *token, VARS *arr)
{
    int r = 0, i;
    if (strcmp(token, "$") == 0)
    {
        STACK_ELEM n = pop(s); // n dado na execução

        if (n.t == LONG)
        {
            STACK_ELEM *storePush = malloc(n.elem.l * sizeof(STACK_ELEM)); // array para guardar os elementos que vao levar push denovo
            for (i = 0; i != n.elem.l; i++)
            {
                storePush[i] = pop(s); // preencher o array
            }
            STACK_ELEM elem = peek(s); // guardar o elemento que se quer copiar
            for (i = n.elem.l - 1; i >= 0; i--)
            {
                push(s, storePush[i]); // voltar a colocar na stack todos os elementos menos o que se move
            }
            push(s, elem); // colocar o elemento no topo
            r = 1;
        }
        else
            sortOn(s, n, arr);
    }
    return r;
}

int convToLong(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "i") == 0)
    {
        STACK_ELEM x = pop(s);
        if (x.t == LONG)
        {
            push(s, x);
            r = 1;
        }
        if (x.t == DOUBLE)
        {
            STACK_ELEM y;
            y.t = LONG;
            y.elem.l = x.elem.d;
            push(s, y);
            r = 1;
        }
        if (x.t == CHAR)
        {
            STACK_ELEM y;
            y.t = LONG;
            y.elem.l = x.elem.c;
            push(s, y);
            r = 1;
        }
        if (x.t == STRING)
        {
            STACK_ELEM y;
            y.t = LONG;
            sscanf(x.elem.str, "%ld", &y.elem.l);
            push(s, y);
            r = 1;
        }
    }
    return r;
}

int convToDouble(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "f") == 0)
    {
        STACK_ELEM x = pop(s);
        if (x.t == LONG)
        {
            STACK_ELEM y;
            y.t = DOUBLE;
            y.elem.d = x.elem.l;
            push(s, y);
            r = 1;
        }
        if (x.t == DOUBLE)
        {
            push(s, x);
        }
        if (x.t == CHAR)
        {
            STACK_ELEM y, z;
            y.t = DOUBLE;
            z.t = LONG;
            z.elem.l = x.elem.c;
            y.elem.d = z.elem.l;
            push(s, y);
            r = 1;
        }
        if (x.t == STRING)
        {
            STACK_ELEM y;
            y.t = DOUBLE;
            sscanf(x.elem.str, "%lf", &y.elem.d);
            push(s, y);
            r = 1;
        }
    }
    return r;
}

int convToChar(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "c") == 0)
    {
        STACK_ELEM x = pop(s);
        if (x.t == LONG)
        {
            STACK_ELEM y;
            y.t = CHAR;
            y.elem.c = x.elem.l;
            push(s, y);
            r = 1;
        }
        if (x.t == CHAR)
        {
            push(s, x);
            r = 1;
        }
        if (x.t == STRING)
        {
            STACK_ELEM y;
            y.t = CHAR;
            y.elem.c = x.elem.str[0];
            push(s, y);
            r = 1;
        }
    }
    return r;
}

int convToString(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "s") == 0)
    {
        STACK_ELEM x = pop(s);
        if (x.t == LONG)
        {
            STACK_ELEM y;
            y.t = STRING;
            y.elem.str = malloc(BUFSIZ * sizeof(char));
            snprintf(y.elem.str, BUFSIZ, "%ld", x.elem.l);
            push(s, y);
        }
        if (x.t == DOUBLE)
        {
            STACK_ELEM y;
            y.t = STRING;
            y.elem.str = malloc(BUFSIZ * sizeof(char));
            snprintf(y.elem.str, BUFSIZ, "%g", x.elem.d);
            push(s, y);
        }
        if (x.t == CHAR)
        {
            STACK_ELEM y;
            y.t = STRING;
            y.elem.str = malloc(2 * sizeof(char));
            y.elem.str[0] = x.elem.c;
            y.elem.str[1] = '\0';
            push(s, y);
        }
        if (x.t == STRING)
        {
            push(s, x);
        }
    }
    return r;
}

int readLine(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "l") == 0)
    {
        STACK_ELEM str;
        str.t = STRING;
        str.elem.str = malloc(BUFSIZ * sizeof(char));
        if (fgets(str.elem.str, BUFSIZ, stdin) != NULL)
        {
            str.elem.str[strcspn(str.elem.str, "\n")] = '\0';
            push(s, str);
        }
        r = 1;
    }
    return r;
}