#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "arraysStrings.h"
#include "handler.h"
#include "blocos.h"

int someArrayOps(STACK *s, char *token, VARS *arr)
{
    return sizeOrRange(s, token, arr) || separateByWhitespace(s, token) || separateByNewline(s, token) || readAllInput(s, token);
}

int putInStack(STACK *s, STACK_ELEM a)
{
    int r = 0;
    if (a.t == ARRAY)
    {
        int i = 0;
        int length = a.elem.arr->sp;
        STACK_ELEM *arr = malloc(length * sizeof(STACK_ELEM));
        for (i = 0; i < length; i++)
        {
            arr[i] = pop(a.elem.arr);
        }
        for (int k = i - 1; k >= 0; k--)
        {
            push(s, arr[k]);
        }
        r = 1;
    }
    return r;
}

int concat(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == STRING && b.t == STRING)
    {
        strcat(b.elem.str, a.elem.str);
        push(s, b);
        r = 1;
    }
    if (b.t == STRING && a.t == CHAR)
    {
        char *ch = malloc(2 * sizeof(char));
        ch[0] = a.elem.c;
        ch[1] = '\0';
        strcat(b.elem.str, ch);
        push(s, b);
        r = 1;
    }
    if (b.t == CHAR && a.t == STRING)
    {
        int i = 0;
        int length = strlen(a.elem.str);
        for (i = length; i > 0; i--)
        {
            a.elem.str[i] = a.elem.str[i - 1];
        }
        a.elem.str[i] = b.elem.c;
        a.elem.str[length + 1] = '\0';
        push(s, a);
        r = 1;
    }
    if (b.t == ARRAY && a.t == ARRAY)
    {
        int i = 0;
        STACK_ELEM *storage = malloc(sizeof(STACK_ELEM) * a.elem.arr->sp);
        while (!isEmpty(a.elem.arr))
        {
            storage[i] = pop(a.elem.arr);
            i++;
        }
        for (int k = i - 1; k >= 0; k--)
        {
            push(b.elem.arr, storage[k]);
        }
        push(s, b);
        r = 1;
    }
    if (b.t == ARRAY && a.t != ARRAY)
    {
        push(b.elem.arr, a);
        push(s, b);
        r = 1;
    }
    if (a.t == ARRAY && b.t != ARRAY)
    {
        int i = 0;
        STACK_ELEM *storage = malloc(sizeof(STACK_ELEM) * a.elem.arr->sp);
        while (!isEmpty(a.elem.arr))
        {
            storage[i] = pop(a.elem.arr);
            i++;
        }
        push(a.elem.arr, b);
        for (int k = i - 1; k >= 0; k--)
        {
            push(a.elem.arr, storage[k]);
        }
        push(s, a);
        r = 1;
    }
    return r;
}

int sizeOrRange(STACK *s, char *token, VARS *arr)
{
    int r = 0;
    if (strcmp(token, ",") == 0)
    {
        STACK_ELEM y;
        y = pop(s);
        if (y.t == LONG)
        {
            STACK_ELEM i, a;
            i.t = LONG;
            a.t = ARRAY;
            a.elem.arr = newstack();
            for (i.elem.l = 0; i.elem.l < y.elem.l; i.elem.l += 1)
            {
                push(a.elem.arr, i);
            }
            push(s, a);
            r = 1;
        }
        if (y.t == DOUBLE)
        {
            STACK_ELEM i, a;
            i.t = LONG;
            a.t = ARRAY;
            a.elem.arr = newstack();
            for (i.elem.l = 0; i.elem.l < y.elem.d; i.elem.l += 1)
            {
                push(a.elem.arr, i);
            }
            push(s, a);
            r = 1;
        }
        if (y.t == CHAR)
        {
            STACK_ELEM arr, i;
            arr.t = ARRAY;
            i.t = LONG;
            arr.elem.arr = newstack();
            for (i.elem.l = 0; i.elem.l < y.elem.c; i.elem.l++)
            {
                push(arr.elem.arr, i);
            }
            push(s, arr);
            r = 1;
        }
        if (y.t == STRING)
        {
            STACK_ELEM len;
            len.t = LONG;
            len.elem.l = strlen(y.elem.str);
            push(s, len);
            r = 1;
        }
        if (y.t == ARRAY)
        {
            STACK_ELEM size;
            int asize = y.elem.arr->sp;
            size.t = LONG;
            size.elem.l = asize;
            push(s, size);
            r = 1;
        }
        filterByBlock(s, y, arr);
    }
    return r;
}

