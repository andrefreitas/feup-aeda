#include "bank.h"
#include <ctime>

agency invalidAgency("Invalid", "Invalid", "Invalid", 0); //used for BST

//! Converts every element of a string to uppercase
string strupper(string str) {
	int cmp = str.size();
	int i = 0;
	for (i = 0; i < cmp; i++) {
		str[i] = toupper(str[i]); //converts the element in position 'i' to uppercase
	}
	return str;
}

//! Searches a string for a substring
/*!
 \param str the original string
 \param x the substring to be found
 \return true if found, false otherwise
 */
bool searchStr(string str, string x) {
	str = strupper(str);
	x = strupper(x);
	if (str == x)
		return true;
	else {
		int cm_str = str.size();
		int cm_x = x.size();
		int i = 0;
		if (cm_x > cm_str)
			return false;
		for (i = 0; i < cm_str - cm_x + 1; i++) {
			if (str.substr(i, cm_x) == x)
				return true;
		}
		return false;
	}
}
Bank::Bank(string name, long bankNumber, long agencyNumber, Localization l) :
														agencies(invalidAgency) {
	this->name = name;
	this->bankNumber = bankNumber;
	this->agencyNumber = agencyNumber;

	account::setAgency(agencyNumber);
	account::setBank(bankNumber);
	local = l;
	ATM::setTarget(local);
	loadFile("accounts");
	loadFile("customers");
	loadFile("employees");
	loadFile("operations");
	loadFile("agencies");
	loadFile("atms");
}

Bank::Bank() :
														agencies(invalidAgency) {
	loadFile("bank");
	loadFile("accounts");
	loadFile("customers");
	loadFile("employees");
	loadFile("operations");
	loadFile("agencies");
	loadFile("atms");
	struct tm *local;
	time_t ti;
	ti = time(NULL);
	local = localtime(&ti);
	long ndays = (local->tm_year + 1900) * 365 + (local->tm_mon + 1) * 30
			+ local->tm_mday;
	for (unsigned int i = 0; i < this->customers.size(); i++) {
		if (customers[i]->isInactive())
			this->inactives_customers.insert(customers[i]);
		else {
			long ndayscustomer = customers[i]->getLastOperation().day
					+ customers[i]->getLastOperation().mon * 30
					+ customers[i]->getLastOperation().year * 365;
			if (ndays - ndayscustomer > 365) {
				this->inactives_customers.insert(customers[i]);
			}

		}
	}
}

