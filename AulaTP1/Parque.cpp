/*
	Autor: André Freitas
	Email: p.andrefreitas@gmail.com
*/
#include "Parque.h"
#include <vector>

using namespace std;

// Alínea (a)
ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int n_max_clientes):lotacao(lot),num_max_clientes(n_max_clientes) {
    num_clientes=0;
    vagas=lotacao;
}

unsigned int ParqueEstacionamento::ParqueEstacionamento::num_lugares() const{
    return lotacao;
}
unsigned int ParqueEstacionamento::maximo_clientes() const{
    return num_max_clientes;
}

// Alínea (b)

int ParqueEstacionamento::posicao_cliente(const string & nome) const{
    for (int unsigned i=0; i < clientes.size();i++)
        if (clientes[i].nome==nome) return i;
    return -1;
}

bool ParqueEstacionamento::novo_cliente(const string & nome){
    if (posicao_cliente(nome)!=-1) return 0;
    else {
        InfoCartao aux;
        aux.nome=nome;
        aux.presente=0;
        clientes.push_back(aux);
        num_clientes++;
        return 1;
    }
}

// Alínea (c)
bool ParqueEstacionamento::entrar(const string & nome){
    if (posicao_cliente(nome)==-1 || vagas==0 || cliente[posicao_cliente(nome)].presente==1) return 0;
    else {
        clientes[posicao_cliente(nome)].presente=1;
        vagas--;
    }
    return 1;
}

// Alínea (d)
bool ParqueEstacionamento::retira_cliente(const string & nome){
    int unsigned i =posicao_cliente(nome);
    if (i==-1 || clientes[i].presente==1) return 0;
    else   {
        clientes.erase(clientes.begin(),clientes.begin()+i+1);
        num_clientes--;
    }
    return 1;
}

// Alínea (e)
bool ParqueEstacionamento::sair(const string & nome){
    if (posicao_cliente(nome)==-1 || clientes[posicao_cliente(nome)].presente=0)
        return 0;
    else {
        clientes[posicao_cliente(nome)].presente=0;
        vagas++;
    }
}

// Alínea (f)
unsigned int ParqueEstacionamento::num_lugares_ocupados() const{
    return lotacao-vagas;
}

unsigned int ParqueEstacionamento::num_clientes_atuais() const{
    return num_clientes;
}
