#include "Empacotador.h"
int Caixa::ultimoId=1;
ostream& operator<<(ostream& os, Objeto obj) {
	os << "O" << obj.id << ": " << obj.peso;
	return os;
}

// Alínea A
int MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs){
	// Basicamente temos de meter na máquina os objectos que podem ser empacotados, ou seja,
	// que têm um peso inferior ou igual ao peso máximo das caixas. Estes objectos devem ser guardados
	// convenientemente na fila de prioridade dos objectos (os que foram aceites para o seu peso).
	// Nota prévia: o push na fila de prioridade já usa automaticamente o operador <, por isso tem de estar implementado!
	int total=0;
	for(int unsigned i=0; i<objs.size();i++)
		if(objs[i].getPeso()<=capacidadeCaixas) {
			objetos.push(objs[i]);
			total++;
			// Temos de retirar da paleta os que foram adicionados
			objs.erase(objs.begin()+i);
			i--;
		}
	return total;
}

// Alínea B
Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj){
	// Vamos considerar que a fila de prioridade está ordenada pelas caixas que têm menos espaço livre(mais pesadas), ou seja:
	// |__++++++| <<<  |___+++++|   <<<  |_____+++| <<  |________|
	int encontrou=0; stack<Caixa> aux; Caixa devolve;
	// (PRIMEIRO!) - Percorre as caixas
	while(!encontrou && !caixas.empty()){
		// Se encontrou a caixa não mete na stack para voltar a meter e sai do ciclo
		if (caixas.top().getEspacoLivre()>=obj.getPeso()) {
			encontrou=1;
			devolve=caixas.top();
		}
		// Se não encontrou continua a encher a stack para voltar a meter
		else aux.push(caixas.top());
		// Remove o elemento das caixas para percorrer a fila de prioridade
		caixas.pop();
	}
	// (SEGUNDO!) Volta a meter as caixas no sítio
	while(!aux.empty()){
		caixas.push(aux.top());
		aux.pop();
	}
	// (TERCEIRO!) Devolve!
	return devolve;
}

// Alínea C
int MaquinaEmpacotar::empacotaObjetos(){
	// Então temos que fazer o seguinte: tem-se que empacotar primeiro os objectos mais pesados
	// e depois preencher os espaços com os outros objectos, mas não esquecendo que temos de despachar
	// sempre os mais pesados!!!!!
	int caixasUsadas=0;
	while(!objetos.empty()){
		Objeto empacotar=objetos.top();
		Caixa devolvida=procuraCaixa(empacotar);
		if(devolvida.getEspacoLivre()==capacidadeCaixas) caixasUsadas++;
		devolvida.addObjeto(empacotar);
		objetos.pop();
		caixas.push(devolvida);
	}
	return caixasUsadas;
}

string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const{
	if (objetos.empty()) return "Não há objetos!\n";
	stringstream ss;
	HEAP_OBJS objetos2=objetos;
	while(!objetos2.empty()){
		ss << "O"<< objetos2.top().getID() <<": " << objetos2.top().getPeso() << '\n';
		objetos2.pop();
	}
	return ss.str();
}
