#ifndef BANK_H_
#define BANK_H_

// Include of libraries
#include "person.h"
#include "account.h"
#include "operation.h"
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <sstream>
#include <hash_set>
#include "atm.h"
#include <queue>
#include "types.h"
#include "BST.h"
#include "agencies.h"
using namespace __gnu_cxx;
using namespace std;

//Defines functions that are system specific
#ifdef WIN32 //if compiled in windows
#define clearscreen() system("cls") //clears the screen
#define clearbuffer() fflush(stdin) //clears the keyboard buffer
#else
#define clearscreen() if(system("clear")) //clears the screen (used if to avoid warnings regarding ignoring return value on Linux)
#include <stdio_ext.h> //needed by fpurge
#define clearbuffer()  __fpurge(stdin) //clears the keyboard buffer
#endif
//! Exception treatment
/*! This is an exception class which is thrown when an item with a given id doesn't exist
 */
class idDoesntExist {
	unsigned int id;
public:
	//! Constructor
	idDoesntExist(unsigned int id) {
		this->id = id;
	}
	//! Returns the ID
	int getID() {
		return id;
	}
};
//! Hash set of the inactive customers
struct customerHash {
	//!Dispersion function
	int operator()(customer *a) const {
		return a->getID();

	}
	//!Equality function
	bool operator()(customer *a, customer *b) const {
		return (a->getID() == b->getID());

	}
};
typedef hash_set<customer*, customerHash, customerHash> HashCustomer;

//!  Class Bank Institution
/*! This class defines a bank institution with their customers, employees, accounts and movements
 */

class Bank {

	//! Bank's 4 digit Number
	long bankNumber;
	//! Agency's 4 digit Number (Note: A Bank can have a lot of agencies, but for this implementation we will only work with one)
	long agencyNumber;
	//! Localization of the Bank
	Localization local;
	//! Name of the bank
	string name;
	//!Hash table with inactive customer
	HashCustomer inactives_customers;
	//! Priority queue ordered by the nearest active banks
	priority_queue<ATM> atms;
	//! Read multiple values in a file and place them in the vector vars
	/*!
	 \param total the number of values to be read
	 \param vars vector where the values will be saved
	 \param file the file to be read
	 */
	void powerfullRead(int total, vector<string> &vars, ifstream &file);
	//! Load the bank's files
	/*!
	 \param data string that contains the type of data to be read (the possible values are bank, operations, accounts, employees and customers)
	 */
	void loadFile(string data);
	//! Save the bank's files
	/*!
	 \param data string that contains the type of data to be saved (the possible values are bank, operations, accounts, employees and customers)
	 */
	void saveFile(string data);
	//! Displays all customers from the given vector on the screen
	/*!
	 \param vec vector of customers to be written on the screen
	 \return returns false if there are no customers to be listed, true upon success
	 */
	bool showCustomer(vector<customer*> vec);
	//! Displays the given customer on the screen
	/*!
	 \param c customer to be written on the screen
	 \return returns true upon success
	 */
	bool showCustomer(customer* c);
	//! Displays the given inactive customer on the screen
	/*!
	 \param c customer to be written on the screen
	 \return returns true upon success
	 */
	bool showInactiveCustomer(customer *c);

	//! Displays all employees from the given vector on the screen
	/*!
	 \param vec vector of employees to be written on the screen
	 \return returns false if there are no employees to be listed, true upon success
	 */
	bool showEmployee(vector<employee*> vec);
	//! Displays all inactive customers from the given hash table on the screen
	/*!
	 \param hHashCustomer to be written on the screen
	 \return returns false if there are no inactive customers to be listed, true upon success
	 */
	bool showInactiveCustomer(HashCustomer hash);
	//! Displays the given employee on the screen
	/*!
	 \param e employee to be written on the screen
	 \return returns true upon success
	 */
	bool showEmployee(employee* e);
	//! Displays all accounts from the given vector on the screen
	/*!
	 \param vec vector of accounts to be written on the screen
	 \return returns false if there are no accounts to be listed, true upon success
	 */
	bool showAccount(vector<account*> vec);
	//! Displays the given account on the screen
	/*!
	 \param a account to be written on the screen
	 \return returns true upon success
	 */
	bool showAccount(account* a);
	//! Displays all operations from the given vector on the screen
	/*!
	 \param vec vector of operations to be written on the screen
	 \return returns false if there are no operations to be listed, true upon success
	 */
	bool showOperation(vector<operation*> vec);
	//! Displays all agencies from the given BST on the screen
	/*!
	 \param bst bst of agencies to be written on the screen
	 \return returns false if there are no agencies to be listed, true upon success
	 */
	bool showAgencies(BST<agency> bst);
	//! Displays the given agency on the screen
	/*!
	 \param tempAgency agency to be written on the screen
	 \return returns true upon success
	 */
	bool showAgency(agency tempAgency);
	//! Vector of customers
	vector<customer*> customers;
	//! Vector of employees
	vector<employee*> employees;
	//! Vector of accounts
	vector<account*> accounts;
	//! Vector of operations
	vector<operation*> operations;
	//! The headquarters agency
	agency headquarters;

public:

