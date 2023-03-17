#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"
#include "blocos.h"
#include "handler.h"
#include "logicVar.h"
#include "arraysStrings.h"
#include "operations.h"

int someBlockOps(STACK *s, char *token, VARS *arr)
{
    return whileLoop(s, token, arr) || peekStack(s, token);
}

char *removeBrackets(char *string)
{
    char *token = malloc(BUFSIZ * sizeof(char));
    int i = 1, j = 0;
    if (string[0] == '{')
    {
        for (i = 1; string[i] != '}'; i++)
        {
            token[j] = string[i];
            j++;
        }
        token[j] = '\0';
    }
    return token;
}

int execBlock(STACK *s, STACK_ELEM a, VARS *arr)
{
    int r = 0;
    if (a.t == BLOCO)
    {
        char *inside = removeBrackets(a.elem.bl);
        parseAfterInput(s, inside, arr);
        r = 1;
    }
    return r;
}

int filterByBlock(STACK *s, STACK_ELEM a, VARS *arr)
{
    int r = 0;
    if (a.t == BLOCO)
    {
        STACK_ELEM b = pop(s);
        if (b.t == STRING)
        {
            STACK_ELEM string;
            string.t = STRING;
            string.elem.str = malloc(BUFSIZ * sizeof(char));
            int i = 0, k = 0;
            while (b.elem.str[i] != '\0')
            {
                STACK_ELEM temp;
                temp.t = CHAR;
                temp.elem.c = b.elem.str[i];
                push(s, temp);
                execBlock(s, a, arr);
                i++;
                if (!truthValue(peek(s)))
                    pop(s);
                else
                {
                    pop(s);
                    string.elem.str[k] = temp.elem.c;
                    k++;
                }
            }
            string.elem.str[k] = '\0';
            push(s, string);
            r = 1;
        }
        if (b.t == ARRAY)
        {
            STACK_ELEM array;
            array.t = ARRAY;
            array.elem.arr = newstack();
            STACK_ELEM *storage = malloc(b.elem.arr->sp * sizeof(STACK_ELEM));
            int i = 0;
            for (i = 0; !isEmpty(b.elem.arr); i++)
            {
                storage[i] = pop(b.elem.arr);
            }
            for (int j = i - 1; j >= 0; j--)
            {
                push(s, storage[j]);
                execBlock(s, a, arr);
                if (!truthValue(peek(s)))
                    pop(s);
                else
                {
                    pop(s);
                    push(array.elem.arr, storage[j]);
                }
            }
            push(s, array);
            r = 1;
        }
    }
    return r;
}

int whileLoop(STACK *s, char *token, VARS *arr)
{
    int r = 0;
    if ((strcmp("w", token)) == 0)
    {
        STACK_ELEM block = pop(s);
        if (block.t == BLOCO)
        {
            do
            {
                execBlock(s, block, arr);
            } while (truthValue(pop(s)));
            r = 1;
        }
    }
    return r;
}

int fold(STACK *s, STACK_ELEM a, STACK_ELEM b, VARS *arr)
{
    int r = 0;
    if (a.t == BLOCO && b.t == ARRAY)
    {
        STACK_ELEM array;
        array.t = ARRAY;
        array.elem.arr = newstack();
        STACK_ELEM *storage = malloc(b.elem.arr->sp * sizeof(STACK_ELEM));
        int i = 0;
        for (i = 0; !isEmpty(b.elem.arr); i++)
        {
            storage[i] = pop(b.elem.arr);
        }
        push(array.elem.arr, storage[i - 1]);
        for (int k = i - 2; k >= 0; k--)
        {
            push(array.elem.arr, storage[k]);
            execBlock(array.elem.arr, a, arr);
        }
        push(s, array);
        r = 1;
    }
    return r;
}

int lowerLongSort(STACK_ELEM b, STACK_ELEM a)
{
    int r = 0;
    if (a.t == LONG && b.t == LONG)
    {
        if (a.elem.l > b.elem.l)
            r = 1;
    }
    if (a.t == DOUBLE && b.t == LONG)
    {
        STACK_ELEM y;
        y.t = DOUBLE;
        y.elem.d = b.elem.l;
        if (a.elem.d > y.elem.d)
            r = 1;
    }
    if (a.t == CHAR && b.t == LONG)
    {
        STACK_ELEM y;
        y.t = LONG;
        y.elem.l = a.elem.c;
        if (y.elem.l > b.elem.l)
            r = 1;
    }
    return r;
}

int lowerDoubleSort(STACK_ELEM b, STACK_ELEM a)
{
    int r = 0;
    if (a.t == DOUBLE && b.t == DOUBLE)
    {
        if (a.elem.d > b.elem.d)
            r = 1;
    }
    if (a.t == LONG && b.t == DOUBLE)
    {
        STACK_ELEM y;
        y.t = DOUBLE;
        y.elem.d = a.elem.l;
        if (y.elem.d > b.elem.d)
            r = 1;
    }
    if (a.t == CHAR && b.t == DOUBLE)
    {
        STACK_ELEM y;
        y.t = DOUBLE;
        y.elem.d = a.elem.c;
        if (y.elem.d > b.elem.d)
            r = 1;
    }
    return r;
}

