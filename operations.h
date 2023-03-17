#ifndef OPERATIONS_H
#define OPERATIONS_H

/**
 * @brief Algumas operações do guião 1, se o token for um operador executa a operação correspondente.
 *
 * @param s Stack.
 * @param token String onde pode ter um operador.
 * @param arr Variáveis globais.
 */
int opsg11(STACK *s, char *token, VARS *arr);

/**
 * @brief Algumas operações do guião 1, se o token for um operador executa a operação correspondente.
 *
 * @param s Stack.
 * @param token String onde pode ter um operador.
 * @param arr Variáveis globais.
 */
int opsg12(STACK *s, char *token, VARS *arr);

/**
 * @brief Converte um elemento para string.
 *
 * @param x O elemento a converter.
 */
STACK_ELEM convertorString(STACK_ELEM x);

/**
 * @brief Função soma
 * A função add tem a tarefa de somar os dois elementos no topo da stack.
 * @param s elemento da stack.
 * @param token operação matemática (soma).
 */
int add(STACK *s, char *token);

/**
 * @brief Função que subtrai
 * A tarefa da função sub é subtrair os dois elementos no topo da stack (o que vem antes do topo - topo da stack).
 * @param s elemento da stack.
 * @param token operação matemática (subtrai).
 */
int sub(STACK *s, char *token);

/**
 * @brief Função que multiplica
 * A função mult multiplica os dois elementos no topo da stack.
 * @param s elemento da stack.
 * @param token operação matemática (multiplicação).
 */
int mult(STACK *s, char *token, VARS *arr);

/**
 * @brief Função que divide
 * A tarefa da função divis é dividir os dois elementos no topo da stack (o que vem antes do topo / topo da stack).
 * @param s elemento da stack.
 * @param token operação matemática (divisão).
 */
int divis(STACK *s, char *token);

/**
 * @brief Função que incrementa
 * Esta função incrementa o elemento no topo da stack.
 * @param s stack.
 * @param token operação lida.
 */
int increment(STACK *s, char *token);

/**
 * @brief Função que decrementa
 * Esta função decrementa o elemento no topo da stack.
 * @param s stack.
 * @param token operação lida.
 */
int decrement(STACK *s, char *token);

/**
 * @brief Função que calcula o resto de uma divisão
 * A função nos dois elementos no topo da stack, calcula o resto da divisão entre eles e devolve o resultado à stack.
 * @param s stack.
 * @param token operação lida.
 */
int mod(STACK *s, char *token, VARS *arr);

/**
 * @brief Função que calcula o expoente de um elemento
 * A função pega nos dois elementos no topo da stack, eleva o primeiro à potência do segundo e devolve o resultado à stack.
 * @param s stack.
 * @param token operação lida.
 */
int expon(STACK *s, char *token);

/**
 * @brief A função aplica a operação bitwise AND.
 *
 * @param s stack.
 * @param token operação lida.
 */
int bitwiseAnd(STACK *s, char *token);

/**
 * @brief A função aplica a operação bitwise OR.
 *
 * @param s stack.
 * @param token operação lida.
 */
int bitwiseOr(STACK *s, char *token);

/**
 * @brief A função aplica a operação bitwise XOR.
 *
 * @param s stack.
 * @param token operação lida.
 */
int bitwiseXor(STACK *s, char *token);

/**
 * @brief A função aplica a operação bitwise NOT.
 *
 * @param s stack.
 * @param token operação lida.
 */
int bitwiseNot(STACK *s, char *token, VARS *arr);

#endif