Bank::~Bank() {
	saveFile("accounts");
	saveFile("customers");
	saveFile("employees");
	saveFile("operations");
	saveFile("agencies");
	saveFile("atms");
}
bool Bank::existATMID(long id)
{
	priority_queue<ATM> a=this->atms;
	while(!a.empty())
	{
		ATM at=a.top();
		if(at.getId()==id)
			return true;
		a.pop();
	}
	return false;

}
bool Bank::existCustomerID(long id) {
	for (unsigned int i = 0; i < customers.size(); i++) {
		if (customers[i]->getID() == id)
			return true;
	}
	return false;
}
bool Bank::existInactiveCustomerID(long id) {
	HashCustomer::iterator it;
	for (it = this->inactives_customers.begin();
			it != this->inactives_customers.end(); it++) {
		customer *a = (*it);
		if (a->getID() == id)
			return true;
	}
	return false;

}
void Bank::loadFile(string data) {
	if (data == "customers") {
		ifstream customersFile;
		// (1) Read Customers File
		customersFile.open("customers.txt");
		if (customersFile.is_open()) {
			string line;
			getline(customersFile, line);
			customers[0]->nextCustomerID = atol(line.c_str());
			getline(customersFile, line);
			unsigned int totalCustomers = atoi(line.c_str());
			for (int unsigned i = 0; i < totalCustomers; i++) {
				string typeRead, nothing;
				customersFile.ignore(256, ' ');
				getline(customersFile, typeRead);
				vector<string> vars;
				powerfullRead(11, vars, customersFile);
				if (typeRead == "particular") {
					particular *p;
					p = new particular(vars[1], vars[2], vars[3], vars[4],
							atol(vars[5].c_str()), atol(vars[6].c_str()),
							atol(vars[10].c_str()), vars[7],
							atoi(vars[8].c_str()), atoi(vars[0].c_str()));

					p->setAgencyNumb(atol(vars[9].c_str()));
					customers.push_back(p);
				} else {
					company *c;
					c = new company(vars[1], vars[2], vars[3], vars[4],
							atol(vars[5].c_str()), atol(vars[6].c_str()),
							atol(vars[10].c_str()), vars[7],
							atoi(vars[8].c_str()), atoi(vars[0].c_str()));
					c->setAgencyNumb(atol(vars[9].c_str()));
					customers.push_back(c);

				}
				getline(customersFile, nothing);
			}
			customersFile.close();
		}
		return;
	}
	if (data == "accounts") {
		ifstream accountsFile;
		// (1) Read Accounts File
		accountsFile.open("accounts.txt");
		if (accountsFile.is_open()) {
			string line;
			getline(accountsFile, line);
			accounts[0]->nextAccountID = atol(line.c_str());
			getline(accountsFile, line);
			unsigned int totalAccounts = atoi(line.c_str());
			for (int unsigned i = 0; i < totalAccounts; i++) {
				string typeRead, nothing, numHolders;
				accountsFile.ignore(256, ' ');
				getline(accountsFile, typeRead);
				vector<string> vars;
				vector<string> holders;
				vector<int> holdersVector;
				if (typeRead == "term") {
					accountsFile.ignore(256, ' ');
					getline(accountsFile, numHolders);
					powerfullRead(atoi(numHolders.c_str()), holders,
							accountsFile); //Read all holders
					for (int i = 0; i < atoi(numHolders.c_str()); i++)
						holdersVector.push_back(atoi(holders[i].c_str()));
					powerfullRead(6, vars, accountsFile);
					Term *t;
					money initialDeposit = atof(vars[1].c_str());
					t = new Term(initialDeposit, holdersVector,
							atoi(vars[2].c_str()), vars[3], vars[4],
							atof(vars[5].c_str()), atoi(vars[0].c_str()));
					accounts.push_back(t);
				} else {
					accountsFile.ignore(256, ' ');
					getline(accountsFile, numHolders);
					powerfullRead(atoi(numHolders.c_str()), holders,
							accountsFile); //Read all holders
					for (int i = 0; i < atoi(numHolders.c_str()); i++)
						holdersVector.push_back(atoi(holders[i].c_str()));
					powerfullRead(3, vars, accountsFile);
					Order *o;
					money initialDeposit = atof(vars[1].c_str());
					o = new Order(initialDeposit, holdersVector,
							atoi(vars[2].c_str()), atoi(vars[0].c_str()));
					accounts.push_back(o);

				}
				getline(accountsFile, nothing);
			}
			accountsFile.close();
		}
		return;
	}
	if (data == "employees") {
		ifstream employeesFile;
		// (1) Read Employees File
		employeesFile.open("employees.txt");
		if (employeesFile.is_open()) {
			string line;
			getline(employeesFile, line);
			employees[0]->nextEmployeeID = atol(line.c_str());
			getline(employeesFile, line);
			unsigned int totalEmployees = atoi(line.c_str());
			for (int unsigned i = 0; i < totalEmployees; i++) {
				string nothing;
				vector<string> vars;
				powerfullRead(11, vars, employeesFile);
				employee *e;
				e = new employee(vars[1], vars[2], vars[3], vars[4],
						atol(vars[5].c_str()), atol(vars[6].c_str()),
						atol(vars[7].c_str()), atol(vars[8].c_str()), vars[9],
						vars[10], atoi(vars[0].c_str()));
				employees.push_back(e);
				getline(employeesFile, nothing);
			}
			employeesFile.close();
		}
		return;
	}
	if (data == "bank") {
		ifstream bankFile;
		bankFile.open("bank.txt");
		if (bankFile.is_open()) {
			vector<string> vars;
			powerfullRead(5, vars, bankFile);
			setName(vars[0]);
			setBankNumber(atol(vars[1].c_str()));
			setAgencyNumber(atol(vars[2].c_str()));
			local = Localization(atof(vars[3].c_str()), atof(vars[4].c_str()));
			ATM::setTarget(local);
			account::setBank(bankNumber);
			account::setAgency(agencyNumber);

			bankFile.close();
		} else {
			clearscreen();
			stringstream text;
			text.str("");
			text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "Create Bank" << endl;
			text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
			string tempString, location, postalCode, Address;
			long tempLong, contact;
			double lat, lon;
			do{
				clearscreen();
				cout<<text.str();
				cout << "Bank name: ";
				getline(cin, tempString);

			}while(tempString.size()<=0);
			setName(tempString);
			clearscreen();
			cout<<text.str();
			cout << "Bank number: ";
			cin >> tempLong;
			setBankNumber(tempLong);
			clearscreen();
			cout<<text.str();
			cout << "Latitude: ";
			cin >> lat;
			clearscreen();
			cout<<text.str();
			cout << "Longitude: ";
			cin >> lon;
			do{
				clearscreen();
				cout<<text.str();
				cout << "Location: ";
				getline(cin, location);
			}while(location.size()<=0);
			do{
				clearscreen();
				cout<<text.str();
				cout << "Address: ";
				getline(cin, Address);
			}while(Address.size()<=0);
			clearscreen();
			cout<<text.str();
			cout << "PostalCode: ";
			cin >> postalCode;
			clearscreen();
			cout<<text.str();
			cout << "Contact: ";
			cin >> contact;
			this->headquarters.setAddress(Address);
			this->headquarters.setContact(contact);
			this->headquarters.setLocation(location);
			this->headquarters.setNumber(1);
			this->headquarters.setPostalCode(postalCode);
			this->headquarters.setNumClients(0);
			this->addAgency(this->headquarters);

			local = Localization(lat, lon);
			ATM::setTarget(local);
			account::setAgency(agencyNumber);
			account::setBank(bankNumber);
			saveFile("bank");
		}
		return;
	}
	if (data == "operations") {
		ifstream operationsFile;
		operationsFile.open("operations.txt");
		if (operationsFile.is_open()) {
			string line;
			getline(operationsFile, line);
			unsigned int totalOperations = atoi(line.c_str());
			for (int unsigned i = 0; i < totalOperations; i++) {
				string typeRead, nothing;
				operationsFile.ignore(256, ' ');
				getline(operationsFile, typeRead);
				vector<string> vars;
				if (typeRead == "transfer") {
					powerfullRead(3, vars, operationsFile);
					transfer *t;
					account *temp;
					account *temp2;
					try {
						temp = getAccountByID(atoi(vars[0].c_str()));
					} catch (idDoesntExist) {
						vector<int> a;
						Order *o;
						o = new Order(0, a, 0, 0);
						temp = o;
					}
					try {
						temp2 = getAccountByID(atoi(vars[2].c_str()));
					} catch (idDoesntExist) {
						vector<int> a;
						Order *o;
						o = new Order(0, a, 0, 0);
						temp2 = o;
					}

					t = new transfer(temp, temp2, atof(vars[1].c_str()),
							"read");

					operations.push_back(t);
				} else if (typeRead == "withdraw") {
					account *temp;
					powerfullRead(2, vars, operationsFile);
					try {
						temp = getAccountByID(atoi(vars[0].c_str()));
					} catch (idDoesntExist) {
						vector<int> a;
						Order *o;
						o = new Order(0, a, 0, 0);
						temp = o;
					}

					withdraw *w;
					w = new withdraw(temp, atof(vars[1].c_str()), "read");

					operations.push_back(w);
				} else {
					powerfullRead(2, vars, operationsFile);
					account *temp;
					try {
						temp = getAccountByID(atoi(vars[0].c_str()));
					} catch (idDoesntExist) {
						vector<int> a;
						Order *o;
						o = new Order(0, a, 0, 0);
						temp = o;
					}

					deposit *d;

					d = new deposit(temp, atof(vars[1].c_str()), "read");

					operations.push_back(d);
				}
				getline(operationsFile, nothing);
			}
			operationsFile.close();
		}
		return;
	}
	if (data == "agencies") {
		ifstream agenciesFile;
		// (1) Read Customers File
		agenciesFile.open("agencies.txt");
		if (agenciesFile.is_open()) {
			BSTItrIn<agency> it(this->agencies);
			string line;
			getline(agenciesFile, line);

			agency::nextAgencyNum = atoi(line.c_str());
			getline(agenciesFile, line);
			unsigned int totalagencies = atoi(line.c_str());
			for (int unsigned i = 0; i < totalagencies; i++) {

				string typeRead, nothing;
				//agenciesFile.ignore(256, ' ');
				vector<string> vars;
				powerfullRead(6, vars, agenciesFile);
				agency a;
				a.setNumber(atol(vars[0].c_str()));
				a.setContact(atol(vars[4].c_str()));
				a.setAddress(vars[2]);
				a.setLocation(vars[1]);
				a.setPostalCode(vars[3]);
				a.setNumClients(atoi(vars[5].c_str()));
				this->agencies.insert(a);

				getline(agenciesFile, nothing);
				if (i == 0) {
					this->setHeadquarters(a);
				}
			}
			agenciesFile.close();
		}
		return;
	}
	if (data == "atms") {
		ifstream atmsFile;
		// (1) Read atms File
		atmsFile.open("atms.txt");
		if (atmsFile.is_open()) {
			string line;
			getline(atmsFile, line);
			ATM::setLastId(atoi(line.c_str()));
			getline(atmsFile, line);
			unsigned int total = atoi(line.c_str());
			getline(atmsFile,line); // nothing
			for (int unsigned i = 0; i < total; i++) {
				cout << "\nCarregou\n";
				vector<string> vars;
				powerfullRead(8, vars,atmsFile);
				getline(atmsFile,line); // nothing
				ATM *p;
				Localization *pL;
				pL=new Localization(atoi(vars[5].c_str()),atoi(vars[6].c_str()));
				p=new ATM(atoi(vars[0].c_str()), atoi(vars[4].c_str()),atoi(vars[3].c_str()),*pL,atoi(vars[2].c_str()),atoi(vars[1].c_str()),vars[7]);
				atms.push(*p);
			}
		}
		atmsFile.close();
	}

}

