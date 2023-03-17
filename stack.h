#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

/**
 * @brief Todos os tipos possiveis para elementos da stack.
 *
 */
typedef enum
{
    LONG,   /**< Tipo long */
    DOUBLE, /**< Tipo double */
    CHAR,   /**< Tipo char */
    STRING, /**< Tipo string */
    ARRAY,  /**< Tipo array */
    BLOCO   /**< Tipo bloco */
} TYPES;

/**
 * @brief Forward declaration de STACK_ELEM.
 *
 */
typedef struct STACK STACK;

/**
 * @brief Struct que guarda o tipo e conteudo de um elemento da stack.
 *
 */
typedef struct STACK_ELEM
{
    TYPES t; /**< Tipo do elemento, vem do enum TYPES*/
    union
    {
        long l;     /**< Espaço na memoria para um long */
        double d;   /**< Espaço na memoria para um double */
        char c;     /**< Espaço na memoria para um char */
        char *str;  /**< Espaço na memoria para uma string */
        STACK *arr; /**< Espaço na memoria para um array */
        char *bl;   /**< Espaço na memoria para um bloco */
    } elem;         /**< Conteúdo do elemento */
} STACK_ELEM;

/**
 * @brief Struct que define a stack.
 *
 */
typedef struct STACK
{
    int size;           /**< tamanho da stack */
    STACK_ELEM *values; /**< Array com os elementos da stack */
    int sp;             /**< Apontador para o topo da stack */
} STACK;

/**
 * @brief Variáveis globais.
 *
 */
typedef struct VARIABLES
{
    STACK_ELEM var[26]; /**< Array com espaço para as variáveis todas */
} VARS;

/**
 * @brief A função cria uma stack.
 */
STACK *newstack();
/**
 * @brief A função duplica o tamanho da stack.
 *
 * @param s
 */
int increaseS(STACK *s);

/**
 * @brief A funçã coloca o elemento no topo da stack, caso a stack esteja cheia é primeiro chamada a função responsável por aumentar o tamanho e de seguida é colocado o elemento.
 * @param s stack.
 * @param elem elemento que é devolvido à stack.
 */
void push(STACK *s, STACK_ELEM elem);

/**
 * @brief Se a stack estiver vazia, a função imprime uma mensagem ("Stack Vazia"), caso contrario diminui o ponteiro e devolve o elemento no topo da stack.
 * @param s stack.
 */
STACK_ELEM pop(STACK *s);

/**
 * @brief A função verifica se a stack está vazia.
 * @param s stack.
 */
int isEmpty(STACK *s);

/**
 * @brief A função devolve o elemento do topo da stack.
 * @param s stack.
 */
STACK_ELEM peek(STACK *s);

/**
 * @brief A função imprime o conteúdo da stack.
 * @param s Stack.
 * @param token string para strcmp.
 */
int debugStack(STACK *s, char *token);

/**
 * @brief A função inicializa as variáveis globais.
 */
VARS *initVars();

#endif