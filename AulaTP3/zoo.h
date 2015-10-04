/*
	Autor: André Freitas
	Email: p.andrefreitas@gmail.com
*/

#ifndef ZOO_H_
#define ZOO_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;


class Veterinario {
	long codOrdem;
public:
	string nome;
	string imprime(){
		stringstream ss;
		ss << nome<<", ";
		ss << codOrdem;
		return ss.str();
	}
	Veterinario(string n, long cod);
	Veterinario(){};
	string getNome(){ return nome;};
};

class Animal {
protected:
	string nome;
	int idade;
	Veterinario *vet;
	static int maisJovem;
public:
	virtual string imprime();  // imprime nome e idade do animal e nome do veterinário
	virtual bool eJovem(){ return 0;};
	static int getMaisJovem();
	Animal(string n, int i);
	string getNome();
	friend class Zoo;
	int getIdade(){ return idade; };
};



class Cao: public Animal {
	string raca;
public:
	Cao(string n, int i, string r);
	string imprime();
	bool eJovem();
};



class Voador {
	int velocidade_max;
	int altura_max;
public:
	virtual string imprime();  // imprime valor de velocidade e altitude máxima
	Voador(int vmax, int amax);
};



class Morcego: public Animal, public Voador {
public:
	Morcego(string n, int i,int vmax, int amax);
	string imprime();
	bool eJovem();
};


class Zoo {
	vector<Animal *> animais;
	vector<Veterinario *> veterinarios;
public:
	void adicionaAnimal(Animal *a1);
	string imprime();
	bool animalJovem(string nomeA);
	void alocaVeterinarios(istream &isV);
	bool removeVeterinario(string nomeV);
	bool operator < (Zoo& zoo2);
	int numAnimais();
	int numVeterinarios();
	int somaIdades();
};


#endif /* ZOO_H_ */
