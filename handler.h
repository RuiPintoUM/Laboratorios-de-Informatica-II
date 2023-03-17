#ifndef HANDLER_H
#define HANDLER_H

/**
 * @brief Esta função engloba todas as operações do projeto.
 *
 * @param s Stack.
 * @param token String que pode conter um operador.
 * @param arr variáveis globais.
 */
int operations(STACK *s, char *token, VARS *arr);

/**
 * @brief Verifica se uma string deverá ser enviada como long para a stack.
 *
 * @param token String que a função recebe e que vai ser avaliada.
 * @return int Retorna 0 se não for long e 1 se for.
 */
int checkLong(char *token);

/**
 * @brief Verifica se uma string deverá ser enviada como double para a stack.
 *
 * @param token String que a função recebe e que vai ser avaliada.
 * @return int Retorna 0 se não for double e 1 se for.
 */
int checkDouble(char *token);

/**
 * @brief Função que converte e envia os tipos numéricos para a stack e trata dos operadores.
 *
 * @param s A stack.
 * @param token String a ser enviada se passar as verificações.
 * @param arr Variáveis globais da stack que sao necessárias para algumas funções.
 * @return int Retorna 1 se a função tratou do token e retorna 0 se não.
 */
int tHandler(STACK *s, char *token, VARS *arr);

/**
 * @brief Função que envia strings para a stack.
 *
 * @param s Stack.
 * @param token String que se quer enviar, sabendo-se já que é uma string que se quer.
 */
void strHandler(STACK *s, char *token);

/**
 * @brief Função que envia arrays para a stack.
 *
 * @param s Stack.
 * @param token String que contem o conteudo do array, sabendo já que é um array que se quer.
 * @param arr Variáveis globais da stack que sao necessárias para certas funções.
 */
void arrHandler(STACK *s, char *token, VARS *arr);

/**
 * @brief Função que envia blocos para a stack.
 *
 * @param s Stack.
 * @param token String que se quer enviar como bloco, sabendo já que se quer um bloco.
 */
void bHandler(STACK *s, char *token);

/**
 * @brief Função para avançar no input depois de dar parse a uma string.
 *
 * @param string String original, de modo a saber até onde avançar.
 * @return int Retorna 0 se não for uma string (ou seja, não houverem aspas) e o tamanho do avanço se for uma string, sendo possivel calcular o avanço.
 */
int strJump(char *string);

/**
 * @brief Função para avançar no input depois de dar parse a um array.
 *
 * @param string String completa com o array, de modo a saber até onde avançar.
 * @return int Retorna 0 se não for um array e o valor do avanço se for um array, pois é possivel calcular o avanço.
 */
int arrJump(char *string);

/**
 * @brief Função para avançar no input para tipos numéricos e operadores.
 *
 * @param string String completa com o número/operador, de modo a saber até onde avançar.
 * @return int Returna o valor do avanço se for um número/operador e 0 se não.
 */
int tokenJump(char *string);

/**
 * @brief Função para avançar no input depois de dar parse a um bloco.
 *
 * @param string String completa com o bloco, de modo a saber até onde avançar.
 * @return int Retorna o valor do avanço.
 */
int blockJump(char *string);

/**
 * @brief Função para dar parse a uma string.
 *
 * @param string String a averiguar sobre a existência de strings (exitência de aspas).
 * @return char* Retorna apenas a string (sem as aspas) ou NULL se não houver uma string.
 */
char *tryParseString(char *string);

/**
 * @brief Função para dar parse a um array.
 *
 * @param string String a averiguar sobre a existência de arrays (existência de parênteses retos).
 * @return char* Retorna o conteúdo do array (sem os parênteses retos) ou NULL se não existir um array na string.
 */
char *tryParseArray(char *string);

/**
 * @brief Função para dar parse a um bloco.
 *
 * @param string String a averiguar sobre a existência de blocos (existência de chavetas).
 * @return char* Retorna NULL se não houver blocos na string ou o próprio bloco (com chavetas) se existir tal bloco na string.
 */
char *tryParseBlock(char *string);

/**
 * @brief Função para dar parse a números e operadores.
 *
 * @param string String a averguiar quanto à existência de operadores ou números (separados por espaços ou com \n(no fim da linha));
 * @return char* Retorna NULL se não for um número/operador e o próprio número/operador se for.
 */
char *tryParseToken(char *string);

/**
 * @brief Função para dar parse a todo o input, sabendo já qual é o input.
 *
 * @param s Stack.
 * @param linha Input.
 * @param arr Variáveis globais, usam-se em certas funções.
 */
void parseAfterInput(STACK *s, char *linha, VARS *arr);

/**
 * @brief Parser da stack, recebe o input.
 *
 * @param s Stack.
 * @param arr Variáveis globais para certas funções.
 */
void parser(STACK *s, VARS *arr);

/**
 * @brief Função para dar print à stack, para todos os tipos.
 *
 * @param s Stack que se quer dar print.
 */
void printStack(STACK *s);

#endif