int concatenateMult(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == LONG && b.t == STRING)
    {
        STACK_ELEM i, fullstr;
        i.t = LONG;
        fullstr.t = STRING;
        fullstr.elem.str = malloc(BUFSIZ * sizeof(char));
        for (i.elem.l = 0; i.elem.l < a.elem.l; i.elem.l++)
        {
            fullstr.elem.str = strcat(fullstr.elem.str, b.elem.str);
        }
        push(s, fullstr);
        free(fullstr.elem.str);
        free(b.elem.str);
    }
    if (a.t == LONG && b.t == ARRAY)
    {
        STACK_ELEM *arr = malloc(b.elem.arr->sp * sizeof(STACK_ELEM));
        int i = 0;
        int j = 0;
        /*         for (i.elem.l = 0; i.elem.l < a.elem.l; i.elem.l++)
                {
                   push(s, b);
                } */
        while (!isEmpty(b.elem.arr))
        {
            arr[j] = pop(b.elem.arr);
            j++;
        }
        for (i = 0; i < a.elem.l; i++)
        {
            for (int k = j - 1; k >= 0; k--)
            {
                push(b.elem.arr, arr[k]);
            }
        }
        push(s, b);
    }
    return r;
}

int valueByIndex(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (b.t == STRING && a.t == LONG)
    {
        STACK_ELEM value;
        value.t = CHAR;
        value.elem.c = b.elem.str[a.elem.l];
        push(s, value);
        r = 1;
    }

    if (b.t == ARRAY && a.t == LONG)
    {
        STACK_ELEM value;
        if (b.elem.arr->values[a.elem.l].t == LONG)
        {
            value.t = LONG;
            value.elem.l = b.elem.arr->values[a.elem.l].elem.l;
            push(s, value);
            r = 1;
        }
        if (b.elem.arr->values[a.elem.l].t == DOUBLE)
        {
            value.t = DOUBLE;
            value.elem.d = b.elem.arr->values[a.elem.l].elem.d;
            push(s, value);
            r = 1;
        }
        if (b.elem.arr->values[a.elem.l].t == CHAR)
        {
            value.t = CHAR;
            value.elem.c = b.elem.arr->values[a.elem.l].elem.c;
            push(s, value);
            r = 1;
        }
        if (b.elem.arr->values[a.elem.l].t == STRING)
        {
            value.t = STRING;
            value.elem.str = b.elem.arr->values[a.elem.l].elem.str;
            push(s, value);
            r = 1;
        }
        if (b.elem.arr->values[a.elem.l].t == ARRAY)
        {
            STACK_ELEM value;
            value.t = ARRAY;
            value.elem.arr = b.elem.arr->values[a.elem.l].elem.arr;
            push(s, value);
            r = 1;
        }
    }
    return r;
}

