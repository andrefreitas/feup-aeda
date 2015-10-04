/*
	Autor: André Freitas
	Email: p.andrefreitas@gmail.com
*/
#include <iostream>
#include <vector>

using namespace std;

/**
 * Versão da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);
// --------------------------------------------------------------------
// Alínea B com overloading do operator <<
template <class N>
class NoRepetido{
public:
	N info;
	NoRepetido(N i){
		info=i;
	};
};

template <class N>
ostream & operator<<(ostream &out, const NoRepetido<N> &b){
		out<< "No repetido: " << b.info;
		return out;
	}

// Alínea C com overloading do operator <<
template <class N>
class ArestaRepetida{
public:
	N inicio;
	N fim;
	ArestaRepetida(N i, N f){
		inicio=i;
		fim=f;
	}
};
template <class N>
ostream & operator<<(ostream &out, const ArestaRepetida<N> &b){
		out<< "Aresta repetida: " << b.inicio << " , "<< b.fim;
		return out;
	}

template <class N>
class NoInexistente{
public:
	N info;
	NoInexistente(N i){
		info=i;
	};
};

template <class N>
ostream & operator<<(ostream &out, const NoInexistente<N> &b){
		out<< "No inexistente: " << b.info;
		return out;
	}

// Alínea D com overloading do operador <<
template <class N>
class ArestaInexistente{
public:
	N inicio;
	N fim;
	ArestaInexistente(N i, N f){
		inicio=i;
		fim=f;
	}
};

template <class N>
ostream & operator<<(ostream &out, const ArestaInexistente<N> &b){
		out<< "Aresta inexistente: " << b.inicio << " , "<< b.fim;
		return out;
	}
// --------------------------------------------------------------------
// Alínea A
template <class N, class A>
Grafo<N,A>::Grafo(){

}

template <class N, class A>
Grafo<N,A>::~Grafo(){

}

template <class N, class A>
int Grafo<N,A>::numNos(void) const{
	return nos.size();
}

template <class N, class A>
int Grafo<N,A>::numArestas(void) const{
	int soma=0;
	for (int unsigned i=0; i<nos.size(); i++){
		soma+=nos[i]->arestas.size();
	}
	return soma;
}
// Alínea B
template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirNo(const N &dados){
	// (1) verificar se existe
	bool existe=0;
	for (int unsigned i=0; i<nos.size(); i++)
		if(nos[i]->info==dados) existe=1;
	// (2)Processar
	if(existe){
		throw NoRepetido<N>(dados);
	}
	else{
		No<N,A> *p;
		p= new No<N,A>(dados);
		nos.push_back(p);
	}
	return *this;
}
// Alínea C
template <class N,class A>
Grafo<N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val){
	// (1) verificar se existe já a aresta
	bool existe=0;
	for (int unsigned i=0; i<nos.size(); i++){
		if (nos[i]->info==inicio){
			for (int unsigned j=0; j<nos[i]->arestas.size(); j++){
				if(nos[i]->arestas[j].destino->info==fim){ // Val não é importante!
					existe=1;
				}

			}
		}
	}
	bool noexiste=0;
	// Verificar se o Nó de Início existe
	bool noInicio=0;
	for (int unsigned i=0; i<nos.size(); i++)
		if (nos[i]->info==inicio) noInicio=1;
	// Verificar se o Nó Final existe
	bool noFim=0;
	for (int unsigned i=0; i<nos.size(); i++)
		if (nos[i]->info==fim) noFim=1;
	noexiste=noInicio & noFim;
	// Verificar qual o nó inexistente caso algum não exista
	N noNaoEncontrado;
	if(!noInicio) noNaoEncontrado=inicio;
	if(!noFim) noNaoEncontrado=fim;
	// (2) Processar caso a aresta exista
	if(noexiste){
		if(!existe){ // Caso a aresta ainda não exista
			// (a) Obter o endereço do próximo nó
			No<N,A> *destino;
			for (int unsigned i=0; i<nos.size(); i++){
				if (nos[i]->info==fim) destino=nos[i];
			}
			// (b) Meter no nó de início a arsta
			for (int unsigned i=0; i<nos.size(); i++){
				if (nos[i]->info==inicio) {
					Aresta<N,A> aux(destino,val);
					nos[i]->arestas.push_back(aux);
				}
			}

		}
		else throw ArestaRepetida<N>(inicio,fim);
	}
	else throw NoInexistente<N>(noNaoEncontrado);
	return *this;

}
// Alínea D
template <class N,class A>
A & Grafo<N,A>::valorAresta(const N &inicio, const N &fim){
	A devolver;
	// (1)Verificar se pelo menos um nó não existe
	bool noexiste=0;
	// Verificar se o Nó de Início existe
	bool noInicio=0;
	for (int unsigned i=0; i<nos.size(); i++)
		if (nos[i]->info==inicio) noInicio=1;
	// Verificar se o Nó Final existe
	bool noFim=0;
    for (int unsigned i=0; i<nos.size(); i++)
		if (nos[i]->info==fim) noFim=1;
	noexiste=noInicio & noFim;
	// Verificar qual o nó inexistente caso algum não exista
	N noNaoEncontrado;
	if(!noInicio) noNaoEncontrado=inicio;
	if(!noFim) noNaoEncontrado=fim;
	// (2) Caso pelo menos um nó não existe, lança excepção
	if(!noexiste) throw NoInexistente<N>(noNaoEncontrado);
	else{
		// (a) verificar se as arestas existem
		bool arestaExiste=0;
		for (int unsigned i=0; i<nos.size(); i++)
			if (nos[i]->info==inicio){
				for (int unsigned j=0; j<nos[i]->arestas.size(); j++){
					if (nos[i]->arestas[j].destino->info==fim){
						arestaExiste=1;
						devolver=nos[i]->arestas[j].valor;
					}
				}

			}
		if(!arestaExiste) throw ArestaInexistente<N>(inicio,fim);
	}
	return devolver;
}
// Alínea E
template <class N,class A>
Grafo<N,A> & Grafo<N,A>::eliminarAresta(const N &inicio, const N &fim){
	// (1)Verificar se pelo menos um nó não existe
	bool noexiste=0;
	// Verificar se o Nó de Início existe
	bool noInicio=0;
	for (int unsigned i=0; i<nos.size(); i++)
		if (nos[i]->info==inicio) noInicio=1;
	// Verificar se o Nó Final existe
	bool noFim=0;
	for (int unsigned i=0; i<nos.size(); i++)
		if (nos[i]->info==fim) noFim=1;
	noexiste=noInicio & noFim;
	// Verificar qual o nó inexistente caso algum não exista
	N noNaoEncontrado;
	if(!noInicio) noNaoEncontrado=inicio;
	if(!noFim) noNaoEncontrado=fim;
	// (2) Caso pelo menos um nó não existe, lança excepção
	if(!noexiste) {
		cout << "\n No nao existe: " << noNaoEncontrado << endl;
		throw NoInexistente<N>(noNaoEncontrado);
	}
	else{
		// (2) verificar se as arestas existem
		bool arestaExiste=0;
		int unsigned i, j;
		int x,y;
		for (i=0; i<nos.size(); i++)
			if (nos[i]->info==inicio){
				for (j=0; j<nos[i]->arestas.size(); j++){
					if (nos[i]->arestas[j].destino->info==fim){
						arestaExiste=1;
						x=i; y=j;
					}
				}

			}
		if(!arestaExiste) throw ArestaInexistente<N>(inicio,fim);
		else {
			nos[x]->arestas.erase(nos[x]->arestas.begin()+y);
			return *this;
		}
	}
}
// Alínea F
template <class N,class A>
void Grafo<N,A> ::imprimir(std::ostream &os) const{
	for(int unsigned i=0; i<nos.size(); i++){
		os << "( ";
		os << nos[i]->info;
		if(nos[i]->arestas.size()>0){
			for (int unsigned j=0; j<nos[i]->arestas.size(); j++){
				os << "[ ";
				os << nos[i]->arestas[j].destino->info;
				os << " ";
				os << nos[i]->arestas[j].valor;
				os << "] ";

			}
		}
		os << ") ";
	}
}
// Alínea G
template <class N,class A>
ostream & operator<<(ostream &os, Grafo<N,A> &f){
	f.imprimir(os);
	return os;
}
