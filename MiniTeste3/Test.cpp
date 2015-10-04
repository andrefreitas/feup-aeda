#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include <list>
#include "CommServer.h"

using namespace std;

void test_1a_Construtor_CommServer(){

	CommServer cs;
	ASSERT_EQUAL(3, cs.getCompFila());
	ASSERT_EQUAL(4, cs.getTamPilha());

	CommServer cs1(12, 21);
	ASSERT_EQUAL(12, cs1.getCompFila());
	ASSERT_EQUAL(21, cs1.getTamPilha());

}

void test_1b_FuncaoTemplate(){

	stack<int> s1;
	s1.push(1);
	s1.push(2);
	s1.push(3);
	stack<int> s2;
	s2.push(1);
	s2.push(2);
	stack<int> s3;
	s3.push(1);
	s3.push(2);
	s3.push(3);
	s3.push(4);
	queue< stack<int> > q;
	q.push(s1);
	q.push(s2);
	q.push(s3);
	ASSERT_EQUAL(false, q.empty());
	ASSERT_EQUAL(9, obterNumElem(q));
	ASSERT_EQUAL(false, q.empty());

	queue< stack<int> > q1;
	ASSERT_EQUAL(true, q1.empty());
	ASSERT_EQUAL(0, obterNumElem(q1));

}

void test_1c_EstadoServidor(){

	CommServer cs0;
	cs0.setCompFila(1);
	cs0.setTamPilha(3);
	ASSERT_EQUAL(true, cs0.servidorVazio());

	Payload pl1(1, "PL1");
	stack<Payload> s1;
	stack<Payload> s2;
	s1.push(pl1);
	s2.push(pl1);
	cs0.adicionarElemento(cs0.getFila1(), s1);
	cs0.adicionarElemento(cs0.getFila2(), s2);
	ASSERT_EQUAL(true, cs0.servidorLivre());

	CommServer cs1;
	cs1.setCompFila(1);
	cs1.setTamPilha(3);

	s1.push(pl1);
	s2.push(pl1);
	s1.push(pl1);
	s2.push(pl1);
	cs0.adicionarElemento(cs1.getFila1(), s1);
	cs0.adicionarElemento(cs1.getFila2(), s2);
	ASSERT_EQUAL(true, cs1.servidorOcupado());

}

void test_1d_AdicionarPayload(){

	CommServer cs0;
	cs0.setCompFila(2);
	cs0.setTamPilha(2);
	// Testar o adicionar quando o servidor está vazio (sem pilha nenhuma)
	// por isso, deve adicionar na fila1 uma nova stack
	Payload pl1(1, "PL1");
	cs0.adicionarPayload(pl1);
	queue< stack<Payload> > f1=cs0.getFila1();
	stack<Payload> s1f=f1.front();
	stack<Payload> s1b=f1.back();
	ASSERT_EQUAL(1, f1.size());
	ASSERT_EQUAL(1, s1f.size());
	queue< stack<Payload> > f2=cs0.getFila2();
	stack<Payload> s2f=f1.front();
	stack<Payload> s2b=f1.back();
	ASSERT_EQUAL(0, f2.size());

	// Insere outro e, agora, terá de o inserir na fila2
	Payload pl2(2, "PL2");

	cs0.adicionarPayload(pl2);

	f1=cs0.getFila1();
	s1f=f1.front();
	s1b=f1.back();
	ASSERT_EQUAL(1, f1.size());
	ASSERT_EQUAL(1, s1f.size());
	f2=cs0.getFila2();
	s2f=f1.front();
	s2b=f1.back();
	ASSERT_EQUAL(1, f2.size());
	ASSERT_EQUAL(1, s2f.size());

	// Insere agora até encher. teremos de validar se lança a excepção FilasCheias
	Payload pl3(3, "PL3");
	Payload pl4(4, "PL4");
	Payload pl5(5, "PL5");
	Payload pl6(6, "PL6");
	Payload pl7(7, "PL7");
	Payload pl8(8, "PL8");
	Payload pl9(9, "PL9");
	cs0.adicionarPayload(pl3);
	cs0.adicionarPayload(pl4);
	cs0.adicionarPayload(pl5);
	cs0.adicionarPayload(pl6);
	cs0.adicionarPayload(pl7);
	cs0.adicionarPayload(pl8);
	// verificar se as filas foram preenchidas correctamente
	f1=cs0.getFila1();
	s1f=f1.front();
	s1b=f1.back();
	ASSERT_EQUAL(2, f1.size());
	ASSERT_EQUAL(2, s1f.size());
	ASSERT_EQUAL(2, s1b.size());
	f2=cs0.getFila2();
	s2f=f1.front();
	s2b=f1.back();
	ASSERT_EQUAL(2, f2.size());
	ASSERT_EQUAL(2, s2f.size());
	ASSERT_EQUAL(2, s2b.size());

	// como está cheio tem de lançar excepção
	ASSERT_THROWS(cs0.adicionarPayload(pl9), FilasCheias);
	// lançando excepção as filas têm de ficar com o mesmo numero de elementos que tinham antes

	f1=cs0.getFila1();
	s1f=f1.front();
	s1b=f1.back();
	ASSERT_EQUAL(2, f1.size());
	ASSERT_EQUAL(2, s1f.size());
	ASSERT_EQUAL(2, s1b.size());
	f2=cs0.getFila2();
	s2f=f1.front();
	s2b=f1.back();
	ASSERT_EQUAL(2, f2.size());
	ASSERT_EQUAL(2, s2f.size());
	ASSERT_EQUAL(2, s2b.size());


}