vector<operation*> Bank::GetOperationByAccountID(unsigned int id) {
	vector<operation*> temp;
	for (unsigned int i = 0; i < operations.size(); i++)
		if (operations[i]->getaccount1()->getID() == id
				|| operations[i]->getaccount2()->getID() == id)
			temp.push_back(operations[i]);
	return temp;
}
void Bank::saveFile(string data) {
	ofstream tempFile;
	if (data == "customers") {
		tempFile.open("~customers.txt");
		if (tempFile.is_open()) {
			tempFile << customers[0]->nextCustomerID << endl;
			tempFile << customers.size() << endl;
			tempFile << "--------------------------------------" << endl;
			for (unsigned int i = 0; i < customers.size(); i++) {
				tempFile << "Type: " << customers[i]->getType() << endl;
				tempFile << "ID: " << customers[i]->getID() << endl;
				tempFile << "Name: " << customers[i]->getName() << endl;
				tempFile << "BirthDate: " << customers[i]->getBirthDate()
																		<< endl;
				tempFile << "Address: " << customers[i]->getAddress() << endl;
				tempFile << "PostalCode: " << customers[i]->getPostalCode()
																		<< endl;
				tempFile << "NIF: " << customers[i]->getNIF() << endl;
				tempFile << "Phone: " << customers[i]->getPhone() << endl;
				tempFile << "LastOperatio: "
						<< customers[i]->getLastOperation().print() << endl;
				tempFile << "IsInactive: " << customers[i]->isInactive()
																		<< endl;
				tempFile << "Agency: " << customers[i]->getAgencyNumb() << endl;
				if (customers[i]->getType() == "particular")
					tempFile << "BI: " << customers[i]->getBI() << endl;
				else
					tempFile << "Capital: " << customers[i]->getCapital()
					<< endl;
				if (i + 1 != customers.size())
					tempFile << "- ------------------------------------"
					<< endl;
			}
			tempFile << "--------------------------------------";
			tempFile.close();
		}
		remove("customers.txt");
		rename("~customers.txt", "customers.txt");
	}
	if (data == "accounts") {
		tempFile.open("~accounts.txt");
		if (tempFile.is_open()) {
			tempFile << accounts[0]->nextAccountID << endl;
			tempFile << accounts.size() << endl;
			tempFile << "--------------------------------------" << endl;
			for (unsigned int i = 0; i < accounts.size(); i++) {
				tempFile << "Type: " << accounts[i]->getType() << endl;
				tempFile << "NumHolders: " << accounts[i]->getNumHolders()
																		<< endl;
				for (int n = 0; n < accounts[i]->getNumHolders(); n++)
					tempFile << "Holder" << n + 1 << ": "
					<< accounts[i]->getHolders()[n] << endl;
				tempFile << "ID: " << accounts[i]->getID() << endl;
				tempFile << "Balance: " << accounts[i]->getBalance() << endl;
				tempFile << "ManagerID: " << accounts[i]->getManagerID()
																		<< endl;
				if (accounts[i]->getType() == "term") {
					tempFile << "BeginDate: " << accounts[i]->getBeginDate()
																			<< endl;
					tempFile << "EndDate: " << accounts[i]->getEndDate()
																			<< endl;
					tempFile << "InterestRate: " << accounts[i]->getInterest()
																			<< endl;
				}
				if (i + 1 != accounts.size())
					tempFile << "- ------------------------------------"
					<< endl;
			}
			tempFile << "--------------------------------------";
			tempFile.close();
		}
		remove("accounts.txt");
		rename("~accounts.txt", "accounts.txt");
	}
	if (data == "employees") {
		tempFile.open("~employees.txt");
		if (tempFile.is_open()) {
			tempFile << employees[0]->nextEmployeeID << endl;
			tempFile << employees.size() << endl;
			tempFile << "--------------------------------------" << endl;
			for (unsigned int i = 0; i < employees.size(); i++) {
				tempFile << "ID: " << employees[i]->getID() << endl;
				tempFile << "Name: " << employees[i]->getName() << endl;
				tempFile << "BirthDate: " << employees[i]->getBirthDate()
																		<< endl;
				tempFile << "Address: " << employees[i]->getAddress() << endl;
				tempFile << "PostalCode: " << employees[i]->getPostalCode()
																		<< endl;
				tempFile << "NIF: " << employees[i]->getNIF() << endl;
				tempFile << "BI: " << employees[i]->getBI() << endl;
				tempFile << "Phone: " << employees[i]->getPhone() << endl;
				tempFile << "Salary: " << employees[i]->getSalary() << endl;
				tempFile << "Post: " << employees[i]->getPost() << endl;
				tempFile << "Qualifications: "
						<< employees[i]->getQualifications() << endl;
				if (i + 1 != employees.size())
					tempFile << "- ------------------------------------"
					<< endl;
			}
			tempFile << "--------------------------------------";
			tempFile.close();
		}
		remove("employees.txt");
		rename("~employees.txt", "employees.txt");
	}
	if (data == "bank") {
		tempFile.open("bank.txt");
		if (tempFile.is_open()) {
			tempFile << "--------------------------------------" << endl;
			tempFile << "BankName: " << getName() << endl;
			tempFile << "BankNumber: " << getBankNumber() << endl;
			tempFile << "AgencyNumber: " << getAgencyNumber() << endl;
			tempFile << "Latitude: " << local.getLatitude() << endl;
			tempFile << "Longitude: " << local.getLongitude() << endl;
			tempFile << "--------------------------------------";
			tempFile.close();
		}
		return;
	}
	if (data == "operations") {
		tempFile.open("~operations.txt");
		if (tempFile.is_open()) {
			tempFile << operations.size() << endl;
			tempFile << "--------------------------------------" << endl;
			for (unsigned int i = 0; i < operations.size(); i++) {
				tempFile << "Type: " << operations[i]->getType() << endl;
				tempFile << "Account1: "
						<< operations[i]->getaccount1()->getID() << endl;
				tempFile << "Value: " << operations[i]->getvalue() << endl;
				if (operations[i]->getType() == "transfer")
					tempFile << "Account2: "
					<< operations[i]->getaccount2()->getID() << endl;
				if (i + 1 != operations.size())
					tempFile << "- ------------------------------------"
					<< endl;
			}
			tempFile << "--------------------------------------";
			tempFile.close();
		}
		remove("operations.txt");
		rename("~operations.txt", "operations.txt");
	}
	if (data == "agencies") {
		tempFile.open("~agencies.txt");
		if (tempFile.is_open()) {
			BSTItrIn<agency> it(this->agencies);
			tempFile << it.retrieve().nextAgencyNum << endl;
			tempFile << this->getNumAgencies() << endl;
			tempFile << "--------------------------------------" << endl;
			while (!it.isAtEnd()) {

				tempFile << "Number: " << it.retrieve().getNumber() << endl;

				tempFile << "Location: " << it.retrieve().getLocation() << endl;

				tempFile << "Address: " << it.retrieve().getAddress() << endl;

				tempFile << "PostalCode: " << it.retrieve().getPostalCode()
																		<< endl;

				tempFile << "Contact: " << it.retrieve().getContact() << endl;

				tempFile << "NumClients: " << it.retrieve().getNumClients()
																		<< endl;

				it.advance();

				tempFile << "--------------------------------------" << endl;
			}
			tempFile.close();
		}
		remove("agencies.txt");
		rename("~agencies.txt", "agencies.txt");
	}

	if (data == "atms") {
		tempFile.open("~atms.txt");
		if (tempFile.is_open()) {
			tempFile << ATM::getLastId() << endl;
			tempFile << atms.size()<< endl;
			tempFile << "--------------------------------------" << endl;
			priority_queue<ATM> aux= atms;
			while(!aux.empty()){
				ATM auxATM=aux.top();
				tempFile << "ID: " << auxATM.getId() << endl;
				tempFile << "MONEY: " << auxATM.getMoney() << endl;
				tempFile << "CAPACITY: " << auxATM.getCapacity() << endl;
				tempFile << "ISSUE: " << auxATM.getIssue() << endl;
				tempFile << "ACTIVE: " << auxATM.getActive() << endl;
				tempFile << "LATITUDE: " << auxATM.getLocalization().getLatitude() << endl;
				tempFile << "LONGITUDE: " << auxATM.getLocalization().getLongitude() << endl;
				tempFile << "LOCALNAME: " << auxATM.getLocal() << endl;
				tempFile << "--------------------------------------" << endl;
				aux.pop();
			}
			tempFile.close();
		}
		remove("atms.txt");
		rename("~atms.txt", "atms.txt");
	}

}
void Bank::addCustomer(customer* custom) {
	customers.push_back(custom);
}

