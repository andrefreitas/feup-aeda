#include "Empacotador.h"
int Caixa::ultimoId=1;
ostream& operator<<(ostream& os, Objeto obj) {
	os << "O" << obj.id << ": " << obj.peso;
	return os;
}

// Al�nea A
int MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs){
	// Basicamente temos de meter na m�quina os objectos que podem ser empacotados, ou seja,
	// que t�m um peso inferior ou igual ao peso m�ximo das caixas. Estes objectos devem ser guardados
	// convenientemente na fila de prioridade dos objectos (os que foram aceites para o seu peso).
	// Nota pr�via: o push na fila de prioridade j� usa automaticamente o operador <, por isso tem de estar implementado!
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

// Al�nea B
Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj){
	// Vamos considerar que a fila de prioridade est� ordenada pelas caixas que t�m menos espa�o livre(mais pesadas), ou seja:
	// |__++++++| <<<  |___+++++|   <<<  |_____+++| <<  |________|
	int encontrou=0; stack<Caixa> aux; Caixa devolve;
	// (PRIMEIRO!) - Percorre as caixas
	while(!encontrou && !caixas.empty()){
		// Se encontrou a caixa n�o mete na stack para voltar a meter e sai do ciclo
		if (caixas.top().getEspacoLivre()>=obj.getPeso()) {
			encontrou=1;
			devolve=caixas.top();
		}
		// Se n�o encontrou continua a encher a stack para voltar a meter
		else aux.push(caixas.top());
		// Remove o elemento das caixas para percorrer a fila de prioridade
		caixas.pop();
	}
	// (SEGUNDO!) Volta a meter as caixas no s�tio
	while(!aux.empty()){
		caixas.push(aux.top());
		aux.pop();
	}
	// (TERCEIRO!) Devolve!
	return devolve;
}

// Al�nea C
int MaquinaEmpacotar::empacotaObjetos(){
	// Ent�o temos que fazer o seguinte: tem-se que empacotar primeiro os objectos mais pesados
	// e depois preencher os espa�os com os outros objectos, mas n�o esquecendo que temos de despachar
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
	if (objetos.empty()) return "N�o h� objetos!\n";
	stringstream ss;
	HEAP_OBJS objetos2=objetos;
	while(!objetos2.empty()){
		ss << "O"<< objetos2.top().getID() <<": " << objetos2.top().getPeso() << '\n';
		objetos2.pop();
	}
	return ss.str();
}
