#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"
#include "handler.h"
#include "operations.h"
#include "convStackmanip.h"
#include "logicVar.h"
#include "arraysStrings.h"
#include "blocos.h"

int operations(STACK *s, char *token, VARS *arr)
{
    return opsg11(s, token, arr) || opsg12(s, token, arr) || opsG2(s, token, arr) || someArrayOps(s, token, arr) || someBlockOps(s, token, arr) || debugStack(s, token) || opsG3(s, token, arr);
}

int checkLong(char *token)
{
    int i, r = 1;
    int length = strlen(token);
    if (token[0] == '-' && isdigit(token[1]))
    {
        for (i = 1; i < length; i++)
        {
            if (!isdigit(token[i]))
                r = 0;
            if (token[i] == '.')
                r = 0;
        }
    }
    else
        for (i = 0; i < length; i++)
        {
            if (!isdigit(token[i]))
                r = 0;
            if (token[i] == '.')
                r = 0;
        }
    return r;
}

int checkDouble(char *token)
{
    int i, r = 1, point = 0, result = 0;
    int length = strlen(token);
    if (token[0] == '-' && isdigit(token[1]))
    {
        for (i = 1; i < length; i++) // antes tinha i = 1
        {
            if (!isdigit(token[i]) && token[i] != '.')
                r = 0;
            if (token[i] == '.')
                point += 1;
        }
    }
    else
        for (i = 0; i < length; i++) // antes tinha i = 1
        {
            if (!isdigit(token[i]) && token[i] != '.')
                r = 0;
            if (token[i] == '.')
                point += 1;
        }
    if (r == 1 && point == 1)
        result = 1;
    return result;
}

int tHandler(STACK *s, char *token, VARS *arr)
{
    int r = 0;
    if (checkLong(token))
    {
        STACK_ELEM y;
        y.t = LONG;
        sscanf(token, "%ld", &y.elem.l);
        push(s, y);
        r = 1;
    }
    else if (checkDouble(token))
    {
        STACK_ELEM y;
        y.t = DOUBLE;
        sscanf(token, "%lf", &y.elem.d);
        push(s, y);
        r = 1;
    }
    else
    {
        operations(s, token, arr);
        r = 1;
    }
    return r;
}

void strHandler(STACK *s, char *token)
{
    STACK_ELEM y;
    y.t = STRING;
    y.elem.str = malloc(BUFSIZ * sizeof(char));
    strcpy(y.elem.str, token);
    push(s, y);
    free(token);
    free(y.elem.str);
}

void arrHandler(STACK *s, char *token, VARS *arr)
{
    STACK_ELEM array;
    array.t = ARRAY;
    array.elem.arr = newstack();
    int i = 0;
    if (isspace(token[0]))
    {
        for (i = 0; token[i] != '\0'; i++)
        {
            token[i] = token[i + 1];
        }
    }
    parseAfterInput(array.elem.arr, token, arr);
    push(s, array);
}

void bHandler(STACK *s, char *token)
{
    STACK_ELEM bloco;
    bloco.t = BLOCO;
    bloco.elem.bl = malloc(BUFSIZ * sizeof(char));
    strcpy(bloco.elem.bl, token);
    push(s, bloco);
    free(token);
    free(bloco.elem.bl);
}

int strJump(char *string)
{
    int r = 0;
    char *original = string;
    if (string[0] == '"')
    {
        string++;
        char *final = strchr(string, '"');
        r = final - original;
    }
    return r;
}

int arrJump(char *string)
{
    int r = 0, open = 1, closed = 0, i = 1;
    char *original = string;
    if (string[0] == '[')
    {
        for (i = 1; open != closed; i++)
        {
            if (string[i] == '[')
                open++;
            if (string[i] == ']')
                closed++;
        }
        char *final = string + i;
        r = final - original;
    }
    return r;
}