void Bank::addEmployee(employee* emplo) {
	employees.push_back(emplo);
}
void Bank::addAccount(account* acco) {
	accounts.push_back(acco);
}
void Bank::addOperation(operation* oper) {
	operations.push_back(oper);
}
void Bank::addAgency(agency agen) {
	agencies.insert(agen);
}
//! Get Customer by Id,returns a pointer to a Customer or returns 0 if there is not the id received
/*!
 \param id id to search
 */
customer* Bank::getCustomerbyID(long id) {
	for (unsigned int i = 0; i < customers.size(); i++) {
		if (id == customers[i]->getID())
			return customers[i];
	}
	return 0;
}
employee* Bank::getEmployeebyID(long id) {
	for (unsigned int i = 0; i < employees.size(); i++) {
		if (id == employees[i]->getID())
			return employees[i];
	}
	throw idDoesntExist(id);
}
void Bank::powerfullRead(int total, vector<string> &vars, ifstream &file) {
	string aux;
	for (int i = 0; i < total; i++) {
		file.ignore(256, ' ');
		getline(file, aux);
		vars.push_back(aux);
	}
}
long Bank::searchEmployeebyNIF(nif NIF) {
	for (unsigned int i = 0; i < employees.size(); i++)
		if (employees[i]->getNIF() == NIF)
			return employees[i]->getID();
	return -1;
}
long Bank::searchCustomerbyNIF(nif NIF) {
	for (unsigned int i = 0; i < customers.size(); i++)
		if (customers[i]->getNIF() == NIF)
			return customers[i]->getID();
	return -1;
}
long Bank::searchInactiveCustomerbyNIF(nif NIF) {

	HashCustomer::iterator it;
	for (it = inactives_customers.begin();
			it != this->inactives_customers.end(); it++) {
		customer *a = (*it);
		if (a->getNIF() == NIF)
			return a->getID();
	}
	return -1;
}
bool Bank::existEmployeeID(long id) {
	for (unsigned int i = 0; i < employees.size(); i++) {
		if (employees[i]->getID() == id)
			return true;
	}
	return false;

}
vector<employee*> Bank::SearchEmployeesbyname(string name) {
	vector<employee*> vec;
	for (unsigned int i = 0; i < employees.size(); i++)
		if (searchStr(employees[i]->getName(), name))
			vec.push_back(employees[i]);
	return (vec);
}
vector<customer*> Bank::SearchCustomersbyname(string name) {
	vector<customer*> vec;
	for (int unsigned i = 0; i < customers.size(); i++)
		if (searchStr(customers[i]->getName(), name))
			vec.push_back(customers[i]);
	return (vec);
}

