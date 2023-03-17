#ifndef ARRAYSSTRINGS_H
#define ARRAYSSTRINGS_H

/**
 * @brief Algumas operações de arrays, se o token for um operador executa a operação correspondente.
 *
 * @param s Stack.
 * @param token String que pode conter um operador.
 * @param arr Variáveis globais.
 */
int someArrayOps(STACK *s, char *token, VARS *arr);

/**
 * @brief A função coloca na stack todos os elementos do array.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 */
int putInStack(STACK *s, STACK_ELEM a);

/**
 * @brief A função concatena arrays com arrays, strings com strings, arrays com elementos ou strings com chars.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 */
int concat(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief A função devolve o tamanho de um array ou string ou a range (como array) de um elemento.
 *
 * @param s Stack.
 * @param token String que pode conter o operador.
 * @param arr Variáveis globais.
 */
int sizeOrRange(STACK *s, char *token, VARS *arr);

/**
 * @brief A função concatena várias vezes arrays ou strings.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 */
int concatenateMult(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief A função devolve o elemento num dado indice de um array ou string.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 */
int valueByIndex(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief A função devolve os N primeiros elementos de um array ou string (sendo N um inteiro) ordenados.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 */
int elemInic(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief A função devolve os N ultimos elementos de um array ou string (sendo N um inteiro) ordenados.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 */
int elemFinal(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief Remove o primeiro elemento de um array ou string e envia-o para a stack principal.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 */
int removeFirst(STACK *s, STACK_ELEM a);

/**
 * @brief Remove o último elemento de um array ou string e envia-o para a stack principal.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 */
int removeLast(STACK *s, STACK_ELEM a);

/**
 * @brief Encontra o indice onde começa uma dada substring na string principal e devolve esse indice.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 */
int findSubstring(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief Separa uma string num array de strings, sendo a string separada onde aparece uma dada substring.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 */
int separateBySubstr(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief Separa uma string num array de strings, sendo a string separado onde aparecem caracteres considerados whitespace.
 *
 * @param s Stack.
 * @param token String que pode conter o operador.
 */
int separateByWhitespace(STACK *s, char *token);

/**
 * @brief Separa uma string num array de strings, sendo a string separado onde existe o caracter newline '\n'..
 *
 * @param s Stack.
 * @param token String que pode conter o operador.
 */
int separateByNewline(STACK *s, char *token);

/**
 * @brief Lê todo o conteúdo de um ficheiro.
 *
 * @param s Stack.
 * @param token String que pode conter o operador.
 */
int readAllInput(STACK *s, char *token);

#endif