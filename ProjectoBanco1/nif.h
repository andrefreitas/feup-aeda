#ifndef nif_h
#define nif_h
// Include of librarys
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
//! Numero de Identificao Fiscal with 9 fields
/*! This class allows the definition of a object of a NIF type and allows the validation of this number. 
 The NIF is an Finance Identifier of a person or company
 */
class nif
{
  //! The 9 length NIF Number
  unsigned long number;
public:
  // ******************************** Constructors
  //! Empty constructor
  nif()
  {
  }
  //! Constructor with nif number param
  nif(unsigned long number);
  // ******************************** Set Methods
  //! Set Number
  bool setNumber(unsigned long number);
  // ******************************** Get Methods
  //! Get NIF Number
  unsigned long getNumber();
  //! Get type of NIF number: singular or colective
  bool isSingular();
  //! Check is NIF is valid
  bool isValid();
  // ******************************** Others
  //! Overloading of Operator ==
  friend bool operator ==(nif a, nif b);
  //! Overloading of Operator <<
  friend ostream & operator<<(ostream & o, nif & d);
  //! Overloading of Operator =
  nif & operator=(long nif_novo);
};
#endif
