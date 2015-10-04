#ifndef EMPACOTADOR_H_
#define EMPACOTADOR_H_

#include <queue>
#include <vector>
#include <stack>
#include <iostream>
#include <sstream>
using namespace std;

class Objeto {
	int id;
	int peso;
public:
	Objeto(int idObj, int pesoObj): id(idObj), peso(pesoObj) {}
	int getID() const { return id; }
	int getPeso() const { return peso; }
	friend ostream& operator<<(ostream& os, Objeto obj);
	// Alínea A
	bool operator<(const Objeto& o1) const {
		return peso<o1.peso;
	}

};


typedef stack<Objeto> STACK_OBJS;

class Caixa {
	STACK_OBJS objetos;
	int id;
	int capacidade;
	int espacoLivre;
	static int ultimoId;
public:
    Caixa(int cap=10): id(ultimoId++), capacidade(cap), espacoLivre(cap) {}
    int getID() const { return id; }
    int getEspacoLivre() const { return espacoLivre; }
    void addObjeto(Objeto& obj) { espacoLivre -= obj.getPeso(); objetos.push(obj); }

    /* A ALTERAR ... */
    bool operator<(const Caixa& c1) const {
    	// Uma caixa é menor do que a outra se tiver menos espaço livre, ou seja,
    	// como todas as caixas têm a mesma capacidade, têm de ser despachadas primeiras as
    	// mais pesadas!!
    	return espacoLivre<c1.espacoLivre;
    }
    // Alínea B
    static void resetID(){
    	ultimoId=1;
    }
};


typedef priority_queue<Objeto> HEAP_OBJS;
typedef priority_queue<Caixa> HEAP_CAIXAS;

class MaquinaEmpacotar {
	HEAP_OBJS objetos;
	HEAP_CAIXAS caixas;
	int capacidadeCaixas;
public:
	MaquinaEmpacotar(int capCaixas = 10): capacidadeCaixas(capCaixas) {}
	int numCaixasUsadas() { return caixas.size(); }
	int addCaixa(Caixa& cx) { caixas.push(cx); return caixas.size(); }
	// Alínea A
	int carregaPaletaObjetos(vector<Objeto> &objs);
	// Alínea B
	Caixa procuraCaixa(Objeto& obj);
	// Alínea C
	int empacotaObjetos();
	// Alínea D
	string imprimeObjetosPorEmpacotar() const;
};

#endif /* EMPACOTADOR_H_ */
