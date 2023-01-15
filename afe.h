/*  Modulo para criacao de um automato finito com movimentos vazios.
 *  2019, Joao Marcello
 */

#ifndef AFE_H
#define AFE_H

#include<string>
#include<list>

using namespace std;


/*************************************************************************/
/*                                                                       */
/*               TIPOS ABSTRATOS DE DADOS UTILIZADOS                     */
/*                                                                       */
/*************************************************************************/


/*      Struct que represent uma transicao do automato.  */
typedef struct _transition_ {
	string lastState;
	char symbol;
	string newState;
}Transition;


/*      Struct que representa um automato.   */
typedef struct _automato_ {
    string initialState;
    list<string> finalStates;
    list<Transition> transitions;
}Automato;

/*************************************************************************/




/*************************************************************************/
/*                                                                       */
/*                        DECLARACAO DE FUNCOES                          */
/*                                                                       */
/*************************************************************************/


/*      Cria um automato.
 *  Recebe:
 *      - initialState: o estado inicial do automato.
 *  Retorna:
 *      - o automato criado.
 */
Automato createAutomato(string initialState);


/*     Adiciona uma transicao no automato. A transicao eh criada na funcao.
 *   Recebe:
 *      - autom: ponteiro para um automato;
 *      - state: o estado da transicao a ser adicionada;
 *      - c: o simbolo lido;
 *      - result: o estado seguinte.
 */
void addTransition(Automato *autom, string state, char c, string result);


/*      Adiciona um estado final no automato.
 *  Recebe:
 *      - autom: ponteiro para um automato;
 *      - state: o estado final a ser inserido.
 */
void addFinalState(Automato *autom, string state);


/*      Adiciona uma string em uma lista de string desde que a string informada
 *  nao esteja na lista.
 *  Recebe:
 *      - state: a string a ser adicionada;
 *      - r: ponteiro para lista de strings.
 *  Retorna:
 *      - true caso consiga adicionar a string na lista ou false caso contrario.
 */
bool addStateInResult(string state, list<string> *r);


/*    Calcula todos os estados atingiveis por um determinado estado
 *  incluindo os movimentos vazios.
 *  Recebe:
 *      - t: endereco de uma lista de transicoes;
 *      - state: o estado que sera calculado o fecho vazio;
 *  Retorna:
 *      - um lista de strings contendo todos os estados atingiveis pelo
 *        estado informado, incluindo os movimentos vazios.
 */
list<string> fechoVazio(list<Transition> *t, string state);


/*    Versao recursiva da funcao fecho vazio (eh usada somente na funcao fechoVazio).
 *  Calcula todos os estados atingiveis por um determinado estado incluindo os movimentos vazios.
 *  Recebe:
 *      - t: ponteiro para uma lista de transicoes;
 *      - state: o estado que sera calculado o fecho vazio;
 *      - r: o endereco de uma lista de strings que sera o resultado da funcao fechoVazioRec.
 */
void fechoVazioRec(list<Transition> *t, string state, list<string> *r);


/*    Calcula o fecho vazio de um conjunto de estados.
 *  Recebe:
 *      - t: ponteiro para uma lista de transicoes;
 *      - states: lista de strings com os estados a calcular o fecho vazio.
 *  Retorna:
 *      - uma lista de strings que representa a uniao dos resultados dos fechos vazios para
 *        cada estado na lista de string states.
 */
list<string> fechoVazioEst(list<Transition> *t, list<string> states);


/*      Implemetacao da funcao programa estendida de um automato finito com
 *  movimentos vazios. (Eh usada na funcao checkWord)
 *  Recebe:
 *      - t: ponteiro para uma lista de transicoes do automato;
 *      - states: o estado inicial do automato na forma de lista de strings;
 *      - str: uma palavra.
 *  Retorna:
 *      - uma lista de string que informa os estados retornados pela funcao ao
 *        processar a string str. Se a lista retornada possuir algum estado final,
 *        o automato aceita a palavra.
 */
list<string> funcProgramEst(list<Transition> *t, list<string> states, string str);


/*    Dado uma lista de strings que representam estados do automato, verifica quais desses
 *  estados produzem resultado ao lerem um caractere informado. (Eh usada na funcProgramEst)
 *  Recebe:
 *      - t: ponteiro para uma lista de transicoes;
 *      - states: lista de strings com os estados;
 *      - c: o caractere a ser lido pelo estado.
 *  Retorna:
 *      - uma lista de strings contendo todos os estados que possuem um resultado ao ler
 *        o caractere informado.
 */
list<string> applyCondition(list<Transition> *t, list<string> states, char c);


/*    Diz se uma lista de estados(strings) possui pelo menos um estado final.
 *  Recebe:
 *      - autom: o automato;
 *      - state: lista de strings com os estados a serem checados.
 *  Retorna:
 *      - true se algum elemento em state se encontra no conjunto de estados
 *        finais do automato, ou false caso contrario.
 */
bool gotFinalState(Automato autom, list<string> states);


/*      Dado um automato e uma palavra, diz se o automato aceita ou nao a palavra.
 *  Recebe:
 *      - autom: o automato;
 *      - palavra: a palavra;
 * Retorna:
 *      - true caso o automato aceita a palavra ou false caso contrario.
 */
bool checkWord(Automato autom, string str);


/*      Imprime uma lista de strings. (Usada para debug)
 */
void printVector(list<string> s);

/*************************************************************************/

#endif // AFE_H
