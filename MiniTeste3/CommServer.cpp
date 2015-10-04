#include "CommServer.h"
#include <string>

using namespace std;

// dado aos alunos
Payload::Payload(int id1, string nm) {
	this->id = id1;
	this->nome = nm;
}

// dado aos alunos
string Payload::getNome() const {
	return this->nome;
}

// dado aos alunos
int Payload::getId() const {
	return this->id;
}

// dado aos alunos
Log::Log(string hora1, Payload & pl1) :
		pl(&pl1) {
	this->hora = hora1;
}

// dado aos alunos
string Log::getHora() const {
	return this->hora;
}

// dado aos alunos
Payload & Log::getPl() const {
	return *pl;
}

// dado aos alunos
void CommServer::setTamPilha(int tp) {
	this->tam_pilha = tp;
}

// dado aos alunos
void CommServer::setCompFila(int cf) {
	this->comp_fila = cf;
}

// dado aos alunos
int CommServer::getCompFila() const {
	return this->comp_fila;
}

// dado aos alunos
int CommServer::getTamPilha() const {
	return this->tam_pilha;
}

// dado aos alunos
queue<stack<Payload> > & CommServer::getFila1() {
	return this->fila1;
}

// dado aos alunos
queue<stack<Payload> > & CommServer::getFila2() {
	return this->fila2;
}

// dado aos alunos
list<Log> & CommServer::getEntrada() {
	return this->entrada;
}

// dado aos alunos
list<Log> & CommServer::getSaida() {
	return this->saida;
}

// dados aos alunos
void CommServer::adicionarElemento(queue<stack<Payload> > &f,
		stack<Payload> &s) {
	f.push(s);
}

// Alínea A
CommServer::CommServer(int comp_fila, int tam_pilha) {
	this->comp_fila = comp_fila;
	this->tam_pilha = tam_pilha;

}

// Alínea C
bool CommServer::servidorOcupado() const {
	return !servidorLivre();
}

bool CommServer::servidorVazio() const {
	if (obterNumElem(fila1) == 0 && obterNumElem(fila2) == 0)
		return true;
	return false;
}

bool CommServer::servidorLivre() const {
	return (obterNumElem(fila1) < (comp_fila * tam_pilha)
			|| obterNumElem(fila2) < (comp_fila * tam_pilha));
}

// Alínea D
void CommServer::adicionarPayload(Payload & pl) {
	// (1) se ocupado lança excepção
	if (servidorOcupado()) throw FilasCheias();
	queue<stack<Payload> > *filaAlterar;
	filaAlterar = &fila1;

	if (obterNumElem(fila2) < obterNumElem(fila1))
		filaAlterar = &fila2;

	if (filaAlterar->empty()) {
		stack<Payload> aux;
		aux.push(pl);
		filaAlterar->push(aux);
	} else {
		if (filaAlterar->back().size() >= tam_pilha) {
			stack<Payload> aux;
			aux.push(pl);
			filaAlterar->push(aux);
		} else
			filaAlterar->back().push(pl);
	}
}

// Alínea E

void CommServer::registaEntrada(string hr, Payload & pl){
	entrada.push_back(Log(hr,pl));
}

void CommServer::registaSaida(string hr, Payload & pl){
	saida.push_back(Log(hr,pl));
}

list<Log> CommServer::conciliaLogs() const{
	list<Log> aux;
	for (list<Log>::const_iterator it1=entrada.begin(); it1!=entrada.end(); it1++){
		bool existe=0;
		for (list<Log>::const_iterator it2=saida.begin(); it2!=saida.end(); it2++){
			if (it1->getPl().getId() == it2->getPl().getId()) existe=1;
		}
		if (!existe) aux.push_back(*it1);
	}

	for (list<Log>::const_iterator it1=saida.begin(); it1!=saida.end(); it1++){
			bool existe=0;
			for (list<Log>::const_iterator it2=entrada.begin(); it2!=entrada.end(); it2++){
				if (it1->getPl().getId() == it2->getPl().getId()) existe=1;
			}
			if (!existe) aux.push_back(*it1);
		}
	return aux;
}


// Alínea D
list<Payload> CommServer::obterPayload(int nelem){
	if (nelem<=0 || nelem> 2*(comp_fila * tam_pilha) )
		throw ErroNumeroElementos();
	queue< stack<Payload> > *pFila;
	list<Payload> aux;
	cout << "\n\n";
	for(int unsigned i=0; i<nelem; i++){
		// (1) Alternar entre filas
		if(i%2 == 0 || fila2.empty()) pFila=&fila1;
		else  pFila=&fila2;
		// (2) Remover e adicionar
		aux.push_back(pFila->front().top());
		pFila->front().pop();
		if (pFila->front().empty()) pFila->pop();

	}
	cout << "Fila1: " << obterNumElem(fila1)<< " Fila2: " << obterNumElem(fila2) << endl;
	return aux;
}
