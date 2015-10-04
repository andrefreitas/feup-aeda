#ifndef COMMSERVER_H_
#define COMMSERVER_H_

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>

using namespace std;

// dado aos alunos
class Payload {
private:
	int id;
	string nome;
public:
	Payload(int id1, string nm);
	int getId() const;
	string getNome() const;
};

// dado aos alunos
class Log {
private:
	string hora;
	Payload * pl;
public:
	Log(string hora1, Payload &pl1);
	string getHora() const;
	Payload & getPl() const;

};

// dados aos alunos
class CommServer {
private:
	int comp_fila;
	int tam_pilha;
	queue< stack<Payload> > fila1;
	queue< stack<Payload> > fila2;
	list<Log> entrada;
	list<Log> saida;
public:
	// dado aos alunos
	int getCompFila() const;
	int getTamPilha() const;
	queue< stack<Payload> > & getFila1();
	queue< stack<Payload> > & getFila2();
	list<Log> & getEntrada();
	list<Log> & getSaida();
	void setCompFila(int cf);
	void setTamPilha(int tp);
	void adicionarElemento(queue< stack<Payload> > &f, stack<Payload> &s);
	// A implementar pelos alunos
	CommServer(int comp_fila = 3, int tam_pilha = 4);
	bool servidorLivre() const;
	bool servidorOcupado() const;
	bool servidorVazio() const;
	void adicionarPayload(Payload & pl);
	list<Payload> obterPayload(int nelem);
	void registaEntrada(string hr, Payload & pl);
	void registaSaida(string hr, Payload & pl);
	list<Log> conciliaLogs() const;
};

// Alínea B
template <class T>
int obterNumElem(const queue< stack<T> > &q){
	int sum=0;
	queue< stack<T> > aux=q;
	while (!aux.empty()){
		sum+=aux.front().size();
		aux.pop();
	}
	return sum;
}
// Alínea D
class FilasCheias{

};

// Alínea G
class ErroNumeroElementos{

};

#endif /* COMMSERVER_H_ */
