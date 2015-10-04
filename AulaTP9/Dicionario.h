#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "BST.h"


class PalavraSignificado {
      string palavra;
      string significado;
public:
       PalavraSignificado(string p, string s): palavra(p), significado(s) {}
       string getPalavra() { return palavra; }
       string getSignificado() { return significado; }
       void setSignificado(string sig) { significado=sig; }
       bool operator < (const PalavraSignificado &ps1) const;
       bool operator ==(const PalavraSignificado &ps1) const;
};

class Dicionario
{
      BST<PalavraSignificado> palavras();
public:
      BST<PalavraSignificado>() getPalavras() const;
};


#endif