int lowerCharSort(STACK_ELEM b, STACK_ELEM a)
{
    int r = 0;
    if (a.t == LONG && b.t == CHAR)
    {
        STACK_ELEM y;
        y.t = LONG;
        y.elem.l = b.elem.c;
        if (a.elem.l > y.elem.l)
            r = 1;
    }
    if (a.t == DOUBLE && b.t == CHAR)
    {
        STACK_ELEM y;
        y.t = DOUBLE;
        y.elem.d = b.elem.c;
        if (a.elem.d > y.elem.d)
            r = 1;
    }
    return r;
}

int lowerStrArrSort(STACK_ELEM b, STACK_ELEM a)
{
    int r = 0;
    if (a.t == STRING && b.t == STRING)
    {
        if (strcmp(b.elem.str, a.elem.str) < 0)
            r = 1;
    }
    if (a.t == ARRAY && b.t == ARRAY)
    {
        if (a.elem.arr->sp > b.elem.arr->sp)
            r = 1;
    }
    return r;
}
int isLowerSort(STACK_ELEM b, STACK_ELEM a)
{
    int r = 0;
    if (lowerLongSort(b, a) || lowerDoubleSort(b, a) || lowerCharSort(b, a) || lowerStrArrSort(b, a))
        r = 1;
    return r;
}

void sortArr(STACK_ELEM *arr, STACK_ELEM *elems, int N)
{
    for (int i = 1; i < N; i++)
    {
        int j;
        STACK_ELEM current;
        STACK_ELEM currentElem;
        current = arr[i];
        currentElem = elems[i];
        j = i - 1;
        while (j >= 0 && !isLowerSort(arr[j], current))
        {
            elems[j + 1] = elems[j];
            arr[j + 1] = arr[j];
            j -= 1;
        }
        elems[j + 1] = currentElem;
        arr[j + 1] = current;
    }
}

void arrRev(STACK_ELEM *arr, int N)
{
    STACK_ELEM temp;
    for (int i = 0; i < N / 2; i++)
    {
        temp = arr[i];
        arr[i] = arr[N - i - 1];
        arr[N - i - 1] = temp;
    }
}

int sortOn(STACK *s, STACK_ELEM block, VARS *arr)
{
    int r = 0;
    STACK_ELEM subject = pop(s);
    if (block.t == BLOCO && subject.t == ARRAY)
    {
        STACK_ELEM array;
        array.t = ARRAY;
        array.elem.arr = newstack();
        STACK_ELEM *storage = malloc(subject.elem.arr->sp * sizeof(STACK_ELEM));
        STACK_ELEM *final = malloc(subject.elem.arr->sp * sizeof(STACK_ELEM));
        int i = 0, j = 0;
        for (i = 0; !isEmpty(subject.elem.arr); i++)
        {
            storage[i] = pop(subject.elem.arr);
        }
        arrRev(storage, i);
        for (int k = 0; k <= i - 1; k++)
        {
            push(array.elem.arr, storage[k]);
            execBlock(array.elem.arr, block, arr);
            final[j] = pop(array.elem.arr);
            j++;
        }
        sortArr(final, storage, j);
        for (int x = 0; x <= j - 1; x++)
        {
            push(array.elem.arr, storage[x]);
        }
        push(s, array);
        r = 1;
    }
    return r;
}

void strrev(char *str)
{
    int length = strlen(str);
    char temp;
    for (int i = 0; i < length / 2; i++)
    {
        temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

int applyBlock(STACK *s, STACK_ELEM a, STACK_ELEM b, VARS *arr)
{
    int r = 0;
    if (a.t == BLOCO && b.t == ARRAY)
    {
        int i = 0;
        STACK_ELEM aux;
        aux.t = ARRAY;
        aux.elem.arr = newstack();
        STACK_ELEM *auxArr = malloc(b.elem.arr->sp * sizeof(STACK_ELEM));
        while (!isEmpty(b.elem.arr))
        {
            STACK_ELEM v;
            v = pop(b.elem.arr);
            push(aux.elem.arr, v);

            execBlock(aux.elem.arr, a, arr);
            while (!isEmpty(aux.elem.arr))
            {
                STACK_ELEM g = pop(aux.elem.arr);
                auxArr[i] = g;
                i++;
            }
        }
        for (int k = i - 1; k >= 0; k--)
        {
            push(aux.elem.arr, auxArr[k]);
        }
        push(s, aux);
        r = 1;
    }
    if (a.t == BLOCO && b.t == STRING)
    {
        int j = 0;
        STACK_ELEM st;
        st.t = STRING;
        st.elem.str = malloc(strlen(b.elem.str) * sizeof(char));
        int length = strlen(b.elem.str);
        for (int i = 0; i < length; i++)
        {
            STACK_ELEM CH;
            CH.t = CHAR;
            CH.elem.c = b.elem.str[i];
            push(s, CH);
            execBlock(s, a, arr);
        }
        while (!isEmpty(s))
        {
            STACK_ELEM g = pop(s);
            st.elem.str[j] = g.elem.c;
            j++;
        }
        st.elem.str[j] = '\0';
        strrev(st.elem.str);
        push(s, st);
        r = 1;
    }
    return r;
}

int peekStack(STACK *s, char *token)
{
    int r = 0;
    if (strcmp("p", token) == 0)
    {
        STACK_ELEM x = peek(s);
        push(s, x);
        r = 1;
    }
    return r;
}