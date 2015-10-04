#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "parque.h"


void test_a_Pesquisa() {
	ParqueEstacionamento p1(10,20);
	p1.novo_cliente("Joao Santos");
	p1.novo_cliente("Pedro Morais");
	p1.novo_cliente("Rui Silva");
	p1.novo_cliente("Susana Costa");
	p1.novo_cliente("Maria Tavares");
	ASSERT_EQUAL(0, p1.posicao_cliente("Joao Santos"));
	ASSERT_EQUAL(4, p1.posicao_cliente("Maria Tavares"));
	ASSERT_EQUAL(1, p1.posicao_cliente("Pedro Morais"));
	ASSERT_EQUAL(-1, p1.posicao_cliente("Tiago Tavares"));
}

void test_b_UtilizacaoParque() {
	ParqueEstacionamento p1(10,20);
	p1.novo_cliente("Joao Santos");
	p1.novo_cliente("Pedro Morais");
	p1.novo_cliente("Rui Silva");
	p1.novo_cliente("Susana Costa");
	p1.novo_cliente("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.entrar("Susana Costa");
	p1.sair("Susana Costa");
	p1.sair("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.sair("Maria Tavares");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Susana Costa");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Rui Silva");
	p1.entrar("Pedro Morais");
	ASSERT_EQUAL(3, p1.num_utilizacoes("Rui Silva"));
	ASSERT_EQUAL(1, p1.num_utilizacoes("Pedro Morais"));
	ASSERT_EQUAL(0, p1.num_utilizacoes("Joao Santos"));

	ASSERT_THROWS(p1.num_utilizacoes("Tiago Silva"), ClienteNaoExistente);
	try {
		p1.num_utilizacoes("Tiago Silva");
	}
	catch (ClienteNaoExistente &e) {
		cout << "Apanhou excepção. Cliente não existente: " << e.getNome() << endl;
		ASSERT_EQUAL("Tiago Silva", e.getNome());
	}
}

void test_c_OrdenaUtilizacao() {
	ParqueEstacionamento p1(10,20);
	p1.novo_cliente("Joao Santos");
	p1.novo_cliente("Pedro Morais");
	p1.novo_cliente("Rui Silva");
	p1.novo_cliente("Susana Costa");
	p1.novo_cliente("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.entrar("Susana Costa");
	p1.sair("Susana Costa");
	p1.sair("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.sair("Maria Tavares");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Susana Costa");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Rui Silva");
	p1.entrar("Pedro Morais");
	// Joao Santos: 0 utilizacoes
	// Pedro Morais: 1 utilizacao
	// Maria Tavares: 2 utilizacoes
	// Susana Costa: 2 utilizacao
	// Rui Silva: 3 utilizacoes
	p1.ordena_clientes_utilizacao();

	InfoCartao ic1=p1.get_cliente_pos(2);
	ASSERT_EQUAL("Susana Costa", ic1.nome);
	ASSERT_EQUAL(2, ic1.utilizacao);
	InfoCartao ic2=p1.get_cliente_pos(0);
	ASSERT_EQUAL("Rui Silva", ic2.nome);
	ASSERT_EQUAL(3, ic2.utilizacao);
}

void test_d_GamasUso() {
ParqueEstacionamento p1(10,20);
	p1.novo_cliente("Joao Santos");
	p1.novo_cliente("Pedro Morais");
	p1.novo_cliente("Rui Silva");
	p1.novo_cliente("Susana Costa");
	p1.novo_cliente("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.entrar("Susana Costa");
	p1.sair("Susana Costa");
	p1.sair("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.sair("Maria Tavares");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Susana Costa");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Rui Silva");
	p1.entrar("Pedro Morais");
	// Joao Santos: 0 utilizacoes
	// Pedro Morais: 1 utilizacao
	// Maria Tavares: 2 utilizacoes
	// Susana Costa: 2 utilizacao
	// Rui Silva: 3 utilizacoes
	vector<string> clientes = p1.clientes_gama_uso(2,3);
	ASSERT_EQUAL(3,clientes.size());
	ASSERT_EQUAL("Rui Silva", clientes[0]);
	ASSERT_EQUAL("Maria Tavares", clientes[1]);
	ASSERT_EQUAL("Susana Costa", clientes[2]);
}


void test_e_OrdenaNome() {
	ParqueEstacionamento p1(10,20);
	p1.novo_cliente("Joao Santos");
	p1.novo_cliente("Pedro Morais");
	p1.novo_cliente("Rui Silva");
	p1.novo_cliente("Susana Costa");
	p1.novo_cliente("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.entrar("Susana Costa");
	p1.sair("Susana Costa");
	p1.sair("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.sair("Maria Tavares");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Susana Costa");
	p1.entrar("Rui Silva");
	p1.sair("Rui Silva");
	p1.entrar("Rui Silva");
	p1.entrar("Pedro Morais");
	p1.ordena_clientes_nome();
	InfoCartao ic1=p1.get_cliente_pos(2);
	ASSERT_EQUAL("Rui Silva", ic1.nome);
	InfoCartao ic2=p1.get_cliente_pos(0);
	ASSERT_EQUAL("Joao Santos", ic2.nome);
}

void test_f_InfoClientes() {
    ParqueEstacionamento p1(10,20);
	p1.novo_cliente("Joao Santos");
	p1.novo_cliente("Pedro Morais");
	p1.novo_cliente("Rui Silva");
	p1.novo_cliente("Susana Costa");
	p1.novo_cliente("Maria Tavares");
	p1.entrar("Maria Tavares");
	p1.entrar("Susana Costa");
	p1.sair("Susana Costa");
	p1.entrar("Rui Silva");
	p1.entrar("Susana Costa");
	ASSERTM("Este teste nunca falha! VERIFICAR informação escrita no monitor", true);
	cout << p1;
	InfoCartao ic=p1.get_cliente_pos(2);
	ASSERT_EQUAL("Rui Silva", ic.nome);

	ASSERT_THROWS(p1.get_cliente_pos(6), PosicaoNaoExistente);
	try {
		p1.get_cliente_pos(6);
	}
	catch (PosicaoNaoExistente &e) {
		ASSERTM("Este teste nunca falha. Verifique no monitor a informação", true);
		cout << "Apanhou excepção. Posição não existente:" << e.getValor() << endl;
		ASSERT_EQUAL(6, e.getValor());
	}
}



void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_a_Pesquisa));
	s.push_back(CUTE(test_b_UtilizacaoParque));
	s.push_back(CUTE(test_c_OrdenaUtilizacao));
	s.push_back(CUTE(test_d_GamasUso));
	s.push_back(CUTE(test_e_OrdenaNome));
	s.push_back(CUTE(test_f_InfoClientes));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "AEDA 2011/2012 - Aula Pratica 5");
}

int main(){

    runSuite();
    return 0;
}



