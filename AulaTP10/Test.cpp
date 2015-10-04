#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include <vector>
#include <string>
#include "Aposta.h"
#include "Jogador.h"

void test_1a_GeraAposta(){

	vector<int> vals;
	vals.push_back(30);
	vals.push_back(45);
	vals.push_back(22);
	vals.push_back(17);
	vals.push_back(45);
	vals.push_back(8);
	vals.push_back(30);
	vals.push_back(15);
	vals.push_back(24);
	vals.push_back(22);
	Aposta ap1;
	ap1.geraAposta(vals,6);
	ASSERT_EQUAL(6, ap1.getNumeros().size());

}

void test_1b_VerificaAposta(){

	vector<int> vals;
	vals.push_back(30); vals.push_back(45); vals.push_back(22);
	vals.push_back(17); vals.push_back(45); vals.push_back(8);
	vals.push_back(30); vals.push_back(15); vals.push_back(24);
	vals.push_back(22);
	Aposta ap1;
	ap1.geraAposta(vals,6);
	ASSERT_EQUAL(true, ap1.contem(30));
	ASSERT_EQUAL(true, ap1.contem(45));
	ASSERT_EQUAL(true, ap1.contem(15));
	ASSERT_EQUAL(false, ap1.contem(21));

}

void test_1c_ImprimeAposta(){

	vector<int> vals;
	vals.push_back(30); vals.push_back(45); vals.push_back(22);
	vals.push_back(17); vals.push_back(45); vals.push_back(8);
	vals.push_back(30); vals.push_back(15); vals.push_back(24);
	vals.push_back(22);
	Aposta ap1;
	ap1.geraAposta(vals,6);
	string apSt=ap1.imprimeAposta();
	ASSERT((apSt.find("17\n"))!=apSt.npos);
	ASSERT((apSt.find("22\n"))!=apSt.npos);
	ASSERT((apSt.find("30\n"))!=apSt.npos);
	ASSERT((apSt.find("10\n"))==apSt.npos);

}

void test_1d_ContaAposta(){

	vector<int> vals;
	vals.push_back(30); vals.push_back(45); vals.push_back(22);
	vals.push_back(17); vals.push_back(45); vals.push_back(8);
	vals.push_back(30); vals.push_back(15); vals.push_back(24);
	vals.push_back(22);
	Aposta ap1;
	ap1.geraAposta(vals,6);
	vector<int> valsF;
	valsF.push_back(44); valsF.push_back(18); valsF.push_back(22);
	valsF.push_back(33); valsF.push_back(45); valsF.push_back(8);
	Aposta chave;
	chave.geraAposta(valsF,6);
	ASSERT_EQUAL(3,ap1.calculaCertos(chave.getNumeros()));

}

void test_2a_JogadorAdicionaAposta(){
/*
	Jogador jogador1("Rui");
	vector<int> vals;
	vals.push_back(30); vals.push_back(45); vals.push_back(22);
	vals.push_back(17); vals.push_back(45); vals.push_back(8);
	vals.push_back(30); vals.push_back(15); vals.push_back(24);
	vals.push_back(22);
	Aposta ap1;
	ap1.geraAposta(vals,6);
	jogador1.adicionaAposta(ap1);
	vals.clear();
	vals.push_back(3); vals.push_back(44); vals.push_back(22);
	vals.push_back(15); vals.push_back(44); vals.push_back(3);
	vals.push_back(34); vals.push_back(20); vals.push_back(17);
	Aposta ap2;
	ap2.geraAposta(vals,6);
	jogador1.adicionaAposta(ap2);
	vals.clear();
	vals.push_back(41); vals.push_back(32); vals.push_back(12);
	vals.push_back(15); vals.push_back(28); vals.push_back(32);
	vals.push_back(12); vals.push_back(41); vals.push_back(4);
	Aposta ap3;
	ap3.geraAposta(vals,6);
	jogador1.adicionaAposta(ap3);
	ASSERT_EQUAL(3,jogador1.getNumApostas());
*/
}

void test_2b_JogadorApostasEmNumero(){
	/*
	Jogador jogador1("Rui");
	vector<int> vals;
	vals.push_back(30); vals.push_back(45); vals.push_back(22);
	vals.push_back(17); vals.push_back(45); vals.push_back(8);
	vals.push_back(30); vals.push_back(15); vals.push_back(24);
	vals.push_back(22);
	Aposta ap1;
	ap1.geraAposta(vals,6);
	jogador1.adicionaAposta(ap1);
	vals.clear();
	vals.push_back(3); vals.push_back(44); vals.push_back(22);
	vals.push_back(15); vals.push_back(44); vals.push_back(3);
	vals.push_back(34); vals.push_back(20); vals.push_back(17);
	Aposta ap2;
	ap2.geraAposta(vals,6);
	jogador1.adicionaAposta(ap2);
	vals.clear();
	vals.push_back(41); vals.push_back(32); vals.push_back(12);
	vals.push_back(15); vals.push_back(28); vals.push_back(32);
	vals.push_back(12); vals.push_back(41); vals.push_back(4);
	Aposta ap3;
	ap3.geraAposta(vals,6);
	jogador1.adicionaAposta(ap3);
	ASSERT_EQUAL(2,jogador1.apostasNoNumero(22));
	*/
}

void test_2c_JogadorApostasSorteadas(){
	/*
	Jogador jogador1("Rui");
	vector<int> vals;
	vals.push_back(30); vals.push_back(45); vals.push_back(22);
	vals.push_back(17); vals.push_back(45); vals.push_back(8);
	vals.push_back(30); vals.push_back(18); vals.push_back(24);
	vals.push_back(22);
	Aposta ap1;
	ap1.geraAposta(vals,6);
	jogador1.adicionaAposta(ap1);
	vals.clear();
	vals.push_back(3); vals.push_back(4); vals.push_back(22);
	vals.push_back(15); vals.push_back(4); vals.push_back(3);
	vals.push_back(34); vals.push_back(20); vals.push_back(17);
	Aposta ap2;
	ap2.geraAposta(vals,6);
	jogador1.adicionaAposta(ap2);
	vals.clear();
	vals.push_back(45); vals.push_back(32); vals.push_back(18);
	vals.push_back(15); vals.push_back(8); vals.push_back(32);
	vals.push_back(18); vals.push_back(45); vals.push_back(33);
	Aposta ap3;
	ap3.geraAposta(vals,6);
	jogador1.adicionaAposta(ap3);

	vector<int> valsF;
	valsF.push_back(44); valsF.push_back(18); valsF.push_back(22);
	valsF.push_back(33); valsF.push_back(45); valsF.push_back(8);
	Aposta chave;
	chave.geraAposta(valsF,6);

	ASSERT_EQUAL(4,ap1.calculaCertos(chave.getNumeros()));
	ASSERT_EQUAL(1,ap2.calculaCertos(chave.getNumeros()));
	ASSERT_EQUAL(4,ap3.calculaCertos(chave.getNumeros()));

	ASSERT_EQUAL(2,jogador1.apostasSorteadas(chave.getNumeros()).size());
	*/
}


void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_1a_GeraAposta));
	s.push_back(CUTE(test_1b_VerificaAposta));
	s.push_back(CUTE(test_1c_ImprimeAposta));
	s.push_back(CUTE(test_1d_ContaAposta));
	s.push_back(CUTE(test_2a_JogadorAdicionaAposta));
	s.push_back(CUTE(test_2b_JogadorApostasEmNumero));
	s.push_back(CUTE(test_2c_JogadorApostasSorteadas));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "AEDA 2011/2012 - Aula Pratica 10");
}

int main(){
    runSuite();
    return 0;
}



