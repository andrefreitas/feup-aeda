#ifndef BALCAO_H_
#define BALCAO_H_

#include <iostream>
#include <queue>

using namespace std;
// Al�nea 2b
class FilaVazia{
public:
	FilaVazia(){};
	string getMsg(){ return "Fila Vazia";};
};

class Cliente {
      int numPresentes;
public:
      Cliente();
      int getNumPresentes();
};


class Balcao {
      queue<Cliente> clientes;
      const int tempo_embrulho;
      int prox_chegada, prox_saida;
      int tempo_atual;
      int clientes_atendidos;
public:
      Balcao(int te=2);
      int getTempoAtual() const;
      int getProxChegada() const;
      int getClientesAtendidos() const;
      int getTempoEmbrulho() const;
      int getProxSaida() const;
      Cliente & getProxCliente();

      void chegada();
      void saida();
      void proximoEvento();

      //friend ostream & operator << (ostream & out, const Balcao & b1);
};


#endif
