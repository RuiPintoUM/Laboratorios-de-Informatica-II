#include <stdio.h>
#include "stack.h"
#include "handler.h"

/**
 * @brief Função main do programa, inicia a stack principal, as variáveis globais e o parser. No final imprime a stack.
 *
 */
int main()
{
    STACK *s = newstack();
    VARS *arr = initVars();
    parser(s, arr);
    printStack(s);
    printf("\n");
    return 0;
}