#ifndef APOSTA_H_
#define APOSTA_H_

#include <hash_set>
#include <string>
#include <sstream>
using namespace __gnu_cxx;
using namespace std;

class Aposta
{
	hash_set<int> numeros;
public:
	Aposta() {};
	void geraAposta(const vector<int> &valores, int n=6);
	bool contem(int num) const;
	int calculaCertos(const hash_set<int> & sorteio) const;
	string imprimeAposta() const;
	hash_set<int> getNumeros() const { return numeros; }
};	

#endif /*APOSTA_H_*/
