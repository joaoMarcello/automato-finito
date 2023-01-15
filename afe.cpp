/*  Implementacao do modulo para criacao de um automato finito com movimentos vazios.
 *  2019, Joao Marcello
 */

#ifndef AFE_CPP
#define AFE_CPP

#ifndef my_iterator
#define my_iterator list<string>::iterator
#endif // my_iterator

#include <iostream>
#include <list>
#include "afe.h"
using namespace std;


/*************************************************************************/
/*                                                                       */
/*               IMPLEMENTACAO DAS FUNCOES DECLARADAS                    */
/*                                                                       */
/*************************************************************************/


/*      Cria um automato.
 *  Recebe:
 *      - initialState: o estado inicial do automato.
 *  Retorna:
 *      - o automato criado.
 */
Automato createAutomato(string initialState){
    Automato autom;
    autom.initialState = initialState;
    return autom;
}


/*     Adiciona uma transicao no automato. A transicao eh criada na funcao.
 *   Recebe:
 *      - autom: ENDERECO do automato;
 *      - state: o estado da transicao a ser adicionada;
 *      - c: o simbolo lido;
 *      - result: o estado seguinte.
 */
void addTransition(Automato *autom, string state, char c, string result){
    Transition t;
    t.lastState = state;
    t.symbol = c;
    t.newState = result;

    autom->transitions.push_back(t);
}


/*      Adiciona um estado final no automato.
 *  Recebe:
 *      - autom: ponteiro para um automato;
 *      - state: o estado final a ser inserido.
 */
void addFinalState(Automato *autom, string state){
    autom->finalStates.push_back(state);
}


/*      Adiciona uma string em uma lista de string desde que a string informada
 *  nao esteja na lista.
 *  Recebe:
 *      - state: a string a ser adicionada;
 *      - r: ponteiro para a lista de strings.
 *  Retorna:
 *      - true caso consiga adicionar a string na lista ou false caso contrario.
 */
bool addStateInResult(string state, list<string> *r){

    // percorrendo os elementos de r
	for (my_iterator it = r->begin(); it != r->end(); it++ ) {

        // se o elemento atual de r eh igual ao estado informado,
        // state nao eh adicionada na lista
		if (it->compare(state) == 0)
			return false;
	}

	r->push_back(state);
	return true;
}


/*    Calcula todos os estados atingiveis por um determinado estado
 *  incluindo os movimentos vazios.
 *  Recebe:
 *      - t: ponteiro para uma lista de transicoes;
 *      - state: o estado que sera calculado o fecho vazio;
 *  Retorna:
 *      - um lista de strings contendo todos os estados atingiveis pelo
 *        estado informado, incluindo os movimentos vazios.
 */
list<string> fechoVazio(list<Transition> *t, string state) {
	list<string> r;
	r.push_back(state);
	fechoVazioRec(t, state, &r);
	return r;
}


/*    Versao recursiva da funcao fecho vazio (eh usada somente na funcao fechoVazio).
 *  Calcula todos os estados atingiveis por um determinado estado incluindo os movimentos vazios.
 *  Recebe:
 *      - t: ponteiro para uma lista de transicoes;
 *      - state: o estado que sera calculado o fecho vazio;
 *      - r: o endereco de uma lista de strings que sera o resultado da funcao fechoVazioRec.
 */
void fechoVazioRec(list<Transition> *t, string state, list<string> *r) {

    // percorrendo cada transicao na lista t
	for (list<Transition>::iterator tr = t->begin(); tr != t->end(); tr++)

        // se encontrou o estado procurado e ele gera resultado ao
        // ler o caractere vazio
		if (tr->lastState.compare(state) == 0 && tr->symbol == ' ') {

		    // tenta adicionar o estado na lista r e guarda o resultado
		    // dessa operacao
			bool result = addStateInResult(tr->newState, r);

            // se conseguiu adicionar, eh necessario adicionar no resultado
            // os estados do fecho vazio do estado adicionado que ainda nao
            // estao no resultado
			if (result)
				fechoVazioRec(t, tr->newState, r);
		}
}


