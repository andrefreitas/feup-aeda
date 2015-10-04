/*
	Autor: André Freitas
	Email: p.andrefreitas@gmail.com
*/
#ifndef FROTA_H_
#define FROTA_H_
#include <string>
#include <vector>

using namespace std;


class  Veiculo {
protected:
   string marca;
   int mes, ano;
public:
   Veiculo(string marca, int mes, int ano);
   bool operator < (const Veiculo & v) const;
   virtual float calcImposto() const = 0;
   string getMarca() const;
   virtual int info() const;
   friend class Frota;
};

class Motorizado: public Veiculo {
   string combustivel;
   int cilindrada;
public:
   Motorizado(string marca, int mes, int ano, string comb,int cc);
   string getCombustivel() const;
   virtual int info() const;
   virtual float calcImposto() const;
};

class Automovel: public Motorizado {
public:
	Automovel(string marca, int mes, int ano, string comb,int cc);
};


class Camiao: public Motorizado {
   int carga_maxima;
public:
   Camiao(string marca, int mes, int ano,string comb,int cc, int cmax);
   int info() const;
};


class Bicicleta: public Veiculo {
  string tipo;
public:
  Bicicleta(string marca, int mes, int ano,string tt);
  int info() const;
  float calcImposto() const{ return 0.0;};
};

class Frota {
	vector<Veiculo *> veiculos;
public:
	int numVeiculos() const;
	int menorAno() const;
	void adicionaVeiculo(Veiculo *v1);
	void info() const;
	float totalImposto() const;
};
#endif /*VEICULO_H_*/
