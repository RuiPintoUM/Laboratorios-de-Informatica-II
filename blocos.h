#ifndef BLOCOS_H
#define BLOCOS_H
/**
 * @brief Algumas operações de blocos, se o token for um operador executa a operação correspondente.
 *
 * @param s Stack.
 * @param token String que pode ter um operador.
 * @param arr Variáveis globais.

 */
int someBlockOps(STACK *s, char *token, VARS *arr);

/**
 * @brief Remove as chavetas de um bloco.
 *
 * @param string String com o bloco
 */
char *removeBrackets(char *string);

/**
 * @brief Executa um bloco, ou seja, aplica o que está no bloco à stack.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param arr Variáveis globais.
 */
int execBlock(STACK *s, STACK_ELEM a, VARS *arr);

/**
 * @brief Filtra um array ou string de acordo com a condição dada no bloco, devolvendo à stack apenas os valores verdadeiros de acordo com a condição.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param arr Variáveis globais.
 */
int filterByBlock(STACK *s, STACK_ELEM a, VARS *arr);

/**
 * @brief Executa o bloco enquanto o que fica no topo da stack tem valor lógico verdadeiro.
 *
 * @param s Stack.
 * @param token String que pode ter o operador.
 * @param arr Variáveis globais.
 */
int whileLoop(STACK *s, char *token, VARS *arr);

/**
 * @brief A função inverte uma string.
 *
 * @param str String.
 */
void strrev(char *str);

/**
 * @brief A função aplica o bloco a todos os elementos de um array ou string.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 * @param arr Variáveis globais.
 */
int applyBlock(STACK *s, STACK_ELEM a, STACK_ELEM b, VARS *arr);

/**
 * @brief A função dá fold sobre um array ou string usando um bloco, ou seja, vai execuntando a operação e guardando o resultado da execução anterior.
 *
 * @param s Stack.
 * @param a Elemento da stack.
 * @param b Elemento da stack.
 * @param arr Variáveis globais.
 */
int fold(STACK *s, STACK_ELEM a, STACK_ELEM b, VARS *arr);

/**
 * @brief Função isLowerSort para longs.
 *
 * @param b Elemento da stack.
 * @param a Elemento da stack.
 */
int lowerLongSort(STACK_ELEM b, STACK_ELEM a);

/**
 * @brief Função isLowerSort para doubles.
 *
 * @param b Elemento da stack.
 * @param a Elemento da stack.
 */
int lowerDoubleSort(STACK_ELEM b, STACK_ELEM a);

/**
 * @brief Função isLowerSort para chars.
 *
 * @param b Elemento da stack.
 * @param a Elemento da stack.
 */
int lowerCharSort(STACK_ELEM b, STACK_ELEM a);

/**
 * @brief Função isLowerSort para arrays.
 *
 * @param b Elemento da stack.
 * @param a Elemento da stack.
 */
int lowerStrArrSort(STACK_ELEM b, STACK_ELEM a);

/**
 * @brief A função compara dois elementos da stack, se (b < a) retorna 1 (verdadeiro) senão retorna 0 (falso).
 *
 * @param b Elemento da stack.
 * @param a Elemento da stack.
 */
int isLowerSort(STACK_ELEM b, STACK_ELEM a);

/**
 * @brief Função para ordenar dois arrays através do array com os resultados das execuções do bloco.
 *
 * @param arr Array com os resultados das execuções do bloco.
 * @param elems Array com os elementos originais.
 * @param N Tamanho dos arrays.
 */
void sortArr(STACK_ELEM *arr, STACK_ELEM *elems, int N);

/**
 * @brief A função inverte a ordem dos elementos de um array.
 * @param arr array.
 * @param N tamanho do array.
 */
void arrRev(STACK_ELEM *arr, int N);

/**
 * @brief A função ordena um array ou string de acordo com a condição dada no bloco.
 *
 * @param s Stack.
 * @param block Elemento da stack.
 * @param arr Variáveis globais.
 */
int sortOn(STACK *s, STACK_ELEM block, VARS *arr);

/**
 * @brief Lê e devolve o elemento no topo da stack (operação peek).
 *
 * @param s Stack.
 * @param token String que pode conter o operador.
 */
int peekStack(STACK *s, char *token);
ºªªªªªªªºº
#endif