int blockJump(char *string)
{
    char *original = string;
    char *final = strchr(string, '}');
    int r = final - original;
    return r;
}

int tokenJump(char *string)
{
    int r = 0;
    char *original = string;
    char *final;
    if ((final = strchr(string, ' ')) != NULL)
        r = final - original;
    else if ((final = strchr(string, '\n')) != NULL)
        r = final - original;
    return r;
}

char *tryParseString(char *string)
{
    char *token = malloc(sizeof(char) * BUFSIZ);
    int j = 0;
    if (string[0] == '"')
    {
        for (int i = 1; string[i] != '"'; i++)
        {
            token[j] = string[i];
            j++;
        }
        token[j] = '\0';
    }
    else
        token = NULL;
    return token;
}

char *tryParseArray(char *string)
{
    int open = 1, closed = 0;
    char *token = malloc(sizeof(char) * BUFSIZ);
    int j = 0;
    if (string[0] == '[')
    {
        for (int i = 1; open != closed; i++)
        {
            if (string[i] == '[')
                open++;
            if (string[i] == ']')
                closed++;
            token[j] = string[i];
            j++;
        }
        token[j - 1] = '\0'; // usa gdb mas assumo que seja por ter de completar o ultimo loop
    }
    else
        token = NULL;
    return token;
}

char *tryParseBlock(char *string)
{
    int i = 0;
    char *token = malloc(sizeof(char) * BUFSIZ);
    if (string[0] == '{')
    {
        for (i = 0; string[i - 1] != '}'; i++)
        {
            token[i] = string[i];
        }
        token[i] = '\0';
    }
    else
        token = NULL;
    return token;
}

char *tryParseToken(char *string)
{
    char *token = malloc(sizeof(char) * BUFSIZ);
    int i = 0;
    if (isspace(string[i]))
        token = NULL;
    else
    {
        while (!isspace(string[i]) && string[i] != '\n')
        {
            token[i] = string[i];
            i += 1;
        }
        token[i] = '\0';
    }
    return token;
}

void parseAfterInput(STACK *s, char *linha, VARS *arr)
{
    while (*linha != '\0')
    {
        char *token;
        if ((token = tryParseString(linha)) != NULL)
        {
            strHandler(s, token);
            linha = linha + strJump(linha) + 1;
        }
        else if ((token = tryParseArray(linha)) != NULL)
        {
            arrHandler(s, token, arr);
            linha = linha + arrJump(linha) + 1;
        }
        else if ((token = tryParseBlock(linha)) != NULL)
        {
            bHandler(s, token);
            linha = linha + blockJump(linha) + 1;
        }
        else if ((token = tryParseToken(linha)) != NULL)
        {
            tHandler(s, token, arr);
            linha = linha + tokenJump(linha) + 1;
        }
        else if (isspace(*linha))
        {
            linha += 1;
        }
        else
        {
            fprintf(stderr, "algo de errado no input\n");
            exit(1);
        }
    }
}

void parser(STACK *s, VARS *arr)
{
    char *linha = malloc(10090 * sizeof(char));
    if (fgets(linha, 10090, stdin) != NULL)
    {
        parseAfterInput(s, linha, arr);
    }
}

void printStack(STACK *s)
{
    int i;
    for (i = 0; i < s->sp; i++)
    {
        if (s->values[i].t == LONG)
        {
            printf("%ld", s->values[i].elem.l);
        }
        if (s->values[i].t == DOUBLE)
        {
            printf("%g", s->values[i].elem.d);
        }
        if (s->values[i].t == CHAR)
        {
            printf("%c", s->values[i].elem.c);
        }
        if (s->values[i].t == STRING)
        {
            printf("%s", s->values[i].elem.str);
        }
        if (s->values[i].t == ARRAY)
        {
            printStack(s->values[i].elem.arr);
        }
        if (s->values[i].t == BLOCO)
        {
            printf("%s", s->values[i].elem.bl);
        }
    }
}