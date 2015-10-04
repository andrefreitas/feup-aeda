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
	idDoesntExist(unsigned int id) {
		this->id = id;
	}
	int getID() {
		return id;
	}
};

//!  Class Bank Institution
/*! This class defines a bank institution with their customers, employees, accounts and movements
 */

class Bank {

	//! Bank's 4 digit Number
	long bankNumber;
	//! Agency's 4 digit Number (Note: A Bank can have a lot of agencies, but for this implementation we will only work with one)
	long agencyNumber;
	//! Name of the bank
	string name;
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
	//! Displays all employees from the given vector on the screen
	/*!
	 \param vec vector of employees to be written on the screen
	 \return returns false if there are no employees to be listed, true upon success
	 */
	bool showEmployee(vector<employee*> vec);
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
	//! Vector of customers
	vector<customer*> customers;
	//! Vector of employees
	vector<employee*> employees;
	//! Vector of accounts
	vector<account*> accounts;
	//! Vector of operations

	vector<operation*> operations;
public:

	//! Empty constructor
	Bank();
	//! Data constructor
	/*!
	 \param name name of the bank
	 \param bankNumber bank's 4 digit Number
	 \param agencyNumber agency's 4 digit Number (Note: A Bank can have a lot of agencies, but for this implementation we will only work with one)
	 */
	Bank(string name, long bankNumber, long agencyNumber);
	//! Destructor
	~Bank();
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
	//! Add operation to the respective vector
	/*!
	 \param oper the operation to be added
	 */
	void addOperation(operation* oper);
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
	 \param id the id of the employee
	 \return returns a vector with all the accounts which have the employee with the given id as their manager
	 */
	vector<account*> getAccountsByEmployeeID(unsigned int ID);
	//! Checks if the Customer ID exists
	/*!
	 \param id the id of the customer
	 \return returns true if the customer with the given id exists, false otherwise
	 */
	bool existCustomerID(long id);
	//! Checks if the Employee ID exists
	/*!
	 \param id the id of the employee
	 \return returns true if the employee with the given id exists, false otherwise
	 */
	bool existEmployeeID(long id);
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
	//! Search the customers vector by name
	/*!
	 \param name the name of the customer to be found
	 \return returns a vector with all the customers whose name is equal or starts with the given name
	 */
	vector<customer*> SearchCustomersbyname(string name);
	// *********************************************** Interface CRUR **************************************************
	//! Asks the user to insert the values for a new account
	void createAccount();
	//! Asks the user to insert the values for a new customer
	void createCustomer();
	//! Asks the user to insert the values for a new employee
	void createEmployee();
	//! Asks the user to insert the values for a new operation
	void createOperation();
	//! Displays all the accounts on the screen (calls showAccount(accounts))
	void readAccounts();
	//! Displays all the customers on the screen (calls showCustomer(customers))
	void readCustomers();
	//! Displays all the employees on the screen (calls showEmployee(employees))
	void readEmployees();
	//! Displays all the operations on the screen (calls showOperation(operations))
	void readOperations();
	//! Asks the user for values to edit an employee
	void updateEmployee();
	//! Asks the user for values to edit a customer
	void updateCustomer();
	//! Asks the user for values to edit an account
	void updateAccount();
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
	//! Lists all the customers and asks the user to select one
	/*!
	 \param title the text to be displayed prior to asking the information
	 \return returns the id selected by the user
	 */
	int readIDCustomer(string title);
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
	//! Asks the user to select a customer for deletion
	void removeCustomer();
	//! Asks the user to select an account for deletion
	void removeAccount();

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