	//! Empty constructor
	Bank();
	//! Data constructor
	/*!
	 \param name name of the bank
	 \param bankNumber bank's 4 digit Number
	 \param agencyNumber agency's 4 digit Number (Note: A Bank can have a lot of agencies, but for this implementation we will only work with one)
	 \param l the localization of the bank (latitude, longitude)
	 */
	Bank(string name, long bankNumber, long agencyNumber, Localization l);
	//! Destructor
	~Bank();
	//! BST of agencies
	BST<agency> agencies;
	//! Get the name of the Bank
	/*!
	 \return returns the name of the bank
	 */
	string getName() {
		return name;
	}
	//! Get the number of the Bank
	/*!
	 \return returns the bank's number
	 */
	long getBankNumber() {
		return bankNumber;
	}
	//! Get the number of the Agency
	/*!
	 \return returns the agency's number
	 */
	long getAgencyNumber() {
		return agencyNumber;
	}
	//! Get accountID by NIB
	/*!
	 \param NIB the account's NIB
	 \return returns the ID of the account with the given NIB
	 */
	int getaccountIDbyNIB(string NIB);
	//! Set the name of the Bank
	/*!
	 \param name the new name of the bank
	 */
	void setName(string name) {
		this->name = name;
	}
	//! Set the number of the Bank
	/*!
	 \param bankNumber the new bank number
	 */
	void setBankNumber(long bankNumber) {
		this->bankNumber = bankNumber;
	}
	//! Set the number of the Agency
	/*!
	 \param agencyNumber the new agency number
	 */
	void setAgencyNumber(long agencyNumber) {
		this->agencyNumber = agencyNumber;
	}
	//! Add customer to vector of customer
	/*!
	 \param cust the customer to be added
	 */
	void addCustomer(customer* cust);
	//! Add employee to the respective vector
	/*!
	 \param empl the employee to be added
	 */
	void addEmployee(employee* empl);
	//! Add account to the respective vector
	/*!
	 \param acco the account to be added
	 */
	void addAccount(account* acco);
	//! Add inative customer to the Hash table
	/*!
	 \param customer the customer to be added
	 */
	void addInative_customer(customer* customer);
	//! Add operation to the respective vector
	/*!
	 \param oper the operation to be added
	 */
	void addOperation(operation* oper);
	//! Add agency to the bst
		/*!
		 \param agen the agency to be added
		 */
	void addAgency(agency agen);
	//! get operations in accounts
	/*!
	 \param id the id of the account
	 \return returns a vector with all the operations of the account with the given id
	 */
	vector<operation*> GetOperationByAccountID(unsigned int id);
	//! Get customer by ID
	/*!
	 \param id the id of the customer
	 \return returns the customer with the given id
	 */
	customer* getCustomerbyID(long id);
	//! Get Inactive Customer by ID
	/*!
	 \param id the id of the inactive ustomer
	 \return returns the customer with the given id
	 */
	customer* getInactiveCustomerbyID(long id);
	//! Get Employee by ID
	/*!
	 \param id the id of the employee
	 \return returns the employee with the given id
	 */
	employee* getEmployeebyID(long id);
	//! Get Accounts By customer ID
	/*!
	 \param id the id of the customer
	 \return returns a vector with all the accounts that have the customer with the given id as a holder
	 */
	vector<account*> getAccountsByCustomerID(long id);
	//! Get Account By employeeID
	/*!
	 \param ID the id of the employee
	 \return returns a vector with all the accounts which have the employee with the given id as their manager
	 */
	vector<account*> getAccountsByEmployeeID(unsigned int ID);
	//! Checks if the Customer ID exists
	/*!
	 \param id the id of the customer
	 \return returns true if the customer with the given id exists, false otherwise
	 */
	bool existCustomerID(long id);
	//! Checks if the Inactive Customer ID exists
	/*!
	 \param id the id of the customer
	 \return returns true if the customer with the given id exists, false otherwise
	 */
	bool existInactiveCustomerID(long id);