HashCustomer Bank::SearchInactiveCustomersbyname(string name) {
	HashCustomer hash;
	HashCustomer::iterator it;
	for (it = this->inactives_customers.begin();
			it != this->inactives_customers.end(); it++) {
		customer *a = (*it);
		if (searchStr(a->getName(), name))
			hash.insert((*it));

	}
	return hash;
}
bool Bank::showCustomer(vector<customer*> vec) {
	if (vec.size() <= 0) {
		cout << "No customers to be listed...\n";
		return false;
	}
	string name;
	cout << "\n------------------------------------------------------------\n";
	cout << "| ID |     NIF     |   TYPE    |            NAME           |";
	for (int unsigned i = 0; i < vec.size(); i++) {
		name = "";
		if (vec[i]->getName().size() > 27) {
			for (int j = 0; j < 24; j++)
				name.push_back(vec[i]->getName()[j]);
			name.push_back('.');
			name.push_back('.');
			name.push_back('.');
		} else
			name = vec[i]->getName();
		cout
		<< "\n------------------------------------------------------------\n";
		cout << "|" << vec[i]->getID() << setw(4) << "|" << setw(13)
																<< vec[i]->getNIF() << "|" << setw(11) << vec[i]->getType()
																<< "|" << setw(27) << name << "|";
	}
	cout << "\n------------------------------------------------------------\n";
	cout << endl;
	return true;
}