/*    Calcula o fecho vazio de um conjunto de estados.
 *  Recebe:
 *      - t: ponteiro para uma lista de transicoes;
 *      - states: lista de strings com os estados a calcular o fecho vazio.
 *  Retorna:
 *      - uma lista de strings que representa a uniao dos resultados dos fechos vazios para
 *        cada estado na lista de string states.
 */
list<string> fechoVazioEst(list<Transition> *t, list<string> states) {
	list<string> result;

    // percorrendo cada estado na lista states
	for (my_iterator st = states.begin(); st != states.end(); st++){

        // calculando o fecho vazio do estado atual
		list<string> f = fechoVazio(t, *st);

        // percorrendo cada estado do fecho vazio do elemento atual
		for (my_iterator sf = f.begin(); sf != f.end(); sf++)
            // adiciona o estado no resultado caso ele ja nao esteja no resultado
			addStateInResult(*sf, &result);
	}

	return result;
}


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
list<string> funcProgramEst(list<Transition> *t, list<string> states, string str) {

	/*if (str.compare("") == 0)
		return fechoVazioEst(t, states);
	else {

        // a palavra informada menos o primeiro caractere
		string sub = str.substr(1, str.length() - 1);

        // fecho vazio estendido dos estados
		list<string> fe = fechoVazioEst(t, states);

		// aplicando a condicao para extrair da lista fe apenas
		// os elementos que geram um resultado ao lerem o primeiro
		// caractere da palavra informada
		list<string> f = applyCondition(t, fe, str.at(0));

		return funcProgramEst(t, f, sub);
	}*/


	if (str.compare("") == 0)
		return fechoVazioEst(t, states);
	else {
        // a palavra informada menos o ultimo caractere
        string sub = str.substr(0, str.length() - 1);

        // aplicando a funcao programa estendida recursivamente usando a substring
        list<string> s = funcProgramEst(t, states, sub);

        // extraindo da lista s os resultados da aplicacao da funcao programa
		// nos estados na lista s ao lerem o ultimo caractere da string
        list<string> r = applyCondition(t, s, str.at(str.length() - 1));

        // aplicando a funcao fecho vazio estendido na lista de estados r
        r = fechoVazioEst(t, r);

        return r;
	}

}


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
list<string> applyCondition(list<Transition> *t, list<string> states, char c) {
	list<string> r;

    // percorrendo cada estado na lista states
	for (my_iterator st = states.begin(); st != states.end(); st++) {

        // percorrendo cada transicao na lista t
		for (list<Transition>::iterator tr = t->begin(); tr != t->end(); tr++) {

            // se o estado da transicao atual eh igual ao estado atual da lista states e
            // o caracter lido da transicao atual eh igual ao caracter informado
			if (st->compare(tr->lastState) == 0 && (tr->symbol == c))
				addStateInResult(tr->newState, &r);
		}
	}
	return r;
}


/*    Diz se uma lista de estados(strings) possui pelo menos um estado final.
 *  Recebe:
 *      - autom: o automato;
 *      - state: lista de strings com os estados a serem checados.
 *  Retorna:
 *      - true se algum elemento em state se encontra no conjunto de estados
 *        finais do automato, ou false caso contrario.
 */
bool gotFinalState(Automato autom, list<string> states) {

    // percorrendo cada estado final do automato
    for(my_iterator finalState = autom.finalStates.begin(); finalState != autom.finalStates.end(); finalState++)

        // percorrendo cada estado na lista states
		for(my_iterator state = states.begin(); state != states.end(); state++)

            // se o estado final atual do automato for igual ao estado atual
            // em state
			if (finalState->compare(*state) == 0)
				return true;
	return false;
}


/*      Dado um automato e uma palavra, diz se o automato aceita ou nao a palavra.
 *  Recebe:
 *      - autom: o automato;
 *      - palavra: a palavra;
 * Retorna:
 *      - true caso o automato aceita a palavra ou false caso contrario.
 */
bool checkWord(Automato autom, string str) {
    list<string> v;
        v.push_back(autom.initialState);

	return gotFinalState(autom, funcProgramEst(&(autom.transitions), v, str) );
}


/*      Imprime uma lista de strings. (Usada para debug)
 */
void printVector(list<string> s) {
	for (my_iterator it = s.begin(); it != s.end(); it++)
		cout << *it << "  ";
	cout << endl;
}


#endif // AFE_CPP