	//! Checks if the Employee ID exists
	/*!
	 \param id the id of the employee
	 \return returns true if the employee with the given id exists, false otherwise
	 */
	bool existEmployeeID(long id);
	//! Check if the Agency exists
		/*!
		 \param id the id of the agency
		 \return returns true if the account with the given id exists, false otherwise
		 */
	bool existAgency(long id);
	//! Check if the AccountID exists
	/*!
	 \param ID the id of the account
	 \return returns true if the account with the given id exists, false otherwise
	 */
	bool accountExists(unsigned int ID);
	//! Search employee by NIF
	/*!
	 \param NIF the NIF of the employee
	 \return returns the ID of the employee with the given NIF
	 */
	long searchEmployeebyNIF(nif NIF);
	//! Search customer by NIF
	/*!
	 \param NIF the NIF of the customer
	 \return returns the ID of the customer with the given NIF
	 */
	long searchCustomerbyNIF(nif NIF);
	//! Search Inactive customer by NIF
	/*!
	 \param NIF the NIF of the inactive customer
	 \return returns the ID of the inactive customer with the given NIF
	 */
	long searchInactiveCustomerbyNIF(nif NIF);
	//! Get Account By ID
	/*!
	 \param ID the id of the account
	 \return returns a pointer to the account with the given id
	 */
	account* getAccountByID(unsigned int ID);
	//! Search the employees vector by name
	/*!
	 \param name the name of the employee to be found
	 \return returns a vector with all the employees whose name is equal or starts with the given name
	 */
	vector<employee*> SearchEmployeesbyname(string name);
	//! Returns the total number of customers in a given agency
	/*!
	 \param num the number of the agency in question
	 \return returns the number of customers in that agency
	 */
	long getNumCustomerInAgency(long num);
	//! Search the customers vector by name
	/*!
	 \param name the name of the customer to be found
	 \return returns a vector with all the customers whose name is equal or starts with the given name
	 */
	vector<customer*> SearchCustomersbyname(string name);
	//! Search the inactive customers vector by name
	/*!
	 \param name the name of the inactive customer to be found
	 \return returns a hash table with all the inactive customers whose name is equal or starts with the given name
	 */
	HashCustomer SearchInactiveCustomersbyname(string name);
	// *********************************************** Interface CRUR **************************************************
	//! Asks the user to insert the values for a new account
	void createAccount();
	//! Asks the user to insert the values for a new customer
	void createCustomer();
	//! Asks the user to insert the values for a new employee
	void createEmployee();
	//! Asks the user to insert the values for a new operation
	void createOperation();
	//! Asks the user to inser the value for a new atm
	void createAtm();
	//! Asks the user to insert the values for a new inative customer
	void createInative_customer();
	//! Asks the user to insert the values for a new agency
	void createAgency();
	//! Displays all the accounts on the screen (calls showAccount(accounts))
	void readAccounts();
	//! Displays all the customers on the screen (calls showCustomer(customers))
	void readCustomers();
	//! Displays all the employees on the screen (calls showEmployee(employees))
	void readEmployees();
	//! Displays all the operations on the screen (calls showOperation(operations))
	void readOperations();
	//! Display all the agencies
	void readAgencies();
	//! Display the atms
	void readAtms();
	//! Displays all the inactive customers on the screen (calls showInactiveCustomers(inactives_customers))
	void readInactiveCustomers();
	//! Asks the user for values to edit an employee
	void updateEmployee();
	//! Asks the user for values to edit a customer
	void updateCustomer();
	//! Asks the user for values to edit a inactive cursomer
	void updateInactiveCustomer();
	//! Asks the user for values to edit an account
	void updateAccount();
	//!  Asks the user for values to edit an agency
	void updateAgency();
	//!  Asks the user for values to edit an atm
	void updateAtm();
	//! Ask the user for the customer to active
	void activeCustomer();
	//! Lists all the employees and asks the user to select one
	/*!
	 \param title the text to be displayed prior to asking the information
	 \return returns the id selected by the user
	 */
	int readIDEmployee(string title);
	//! Lists all the accounts and asks the user to select one
	/*!
	 \param title the text to be displayed prior to asking the information
	 \return returns the id selected by the user
	 */
	int readIDAccount(string title);
	//!Returns an agency by reference with the number given as a parameter
	/*!
	  \param num the number of the agency in question
	  \return returns a reference to the wanted agency
	*/
	agency* getAgencyByNumber(long num)
	{
		BSTItrIn<agency> it(this->agencies);
		while(!it.isAtEnd())
		{
			if(it.retrieve().getNumber()==num)
				return &it.retrieve();
			it.advance();
		}
		return &it.retrieve();
	}
	//! Lists all the customers and asks the user to select one
	/*!
	 \param title the text to be displayed prior to asking the information
	 \return returns the id selected by the user
	 */
	int readIDInactiveCustomer(string title);
	//! Lists all the inactive customers and asks the user to select one
	/*!
	 \param title the text to be displayed prior to asking the information
	 \return returns the id selected by the user
	 */
	int readIDCustomer(string title);