int elemInic(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (b.t == STRING && a.t == LONG)
    {
        STACK_ELEM chr;
        chr.t = CHAR;
        for (int i = 0; i < a.elem.l; i++)
        {
            chr.elem.c = b.elem.str[i];
            push(s, chr);
            r = 1;
        }
    }
    if (b.t == ARRAY && a.t == LONG)
    {
        STACK_ELEM value;
        for (int j = 0; j < a.elem.l; j++)
        {
            if (b.elem.arr->values[j].t == LONG)
            {
                value.t = LONG;
                value.elem.l = b.elem.arr->values[j].elem.l;
                push(s, value);
                r = 1;
            }
            if (b.elem.arr->values[j].t == DOUBLE)
            {
                value.t = DOUBLE;
                value.elem.d = b.elem.arr->values[j].elem.d;
                push(s, value);
                r = 1;
            }
            if (b.elem.arr->values[j].t == CHAR)
            {
                value.t = CHAR;
                value.elem.c = b.elem.arr->values[j].elem.c;
                push(s, value);
                r = 1;
            }
            if (b.elem.arr->values[j].t == STRING)
            {
                value.t = STRING;
                value.elem.str = b.elem.arr->values[j].elem.str;
                push(s, value);
                r = 1;
            }
            if (b.elem.arr->values[j].t == ARRAY)
            {
                STACK_ELEM value;
                value.t = ARRAY;
                value.elem.arr = b.elem.arr->values[j].elem.arr;
                push(s, value);
                r = 1;
            }
        }
    }
    return r;
}

int elemFinal(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (b.t == STRING && a.t == LONG)
    {
        int len = strlen(b.elem.str);
        STACK_ELEM chr;
        chr.t = CHAR;
        for (int i = len - a.elem.l; i < len; i++)
        {
            chr.elem.c = b.elem.str[i];
            push(s, chr);
            r = 1;
        }
    }
    if (b.t == ARRAY && a.t == LONG)
    {
        STACK_ELEM value;
        int alen = b.elem.arr->sp;
        for (int j = alen - a.elem.l; j < alen; j++)
        {
            if (b.elem.arr->values[j].t == LONG)
            {
                value.t = LONG;
                value.elem.l = b.elem.arr->values[j].elem.l;
                push(s, value);
                r = 1;
            }
            if (b.elem.arr->values[j].t == DOUBLE)
            {
                value.t = DOUBLE;
                value.elem.d = b.elem.arr->values[j].elem.d;
                push(s, value);
                r = 1;
            }
            if (b.elem.arr->values[j].t == CHAR)
            {
                value.t = CHAR;
                value.elem.c = b.elem.arr->values[j].elem.c;
                push(s, value);
                r = 1;
            }
            if (b.elem.arr->values[j].t == STRING)
            {
                value.t = STRING;
                value.elem.str = b.elem.arr->values[j].elem.str;
                push(s, value);
                r = 1;
            }
            if (b.elem.arr->values[j].t == ARRAY)
            {
                STACK_ELEM value;
                value.t = ARRAY;
                value.elem.arr = b.elem.arr->values[j].elem.arr;
                push(s, value);
                r = 1;
            }
        }
    }
    return r;
}

int removeFirst(STACK *s, STACK_ELEM a)
{
    int r = 0;
    if (a.t == STRING)
    {
        STACK_ELEM ch;
        ch.t = CHAR;
        ch.elem.c = *a.elem.str;
        a.elem.str++;
        push(s, a);
        push(s, ch);
        r = 1;
    }
    if (a.t == ARRAY)
    {
        int tail = a.elem.arr->sp - 1;
        STACK_ELEM *saved = malloc(tail * sizeof(STACK_ELEM));
        for (int i = 0; i < tail; i++)
        {
            saved[i] = pop(a.elem.arr);
        }
        STACK_ELEM fst = pop(a.elem.arr);
        for (int j = tail - 1; j >= 0; j--)
        {
            push(a.elem.arr, saved[j]);
        }
        push(s, a);
        push(s, fst);
        r = 1;
    }
    return r;
}

int removeLast(STACK *s, STACK_ELEM a)
{
    int r = 0, i = 0;
    if (a.t == STRING)
    {
        int fIndex = strlen(a.elem.str) - 1;
        STACK_ELEM ch;
        STACK_ELEM st;
        ch.t = CHAR;
        st.t = STRING;
        st.elem.str = malloc(BUFSIZ * sizeof(char));
        ch.elem.c = a.elem.str[fIndex];
        for (i = 0; a.elem.str[i + 1] != '\0'; i++)
        {
            st.elem.str[i] = a.elem.str[i];
        }
        st.elem.str[i] = '\0';
        push(s, st);
        push(s, ch);
        r = 1;
        free(a.elem.str);
    }
    if (a.t == ARRAY)
    {
        STACK_ELEM p = pop(a.elem.arr);
        push(s, a);
        push(s, p);
        r = 1;
    }
    return r;
}