bool Bank::showOperation(vector<operation*> vec) {
	if (vec.size() == 0) {
		cout << "No operations to be listed...\n";
		return false;
	} else {
		cout
		<< "\n--------------------------------------------------------------------------------";
		cout
		<< "|       DESTINATION        |          SOURCE          |   VALUE   |    TYPE    |";

		for (unsigned int i = 0; i < vec.size(); i++) {

			cout
			<< "--------------------------------------------------------------------------------";
			if (vec[i]->getType() == "transfer") {
				string nib1;
				string nib2;
				try {
					getAccountByID(vec[i]->getaccount1()->getID());
					if (vec[i]->getaccount1()->getNIB().getNumber() == 0)
						nib1 = "   This account has remove";

					else
						nib1 = vec[i]->getaccount1()->getNIB().print();
				} catch (idDoesntExist) {
					nib1 = "   This account has remove";
				}
				try {
					getAccountByID(vec[i]->getaccount2()->getID());

					if (vec[i]->getaccount2()->getNIB().getNumber() == 98)

						nib2 = "   This account has remove";

					else
						nib2 = vec[i]->getaccount2()->getNIB().print();
				} catch (idDoesntExist) {
					nib2 = "   This account has remove";
				}
				cout << "|" << nib1 << "|" << nib2 << "|" << setw(11)
																		<< vec[i]->getvalue() << "|" << setw(12)
																		<< vec[i]->getType() << "|";
			} else
				cout << "|" << vec[i]->getaccount1()->getNIB() << "|"
				<< "--------------------------" << "|" << setw(11)
				<< vec[i]->getvalue() << "|" << setw(12)
				<< vec[i]->getType() << "|";

		}
		cout
		<< "--------------------------------------------------------------------------------";
		cout << endl;
	}

	return true;
}

bool Bank::showEmployee(vector<employee*> vec) {
	if (vec.size() <= 0) {
		cout << "No employees to be listed...\n";
		return false;
	}
	string name;
	cout << "\n------------------------------------------------------------\n";
	cout << "| ID |     NIF     |   POST    |            NAME           |";
	for (int unsigned i = 0; i < vec.size(); i++) {
		name = "";
		if (vec[i]->getName().size() > 27) {
			for (int j = 0; j < 24; j++)
				name.push_back(vec[i]->getName()[j]);
			name.push_back('.');
			name.push_back('.');
			name.push_back('.');
		} else
			name = vec[i]->getName();

		cout
		<< "\n------------------------------------------------------------\n";
		cout << "|" << vec[i]->getID() << setw(4) << "|" << setw(13)
																<< vec[i]->getNIF() << "|" << setw(11) << vec[i]->getPost()
																<< "|" << setw(27) << name << "|";
	}
	cout << "\n------------------------------------------------------------\n";

	cout << endl;
	return true;
}