void test_1e_RegistaEntradaSaida(){

	CommServer cs0;
	cs0.setCompFila(1);
	cs0.setTamPilha(3);
	Payload pl1(1, "PL1");
	Payload pl2(2, "PL2");
	Payload pl3(3, "PL3");
	Payload pl4(4, "PL4");
	// Regista as 4 entradas para os 4 payloads
	cs0.registaEntrada("10:00", pl1);
	cs0.registaEntrada("11:00", pl2);
	cs0.registaEntrada("12:00", pl3);
	cs0.registaEntrada("13:00", pl4);
	ASSERT_EQUAL(4, cs0.getEntrada().size());
	ASSERT_EQUAL(1, cs0.getEntrada().front().getPl().getId());
	ASSERT_EQUAL(4, cs0.getEntrada().back().getPl().getId());

	CommServer cs1;
	cs1.setCompFila(1);
	cs1.setTamPilha(3);
	// Regista as 4 saidas para os 4 payloads
	cs1.registaSaida("10:00", pl1);
	cs1.registaSaida("11:00", pl2);
	cs1.registaSaida("12:00", pl3);
	cs1.registaSaida("13:00", pl4);
	ASSERT_EQUAL(4, cs1.getSaida().size());
	ASSERT_EQUAL(1, cs1.getSaida().front().getPl().getId());
	ASSERT_EQUAL(4, cs1.getSaida().back().getPl().getId());

}

void test_1f_ConciliaLogs(){

	// quando a lista de entrada é maior que a da saida
	CommServer cs0;
	cs0.setCompFila(1);
	cs0.setTamPilha(3);
	Payload pl1(1, "PL1");
	Payload pl2(2, "PL2");
	Payload pl3(3, "PL3");
	Payload pl4(4, "PL4");
	// Regista as 4 entradas para os 4 payloads
	cs0.registaEntrada("10:00", pl1);
	cs0.registaEntrada("11:00", pl2);
	cs0.registaEntrada("12:00", pl3);
	cs0.registaEntrada("13:00", pl4);
	// Regista as 3 saidas
	cs0.registaSaida("10:00", pl1);
	cs0.registaSaida("11:00", pl2);
	cs0.registaSaida("12:00", pl3);
	list<Log> ls = cs0.conciliaLogs();
	ASSERT_EQUAL(false, ls.empty());
	ASSERT_EQUAL(4, ls.back().getPl().getId() );

	// Agora quando a lista de saida é maior que a da entrada
	CommServer cs1;
	cs1.setCompFila(1);
	cs1.setTamPilha(3);
	// Regista as 3 entradas
	cs1.registaEntrada("11:00", pl2);
	cs1.registaEntrada("12:00", pl3);
	cs1.registaEntrada("13:00", pl4);
	// Regista as 4 saidas
	cs1.registaSaida("10:00", pl1);
	cs1.registaSaida("11:00", pl2);
	cs1.registaSaida("12:00", pl3);
	cs1.registaSaida("13:00", pl4);
	list<Log> ls1 = cs1.conciliaLogs();
	ASSERT_EQUAL(false, ls1.empty());
	ASSERT_EQUAL(1, ls1.back().getPl().getId());

	// agora quando não há diferenças
	CommServer cs2;
	cs2.setCompFila(1);
	cs2.setTamPilha(3);
	// Regista as 4 entradas para os 4 payloads
	cs2.registaEntrada("10:00", pl1);
	cs2.registaEntrada("11:00", pl2);
	cs2.registaEntrada("12:00", pl3);
	cs2.registaEntrada("13:00", pl4);
	// Regista as 3 saidas
	cs2.registaSaida("10:00", pl1);
	cs2.registaSaida("11:00", pl2);
	cs2.registaSaida("12:00", pl3);
	cs2.registaSaida("13:00", pl4);
	list<Log> ls3 = cs2.conciliaLogs();
	ASSERT_EQUAL(true, ls3.empty());

}

