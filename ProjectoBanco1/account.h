#ifndef ACCOUNT_H_
#define ACCOUNT_H_
// Include Libraries
#include "types.h"
#include "nib.h"
#include <vector>
//!  Class that holds the information of a bank account
/*!  An account have an ID, the NIB Identification, a balance, the manager ID, the holders,the agency and bank number
 */
class account
{
protected:
  //! unique ID number
  unsigned int ID;
  //! The nib number of the account
  nib NIB;
  //! The balance of the account
  money balance;
  //! The ids of the account holders
  //! The manager ID
  unsigned int managerID;
  //! The bank number
  static long bank;
  //! The agency number
  static long agency;
public:
  vector<int> holders;
  // ******************************** Constructors
  //! empty constructor
  account()
  {
  }
  virtual ~account()
  {
  }
  //! constructor that receives the data
  account(money initialDeposit, vector<int> &holders, unsigned int managerID);
  account(money initialDeposit, vector<int> &holders, unsigned int managerID,
      unsigned int ID);
  //! Total accounts
  static long nextAccountID;
  // ******************************** Get Methods
  //! get the NIB from this account
  nib getNIB() const
  {
    return NIB;
  }
  //! get this account's balance
  money getBalance() const
  {
    return balance;
  }
  //! return the holders vector
  vector<int> getHolders();
  //! get the account id
  unsigned int getID()
  {
    return ID;
  }
  //! returns the number of holders
  int getNumHolders();
  //! get the manager id
  unsigned int getManagerID();
  // ******************************** Set Methods
  //! set the account balance
  void setBalance(money new_balance); /*Not defined here to be able to declare as pure virtual class*/
  //! set the accounts NIB
  void setNIB(nib n);
  //! adds a holder to the holders vector
  void addHolder(int a);
  //! add an ammount of money to an account
  void deposit(money ammount);
  //! remover holder
  void reHolder(int a);
  //! set the bank number
  static void setBank(long number);
  //! set Manager ID
  void setManagerID(unsigned int id)
  {
    managerID = id;
  }
  //! set the agency number
  static void setAgency(long number);
  // WARNING: THIS IS NECESSARY TO CALL FROM THE BASE POINTER
  //! get the begin date for this account
  virtual string getBeginDate()=0;
  //! get the end date for this account
  virtual string getEndDate()=0;
  //! get the interest
  virtual float getInterest()=0;
  //! get the type of account
  virtual string getType()=0;
  bool operator==(unsigned int id)
  {
    return this->ID == id;
  }
  static int getBank()
  {
	  return bank;
  }
  static int getAgency()
  {
	  return agency;
  }
};

//!  Sub-Class that holds the information of a Term account
/*!  A term account is an account that is created by a contract, having an interest that makes the inititalDeposit grow
 */
class Term: public account
{
private:
  float interest;
  date beginDate;
  date endDate;
  money initialDeposit;
public:
  // ******************************** Constructors
  //! empty constructor
  Term()
  {
  }
  //! constructor that receives the data
  Term(money initialDeposit, vector<int> &holders, int managerID,
      string beginDate, string endDate, float interest);
  Term(money initialDeposit, vector<int> &holders, int managerID,
      string beginDate, string endDate, float interest, unsigned int ID);
  // ******************************** Get Methods
  //! get the begin date for this account
  string getBeginDate()
  {
    return beginDate.print();
  }
  //! get the end date for this account
  string getEndDate()
  {
    return endDate.print();
  }
  //! get the initial deposit for this account
  money getInitialDeposit() const
  {
    return initialDeposit;
  }
  //! get the interest
  float getInterest()
  {
    return interest;
  }
  //! get the type of account
  string getType()
  {
    return "term";
  }
  // ******************************** Set Methods
  //! set the interest rate for this account
  void setInterest(float interest)
  {
    this->interest = interest;
  }
  //! set the begin date for this account
  void setBeginDate(date beginDate)
  {
    this->beginDate = beginDate;
  }
  //! set the end date for this account
  void setEndDate(date endDate)
  {
    this->endDate = endDate;
  }
  //! set the initial deposit for this account
  void setinitialDeposit(money ini)
  {
    initialDeposit = ini;
  }
};

//!  Sub-Class that holds the information of an Order account
/*!  An order account is created to do payments and withdraws
 */
class Order: public account
{
public:
  // ******************************** Constructors
  //! empty constructor
  Order();
  //! constructor that receives the data
  Order(money initialDeposit, vector<int> &holders, int managerID);
  Order(money initialDeposit, vector<int> &holders, int managerID,
      unsigned int ID);
  //! Withdraw money
  bool withdraw(money ammount);
  //! get the type of account
  string getType()
  {
    return "order";
  }
  //! This functions are only because of the base pointer vector
  float getInterest()
  {
    return 0;
  }
  //! Get the begin date
  string getBeginDate()
  {
    return 0;
  }
  //! Get the end date
  string getEndDate()
  {
    return 0;
  }
};
#endif
