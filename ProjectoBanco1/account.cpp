// Include of Librarys
#include "account.h"
using namespace std;

// ******************************************************************************************
//                                         Class Account
// ******************************************************************************************
//! Constructor
/*!
 \param money the initial deposit
 \param &holders the vector that have the ids of the holders
 \param managerID the id of the account manager
 */

account::account(money initialDeposit, vector<int> &holders,
    unsigned int managerID)
{
  this->holders = holders;
  this->managerID = managerID;
  // Generate the NIB
  this->ID = nextAccountID;
  nextAccountID++;
  nib aux(bank, agency, ID);
  NIB = aux;
  // Do the initial deposit
  deposit(initialDeposit);
}

account::account(money initialDeposit, vector<int> &holders,
    unsigned int managerID, unsigned int ID)
{
  this->holders = holders;
  this->managerID = managerID;
  // Generate the NIB
  this->ID = ID;
  nib aux(bank, agency, ID);
  NIB = aux;
  // Do the initial deposit
  deposit(initialDeposit);
}

//! Set the total accounts number
long account::nextAccountID = 1; //Starts at 1

//! The bank number
long account::bank = 0;

//! The agency number
long account::agency = 0;

unsigned int account::getManagerID()
{
  return managerID;
}

//! Set the NIB of the account
void account::setNIB(nib n)
{
  NIB = n;
}

//! Set the balance of the account
void account::setBalance(money balance)
{
  this->balance = balance;
}

//! set the bank number
void account::setBank(long number)
{
  bank = number;
}

//! set the agency number
void account::setAgency(long number)
{
  agency = number;
}

//! add an ammount of money to an account
void account::deposit(money ammount)
{
  balance += ammount;
}

//! Get the holders vector
vector<int> account::getHolders()
{
  return holders;
}

//! Add an holder to the account
void account::addHolder(int a)
{
  holders.push_back(a);
}

//! Get the number of holders
int account::getNumHolders()
{
  return holders.size();
}
void account::reHolder(int a)
{
  vector<int> new_vector;
  for (unsigned int i = 0; i < holders.size(); i++)
    if (holders[i] != a)
      new_vector.push_back(holders[i]);
  holders = new_vector;

}

// ******************************************************************************************
//                                         Class Term: Public Account
// ******************************************************************************************
//! Constructor
/*!
 \param money the initial deposit
 \param &holders the vector that have the ids of the holders
 \param managerID the id of the account manager
 \param begindate the account creation date
 \param enddate the end date of the contract
 \param interestp the interest of the account
 */
Term::Term(money initialDeposit, vector<int> &holders, int managerID,
    string beginDate, string endDate, float interest) :
    account(initialDeposit, holders, managerID)
{

  this->beginDate = date(beginDate);
  this->endDate = date(endDate);
  this->interest = interest;
}

Term::Term(money initialDeposit, vector<int> &holders, int managerID,
    string beginDate, string endDate, float interest, unsigned int ID) :
    account(initialDeposit, holders, managerID, ID)
{

  this->beginDate = date(beginDate);
  this->endDate = date(endDate);
  this->interest = interest;
}

// ******************************************************************************************
//                                         Class Order: Public Account
// ******************************************************************************************
//! Constructor
/*!
 \param money the initial deposit
 \param &holders the vector that have the ids of the holders
 \param managerID the id of the account manager
 */
Order::Order(money initialDeposit, vector<int> &holders, int managerID) :
    account(initialDeposit, holders, managerID)
{
  // Nothing to do
}
;

Order::Order(money initialDeposit, vector<int> &holders, int managerID,
    unsigned int ID) :
    account(initialDeposit, holders, managerID, ID)
{
  // Nothing to do
}
;

//! Withdraw money from the account
bool Order::withdraw(money ammount)
{
  if (balance < ammount)
    return false;
  this->setBalance(balance - ammount);
  return true;
}
