/*
	Autor: André Freitas
	Email: p.andrefreitas@gmail.com
*/
#include "Frota.h"
#include <iostream>
#include <string>

using namespace std;
// Alinea (a)
Veiculo::Veiculo(string marca, int mes, int ano){
	this->marca=marca;
	this->mes=mes;
	this->ano=ano;
}
Motorizado::Motorizado(string marca, int mes, int ano, string comb,int cc):Veiculo(marca,mes,ano){
	combustivel=comb;
	cilindrada=cc;
}
Automovel::Automovel(string marca, int mes, int ano, string comb,int cc):Motorizado(marca,mes,ano,comb,cc){

}
Camiao::Camiao(string marca, int mes, int ano,string comb,int cc, int cmax):Motorizado(marca,mes,ano,comb,cc){
	carga_maxima=cmax;
}
Bicicleta::Bicicleta(string marca, int mes, int ano,string tt):Veiculo(marca,mes,ano){
	tipo=tt;
}
string Veiculo::getMarca() const{
	return marca;
}
string Motorizado::getCombustivel() const{
	return combustivel;
}
// Alinea b
int Veiculo::info() const{
	cout << "Marca: "<< marca << endl;
	cout << "Mes "<< mes << endl;
	cout << "Ano: "<< ano << endl;
	return 3;
}
int Motorizado::info() const{
	Veiculo::info();
	cout << "Combustivel: "<< combustivel << endl;
	cout << "Cilindrada: "<< cilindrada << endl;
	return 5;
}
int Camiao::info() const{
	Motorizado::info();
	cout << "Carga Maxima: " << carga_maxima << endl;
	return 6;
}
int Bicicleta::info() const{
	Veiculo::info();
	cout << "Tipo: " << tipo << endl;
	return 4;
}
// Alinea C
float Motorizado::calcImposto() const{
	double *p;
		int *pt;
		// Ano
		double depois95[]={14.56,29.06, 45.15, 113.98,181.17,320.89};
		double ate95[]={8.10,14.56,22.65,54.89,87.13,148.37};
		// Combustivel e cilindradas
		int outro[]={1500,2000,3000};
		int gasolina[]={1000,1300,1750,2600,3500};
		// (1) Determinar ano
		if (ano>1995) p=depois95;
		else p=ate95;
		// (2) Determinar Combustivel
		int tamanho;
		if (combustivel=="gasolina"){
			cout << "**\nGASOLINAAAAAAA\n";
			pt=gasolina;
			tamanho=5;}
		else{
			pt=outro;
			tamanho=3;
		}
		// (3) Ciclo para determinar
		for (int unsigned i=0; i<=tamanho;i++){
			if (i<tamanho && cilindrada<=*(pt+i))
				return *(p+i);
			if(i==tamanho) return *(p+tamanho);
		}
		return 0;
}
// Alinea d
bool Veiculo::operator < (const Veiculo & v) const{
	if (ano==v.ano) return mes<v.mes;
	else return ano < v.ano;
}
// Alinea e
int Frota::numVeiculos() const{
	return veiculos.size();
}
int Frota::menorAno() const{
	int menor;
	if (veiculos.size()==0) return 0;
	else{
		menor=veiculos[0]->ano;
		for (int unsigned i=0; i<veiculos.size(); i++)
			if (veiculos[i]->ano<menor) menor=veiculos[i]->ano;

	}
	return menor;
}
void Frota::adicionaVeiculo(Veiculo *v1){
	veiculos.push_back(v1);
}
// Alinea f
float Frota::totalImposto() const{
	float soma=0;
	for (int unsigned i=0; i<veiculos.size(); i++)
		soma+=veiculos[i]->calcImposto();
	return soma;
}
// Alinea g
void Frota::info() const{
	for(int unsigned i=0; i<veiculos.size(); i++)
		veiculos[i]->info();
}
