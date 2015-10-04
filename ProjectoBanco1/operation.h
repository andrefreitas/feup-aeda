#ifndef OPERATION_H_
#define OPERATION_H_
#include "account.h"
//!  Super-Class operation
/*! This class defines an operation/movement in the bank
 */
class operation {
protected:
	//! The pointer to the account that is holding this operation
	account* account_oper;
	//! The value that is beeing moved in the operation
	double value;
public:
	//! Empty Constructor
	operation() {
	}
	//! Destructor
	virtual ~operation() {
	}
	// ! Constructor
	/*!
	 \param *account1 the pointer of the account
	 \param value the value of the operation
	 */
	operation(account* account1, double value) {
		account_oper = account1;
		this->value = value;
	}
	//! Get the pointer of the account
	virtual account* getaccount1() {
		return account_oper;
	}
	//! Set the account
	virtual void setaccount1(account* account1) {
		this->account_oper = account1;
	}
	//! Get the type of operation
	virtual string getType() const {
		return "";
	}
	//! Get the value of operation
	virtual double getvalue() {
		return value;
	}
	//! Set the value of the operation
	virtual void setvalue(double value) {
		this->value = value;
	}
	// Get the Account2 (later implemented in a sub-class)
	virtual account* getaccount2() {
		return account_oper; //never called
	}
};
//!  Exception Treatment
/*! This class is implemented to handle exceptions when an account don't have enough money to do an operation
 */
class notenoughmoney {
	//! The value of the operation
	double money;
	//! The balance of the account
	double balance;
public:
	//! Constructor
	/*!
	 \param money the value of the operation
	 \param balance the balance of the account
	 */
	notenoughmoney(double money, double balance) {
		this->money = money;
		this->balance = balance;
	}
	//! Get the ammount of money of the operation
	double getmoney() {
		return money;
	}
	//! Get the balance of the accoun
	double getbalance() {
		return balance;
	}

};
//!  Sub-Class Transfer
/*! This class defines a transfer between 2 accounts
 */
class transfer: public operation {
	//! The second account
	account* account2;
public:
	//! Empty Constructor
	transfer() {
	}
	//! Constructor
	/*!
	 \param account1 the first account
	 \param account2 the second account
	 \param val the value ammount of operation
	 */
	transfer(account* account1, account* account2, double val);
	//! Constructor Overloading - useful in loading from files
	/*!
	 \param account1 the first account
	 \param account2 the second account
	 \param val the value ammount of operation
	 \param the type of operation
	 */
	transfer(account* account1, account* account2, double val, string type);
	//! Get the pointer of the second account
	account* getaccount2() {
		return account2;
	}
	//! Set the second account pointer
	void setaccount2(account* accounts2) {
		this->account2 = accounts2;
	}
	//! Returns transfer
	string getType() const {
		return "transfer";
	}
};
//!  Sub-Class withdraw
/*! This class defines an withdraw action
 */
class withdraw: public operation {
public:
	//! Empty constructor
	withdraw() {
	}
	//! Constructor
	/*!
	 \param account1 the account that holds the operations
	 \param val the value of operation
	 */
	withdraw(account* account1, double val);
	//! Overloaded Constructor
	/*!
	 \param account1 the account that holds the operations
	 \param val the value of operation
	 \param type the type of account
	 */
	withdraw(account* account1, double val, string type);
	//! Returns the type of account, in this case "withdraw"
	string getType() const {
		return "withdraw";
	}

};
//!  Sub-Class deposit
/*! This class defines a deposit action
 */
class deposit: public operation {
public:
	//! Empty constructor
	deposit() {
	}
	//! Constructor
	/*!
	 \param account1 the account that holds the operations
	 \param val the value of operation
	 */
	deposit(account* account1, double val);
	//! Overloaded constructor
	/*!
	 \param account1 the account that holds the operations
	 \param val the value of operation
	 \param type the type of account
	 */
	deposit(account* account1, double val, string type);
	string getType() const {
		return "deposit";
	}

};
#endif /* OPERATION_H_ */