bool Bank::showEmployee(employee* a) {
	cout << "* * * * * * * *" << endl;
	cout << "Employee Data *" << endl;
	cout << "* * * * * * * *" << endl << endl;
	cout
	<< "===============================================================================\n\n";
	cout << "Name: " << a->getName() << endl;
	cout << "Brirth Date: " << a->getBirthDate() << endl;
	cout << "Adress: " << a->getAddress() << endl;
	cout << "Postal Code: " << a->getPostalCode() << endl;
	cout << "NIF: " << a->getNIF() << endl;
	cout << "BI/CC: " << a->getBI() << endl;
	cout << "Phone: " << a->getPhone() << endl;
	cout << "Post: " << a->getPost() << endl;
	cout << "Qualifications: " << a->getQualifications() << endl;
	cout << "Salary: " << a->getSalary() << endl;
	cout
	<< "===============================================================================\n\n";

	return true;
}
bool Bank::showInactiveCustomer(HashCustomer hash) {
	HashCustomer::iterator it;

	if (hash.size() <= 0) {
		cout << "No customers to be listed...\n";
		return false;
	}
	string name;
	cout << "\n------------------------------------------------------------\n";
	cout << "| ID |     NIF     |   TYPE    |            NAME           |";
	for (it = hash.begin(); it != hash.end(); it++) {
		name = "";
		customer *a = (*it);

		if (a->getName().size() > 27) {
			for (int j = 0; j < 24; j++)
				name.push_back(a->getName()[j]);
			name.push_back('.');
			name.push_back('.');
			name.push_back('.');
		} else
			name = a->getName();
		cout
		<< "\n------------------------------------------------------------\n";
		cout << "|" << a->getID() << setw(4) << "|" << setw(13) << a->getNIF()
																<< "|" << setw(11) << a->getType() << "|" << setw(27) << name
																<< "|";
	}
	cout << "\n------------------------------------------------------------\n";
	cout << endl;
	return true;
}
bool Bank::showAccount(account* a) {
	cout
	<< "===============================================================================\n\n";
	cout << "* * * * * * * *" << endl;
	cout << "Account Data *" << endl;
	cout << "* * * * * * * *" << endl << endl;

	cout << "NIB: " << a->getNIB() << endl;
	vector<int> temp = a->getHolders();
	cout << "Balance: " << a->getBalance() << "�" << endl;

	for (unsigned int i = 0; i < temp.size(); i++)
		cout << "Holder " << i + 1 << ": "
		<< this->getCustomerbyID(temp[i])->getName() << endl;
	cout << "Manager: " << getEmployeebyID(a->getManagerID())->getName()
															<< endl;
	cout << "Type: " << a->getType() << endl;
	if (a->getType() == "term") {
		cout << "Begin Date: " << a->getBeginDate() << endl;
		cout << "End Date: " << a->getEndDate() << endl;
		cout << "Interest: " << a->getInterest() << endl;

	}
	cout
	<< "===============================================================================\n\n";
	return true;
}

bool Bank::showAccount(vector<account*> vec) {
	string holder, manager;

	if (vec.size() == 0) {
		cout << "No accounts to be listed...";
		return false;
	} else {
		cout
		<< "\n--------------------------------------------------------------------------------";
		cout
		<< "| ID |           NIB            | BALANCE |     HOLDERS      |     MANAGER     |";
		for (int unsigned i = 0; i < vec.size(); i++) {
			cout
			<< "--------------------------------------------------------------------------------";
			try {
				holder = getCustomerbyID(vec[i]->getHolders()[0])->getName();
				if (getCustomerbyID(vec[i]->getHolders()[0])->getName().size()
						> 18) {
					holder = "";
					for (int j = 0; j < 14; j++)
						holder.push_back(
								getCustomerbyID(vec[i]->getHolders()[0])->getName()[j]);
					holder.push_back('.');
					holder.push_back('.');
					holder.push_back('.');

				}
				manager = getEmployeebyID(vec[i]->getManagerID())->getName();
				if (getEmployeebyID(vec[i]->getManagerID())->getName().size()
						> 18) {
					manager = "";
					for (int j = 0; j < 14; j++)
						manager.push_back(
								getEmployeebyID(vec[i]->getManagerID())->getName()[j]);
					manager.push_back('.');
					manager.push_back('.');
					manager.push_back('.');
				}
				cout << "|" << vec[i]->getID() << setw(4) << "|" << setw(4)
																		<< vec[i]->getNIB() << "|" << setw(9)
																		<< vec[i]->getBalance() << "|" << setw(18) << holder
																		<< "|" << setw(17) << manager << "|";
			} catch (idDoesntExist) {
				holder = getCustomerbyID(vec[i]->getHolders()[0])->getName();
				if (getCustomerbyID(vec[i]->getHolders()[0])->getName().size()
						> 18) {
					holder = "";
					for (int j = 0; j < 14; j++)
						holder.push_back(
								getCustomerbyID(vec[i]->getHolders()[0])->getName()[j]);
					holder.push_back('.');
					holder.push_back('.');
					holder.push_back('.');

				}

				cout << "|" << vec[i]->getID() << setw(4) << "|" << setw(4)
																		<< vec[i]->getNIB() << "|" << setw(9)
																		<< vec[i]->getBalance() << "|" << setw(18) << holder
																		<< "|" << setw(17) << "Without employee" << "|";

			}

		}
		cout
		<< "--------------------------------------------------------------------------------";
	}
	cout << endl;
	return true;
}

bool Bank::showAgencies(BST<agency> bst) {
	BSTItrIn<agency> it(bst);
	if (bst.isEmpty()) {
		cout << "No agencies to be listed...\n";
		return false;
	}

	cout << "\n-------------------------------------------------\n";
	cout << "| NUMBER |    LOCATION    |     NUM CLIENTS     |";
	while (!it.isAtEnd()) {

		cout << "\n-------------------------------------------------\n";
		if(it.retrieve().getLocation().size()<=17)

			cout << "|" << setw(8) << it.retrieve().getNumber() << "|" << setw(16)
			<< it.retrieve().getLocation() << "|" << setw(21)
			<< it.retrieve().getNumClients() << "|";
		else
		{
			cout << "|" << setw(8) << it.retrieve().getNumber() << "|";
			for(unsigned int i=0;i<13;i++)
			{
				cout<<it.retrieve().getLocation()[i];
			}
			cout<<"..."<< "|" << setw(21)
							<< it.retrieve().getNumClients() << "|";

		}

		it.advance();
	}
	cout << "\n-------------------------------------------------\n";
	cout << endl;
	return true;
}

