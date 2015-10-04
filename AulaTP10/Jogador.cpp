#include "Jogador.h"
// Alínea A
void Jogador::adicionaAposta(const Aposta &ap){
	apostas.insert(ap);
}


// Alínea B
int Jogador::apostasNoNumero(int num) const{

	HashApostas::const_iterator it;
	int c=0;
	for (it=apostas.begin(); it!=apostas.end(); it++)
		if (it->contem(num)) c++;
	return c;

}

