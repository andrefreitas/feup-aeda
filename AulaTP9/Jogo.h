#ifndef JOGO_H_
#define JOGO_H_

#include "BinaryTree.h"
#include <iostream>
#include <stdlib.h>
using namespace std;


class Circulo {
 int pontuacao;
 bool estado;
 int nVisitas;
public:
 Circulo(int p=0, bool e=false): pontuacao(p), estado(e), nVisitas(0) {}
 int getPontuacao() const { return pontuacao; }
 bool getEstado() const { return estado; }
 int getNVisitas() const { return nVisitas; }
 friend ostream &operator << (ostream &os, Circulo &c1);
 void mudaEstado() { if (estado==false) estado=true; else estado=false; }
 int incNVisitas() { return nVisitas++; }
};



class Jogo {
	BinaryTree<Circulo> jogo;
public:
	BinaryTree<Circulo> &getJogo() { return jogo; }
	// Alínea A
	Jogo(int niv, vector<int> &pontos, vector<bool> &estados );
	BinaryTree<Circulo> iniciaJogo(int pos, int nivel, vector<int> &pontos, vector<bool> &estados );
	// Alínea B
	string escreveJogo();
	// Alínea C
	int jogada();
	// Alínea D
	int maisVisitado();
};


#endif
