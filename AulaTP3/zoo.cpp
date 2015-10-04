/*
	Autor: André Freitas
	Email: p.andrefreitas@gmail.com
*/
#include "zoo.h"
#include <stdlib.h>
// Alínea A
Veterinario::Veterinario(string n, long cod){
	nome=n;
	codOrdem=cod;
}

int Animal::maisJovem=1000;

Animal::Animal(string n, int i){
	nome=n;
	idade=i;
	if(i<maisJovem) maisJovem=i;
}
string Animal::getNome(){
	return nome;
}
int Animal::getMaisJovem(){
	return maisJovem;
}

Cao::Cao(string n, int i, string r):Animal(n,i){
	raca=r;
}
Voador::Voador(int vmax, int amax){
	 velocidade_max=vmax;
	 altura_max=amax;
}
Morcego::Morcego(string n, int i,int vmax, int amax):Animal(n,i),Voador(vmax,amax){
}
// Alínea B
void Zoo::adicionaAnimal(Animal *a1){
	animais.push_back(a1);
}
int Zoo::numAnimais(){
	return animais.size();
}
// Alínea C
string  Animal::imprime(){
	stringstream ss;
	ss << nome << ", ";
	ss << idade << ", ";
	return ss.str();
}
string Cao::imprime(){
	stringstream ss;
	ss << Animal::imprime();
	ss << raca;
	return ss.str();
}
string  Voador::imprime(){
	stringstream ss;
	ss << velocidade_max << ", ";
	ss << altura_max;
	return ss.str();
}

string  Morcego::imprime(){
	stringstream ss;
	ss<<Animal::imprime();
    ss<<Voador::imprime();
	return ss.str();
}
string Zoo::imprime(){
	stringstream ss;
	for (int unsigned i=0; i<animais.size(); i++){
		ss<< animais[i]->imprime();
		ss << "\n";
	}
	return ss.str();
}

// Alínea D
bool Cao::eJovem(){
	return idade<5;
}

bool Morcego::eJovem(){
	return idade<4;
}

bool Zoo::animalJovem(string nomeA){
	for (int unsigned i=0; i<animais.size(); i++)
		if (animais[i]->getNome()==nomeA) return animais[i]->eJovem();
	return 0;
}
// Alínea E
void Zoo::alocaVeterinarios(istream &isV){
	vector<Veterinario> temporario;
	// (1) Não colocar directamente no vector de ponteiros!!
	while(isV.good()){
		string n;
		string cod;
		getline(isV,n);
		getline(isV,cod);
		long codlong=atoi(cod.c_str());
		Veterinario aux(n,codlong);
		temporario.push_back(aux);
	}
	// (2) Associar ao vector de ponteiros
	for (int unsigned i=0; i<temporario.size(); i++){
		veterinarios.push_back(&temporario[i]);
	}

}

int Zoo::numVeterinarios(){
	return veterinarios.size();
}
// Alínea F
bool Zoo::removeVeterinario(string nomeV){
	bool exist=0;
	int unsigned i;
	for ( i=0; i<veterinarios.size(); i++){
		if(veterinarios[i]->nome==nomeV){
			exist=1;
			break;
		}
	}
	if (exist) {
		veterinarios.erase(veterinarios.begin()+i);
		return 1;
	}
	else return 0;

}
// Alínea G
// Não não pode, porque assim iria dar erro com o acesso com ->

// Alínea H
int Zoo::somaIdades(){
	int soma=0;
	for (int unsigned i=0; i<animais.size(); i++){
		soma+=animais[i]->getIdade();
	}
	return soma;
}

bool Zoo::operator < (Zoo& zoo2) {
	int proprio=somaIdades();
	return  proprio< zoo2.somaIdades();
}
