// Include of Librarys
#include "nib.h"
#include <iomanip>
#include <cmath>
using namespace std;

//! Constructor
/*!
 \param bank the bank number with 4 digits length
 \param agency the agency number with 4 digits length
 \param number the account number with 11 digits length
 \returns void
 */
nib::nib(int bank, int agency, long long number)
{
  // (1) Set normal fields of NIB
  this->bank = bank;
  this->agency = agency;
  this->number = number;
  // (2) Generate Control Digit
  setControl();
}
//! Set Bank Number
/*!
 \param bank the bank number with 4 digits length
 \returns true upon sucess
 */
bool nib::setBank(int bank)
{
  stringstream ss;
  ss << bank;
  if (ss.str().size() > 4)
    return 0;
  else
  {
    this->bank = bank;
    return 1;
  }
}
//! Set Agency number
/*!
 \param agency the 4 digits of agency number
 \returns true upon sucess
 */
bool nib::setAgency(int agency)
{
  stringstream ss;
  ss << agency;
  if (ss.str().size() > 4)
    return 0;
  else
  {
    this->agency = agency;
    return 1;
  }
}

//! Set Account Number
/*!
 \param number the bank number with 11 digits length
 \returns true upon sucess
 */
bool nib::setNumber(long long number)
{
  stringstream ss;
  ss << number;
  if (ss.str().size() > 11)
    return 0;
  else
  {
    this->number = number;
    return 1;
  }
}
//! Set the Control Digit using a know algorithm
/*!

 \returns void
 */
void nib::setControl()
{
  long long sum = bank * pow(10.0, 15) + agency * pow(10.0, 11);
  sum += number;
  control = 98 - (sum % 97);
}
//! Set the Control Digit by hand
/*!	  \param control the control digit of the nib
 \returns false if the control digit lenght is bigger than 2
 */
bool nib::setControl(long long control)
{
  stringstream ss;
  ss << control;
  if (ss.str().size() > 2)
    return 0;
  else
  {
    this->control = control;
    return 1;
  }
}
//! Get bank number
/*!
 \returns the bank number
 */
int nib::getBank()
{
  return bank;
}
//! Get agency number
/*!
 \returns the agency number
 */
int nib::getAgency()
{
  return agency;
}
//! Get account number
/*!
 \returns the account number
 */
long long nib::getNumber()
{
  return number;
}

//! Get control number
/*!
 \returns the control number
 */
long long nib::getControl()
{
  return control;

}
// Auxiliar function
void fillStringInt(int begin, int end, long long number, string &st)
{
  long long aux = number;
  for (int i = end; i >= begin; i--)
  {
    stringstream ss;
    ss << aux % 10;
    st[i - 1] = ss.str()[0];
    aux /= 10;
  }
}
//! Check if the NIB is valid, using a know algorithm
/*!
 \returns true if valid
 */
bool nib::isValid()
{
  long long sum = bank * pow(10.0, 15) + agency * pow(10.0, 11);
  sum += number;
  long long correctControl = 98 - (sum % 97);
  return correctControl == control;
}
//! Operator <<, that prints in the corrent format the NIB
/*!
 \param &o the ostream that will receive the nib
 \param &d the nib object
 \returns the changed ostream
 */
ostream & operator<<(ostream & o, const nib & d)
{
  string st;
  // (1) Fill by default with zeros
  for (int unsigned i = 0; i < 21; i++)
    st.push_back('0');
  // (2) Fill the string with fields
  fillStringInt(1, 4, d.bank, st);
  fillStringInt(5, 8, d.agency, st);
  fillStringInt(9, 19, d.number, st);
  fillStringInt(20, 21, d.control, st);
  // (3) Add the spaces between fields
  o << st.substr(0, 4) << " " << st.substr(4, 4) << " " << st.substr(8, 4)
      << " " << st.substr(12, 4) << " " << st.substr(16, 4) << " "
      << st.substr(20, 1);
  return o;
}
string nib::getNIBstring()
{
	stringstream o;
	 string st;
	  // (1) Fill by default with zeros
	  for (int unsigned i = 0; i < 21; i++)
	    st.push_back('0');
	  // (2) Fill the string with fields
	  fillStringInt(1, 4, bank, st);
	  fillStringInt(5, 8, agency, st);
	  fillStringInt(9, 19, number, st);
	  fillStringInt(20, 21, control, st);
	  // (3) Add the spaces between fields
	  o << st.substr(0, 4) << " " << st.substr(4, 4) << " " << st.substr(8, 4)
	      << " " << st.substr(12, 4) << " " << st.substr(16, 4) << " "
	      << st.substr(20, 1);
	  return o.str();
}
//! Operator == to compare if 2 NIBs objects are equal
/*!
 \param nib an object of type nib
 \returns true if equal
 */
bool nib::operator==(nib n)
{
  return (n.agency == agency && n.bank == bank && n.control == control
      && n.number == number);
}
//! Print the string
string nib::print()
{
  stringstream o;
  string st;
  // (1) Fill by default with zeros
  for (int unsigned i = 0; i < 21; i++)
    st.push_back('0');
  // (2) Fill the string with fields
  fillStringInt(1, 4, bank, st);
  fillStringInt(5, 8, agency, st);
  fillStringInt(9, 19, number, st);
  fillStringInt(20, 21, control, st);
  // (3) Add the spaces between fields
  o << st.substr(0, 4) << " " << st.substr(4, 4) << " " << st.substr(8, 4)
      << " " << st.substr(12, 4) << " " << st.substr(16, 4) << " "
      << st.substr(20, 1);
  return o.str();
}