bool Bank::showAgency(agency tempAgency) {
	cout << "\n-------------------------------------------------\n";
	cout << "| NUMBER |    LOCATION    |     NUM CLIENTS     |";

	cout << "\n-------------------------------------------------\n";
	if(tempAgency.getLocation().size()<=17)

		cout << "|" << setw(8) << tempAgency.getNumber() << "|" << setw(16)
		<< tempAgency.getLocation() << "|" << setw(21)
		<< tempAgency.getNumClients() << "|";
	else
	{
		cout << "|" << setw(8) << tempAgency.getNumber() << "|";
		for(unsigned int i=0;i<13;i++)
		{
			cout<<tempAgency.getLocation()[i];
		}
		cout<<"..."<< "|" << setw(21)
								<< tempAgency.getNumClients() << "|";

	}
	cout << "\n-------------------------------------------------\n";

	cout << endl;
	return true;
}

vector<account*> Bank::getAccountsByCustomerID(long id) {
	vector<account*> temp;
	for (unsigned int i = 0; i < accounts.size(); i++) {
		for (unsigned int j = 0; j < accounts[i]->getHolders().size(); j++)
			if (accounts[i]->getHolders()[j] == id) {
				temp.push_back(accounts[i]);
				break;
			}

	}
	return temp;
}

int Bank::getaccountIDbyNIB(string NIB) {
	for (unsigned int i = 0; i < accounts.size(); i++)
		if (accounts[i]->getNIB().getNIBstring() == NIB)
			return (accounts[i]->getID());

	return -1;

}
bool Bank::accountExists(unsigned int ID) {
	for (unsigned int i = 0; i < accounts.size(); i++)
		if (accounts[i]->getID() == ID)
			return 1;
	return 0;
}
bool Bank::existAgency(long id) {
	BSTItrIn<agency> it(this->agencies);
	while (!it.isAtEnd()) {
		if (it.retrieve().getNumber() == id)
			return true;
		it.advance();
	}
	return false;
}

bool Bank::showCustomer(customer* a) {
	cout << "* * * * * * * *" << endl;
	cout << "Customer Data *" << endl;
	cout << "* * * * * * * *" << endl << endl;
	cout
	<< "===============================================================================\n\n";
	cout << "Name: " << a->getName() << endl;
	cout << "Brirth Date: " << a->getBirthDate() << endl;
	cout << "Adress: " << a->getAddress() << endl;
	cout << "Postal Code: " << a->getPostalCode() << endl;
	cout << "NIF: " << a->getNIF() << endl;
	if (a->getType() == "particular")
		cout << "BI/CC: " << a->getBI() << endl;
	else
		cout << "Capital: " << a->getCapital() << endl;
	cout
	<< "===============================================================================\n\n";
	return true;
}
bool Bank::showInactiveCustomer(customer *a) {
	cout << "* * * * * * * *" << endl;
	cout << "Customer Data *" << endl;
	cout << "* * * * * * * *" << endl << endl;
	cout
	<< "===============================================================================\n\n";
	cout << "Name: " << a->getName() << endl;
	cout << "Brirth Date: " << a->getBirthDate() << endl;
	cout << "Adress: " << a->getAddress() << endl;
	cout << "Postal Code: " << a->getPostalCode() << endl;
	cout << "NIF: " << a->getNIF() << endl;
	if (a->getType() == "particular")
		cout << "BI/CC: " << a->getBI() << endl;
	else
		cout << "Capital: " << a->getCapital() << endl;
	cout
	<< "===============================================================================\n\n";
	return true;
}
account* Bank::getAccountByID(unsigned int ID) {
	for (unsigned int i = 0; i < accounts.size(); i++)
		if (accounts[i]->getID() == ID)
			return accounts[i];
	throw idDoesntExist(ID);
}

vector<account*> Bank::getAccountsByEmployeeID(unsigned int ID) {
	vector<account*> temp;
	for (unsigned int i = 0; i < accounts.size(); i++)
		if (accounts[i]->getManagerID() == ID)
			temp.push_back(accounts[i]);
	return temp;
}
void Bank::addInative_customer(customer* c) {
	this->inactives_customers.insert(c);
}

customer* Bank::getInactiveCustomerbyID(long id) {
	HashCustomer::iterator it;
	for (it = inactives_customers.begin(); it != inactives_customers.end();
			it++) {
		customer *a = (*it);
		if (a->getID() == id) {
			return (*it);

		}
	}
	throw idDoesntExist(id);

}

long Bank::getNumCustomerInAgency(long num) {
	BSTItrIn<agency> it(this->agencies);
	BST<agency> bst(invalidAgency);
	long soma = 0;
	for (unsigned int i = 0; i < this->customers.size(); i++) {
		if (customers[i]->getAgencyNumb() == num)
			soma++;

	}
	agency a = *this->getAgencyByNumber(num);
	a.setNumClients(soma);
	while (!it.isAtEnd()) {
		if (it.retrieve().getNumber() != a.getNumber())
			bst.insert(it.retrieve());
		it.advance();
	}
	bst.insert(a);
	this->agencies = bst;
	return soma;
}
