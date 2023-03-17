#ifndef LOGICVAR_H
#define LOGICVAR_H

/**
 * @brief Operações do guião 3, se o token for um operador executa a operação correspondente.
 *
 * @param s Stack.
 * @param token String onde pode ter um operador.
 * @param arr Variáveis globais.
 */
int opsG3(STACK *s, char *token, VARS *arr);

/**
 * @brief Função que determina o valor lógico de um elemento da stack.
 *
 * @param x O elemento a ser avaliado.
 */
_Bool truthValue(STACK_ELEM x);

/**
 * @brief Função isEqual para longs.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 */
int equalLong(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief Função isEqual para doubles.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 */
int equalDouble(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief Função isEqual para chars.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 */
int equalChar(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief A função pega nos dois elementos no topo da stack e compara-os (se são iguais ou não) e devolve o resultado dessa comparação à stack.
 * @param s stack.
 * @param token operação lida.
 */
int isEqual(STACK *s, char *token);

/**
 * @brief A função retira o topo da stack, e devolve à stack a negação do valor logico do elemento retirado inicialmente.
 * @param s stack.
 * @param token operação lida.
 */
int negate(STACK *s, char *token);

/**
 * @brief Se os dois elementos no topo da stack tiverem valor lógico verdadeiro, a função retira o elemento superior e devolve-o à stack.
 * @param s stack.
 * @param token operação lida.
 */
int shortcutAnd(STACK *s, char *token);

/**
 * @brief Retira os dois elementos do topo da stack e envia para a stack o primeiro elemento verdadeiro que encontrar, se forem os dois falsos envia o ultimo falso.
 * @param s stack.
 * @param token operação lida.
 */
int shortcutOr(STACK *s, char *token);

/**
 * @brief A função retira os 3 elementos no topo da stack, se o primeiro tiver valor lógico true, a função devolve à stack o segundo elemento, caso contrário
 * (se o valor lógico do primeiro for false) a função devolve à stack o terceiro elemento.
 * @param s stack.
 * @param token operação lida.
 */
int ifThenElse(STACK *s, char *token);

/**
 * @brief Função isLower para longs.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 * @return int
 */
int lowerLong(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief Função isLower para doubles.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 * @return int
 */
int lowerDouble(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief Função isLower para chars.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 * @return int
 */
int lowerChar(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief A função pega nos dois elementos no topo da stack e compara-os (se anterior ao topo < topo), e devolve o resultado dessa comparação à stack.
 * @param s stack.
 * @param token operação lida.
 */
int isLower(STACK *s, char *token);

/**
 * @brief Função isHigher para longs.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 * @return int
 */
int higherLong(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief Função isHigher para double.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 * @return int
 */
int higherDouble(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief Função isHigher para chars.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 * @return int
 */
int higherChar(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief A função pega nos dois elementos do topo da stack e compara-os (se anterior ao topo > topo), e devolve o resultado dessa comparação à stack.
 * @param s stack.
 * @param token operação lida.
 */
int isHigher(STACK *s, char *token);

/**
 * @brief Função putLower para longs.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 * @return int
 */
int putLowerLong(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief Função putLower para doubles.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 * @return int
 */
int putLowerDouble(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief Função putLower para chars.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 * @return int
 */
int putLowerChar(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief A função retira dois elementos do topo da stack, compara-os e devolve o menor à stack.
 * @param s stack.
 * @param token operação lida.
 */
int putLower(STACK *s, char *token);

/**
 * @brief Função putHigher para longs.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 * @return int
 */
int putHigherLong(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief Função putHigher para doubles.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 * @return int
 */
int putHigherDouble(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief Função putHigher para chars.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 * @return int
 */
int putHigherChar(STACK *s, STACK_ELEM a, STACK_ELEM b);

/**
 * @brief A função retira dois elementos do topo da stack, compara-os e devolve o maior à stack.
 * @param s stack.
 * @param token operação lida.
 */
int putHigher(STACK *s, char *token);

/**
 * @brief A função verifica se o token é uma variável global, se sim, devolve o valor dessa variável no array à stack.
 * @param s stack.
 * @param token operação lida.
 * @param arr array com os valores das variáveis globais.
 */
int variable(STACK *s, char *token, VARS *arr);

#endif