/*
	Autor: André Freitas
	Email: p.andrefreitas@gmail.com
*/
#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int n_max_clientes):
	lotacao(lot), num_max_clientes(n_max_clientes) {
    num_clientes=0; 
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}


bool ParqueEstacionamento::novo_cliente(const string & nome) 
{
 	if ( num_clientes==num_max_clientes ) return false;
	if ( posicao_cliente(nome)!=-1 ) return false;
	InfoCartao info;
	info.nome=nome; 
    info.presente=false;
	clientes.push_back(info);
	num_clientes++;
	// Alínea B
	clientes[clientes.size()-1].utilizacao=0;
	return true;
}
 
bool ParqueEstacionamento::retira_cliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( (*it).nome==nome ) {
			if ( (*it).presente==false ) {
				clientes.erase(it);
				num_clientes--;
				return true;
			}
			else return false;
		}
	return false;
}
  
unsigned int ParqueEstacionamento::num_lugares() const
{
	return lotacao;
}
                   
unsigned int ParqueEstacionamento::num_lugares_ocupados() const
{
	return lotacao-vagas;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas==0 ) return false;
	int pos=posicao_cliente(nome);
	if ( pos==-1 ) return false;
	if ( clientes[pos].presente==true ) return false;
	clientes[pos].presente=true;
	vagas--;
	// Alínea B
	clientes[pos].utilizacao++;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos=posicao_cliente(nome);
	if ( pos==-1 ) return false;
	if ( clientes[pos].presente==false ) return false;
	clientes[pos].presente=false;
	vagas++;
	return true;
}

// Alínea A
int ParqueEstacionamento::posicao_cliente(const string & nome) const {
	InfoCartao aux;
	aux.nome=nome;
	return sequentialSearch(clientes,aux);
}


// Alínea B
int ParqueEstacionamento::num_utilizacoes(const string &nome) const{
	if (posicao_cliente(nome)!=-1)
		return clientes[posicao_cliente(nome)].utilizacao;
	else
		throw ClienteNaoExistente(nome);
	return 0;
}
// Alínea C
void ParqueEstacionamento::ordena_clientes_utilizacao(){
	for (int unsigned i=0; i<clientes.size(); i++){
		int unsigned maior=i;
		for (int unsigned j=i; j<clientes.size(); j++)
			if (clientes[j].utilizacao>=clientes[maior].utilizacao)
				maior=j;
		// -->
		InfoCartao aux;
		aux=clientes[i];
		clientes[i]=clientes[maior];
		clientes[maior]=aux;
	}
	for (int unsigned i=0; i<clientes.size(); i++){
		cout << clientes[i].nome << " " << clientes[i].utilizacao << endl;
	}
}
InfoCartao ParqueEstacionamento::get_cliente_pos(int p) const{
	// Alínea F
	if(p<0 || p>=clientes.size())
		throw PosicaoNaoExistente(p);
	return clientes[p];
}

// Alínea D
vector<string> ParqueEstacionamento::clientes_gama_uso(int n1, int n2){
	vector<string> aux;
	ordena_clientes_utilizacao();
	for (int unsigned i=0; i<clientes.size(); i++){
		if (clientes[i].utilizacao>=n1 & clientes[i].utilizacao<=n2)
			aux.push_back(clientes[i].nome);
	}
	return aux;
}

// Alínea E
void ParqueEstacionamento::ordena_clientes_nome(){
	for (int unsigned i=0; i<clientes.size(); i++){
				cout << clientes[i].nome <<  endl;
			}
	cout << "\n-------------\n";

	for (int unsigned i=0; i<clientes.size(); i++){
		int menor=i;
		for (int unsigned j=i; j<clientes.size(); j++){
			if (clientes[i].nome<clientes[menor].nome){
				menor=j;
			}
		}
		// -->
		InfoCartao aux;
		aux=clientes[i];
		clientes[i]=clientes[menor];
		clientes[menor]=aux;
	}


	for (int unsigned i=0; i<clientes.size(); i++){
			cout << clientes[i].nome <<  endl;
		}
}
ostream & operator << (ostream &os, const ParqueEstacionamento &pe){
	for (int unsigned i=0; i<pe.clientes.size(); i++){
		os << pe.clientes[i].nome << ": ";
		if(pe.clientes[i].presente) os << "PRESENTE ";
		else os << "NAO PRESENTE ";
		cout <<" - Utilizacoes: " << pe.clientes[i].utilizacao << endl;
	}
}
