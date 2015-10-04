#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include <string>
#include "Frota.h"


void test_a_CriarVeiculos() {

	Automovel a1("Fiat",5,1997,"gasolina",1200);
	Camiao c1("Ford",3,1999,"gasolina",1400,1000);
	Automovel a2("Renault",9,1997,"gasoleo",1300);
	Bicicleta b1("XX",4,2002,"TodoTerreno");

	ASSERT_EQUAL("gasolina", c1.getCombustivel());
	ASSERT_EQUAL("Fiat", a1.getMarca());
	ASSERT_EQUAL("Ford", c1.getMarca());
}


void test_b_InfoVeiculo() {

	Automovel a1("Fiat",5,1997,"gasolina",1200);
	Camiao c1("Ford",3,1999,"gasolina",1400,1000);
	Bicicleta b1("XX",4,2002,"TodoTerreno");
	ASSERT_EQUAL(5, a1.info());
	ASSERT_EQUAL(6,c1.info());
	ASSERT_EQUAL(4,b1.info());

}

void test_c_ImpostoVeiculo() {
	Automovel a1("Fiat",5,1997,"gasolina",1200);
	Camiao c1("Ford",3,1999,"gasolina",1400,1000);
	Bicicleta b1("XX",4,2002,"TodoTerreno");
	ASSERT_EQUAL_DELTA(29.06, a1.calcImposto(),0.001);
	ASSERT_EQUAL_DELTA(45.15,c1.calcImposto(),0.001);
	ASSERT_EQUAL_DELTA(0,b1.calcImposto(),0.001);
}

void test_d_OperadorMenor() {

	Automovel a1("Fiat",5,1997,"gasolina",1200);
	Camiao c1("Ford",3,1999,"gasolina",1400,1000);
	Bicicleta b1("XX",4,2002,"TodoTerreno");
	ASSERT_EQUAL(true, a1<c1);
	ASSERT_EQUAL(false,b1<c1);
	ASSERT_EQUAL(true,a1<b1);

}


void test_e_CriarFrota() {

	Frota f;
	ASSERT_EQUAL(0, f.numVeiculos());
	ASSERT_EQUAL(0, f.menorAno());
	Veiculo *v1 =new Automovel("Fiat",5,1997,"gasolina",1200);
	Veiculo *v2= new Camiao("Ford",3,1999,"gasolina",1400,1000);
	Veiculo *v3=new Automovel("Renault",9,1997,"gasoleo",1300);
	Veiculo *v4=new Bicicleta("XX",4,2002,"TodoTerreno");
	f.adicionaVeiculo(v1);
	f.adicionaVeiculo(v2);
	f.adicionaVeiculo(v3);
	f.adicionaVeiculo(v4);
	ASSERT_EQUAL(4, f.numVeiculos());
	ASSERT_EQUAL(1997, f.menorAno());
}


void test_f_CalculoImposto() {

	Veiculo *v1 =new Automovel("Fiat",5,1997,"gasolina",1200);
	Veiculo *v2= new Camiao("Ford",3,1999,"gasolina",1400,1000);
	Veiculo *v3=new Bicicleta("XX",4,2002,"TodoTerreno");
	Frota f;
	f.adicionaVeiculo(v1);
	f.adicionaVeiculo(v2);
	f.adicionaVeiculo(v3);
	ASSERT_EQUAL_DELTA(74.21, f.totalImposto(),0.001);
}

void test_g_InfoFrota() {

	Veiculo *v1 =new Automovel("Fiat",5,1997,"gasolina",1200);
	Veiculo *v2= new Camiao("Ford",3,1999,"gasolina",1400,1000);
	Veiculo *v3=new Bicicleta("XX",4,2002,"TodoTerreno");
	Frota f;
	f.adicionaVeiculo(v1);
	f.adicionaVeiculo(v2);
	f.adicionaVeiculo(v3);
	ASSERTM("Este teste nunca falha! VERIFICAR informa��o escrita no monitor", true);
	f.info();
}


void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_a_CriarVeiculos));
	s.push_back(CUTE(test_b_InfoVeiculo));
	s.push_back(CUTE(test_c_ImpostoVeiculo));
	s.push_back(CUTE(test_d_OperadorMenor));
	s.push_back(CUTE(test_e_CriarFrota));
	s.push_back(CUTE(test_f_CalculoImposto));
	s.push_back(CUTE(test_g_InfoFrota));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "AEDA 2011/2012 - Aula Pratica 2");
}

int main(){
    runSuite();
}
