#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Empacotador.h"

void test_a_CarregaObjetos() {

	vector<Objeto> objetos;
	objetos.push_back(Objeto(1, 2)); objetos.push_back(Objeto(2, 11));
	objetos.push_back(Objeto(3, 17)); objetos.push_back(Objeto(4, 3));
	objetos.push_back(Objeto(5, 9)); objetos.push_back(Objeto(6, 4));
	objetos.push_back(Objeto(7, 2)); objetos.push_back(Objeto(8, 12));
	objetos.push_back(Objeto(9, 7)); objetos.push_back(Objeto(10, 1));

	for(unsigned i = 0; i < objetos.size(); i++) cout << objetos[i] << endl;

	MaquinaEmpacotar maquina;
	int objsCarregados = maquina.carregaPaletaObjetos(objetos);
	int objsIgnorados  = objetos.size();
	ASSERT_EQUAL(7, objsCarregados);
	ASSERT_EQUAL(3, objsIgnorados);
}

void test_b_ProcuraCaixa() {


	vector<Objeto> objetos;
	objetos.push_back(Objeto(1, 2)); objetos.push_back(Objeto(2, 5));
	objetos.push_back(Objeto(3, 8)); objetos.push_back(Objeto(4, 1));
	objetos.push_back(Objeto(5, 4)); objetos.push_back(Objeto(6, 6));
	objetos.push_back(Objeto(7, 1)); objetos.push_back(Objeto(8, 4));

	Caixa::resetID();

	Caixa c1(10); //7
	c1.addObjeto( objetos[0] );
	c1.addObjeto( objetos[1] );
	Caixa c2(10); //8
	c2.addObjeto( objetos[2] );

	MaquinaEmpacotar maquina;
	maquina.addCaixa( c1 );
	maquina.addCaixa( c2 );

	cout << "Espaço livre em C" << c1.getID() << ": " << c1.getEspacoLivre() << endl; //3
	cout << "Espaço livre em C" << c2.getID() << ": " << c2.getEspacoLivre() << endl; //2

	ASSERT_EQUAL(2, maquina.numCaixasUsadas()); // 8 7

	Caixa cx = maquina.procuraCaixa( objetos[3] );
	cx.addObjeto( objetos[3] );
	maquina.addCaixa( cx );
	cout << "Espaço livre em C" << cx.getID() << ": " << cx.getEspacoLivre() << endl;
	ASSERT_EQUAL(2, maquina.numCaixasUsadas()); // 9 7

	cx = maquina.procuraCaixa( objetos[4] );
	cx.addObjeto( objetos[4] );
	maquina.addCaixa( cx );
	cout << "Espaço livre em C" << cx.getID() << ": " << cx.getEspacoLivre() << endl;
	ASSERT_EQUAL(3, maquina.numCaixasUsadas()); // 9 7 4

	cx = maquina.procuraCaixa( objetos[5] );
	cx.addObjeto( objetos[5] );
	maquina.addCaixa( cx );
	cout << "Espaço livre em C" << cx.getID() << ": " << cx.getEspacoLivre() << endl;
	ASSERT_EQUAL(3, maquina.numCaixasUsadas()); // 10 9 7

	cx = maquina.procuraCaixa( objetos[6] );
	cx.addObjeto( objetos[6] );
	maquina.addCaixa( cx );
	cout << "Espaço livre em C" << cx.getID() << ": " << cx.getEspacoLivre() << endl;
	ASSERT_EQUAL(3, maquina.numCaixasUsadas()); // 10 10 7

	cx = maquina.procuraCaixa( objetos[7] );
	cx.addObjeto( objetos[7] );
	maquina.addCaixa( cx );
	cout << "Espaço livre em C" << cx.getID() << ": " << cx.getEspacoLivre() << endl;
	ASSERT_EQUAL(4, maquina.numCaixasUsadas()); // 10 10 7 6}

}

void test_c_EmpacotaObjetos() {

	vector<Objeto> objetos;
	objetos.push_back(Objeto(1, 2)); objetos.push_back(Objeto(2, 11));
	objetos.push_back(Objeto(3, 17)); objetos.push_back(Objeto(4, 3));
	objetos.push_back(Objeto(5, 9)); objetos.push_back(Objeto(6, 4));
	objetos.push_back(Objeto(7, 2)); objetos.push_back(Objeto(8, 12));
	objetos.push_back(Objeto(9, 7)); objetos.push_back(Objeto(10, 10));
	objetos.push_back(Objeto(11, 10)); objetos.push_back(Objeto(12, 1));

	Caixa::resetID();

	MaquinaEmpacotar maquina;

	ASSERT_EQUAL(9, maquina.carregaPaletaObjetos(objetos));
	ASSERT_EQUAL(3, objetos.size());
	ASSERT_EQUAL(5, maquina.empacotaObjetos());

}

