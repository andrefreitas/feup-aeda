#ifndef nib_h
#define nib_h
// Include of Librarys
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
//!  Numero de Identificao Bancaria (21 Digits) - Format BBBB AAAA NNNN NNNN NNNC C
/*! The NIB is a 21 lenght number that contains the Bank, the Agency and the Bank Account Number and it has a control digit
 To compute the digit control we need to do the remaind by 97 of the NIB number without the last 2 digits and then subtract from 98 the result
 */
class nib
{
  //! bank number (4 digits)
  int bank;
  //! bank agency number (4 digits)
  int agency;
  //! bank account number (11 digits)
  long long number;
  //! control number (2 digits)
  long long control;
public:
  // ******************************** Constructors
  //! Empty Constructor
  nib()
  {
    bank = 0;
    agency = 0;
    number = 0;
    control = 0;
  }
  //! NIB Constructor
  nib(int bank, int agency, long long number);
  // ******************************** Set Methods
  //! Set Bank number
  bool setBank(int bank);
  //! Set Agency number
  bool setAgency(int agency);
  //! Set Account number
  bool setNumber(long long number);
  //! Set Control number by the algorithm
  void setControl();
  //! Set Control number by user input
  bool setControl(long long control);
  // ******************************** Get Methods
  //! Get bank number
  int getBank();
  //! Get agency number
  int getAgency();
  //! Get account number
  long long getNumber();
  //! Get control number
  long long getControl();
  string print();
  // ******************************** Others
  //! Check if the NIB is valid
  bool isValid();
  //! Overloading of operator << to pring the number in the standard format
  friend ostream & operator<<(ostream & o, const nib & d);
  //! Overloading of operator ==
  bool operator==(nib n);
  //!Get string with NIB
  string getNIBstring();
};
#endif
