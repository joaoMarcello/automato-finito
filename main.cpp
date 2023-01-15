/*      Atividade de Linguagens Formais e Automatos valendo a terceira nota.
 *
 *  2019, Joao Marcello.
 */
#include <iostream>
#include <string>
#include "afe.h"
using namespace std;


/*************************************************************************/
/*                                                                       */
/*                              MAIN                                     */
/*                                                                       */
/*************************************************************************/

/*		FUNCAO PRINCIPAL. Cria-se o automato, adicionando seus estados
 *  finais, transicoes e estado inicial. Em seguida, le-se uma palavra
 *  inserida pelo usuario e diz se o automato gera ou nao aquela palavra.
 *  O programa finaliza ao informar a palavra 'quit' ou pressionar as
 *  teclas ctrl + Z.
 */
int main(){

    // criando o automato passando o estado inicial como parametro
    Automato autom = createAutomato("q0");

    // adicionando os estados finais
    addFinalState(&autom, "q2");
    addFinalState(&autom, "q5");

    // adicionando as transicoes
    addTransition(&autom, "q0", 'a', "q1");
    addTransition(&autom, "q0", 'b', "q3");

    addTransition(&autom, "q1", ' ', "q2");
    addTransition(&autom, "q1", ' ', "q3");

    addTransition(&autom, "q2", 'c', "q2");
    addTransition(&autom, "q2", 'b', "q4");

    addTransition(&autom, "q3", 'b', "q4");

    addTransition(&autom, "q4", 'b', "q5");


	string palavra;

    cout << ">>> ";

	// ler palavra e checa se eh diferente de 'quit'
	while (cin >> palavra && palavra.compare("quit") != 0) {
		cout << ">>> A palavra '" << palavra << "' foi "
             << (checkWord(autom, palavra) ? "ACEITA." : "REJEITADA.") << endl;

		cout << ">>> ";
	}

    cout << ">>> Programa encerrado.\n\n";

    return 0;
}
