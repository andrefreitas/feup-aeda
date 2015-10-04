// Include of Librarys
#include "nif.h"
using namespace std;

//! Constructor
/*!
 \param number the number of nif
 */
nif::nif(unsigned long number)
{
  this->number = number;
}

//! Set Number
/*!
 \param number the number of nif
 \returns true if nif is valid
 */
bool nif::setNumber(unsigned long number)
{
  this->number = number;
  return isValid();
}

//! Get the Number
unsigned long nif::getNumber()
{
  return number;
}

//! Check if NIF is Valid
/*!
 \returns true if the remainder of the sum(described bellow) of the numbers by 11 is 0
 */
bool nif::isValid()
{
  // (1) First check if the size is correct
  stringstream ss;
  ss << number;
  if (ss.str().size() != 9)
    return 0;
  // (2) If correct check with the algorithm
  // Algorithm:  9xd1+8xd2+7xd3+6xd4+5xd5+4xd6+3xd7+2xd8+d9 must be a multiple of 11
  // where d1 is the first digit counting from the left
  int unsigned sum = 0;
  unsigned long num = number;
  for (int unsigned i = 1; i <= 9; i++)
  {
    sum += num % 10 * i;
    num /= 10;
  }
  if (sum % 11 != 0)
    return 0;
  return 1;
}

//! Operator == overloading
/*!
 \param a the first nif
 \param b the second nif
 \returns true if equal
 */
bool operator ==(nif a, nif b)
{
  return (a.getNumber() == b.getNumber());
}

//! Operator << overloading
/*!
 \param &o the ostream object
 \param &d the nif object
 \returns the changed ostream
 */
ostream & operator<<(ostream & o, nif & d)
{
  o << d.getNumber();
  return o;
}
//! Check if is a Singular Person
/*!
 \returns true if the first number is 1 or 2
 */
bool nif::isSingular()
{
  stringstream ss;
  ss << number;
  // If the first number is 1 or 2 is singular
  if (ss.str()[0] == '1' || ss.str()[0] == '2')
    return 1;
  return 0;
}

//! Operator = overloading
/*!
 \param new_nif the new nif of the object
 \returns the new nif object
 */
nif & nif::operator=(long new_nif)
{
  number = new_nif;
  return *this;
}

