#include "Jogo.h"
#include <sstream>
// Alínea A
Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados ){
	jogo=iniciaJogo(0,niv,pontos,estados);
}

BinaryTree<Circulo> Jogo::iniciaJogo(int pos, int nivel, vector<int> &pontos, vector<bool> &estados ){
    Circulo aux(pontos[pos],estados[pos]);
    // Usar Recursividade!!!
    if (nivel==0) return BinaryTree<Circulo>(aux);
    else{
    	BinaryTree<Circulo> arvore(aux,iniciaJogo(2*pos+1,nivel-1,pontos,estados),iniciaJogo(2*pos+2,nivel-1,pontos,estados));
    	return arvore;
    }
}

// Alínea B
string Jogo::escreveJogo(){
	BTItrLevel<Circulo> iterador(jogo);
	stringstream ss;
	while( !iterador.isAtEnd()){
		ss<< iterador.retrieve().getPontuacao() << "-";
		if(iterador.retrieve().getEstado())
			ss << "true";
		else
			ss << "false";
		ss <<"-"<< iterador.retrieve().getNVisitas() << '\n';
		iterador.advance();
	}
	return ss.str();
}
// Alínea C
// Verifica se é uma folha a posição actual
bool folha(BTItrLevel<Circulo> iterador, int pos){
	int total=2*pos-pos;
	for (int i=0;i<total;i++){
		iterador.advance();
		if (iterador.isAtEnd()) return true;

	}
	return false;
}
// Avança o iterador de uma certa posição para a outra
void avancaIt(BTItrLevel<Circulo> &iterador, int posActual, int posFinal){
	int total=posFinal-posActual;
	for (int i=0;i<total;i++) iterador.advance();
}

int Jogo::jogada(){
	BTItrLevel<Circulo> iterador(jogo);
	int unsigned pos=1;
	cout << "------ Jogada ------\n";
	// Vamos percorrer a árvore enquanto o nó não é uma folha
	while(!folha(iterador,pos)){
		cout << pos << endl;
		// Se é true o estado vai para a direita 2*posicao+1
		if (iterador.retrieve().getEstado()) {
			iterador.retrieve().incNVisitas();
			iterador.retrieve().mudaEstado();
			avancaIt(iterador,pos,2*pos+1);
			pos=2*pos+1;
		}
		// Se é false o estado vai para a esquerda 2*posicao
		else {
			iterador.retrieve().incNVisitas();
			iterador.retrieve().mudaEstado();
			avancaIt(iterador,pos,2*pos);
			pos=2*pos;
		}

	}
	cout << pos << endl;
	return iterador.retrieve().getPontuacao();
}

// Alínea D
int Jogo::maisVisitado(){
	BTItrLevel<Circulo> iterador(jogo);
	iterador.advance();
	int maior=iterador.retrieve().getNVisitas();
	while(!iterador.isAtEnd()){
		if (iterador.retrieve().getNVisitas()>maior) maior=iterador.retrieve().getNVisitas();
		iterador.advance();
	}
	return maior;
}
