#ifndef CONVSTACKMANIP_H
#define CONVSTACKMANIP_H

/**
 * @brief Operações do guião 2, se o token for um operador executa a operação correspondente.
 *
 * @param s Stack.
 * @param token String que pode conter um operador.
 * @param arr Variáveis globais.
 */
int opsG2(STACK *s, char *token, VARS *arr);

/**
 * @brief A função duplica o topo da stack.
 * @param s stack.
 * @param token operação lida.
 */
int duplicate(STACK *s, char *token);

/**
 * @brief A função dá pop à stack.
 * @param s stack.
 * @param token operação lida.
 */
int sacar(STACK *s, char *token);

/**
 * @brief A função troca os dois elemntos do topo da stack.
 * @param s stack.
 * @param token operação lida.
 */
int switchTop(STACK *s, char *token);

/**
 * @brief A função roda os 3 elementos no topo da stack.
 * @param s stack.
 * @param token operação lida.
 */
int rodar(STACK *s, char *token);

/**
 * @brief A função copia o n-ésimo elemento para o topo da stack, sendo que 0 é o indice do topo da stack.
 * @param s stack.
 * @param token operação lida.
 */
int toTop(STACK *s, char *token, VARS *arr);

/**
 * @brief A função pega no elemento do topo da stack e converte-o num inteiro.
 * @param s stack.
 * @param token operação lida.
 */
int convToLong(STACK *s, char *token);

/**
 * @brief A função pega no elemento do topo da stack e converte-o num double.
 * @param s stack.
 * @param token operação lida.
 */
int convToDouble(STACK *s, char *token);

/**
 * @brief A função pega no elemento do topo da stack e converte-o num char.
 * @param s stack.
 * @param token operação lida.
 */
int convToChar(STACK *s, char *token);

/**
 * @brief A função pega no elemento do topo da stack e converte-o para uma string.
 * @param s stack.
 * @param token operação lida.
 */
int convToString(STACK *s, char *token);

/**
 * @brief A função lê uma linha.
 * @param s stack.
 * @param token Operação lida.
 */
int readLine(STACK *s, char *token);

#endif