#include "Balcao.h"
#include <ctime>
#include <cstdlib>
using namespace std;
// Alínea 2a
Cliente::Cliente(){
	numPresentes= rand() % 5 + 1;
}

int Cliente::getNumPresentes(){
	return numPresentes;
}

// Alínea 2b
Balcao::Balcao(int te): tempo_embrulho(te){
	tempo_atual=0;
	prox_chegada=rand()% 20 +1;
	prox_saida=0;
	clientes_atendidos=0;
}

int Balcao::getTempoAtual() const{
	return tempo_atual;
}

int Balcao::getProxChegada() const{
	return prox_chegada;
}

int  Balcao::getClientesAtendidos() const{
	return clientes_atendidos;
}

int Balcao::getTempoEmbrulho() const{
	return tempo_embrulho;
}

int Balcao::getProxSaida() const{
	return prox_saida;
}
Cliente & Balcao::getProxCliente(){
	if (clientes.empty()) throw FilaVazia();
	return clientes.front();
}

// Alínea C
void Balcao::chegada(){
	// (1) Criar um novo cliente e inserir na fila
	Cliente a;
	clientes.push(a);
	// (2) Gerar aleatoriamente o tempo de chegada do próximo cliente (prox_chegada) com um valor entre 1 e 20
	prox_chegada= rand() % 20 +1;
	// (3) Actualizar proxima saida
	prox_saida=tempo_atual+a.getNumPresentes()*tempo_embrulho;
	cout << "tempo= " << tempo_atual << "\nchegou novo cliente com "<< a.getNumPresentes()<<  " presentes";

}
// Alínea D
void Balcao::saida(){
	Cliente aux;
	// (1) Obter o cliente em questão
	try{
		aux=getProxCliente();
	}
	catch(FilaVazia &e){
		cout << "Apanhou excepção. FilaVazia: " << e.getMsg() << endl;
	}
	// (2) Remover o cliente
	clientes.pop();
	// (2) Actualizar o tempo de saída se a fila ficar vazia
	if(clientes.empty()) prox_saida=0;
	// (3) Actualizar proxima saida
	prox_saida=tempo_atual+aux.getNumPresentes()*tempo_embrulho;
	cout << "tempo= " << tempo_atual << "\nchegou novo cliente com "<< aux.getNumPresentes()<<  " presentes";
}
// Alínea E
void Balcao::proximoEvento(){
	if (prox_saida<tempo_atual) saida();
	else if (prox_chegada< tempo_atual) chegada();
}
