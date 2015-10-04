#include "Jogo.h"
// Alínea A
void Jogo::insereCrianca(Crianca &c1) {
	criancas.push_back(c1);
}
const list<Crianca>& Jogo::getCriancasJogo() const {
	return criancas;
}
// Alínea B
string Jogo::escreve() {
	stringstream ss;
	list<Crianca>::iterator it;
	for (it = criancas.begin(); it != criancas.end(); it++) {
		ss << it->getNome() << " : " << it->getIdade() << endl;
	}
	return ss.str();
}

// Alínea C
int Jogo::nPalavras(string frase) {
	int soma = 1;
	for (int unsigned i = 0; i < frase.size(); i++)
		if (frase[i] == ' ')
			soma++;
	return soma;
}
// Alínea D
Crianca& Jogo::perdeJogo(string frase) {
    int total=nPalavras(frase);
	list<Crianca>::iterator it=criancas.begin();
	while (criancas.size()>1){
		for (int i=0; i< total; i++){
			it++;
			if (it==criancas.end()) it=criancas.begin();}
		it=criancas.erase(it);
	}
	return criancas.front();

}
// Alínea E
list<Crianca>& Jogo::inverte() {
	criancas.reverse();
	return criancas;
}
// Alínea F
list<Crianca> Jogo::divide(int id){
	list<Crianca>::iterator it;
	list<Crianca> aux;
	for (it=criancas.begin();it!=criancas.end(); it++){
		if (it->getIdade()>id) {
			aux.push_back(*it);
			it=criancas.erase(it);
			it--;
		}
	}
	return aux;
}


// Alínea G
bool Jogo::operator==(Jogo& j2){
	list<Crianca>::iterator it1,it2;
	for (it1=criancas.begin(), it2=j2.criancas.begin(); it1!=criancas.end() && it2!=j2.criancas.end(); it1++,it2++){
		if (it1->getNome()!=it2->getNome()) return 0;
	}
	return 1;
}

// Alínea H
list<Crianca> Jogo::baralha(const list<Crianca>& lista){
	list<Crianca> aux=criancas;
	list<Crianca>::iterator it=aux.begin();
	for (int unsigned i=0; i<aux.size(); i++){
		Crianca temp(it->getNome(), it->getIdade());
		int gerado=rand()% aux.size();
		list<Crianca>::iterator git=aux.begin();
		for (git=aux.begin(); gerado; gerado--){
			git++;
		}
		*it=*git;
		*git=temp;
		it++;
	}
	return aux;
}