	//!List all agencys and asks the user to select one
	/*!
	  \param title the text to be display prior to asking the information
	  \return the id selected by the user
	 */
	int readIDAgency(string title);
	//!Asks the user for an agency ID and sets the variable passed by reference as it
	/*!
	  \param tempAgency the agency that's going to be selected by the user
	*/
	void readAgencyByNumber(agency &tempAgency);
	//! Asks the user to select an account and lists that account's operations
	void viewOperation();
	//! Gets the position of the vector where the element with the given id is located
	/*!
	 \param ID the id to be found
	 \param searchVector the vector to be searched
	 \return returns the position of the vector where the element with the given id is located
	 */
	template<class vec>
	int getPos(unsigned int ID, vec searchVector) {
		for (unsigned int i = 0; i < searchVector.size(); i++)
			if (*searchVector[i] == ID)
				return i;
		return -1;
	}
	//! Deletes the vector element with the given id
	/*!
	 \param ID the id of the element to be deleted
	 \param delVector the vector to be deleted
	 */
	template<class vec>
	void deleteByID(unsigned int ID, vec &delVector) {
		int pos = getPos(ID, delVector);
		if (pos == -1)
			throw idDoesntExist(ID);
		delVector.erase(delVector.begin() + pos);
	}
	//! Changes one member from the vector
	/*!
	 \param ID the id of the element to be deleted
	 \param upVector the vector to be edited
	 \param upValue the changed element to be added to the vector
	 */
	template<class val, class inherited>
	void updateVector(unsigned int ID, vector<val*> &upVector,
			inherited* upValue) {
		int pos = getPos(ID, upVector);
		deleteByID(ID, upVector);
		upVector.insert(upVector.begin() + pos, upValue);
	}
	//! Asks the user to select an employee for deletion
	void removeEmployee();
	//! Asks the  user to select an inactive customer for deletion
	void removeInactiveCustomer();
	//! Asks the user to select a customer for deletion
	void removeCustomer();
	//! Asks the user to select an account for deletion
	void removeAccount();
	//!  Asks the user to select an agency for deletion
	void removeAgency();
	//! Asks the user to select an atm for deletion
	void removeAtm();
	//! Set the headquarters agency
	void setHeadquarters(agency headquarters) {
		this->headquarters = headquarters;
	}
	//! Find the nearest atm with money
	void nearestAtm();
	//! Deposit in an ATM
	void depositAtm();
	//! Withdraw from an ATM
	void withdrawAtm();
	//!List the accounts the a agency
	void listAccountsByAgency();
	//! Gets the total number of agencies
	/*!
	 \return returns the total number of agencies
	 */
	int getNumAgencies()
	{
		BSTItrIn<agency> it(this->agencies);
		int i=0;
		while(!it.isAtEnd())
		{
			i++;
			it.advance();
		}
		return i;
	};
	//! Checks if the ATM ID exists
	/*!
	 \param id the id of the ATM
	 \return returns true if the ATM with the given id exists, false otherwise
	*/
	bool existATMID(long id);
};

//! Verifies if given input string is numeric
bool isnumeric(string str);
//! Reads an user input and verifies if it is an integer
/*!
 \param text the text to be displayed prior to the input
 \return returns the read integer
 */
int readint(string text);
//! Reads an user input and verifies if it is a float
/*!
 \param text the text to be displayed prior to the input
 \return returns the read float
 */
float readfloat(string text);


#endif
