#include "operation.h"
// Consctructor
transfer::transfer(account* account1, account* account2, double val) :
		operation(account1, val) {
	if (account2->getBalance() < val)
		throw(notenoughmoney(val, account2->getBalance()));
	this->account2 = account2;
	account2->setBalance(account2->getBalance() - val);
	account_oper->setBalance(account_oper->getBalance() + val);
}
// Overloaded Constructor
transfer::transfer(account* account1, account* account2, double val,
		string type) :
		operation(account1, val) {
	this->account2 = account2;
}
// Constructor
withdraw::withdraw(account* account1, double val) :
		operation(account1, val) {
	if (account1->getBalance() < val)
		throw(notenoughmoney(val, account1->getBalance()));
	account_oper->setBalance(account_oper->getBalance() - val);
}
// Overloaded Constructor
withdraw::withdraw(account* account1, double val, string type) :
		operation(account1, val) {
}
// Constructor
deposit::deposit(account* account1, double val) :
		operation(account1, val) {
	account_oper->setBalance(account_oper->getBalance() + val);
}
// Overloaded Constructor
deposit::deposit(account* account1, double val, string type) :
		operation(account1, val) {
}
