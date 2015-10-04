/*
 * Crianca.h
 *
 *  Created on: 31 de Out de 2010
 *      Author: RRossetti
 */

#ifndef CRIANCA_H_
#define CRIANCA_H_

#include <string>
#include <sstream>
using namespace std;

class Crianca {
	string nome;
	int idade;
public:
	Crianca(): nome(""), idade(0){}
	Crianca(string nome, int idade): nome(nome), idade(idade){}
	Crianca(const Crianca& c1){
		this->nome = c1.nome;
		this->idade = c1.idade;
	}
	string getNome() const{ return this->nome; }
	int getIdade() const{ return this->idade; }
	bool operator==(const Crianca& c2) const{ return( this->nome == c2.nome && this->idade == c2.idade); }
	bool operator!=(const Crianca& c2) const{ return( this->nome != c2.nome || this->idade != c2.idade); }
	Crianca& operator=(const Crianca& c2){
		if( this != &c2){
			this->nome = c2.nome;
			this->idade = c2.idade;
		}
		return *this;
	}

	friend ostream & operator<<(ostream & o, const Crianca & d) {
		o << d.nome << " " << d.idade << endl;
		return o;
	}

	string escreve(){
		stringstream oss;
		oss << nome << " : " << idade;
		return oss.str();
	}
};

#endif /* CRIANCA_H_ */