void test_1g_ObterPayload(){

	CommServer cs0;
	cs0.setCompFila(1);
	cs0.setTamPilha(3);
	// testar se lança excepção quando o numero de elementos pedidos esta errado
	ASSERT_THROWS(cs0.obterPayload(0), ErroNumeroElementos);
	ASSERT_THROWS(cs0.obterPayload(13), ErroNumeroElementos);

	// adiciona elementos para prosseguir os testes
	Payload pl1(1, "PL1");
	Payload pl2(2, "PL2");
	Payload pl3(3, "PL3");
	Payload pl4(4, "PL4");
	Payload pl5(5, "PL5");
	Payload pl6(6, "PL6");

	stack<Payload> sa;
	sa.push(pl1);
	sa.push(pl3);
	sa.push(pl5);

	stack<Payload> sb;
	sb.push(pl2);
	sb.push(pl4);
	sb.push(pl6);

	cs0.adicionarElemento(cs0.getFila1(), sa);
	cs0.adicionarElemento(cs0.getFila2(), sb);


	// verifica se retira os elementos certos começando na fila1
	// e, depois, alternadamente.
	list<Payload> comp;

	comp = cs0.obterPayload(6);
	ASSERT_EQUAL(6, comp.size());
	ASSERT_EQUAL(true, cs0.getFila1().empty());
	ASSERT_EQUAL(true, cs0.getFila2().empty());

	// Verifica se devolveu a lista com os payloads correctos
	// e com o tamanho correcto
	ASSERT_EQUAL(6, comp.size());
	ASSERT_EQUAL(pl5.getId(), comp.front().getId());
	comp.pop_front();
	ASSERT_EQUAL(pl6.getId(), comp.front().getId());
	comp.pop_front();

	// testa situacao em que uma fila fica vazia
	CommServer cs1;
	cs1.setCompFila(1);
	cs1.setTamPilha(3);
	// adiciona elementos para prosseguir os testes
	stack<Payload> s1;
	s1.push(pl1);
	stack<Payload> s2;
	s2.push(pl2);
	stack<Payload> s3;
	s3.push(pl3);
	stack<Payload> s4;
	s4.push(pl4);
	cs1.adicionarElemento(cs1.getFila1(), s1);
	cs1.adicionarElemento(cs1.getFila1(), s2);
	cs1.adicionarElemento(cs1.getFila1(), s3);
	cs1.adicionarElemento(cs1.getFila2(), s4);

	// verifica se retira os elementos certos começando na fila1.
	list<Payload> comp1;
	comp1 = cs1.obterPayload(4);
	ASSERT_EQUAL(true, cs1.getFila1().empty());
	ASSERT_EQUAL(true, cs1.getFila2().empty());

	// Verifica se devolveu a lista com os payloads correctos
	// e com o tamanho correcto
	ASSERT_EQUAL(4, comp1.size());
	ASSERT_EQUAL(pl1.getId(), comp1.front().getId());
	comp1.pop_front();
	ASSERT_EQUAL(pl4.getId(), comp1.front().getId());
	comp1.pop_front();



}

void runSuite(){
	cute::suite s;
	s.push_back(CUTE(test_1a_Construtor_CommServer));
	s.push_back(CUTE(test_1b_FuncaoTemplate));
	s.push_back(CUTE(test_1c_EstadoServidor));
	s.push_back(CUTE(test_1d_AdicionarPayload));
	s.push_back(CUTE(test_1e_RegistaEntradaSaida));
	s.push_back(CUTE(test_1f_ConciliaLogs));
	s.push_back(CUTE(test_1g_ObterPayload));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "AEDA 2010/2011 - Componente Individual 3 - 24/11/2010");
}

int main(){
    runSuite();
    return 0;
}



