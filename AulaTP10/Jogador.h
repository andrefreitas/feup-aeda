#ifndef JOGADOR_H_
#define JOGADOR_H_

#include "Aposta.h"
#include <string>

using namespace std;

// É NECESSÁRIO DEFINIR
struct apostaHash
{
	int operator()(Aposta numeros) const{
		hash_set<int>::const_iterator it;
		int soma=0;
		for (it=numeros.getNumeros().begin(); it!=numeros.getNumeros().end(); it++){
				soma+= *(it);
		}
		return soma;
	}
	bool operator()(Aposta a,Aposta b)const {
		hash_set<int>::const_iterator  it;

		int soma1=0;
		for (it=a.getNumeros().begin(); it!=a.getNumeros().end(); it++)
			soma1+= *(it);

		int soma2=0;
		for (it=b.getNumeros().begin(); it!=b.getNumeros().end(); it++)
			soma2+= *(it);

		return soma1==soma2;
	}
};

typedef hash_set<Aposta, apostaHash, apostaHash> HashApostas;

class Jogador
{
	HashApostas apostas;
	string nome;
public:
	Jogador(string nm="anónimo") { nome=nm; }
	void adicionaAposta(const Aposta & ap);
	int apostasNoNumero(int num) const;
	HashApostas apostasSorteadas(const hash_set<int> & sorteio) const;
	int getNumApostas() const { return apostas.size(); }
};

#endif /*JOGADOR1_H_*/