void test_d_ObjetosPorEmpacotar() {

	MaquinaEmpacotar maquina;

	ASSERT_EQUAL("Não há objetos!\n", maquina.imprimeObjetosPorEmpacotar());

	vector<Objeto> objetos;
	objetos.push_back(Objeto(1, 2)); 	 objetos.push_back(Objeto(2, 12));
	objetos.push_back(Objeto(3, 8)); 	 objetos.push_back(Objeto(4, 1));

	ASSERT_EQUAL(3, maquina.carregaPaletaObjetos(objetos));
	string objsPorEmpacotar = maquina.imprimeObjetosPorEmpacotar();
	cout << objsPorEmpacotar;
	ASSERT_EQUAL("O3: 8\nO1: 2\nO4: 1\n", maquina.imprimeObjetosPorEmpacotar());

	ASSERT_EQUAL(2, maquina.empacotaObjetos());

	ASSERT_EQUAL("Não há objetos!\n", maquina.imprimeObjetosPorEmpacotar());

}

void test_e_ConteudoCaixa() {
	/*
	vector<Objeto> objetos;
	objetos.push_back(Objeto(1, 2)); 	objetos.push_back(Objeto(2, 5));

	Caixa::resetID();

	Caixa c1(10);
	ASSERT_EQUAL("Caixa 1 vazia!\n", c1.imprimeConteudo());

	c1.addObjeto( objetos[0] );
	c1.addObjeto( objetos[1] );

	ASSERT_EQUAL("C1[ O2: 5 O1: 2 ]\n", c1.imprimeConteudo());
	*/
}

void test_f_CaixaMaisCheia() {
	/*
	vector<Objeto> objetos;
	objetos.push_back(Objeto(1, 2)); 	 objetos.push_back(Objeto(2, 11));
	objetos.push_back(Objeto(3, 17));  objetos.push_back(Objeto(4, 3));
	objetos.push_back(Objeto(5, 9)); 	 objetos.push_back(Objeto(6, 4));
	objetos.push_back(Objeto(7, 2)); 	 objetos.push_back(Objeto(8, 12));
	objetos.push_back(Objeto(9, 7));   objetos.push_back(Objeto(10, 10));
	objetos.push_back(Objeto(11, 10)); objetos.push_back(Objeto(12, 1));

	Caixa cx;
	Caixa::resetID();

	MaquinaEmpacotar maquina;

	ASSERT_THROWS(maquina.caixaMaisCheia(), MaquinaEmpacotar::MaquinaSemCaixas);
	try {
		cx = maquina.caixaMaisCheia();
	}
	catch(MaquinaEmpacotar::MaquinaSemCaixas &msc) {
		ASSERTM("Este teste nunca falha! VERIFICAR informação escrita no monitor", true);
	}

	ASSERT_EQUAL(9, maquina.carregaPaletaObjetos(objetos));
	ASSERT_EQUAL(3, objetos.size());
	ASSERT_EQUAL(5, maquina.empacotaObjetos());

	cx = maquina.caixaMaisCheia();
	ASSERT_EQUAL(5, cx.getID());
	ASSERT_EQUAL("C5[ O1: 2 O7: 2 O6: 4 ]\n", cx.imprimeConteudo());
	*/
}

void test_g_CaixaMenosCheia() {
	/*
	vector<Objeto> objetos;
	objetos.push_back(Objeto(1, 2)); 	 objetos.push_back(Objeto(2, 11));
	objetos.push_back(Objeto(3, 17));  objetos.push_back(Objeto(4, 3));
	objetos.push_back(Objeto(5, 9)); 	 objetos.push_back(Objeto(6, 4));
	objetos.push_back(Objeto(7, 2)); 	 objetos.push_back(Objeto(8, 12));
	objetos.push_back(Objeto(9, 7));   objetos.push_back(Objeto(10, 10));
	objetos.push_back(Objeto(11, 10)); objetos.push_back(Objeto(12, 1));

	Caixa cx;
	Caixa::resetID();

	MaquinaEmpacotar maquina;

	ASSERT_THROWS(maquina.caixaMenosCheia(), MaquinaEmpacotar::MaquinaSemCaixas);
	try {
		cx = maquina.caixaMenosCheia();
	}
	catch(MaquinaEmpacotar::MaquinaSemCaixas &msc) {
		ASSERTM("Este teste nunca falha! VERIFICAR informação escrita no monitor", true);
	}

	ASSERT_EQUAL(9, maquina.carregaPaletaObjetos(objetos));
	ASSERT_EQUAL(3, objetos.size());
	ASSERT_EQUAL(5, maquina.empacotaObjetos());

	cx = maquina.caixaMenosCheia();
	ASSERT_EQUAL(1, cx.getID());
	ASSERT_EQUAL("C1[ O10: 10 ]\n", cx.imprimeConteudo());
	*/
}

void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_a_CarregaObjetos));
	s.push_back(CUTE(test_b_ProcuraCaixa));
	s.push_back(CUTE(test_c_EmpacotaObjetos));
	s.push_back(CUTE(test_d_ObjetosPorEmpacotar));
	s.push_back(CUTE(test_e_ConteudoCaixa));
	s.push_back(CUTE(test_f_CaixaMaisCheia));
	s.push_back(CUTE(test_g_CaixaMenosCheia));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "AEDA 2011/12 - Aula Prática - Filas de Prioridade.");
}

int main(){
    runSuite();
    return 0;
}



