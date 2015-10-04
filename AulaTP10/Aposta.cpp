#include "Aposta.h"
// Alinea A
void Aposta::geraAposta(const vector<int> &valores, int n){
	int i=0;
	while(n){
		if (numeros.find(valores[i])==numeros.end()){
			numeros.insert(valores[i]);
			n--;
		}
		i++;
	}
}
// Alínea B
bool Aposta::contem(int num) const{
	return numeros.find(num)!=numeros.end();
}

// Alínea C
string Aposta::imprimeAposta() const{
	stringstream ss;
	hash_set<int>::iterator it;
	for (it=numeros.begin(); it!=numeros.end(); it++){
		ss << *it << "\nl";
	}
	return ss.str();
}

// Alínea D
int Aposta::calculaCertos(const hash_set<int> &sorteio) const{
	hash_set<int>::iterator it;
	int c =0;
	for (it=numeros.begin(); it!=numeros.end(); it++)
		if (sorteio.find(*it)!=sorteio.end()) c++;
	return c;
}