int findSubstring(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == STRING && b.t == STRING)
    {
        STACK_ELEM index;
        index.t = LONG;
        index.elem.l = -1;
        char *subs = malloc(strlen(b.elem.str) * sizeof(char));
        if ((subs = strstr(b.elem.str, a.elem.str)) != NULL)
        {
            index.elem.l = subs - b.elem.str;
        }
        push(s, index);
        r = 1;
    }
    return r;
}

int separateBySubstr(STACK *s, STACK_ELEM a, STACK_ELEM b)
{
    int r = 0;
    if (a.t == STRING && b.t == STRING)
    {
        STACK_ELEM arr;
        arr.t = ARRAY;
        arr.elem.arr = newstack();
        if (strcmp(a.elem.str, "") == 0)
        {
            STACK_ELEM arr;
            arr.t = ARRAY;
            arr.elem.arr = newstack();
            for (int i = 0; b.elem.str[i] != '\0'; i++)
            {
                STACK_ELEM string;
                string.t = STRING;
                string.elem.str = malloc(strlen(b.elem.str) * sizeof(char));
                string.elem.str[0] = b.elem.str[i];
                string.elem.str[1] = '\0';
                push(arr.elem.arr, string);
            }
            push(s, arr);
            r = 1;
        }
        else
        {
            STACK_ELEM subst;
            subst.t = STRING;
            subst.elem.str = strtok(b.elem.str, a.elem.str);
            while (subst.elem.str != NULL)
            {
                push(arr.elem.arr, subst);
                subst.elem.str = strtok(NULL, a.elem.str);
            }
            push(s, arr);
            r = 1;
        }
    }
    return r;
}

int separateByWhitespace(STACK *s, char *token)
{
    int r = 0;
    if ((strcmp(token, "S/") == 0))
    {
        STACK_ELEM str = pop(s);
        if (str.t == STRING)
        {
            char *delim = " \t\v\f\r\n";
            STACK_ELEM arr;
            STACK_ELEM subst;
            arr.t = ARRAY;
            subst.t = STRING;
            arr.elem.arr = newstack();
            subst.elem.str = strtok(str.elem.str, delim);
            while (subst.elem.str != NULL)
            {
                push(arr.elem.arr, subst);
                subst.elem.str = strtok(NULL, delim);
            }
            push(s, arr);
            r = 1;
        }
    }
    return r;
}

int separateByNewline(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "N/") == 0)
    {
        STACK_ELEM str = pop(s);
        if (str.t == STRING)
        {
            char *delim = "\n";
            STACK_ELEM arr;
            STACK_ELEM subst;
            arr.t = ARRAY;
            subst.t = STRING;
            arr.elem.arr = newstack();
            subst.elem.str = strtok(str.elem.str, delim);
            while (subst.elem.str != NULL)
            {
                push(arr.elem.arr, subst);
                subst.elem.str = strtok(NULL, delim);
            }
            push(s, arr);
            r = 1;
        }
    }
    return r;
}

int readAllInput(STACK *s, char *token)
{
    int r = 0;
    if (strcmp(token, "t") == 0)
    {
        STACK_ELEM str;
        str.t = STRING;
        str.elem.str = malloc(BUFSIZ * sizeof(char));
        STACK_ELEM fstr;
        fstr.t = STRING;
        fstr.elem.str = malloc(BUFSIZ * sizeof(char));
        fstr.elem.str[0] = '\0';
        while ((fgets(str.elem.str, BUFSIZ, stdin) != NULL))
        {
            strcat(fstr.elem.str, str.elem.str);
        }
        push(s, fstr);
        r = 1;
    }
    return r;
}