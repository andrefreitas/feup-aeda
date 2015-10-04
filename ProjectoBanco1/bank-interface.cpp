#include "bank.h"

bool isnumeric(string str) //verifica se a string str que � passada como argumento da funcao � ou nao ou numero
		{
	int i = 0;
	int cmp_str = str.size();
	while (i < cmp_str) {
		if (str[i] == -17) //codigo ascky do "�" acento
			return false;
		if (!isdigit(str[i]))
			return false;
		i++;
	}

	return true;
}
int readint(string text) {

	string tmp;
	do {
		clearscreen();
		cout << text;
		clearbuffer();
		cin >> tmp;
	} while (!isnumeric(tmp));
	return atoi(tmp.c_str());
}
float readfloat(string text) {
	string tmp;
	bool flag = true;
	int soma, i;
	soma = 0;
	do {
		clearscreen();
		cout << text;
		clearbuffer();
		cin >> tmp;

		i = 0;
		int cmp_str = tmp.size();
		while (i < cmp_str) {
			if (tmp[i] == -17) //codigo ascky do "�" acento
				flag = false;
			if (!isdigit(tmp[i])) {
				if (tmp[i] == '.')
					soma++;
				else
					flag = false;
			}
			i++;
		}
		if (soma > 1)
			flag = false;

	} while (!flag);
	return atof(tmp.c_str());
}

void Bank::createAccount() {
	// WARNING: Must have customers and employees to create an account

	if (customers.size() == 0) {
		cout << "There are no customers registered..." << endl;
		return;
	}
	if (employees.size() == 0) {
		cout << "There are no employees registered..." << endl;
		return;
	}

	string type;
	stringstream text;
	money initialDeposit;
	unsigned int numHolders, managerID, opt;
	int holderID;
	vector<int> holders;
	clearscreen();
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << "Create Account" << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	// (1) Check if is term or order
	do {
		text << "1) Term" << endl << "2) Order" << endl;
		opt = readint(text.str());
		if (opt == 1)
			type = "term";
		else if (opt == 2)
			type = "order";

	} while (type != "term" && type != "order");
	// (2) Get the initial deposit and the id of holders
	text.str("");

	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << "Create Account" << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	text << "Initial Deposit: ";
	initialDeposit = readfloat(text.str());
	text.str("");

	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << "Create Account" << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	text << "Number of Holders: ";
	numHolders = readint(text.str());
	while (numHolders > customers.size() || numHolders == 0) {
		if (numHolders == 0)
			cout << "Must have at least one holder" << endl;
		else
			cout << "Only customers can choose up to " << customers.size()
					<< endl;
		cout << "Press ENTER to continue\n";
		clearbuffer();
		cin.get();
		numHolders = readint(text.str());
	}
	for (unsigned int i = 0; i < numHolders; i++) {
		holderID = readIDCustomer("Choose a Customer");
		bool flag = false;
		for (unsigned int j = 0; j < holders.size(); j++) {
			if (holders[j] == holderID)
				flag = true;
		}
		while (flag) {
			cout << "This customer already holds an account" << endl;
			cout << "Press ENTER to continue\n";
			clearbuffer();
			cin.get();
			holderID = readIDCustomer("Choose a Customer");
			flag = false;
			for (unsigned int j = 0; j < holders.size(); j++) {
				if (holders[j] == holderID)
					flag = true;
			}
		}
		holders.push_back(holderID);

	}
	managerID = readIDEmployee("Choose a Manager");
	// (OPTIONAL) If is a term account -->
	if (type == "term") {
		text.str("");

		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << "Create Account" << endl;
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";

		string beginDate, endDate;
		float interest;
		clearscreen();
		cout << text.str();
		cout << "Begin Date: ";
		cin >> beginDate;
		clearscreen();
		cout << text.str();
		cout << "End Date: ";
		cin >> endDate;
		clearscreen();
		text << "Interest(0.xx format): ";
		interest = readfloat(text.str());
		// (FINAL1): Add a new object of type term
		Term *t;
		t = new Term(initialDeposit, holders, managerID, beginDate, endDate,
				interest);
		accounts.push_back(t);
		return;
	}

	// (FINAL2): Add a new object of type order
	Order *o;
	o = new Order(initialDeposit, holders, managerID);
	accounts.push_back(o);
}

void Bank::createCustomer() {
	string type;
	string name, birthDate, address, postalCode;
	long NIF, phone;
	int opt;
	stringstream text;
	nif novo_nif(1);
	// (1) Get the data
	clearscreen();
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << "Create Customer" << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";

	// (1) Check the type of customer
	do {
		text << "1) Particular" << endl << "2) Company" << endl;
		opt = readint(text.str());
		if (opt == 1)
			type = "particular";
		else if (opt == 2)
			type = "company";
	} while (type != "particular" && type != "company");
	// (2) Fetch data

	text.str("");
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << "Create Customer" << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";

	do {
		clearscreen();

		cout << text.str();
		cout << "Name: ";
		getline(cin, name);
	} while (name.size() <= 0);
	do {
		clearscreen();
		cout << text.str();
		cout << "Birth Date: ";
		cin >> birthDate;
	} while (birthDate.size() <= 0);
	do {
		clearscreen();

		cout << text.str();
		cout << "Address: ";
		getline(cin, address);
	} while (address.size() <= 0);
	clearscreen();
	do {
		cout << text.str();
		cout << "Postal Code: ";
		cin >> postalCode;
	} while (postalCode.size() <= 0);
	text << "NIF: ";
	NIF = readint(text.str());
	novo_nif.setNumber(NIF);
	clearscreen();
	text.str("");
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << "Create Customer" << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	text << "Phone: ";
	phone = readint(text.str());
	if (type == "particular") {
		long BI;
		clearscreen();
		text.str("");
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << "Create Customer" << endl;
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
		text << "BI/CC: ";
		BI = readint(text.str());
		particular *p;
		p = new particular(name, birthDate, address, postalCode, NIF, BI,
				phone);
		customers.push_back(p);
	} else {
		// (FINAL2): Is a company customer
		double capital;
		text.str("");
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << "Create Customer" << endl;
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
		text << "Capital:  ";
		capital = readfloat(text.str());
		company *c;
		c = new company(name, birthDate, address, postalCode, NIF, capital,
				phone);
		customers.push_back(c);
	}
}

void Bank::createEmployee() {
	string name, birthDate, address, postalCode, post, qualifications;
	long NIF, phone, BI, salary;
	stringstream text;
	nif novo_nif(1);
	// (1) Get the data
	clearscreen();
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << "Create Employee" << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	do {
		clearscreen();
		cout << text.str();
		cout << "Name: ";
		getline(cin, name);
	} while (name.size() <= 0);
	do {
		clearscreen();
		cout << text.str();
		cout << "Birth Date: ";
		cin >> birthDate;

	} while (birthDate.size() <= 0);
	do {
		clearscreen();
		cout << text.str();
		cout << "Address: ";
		getline(cin, address);
	} while (address.size() <= 0);
	do {

		clearscreen();
		cout << text.str();
		cout << "Postal Code: ";
		cin >> postalCode;
	} while (postalCode.size() <= 0);
	text << "NIF: ";
	NIF = readint(text.str());
	novo_nif.setNumber(NIF);
	clearscreen();
	text.str("");
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << "Create Employee" << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	text << "Phone: ";
	phone = readint(text.str());
	clearscreen();
	text.str("");
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << "Create Employee" << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	text << "BI/CC: ";
	BI = readint(text.str());
	clearscreen();
	text.str("");
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << "Create Employee" << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	text << "Salary: ";
	salary = readfloat(text.str());

	text.str("");
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << "Create Employee" << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";

	do {
		clearscreen();

		cout << text.str();
		cout << "Post: ";

		getline(cin, post);
	} while (post.size() <= 0);
	do {

		clearscreen();
		cout << text.str();
		cout << "Qualifications: ";

		getline(cin, qualifications);
	} while (qualifications.size() <= 0);
	//(FINAL): Add an object of type employee
	employee *e;
	e = new employee(name, birthDate, address, postalCode, NIF, BI, phone,
			salary, post, qualifications);
	employees.push_back(e);
	vector<account*> temp = getAccountsByEmployeeID(-1);
	for (unsigned int i = 0; i < temp.size(); i++)
		temp[i]->setManagerID(employees[0]->getID());
}

void Bank::createOperation() {
	stringstream text;
	int opt, account1, account2;
	double Amount;
	clearscreen();
	transfer *t;
	withdraw *w;
	deposit *d;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << "Operation" << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";

	if (accounts.size() == 0) {
		cout << text.str();
		cout << "There are no accounts registered..." << endl;
		return;
	}

	text << "1) Transfer\n2) Withdraw\n3) Deposit\n0) Return to Menu\n";
	opt = readint(text.str());
	switch (opt) {
	case 1:
		clearscreen();
		text.str("");

		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << "Transfer" << endl;
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		if (accounts.size() < 2) {
			cout << text.str();
			cout << "We need at least two accounts to do this!\n";
			cout << "Press ENTER to continue\n";
			clearbuffer();
			cin.get();
			return;
		}
		account1 = readIDAccount(
				"Choose the account that will receive the money");
		if (account1 == -1)
			return;
		account2 = readIDAccount(
				"Choose the account that will transfer the money");
		if (account2 == -1)
			return;
		while (account1 == account2) {
			account2 =
					readIDAccount(
							"Choose the account that will transfer the money\nThe accounts must be different");
			if (account2 == -1)
				return;
		}
		text << "Amount to transfer: ";

		do {
			Amount = readfloat(text.str());
		} while (Amount < 0);
		try {

			t = new transfer(getAccountByID(account1), getAccountByID(account2),
					Amount);
			addOperation(t);
		} catch (notenoughmoney &n) {
			cout
					<< "The transfer can not be executed because there are insufficient funds\n";
			cout << "Press ENTER to continue\n";
			clearbuffer();
			cin.get();
			return;
		}
		cout << "The transfer was successful\n";
		cout << "Press ENTER to continue\n";
		clearbuffer();
		cin.get();
		return;
		break;
	case 2:
		account1 = readIDAccount("Choose the account");

		clearscreen();
		text.str("");

		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << "Withdraw" << endl;
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << "Amount to transfer: ";

		do {
			Amount = readfloat(text.str());
		} while (Amount < 0);
		try {

			w = new withdraw(getAccountByID(account1), Amount);
			addOperation(w);

		} catch (notenoughmoney &n) {
			cout
					<< "The withdraw can not be executed because there are insufficient funds\n";
			cout << "Press ENTER to continue\n";
			clearbuffer();
			cin.get();
			return;
		}
		cout << "The withdraw was successful\n";
		cout << "Press ENTER to continue\n";
		clearbuffer();
		cin.get();
		return;
		break;

	case 3:
		account1 = readIDAccount("Choose the account");

		clearscreen();
		text.str("");

		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << "Deposit" << endl;
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << "Amount to transfer: ";

		do {
			Amount = readfloat(text.str());
		} while (Amount < 0);

		d = new deposit(getAccountByID(account1), Amount);

		addOperation(d);

		cout << "The deposit was successful\n";
		cout << "Press ENTER to continue\n";
		clearbuffer();
		cin.get();
		return;
		break;
	case 0:
		return;
	}
}

void Bank::readAccounts() {
	showAccount(accounts);
}
void Bank::readCustomers() {
	showCustomer(customers);
}
void Bank::readEmployees() {
	showEmployee(employees);
}
void Bank::readOperations() {
	showOperation(operations);
}
int Bank::readIDEmployee(string title) {
	int opt;
	long NIF;
	string name;
	nif novo_nif;
	bool rep = false;
	int id = -1;
	string a;
	stringstream text;

	clearscreen();
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << title << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	cout << text.str();
	bool flag;

	vector<employee*> temp;

	if (employees.size() == 0) {
		cout << "\nThere are no employees registered..." << endl;
		cout << "Press ENTER to continue\n";
		clearbuffer();
		cin.get();
		return id;
	}

	text
			<< "\n1) List all Employee\n2) Search Employee by NIF\n3) Search by Name\n0) Return to Menu\n";
	do {

		opt = readint(text.str());

		switch (opt) {
		case 1:

			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << title << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << endl;

			do {

				clearscreen();
				cout << text.str();
				readEmployees();
				cout << "Choose an Employee: ";
				cin >> a;
			} while (!isnumeric(a));
			id = atoi(a.c_str());
			while (!existEmployeeID(id)) {
				do {

					clearscreen();
					cout << text.str();
					readEmployees();
					cout << "This Employee ID does not exist." << endl;
					cout << "Choose an Employee: ";
					cin >> a;
				} while (!isnumeric(a));
				id = atoi(a.c_str());
			}

			break;
		case 2:
			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << title << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << endl;

			text << "Search Employee by NIF" << endl;
			text << "\nNIF: ";
			NIF = readint(text.str());

			while (searchEmployeebyNIF(novo_nif) != 0) {
				clearscreen();
				text.str("");
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << title << endl;
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << endl;

				text << "Search Employee by NIF" << endl;

				text << "\nThis nif does not exist\n";
				text << "NIF: ";
				NIF = readint(text.str());
				novo_nif.setNumber(NIF);
			}
			id = searchEmployeebyNIF(novo_nif);
			break;
		case 3:
			clearscreen();
			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << title << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << endl;
			text << "Search by name\n";

			text << "\nName: ";
			cout << text.str();
			cin >> name;
			clearscreen();
			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << title << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << endl;
			text << "Search by name\n";
			temp = SearchEmployeesbyname(name);

			if (showEmployee(temp)) {
				flag = false;
				do {

					clearscreen();
					cout << text.str();
					showEmployee(temp);
					//cout << "ThisEmployee ID does not exist." << endl;
					cout << "Chouse a employee: ";
					cin >> a;
				} while (!isnumeric(a));
				id = atoi(a.c_str());
				for (unsigned int i = 0; i < temp.size(); i++)
					if (temp[i]->getID() == id)
						flag = true;
				while (!flag) {

					do {

						clearscreen();
						cout << text.str();
						showEmployee(temp);
						cout << "This ID does not list\n";
						cout << "Chouse a employee: ";
						cin >> a;
					} while (!isnumeric(a));
					id = atoi(a.c_str());
					for (unsigned int i = 0; i < temp.size(); i++)
						if (temp[i]->getID() == id)
							flag = true;

				}
			} else {
				clearscreen();
				text.str("");
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << title << endl;
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << endl;
				text << "Search by name\n";
				text << "The search returned no results\n";
				cout << text.str();
				cout << "Press ENTER to continue\n";
				clearbuffer();
				cin.get();
				id = -1;
				rep = true;
				clearscreen();
				text.str("");
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << title << endl;
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text
						<< "\n1) List all Employee\n2) Search Employee by NIF\n3) Search by Name\n0) Return to Menu\n";

			}
			break;

		case 0:
			id = -1;
			break;
		}
	} while (rep);
	return id;
}

int Bank::readIDAccount(string title) {
	int opt;
	int id = -1;
	string new_nib;
	string a;
	stringstream text;
	clearscreen();
	bool flag;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << title << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	cout << text.str();
	if (accounts.size() == 0) {
		cout << "\nThere are no accounts registered..." << endl;
		cout << "Press ENTER to continue\n";
		clearbuffer();
		cin.get();
		return id;
	}
	text
			<< "\n1) List all accounts\n2) Search Account by NIB\n3) Search By Customer\n0) Return to Menu\n";
	opt = readint(text.str());
	switch (opt) {
	case 1:

		text.str("");
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << title << endl;
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << endl;

		do {

			clearscreen();
			cout << text.str();
			readAccounts();
			cout << "Choose an Account: ";
			cin >> a;
		} while (!isnumeric(a));
		id = atoi(a.c_str());
		while (!accountExists(id)) {
			do {

				clearscreen();
				cout << text.str();
				readAccounts();
				cout << "This Account ID does not exist." << endl;
				cout << "Choose an Account: ";
				cin >> a;
			} while (!isnumeric(a));
			id = atoi(a.c_str());
		}
		break;
	case 2:
		clearscreen();
		text.str("");
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << title << endl;
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << "\nNIB (xxxx xxxx xxxx xxxx xxxx x): ";
		cin.ignore();
		getline(cin, new_nib);

		while (getaccountIDbyNIB(new_nib) == -1) {
			clearscreen();
			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << title << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "\nThis NIB does not exist\n";
			text << "NIB (xxxx xxxx xxxx xxxx xxxx x): ";

			cout << text.str();
			clearbuffer();
			getline(cin, new_nib);

		}
		id = getaccountIDbyNIB(new_nib);
		break;
	case 0:
		id = -1;
		break;
	case 3:
		clearscreen();
		text.str("");
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << title << endl;
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		long id2 = -1;
		vector<account*> temp;
		nif novo_nif;
		id2 = readIDCustomer("Choose Customer");
		if (id2 == -1)
			return -1;
		temp = getAccountsByCustomerID(id2);

		do {

			clearscreen();
			cout << text.str();
			showAccount(temp);
			cout << "Choose an Account: ";
			clearbuffer();
			cin >> a;
		} while (!isnumeric(a));
		id = atoi(a.c_str());
		flag = false;
		for (unsigned int i = 0; i < temp.size(); i++) {
			if (temp[i]->getID() == (unsigned) id)
				flag = true;
		}
		while (!flag) {
			do {

				clearscreen();
				cout << text.str();
				showAccount(temp);
				cout << "This Account ID does not list." << endl;
				cout << "Choose an Account: ";
				clearbuffer();
				cin >> a;
			} while (!isnumeric(a));
			for (unsigned int i = 0; i < temp.size(); i++) {
				if (temp[i]->getID() == (unsigned) id)
					flag = true;
			}
			id = atoi(a.c_str());
		}
		break;

	}
	return id;
}

int Bank::readIDCustomer(string title) {
	int opt;
	long NIF;
	nif novo_nif;
	int id = -1;
	bool flag;
	stringstream text;
	string a;
	bool rep = false;
	clearscreen();
	vector<customer*> temp;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << title << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	cout << text.str();
	if (customers.size() == 0) {
		cout << "\nThere are no customers registered..." << endl;
		cout << "Press ENTER to continue\n";
		clearbuffer();
		cin.get();
		return id;
	}
	text
			<< "\n1) List all Customer\n2) Search Customer by NIF\n3) Search by Name\n0) Return to Menu\n";

	do {

		opt = readint(text.str());
		switch (opt) {
		case 1:

			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << title << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << endl;

			do {

				clearscreen();
				cout << text.str();
				readCustomers();
				cout << "Choose an Customer: ";
				cin >> a;
			} while (!isnumeric(a));
			id = atoi(a.c_str());
			while (!existCustomerID(id)) {
				do {

					clearscreen();
					cout << text.str();
					readCustomers();
					cout << "This Customer ID does not exist." << endl;
					cout << "Choose an Customer: ";
					cin >> a;
				} while (!isnumeric(a));
				id = atoi(a.c_str());
			}

			/*showCustomer(customers);
			 id = readint("Choose a Customer: ");
			 while (!existCustomerID(id)) {
			 cout << "This Customer ID does not exist." << endl;
			 readCustomers();
			 id = readint("Choose a Customer: ");
			 }*/
			break;
		case 2:

			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << title << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << endl;

			text << "Search Customer by NIF" << endl;
			text << "\nNIF: ";
			NIF = readint(text.str());

			while (searchCustomerbyNIF(novo_nif) != 0) {
				clearscreen();
				text.str("");
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << title << endl;
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << endl;

				text << "Search Customer by NIF" << endl;

				text << "\nThis nif does not exist\n";
				text << "NIF: ";
				NIF = readint(text.str());
				novo_nif.setNumber(NIF);
			}
			id = searchCustomerbyNIF(novo_nif);

			/*
			 cout << "NIF: ";
			 NIF = readint("NIF: ");
			 while (searchCustomerbyNIF(novo_nif) != 0) {
			 cout << "This NIF does not exist\n";
			 NIF = readint("NIF: ");
			 novo_nif.setNumber(NIF);
			 }
			 id = searchCustomerbyNIF(novo_nif);*/
			break;

		case 3:
			clearscreen();
			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << title << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << endl;
			text << "Search by name\n";

			text << "\nName: ";
			cout << text.str();
			cin >> name;
			clearscreen();
			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << title << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << endl;
			text << "Search by name\n";
			temp = SearchCustomersbyname(name);

			if (showCustomer(temp)) {
				flag = false;
				do {

					clearscreen();
					cout << text.str();
					showCustomer(temp);
					//cout << "ThisEmployee ID does not exist." << endl;
					cout << "Choose  a customer: ";
					cin >> a;
				} while (!isnumeric(a));
				id = atoi(a.c_str());
				for (unsigned int i = 0; i < temp.size(); i++)
					if (temp[i]->getID() == id)
						flag = true;
				while (!flag) {

					do {

						clearscreen();
						cout << text.str();
						showCustomer(temp);
						cout << "This ID does not list\n";
						cout << "Choose  a customer: ";
						cin >> a;
					} while (!isnumeric(a));
					id = atoi(a.c_str());
					for (unsigned int i = 0; i < temp.size(); i++)
						if (temp[i]->getID() == id)
							flag = true;

				}
			} else {
				clearscreen();
				text.str("");
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << title << endl;
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << endl;
				text << "Search by name\n";
				text << "The search returned no results\n";
				cout << text.str();
				cout << "Press ENTER to continue\n";
				clearbuffer();
				cin.get();
				id = -1;
				rep = true;
				clearscreen();
				text.str("");
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << title << endl;
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text
						<< "\n1) List all Customer\n2) Search Customer by NIF\n3) Search by Name\n0) Return to Menu\n";

			}
			break;
		case 0:
			id = -1;
			break;
		}
	} while (rep);

	return id;
}

void Bank::updateEmployee() {
	string name, birthDate, address, postalCode, post, qualifications, a;
	long NIF, phone, BI, salary;
	nif novo_nif;
	bool flag = false;
	int id;
	do {

		id = readIDEmployee("Update Employee");
		int opt;
		stringstream text;

		clearscreen();
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << "Update Employee" << endl;
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
		cout << text.str();
		if (id == -1)
			return;

		do {

			clearscreen();
			cout << text.str();
			showEmployee(getEmployeebyID(id));
			cout << "You really want to change this employee?\n";
			cout << "1) Yes\n2) No\n";
			cin >> a;
		} while (a != "1" && a != "2");
		opt = atoi(a.c_str());
		if (opt == 2) {
			flag = true;
			cout << "Press ENTER to continue\n";
			clearbuffer();
			cin.get();
		} else {
			do {
				clearscreen();
				cout << text.str();
				cout << "Name: ";
				getline(cin, name);
			} while (name.size() <= 0);
			do {
				clearscreen();
				cout << text.str();
				cout << "Birth Date: ";
				cin >> birthDate;
			} while (birthDate.size() <= 0);

			do {
				clearscreen();
				cout << text.str();
				cout << "Address: ";
				getline(cin, address);
			} while (address.size() <= 0);
			do {
				clearscreen();
				cout << text.str();
				cout << "Postal Code: ";
				cin >> postalCode;
			} while (postalCode.size() <= 0);
			text << "NIF: ";
			NIF = readint(text.str());
			novo_nif.setNumber(NIF);
			clearscreen();
			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "Update Employee" << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
			text << "Phone: ";
			phone = readint(text.str());
			clearscreen();
			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "Update Employee" << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
			text << "BI/CC: ";
			BI = readint(text.str());
			clearscreen();
			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "Update Employee" << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
			text << "Salary: ";
			salary = readfloat(text.str());

			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "Update Employee" << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
			do {
				clearscreen();
				cout << text.str();
				cout << "Post: ";
				getline(cin, post);
			} while (post.size() <= 0);

			do {
				clearscreen();
				cout << text.str();
				cout << "Qualifications: ";
				getline(cin, qualifications);
			} while (qualifications.size() <= 0);
			employee *e;
			e = new employee(name, birthDate, address, postalCode, novo_nif, BI,
					phone, salary, post, qualifications, id);
			updateVector(id, employees, e);
			cout << "The employee data were successfully changed\n";
			cout << "Press ENTER to continue\n";
			clearbuffer();
			cin.get();

		}
	} while (flag);
}

void Bank::updateCustomer() {
	int opt;
	long NIF, phone;
	nif novo_nif;
	int id;
	bool flag = false;
	string name, birthDate, address, postalCode, a;
	do {

		id = readIDCustomer("Update Customer");
		stringstream text;

		clearscreen();
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << "Update Customer" << endl;
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
		cout << text.str();
		if (id == -1)
			return;
		showCustomer(getCustomerbyID(id));

		cout << "\nYou really want to change this Customer?\n";
		cout << "1) Yes\n2) No\n";
		do {

			clearscreen();
			cout << text.str();
			showCustomer(getCustomerbyID(id));
			cout << "You really want to change this Customer?\n";
			cout << "1) Yes\n2) No\n";
			cin >> a;
		} while (a != "1" && a != "2");
		opt = atoi(a.c_str());
		if (opt == 2) {
			flag = true;
			cout << "Press ENTER to continue\n";
			clearbuffer();
			cin.get();
		} else {
			do {
				clearscreen();
				cout << text.str();
				cout << "Name: ";
				getline(cin, name);
			} while (name.size() <= 0);
			do {
				clearscreen();
				cout << text.str();
				cout << "Birth Date: ";
				cin >> birthDate;
			} while (birthDate.size() <= 0);
			clearscreen();
			do {
				cout << text.str();
				cout << "Address: ";
				getline(cin, address);
			} while (address.size() <= 0);
			do {
				clearscreen();
				cout << text.str();
				cout << "Postal Code: ";
				cin >> postalCode;
			} while (postalCode.size() <= 0);
			text << "NIF: ";
			NIF = readint(text.str());
			novo_nif.setNumber(NIF);
			clearscreen();
			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "Update Customer" << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
			text << "Phone: ";
			phone = readint(text.str());
			if (getCustomerbyID(id)->getType() == "particular") {
				long BI;

				text.str("");
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << "Update Customer" << endl;
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
				text << "BI/CC: ";
				clearscreen();
				BI = readint(text.str());
				particular *p;
				p = new particular(name, birthDate, address, postalCode,
						novo_nif, BI, phone, id);
				updateVector(id, customers, p);
			} else {
				// (FINAL2): Is a company customer
				double capital;
				text.str("");
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << "Update Customer" << endl;
				text
						<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
				text << "Capital:  ";
				capital = readfloat(text.str());
				company *c;
				c = new company(name, birthDate, address, postalCode, novo_nif,
						phone, id, capital);
				updateVector(id, customers, c);
				cout << "The customer data were successfully changed\n";
				cout << "Press ENTER to continue\n";
				clearbuffer();
				cin.get();
			}
		}
	} while (flag);
}

void Bank::updateAccount() {
	int opt, opt2;
	int id;
	bool flag = false;
	stringstream text;
	string a;
	clearscreen();
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << "Update Account" << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	id = readIDAccount("Upadate Account");
	if (id == -1)
		return;
	account* tempaccount = getAccountByID(id);
	cout << text.str();

	do {

		clearscreen();
		cout << text.str();
		showAccount(tempaccount);
		cout << "You really want to change this account?\n";
		cout << "1) Yes\n2) No\n";
		cin >> a;
	} while (a != "1" && a != "2");
	opt = atoi(a.c_str());
	if (opt == 2) {
		flag = true;
		cout << "Press ENTER to continue\n";
		clearbuffer();
		cin.get();
	} else {

		text << "1)Add holders\n2)Delete holder\n";
		opt = readint(text.str());

		switch (opt) {
		case 1:
			clearscreen();
			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "Update Account" << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
			cout << text.str();
			int holderID;
			holderID = readIDCustomer("Choose Customer");
			if (holderID == -1)
				return;
			for (unsigned int i = 0; i < tempaccount->getHolders().size(); i++)
				if (tempaccount->getHolders()[i] == holderID)
					flag = true;
			while (flag) {
				clearscreen();
				cout << text.str();
				cout << "This client already holds this account\n";
				cout << "Press ENTER to continue\n";
				clearbuffer();
				cin.get();
				holderID = readIDCustomer("Choose Customer");
				if (holderID == -1)
					return;
				for (unsigned int i = 0; i < tempaccount->getHolders().size();
						i++)
					if (tempaccount->getHolders()[i] == holderID)
						flag = true;
			}

			tempaccount->addHolder(holderID);
			break;
		case 2:
			clearscreen();
			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "Update Account" << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
			vector<customer*> temp;
			if (tempaccount->getHolders().size() == 1) {
				cout << text.str();
				text << "If you remove that person's account will be deleted\n";
				text << "Want to continue?\n1) Yes\n2) No\n";
				do {
					opt2 = readint(text.str());
				} while (opt2 > 2 && opt2 < 1);
				if (opt2 == 1) {
					deleteByID(id, accounts);
					cout << "The account was deleted\n";
				}
				cout << "Press ENTER to continue\n";
				clearbuffer();
				cin.get();
				return;
			}

			for (unsigned int i = 0; i < tempaccount->getHolders().size();
					i++) {
				temp.push_back(getCustomerbyID(tempaccount->getHolders()[i]));

			}
			int idcustomer;
			do {
				clearscreen();
				cout << text.str();
				showCustomer(temp);
				cout << "Choose a customer: ";
				clearbuffer();
				cin >> a;
			} while (!isnumeric(a));
			idcustomer = atoi(a.c_str());

			bool flag = false;
			for (unsigned int j = 0; j < tempaccount->getHolders().size();
					j++) {
				if (tempaccount->getHolders()[j] == idcustomer)
					flag = true;
			}
			while (!flag) {

				do {
					clearscreen();
					cout << text.str();
					showCustomer(temp);
					cout << "This customer is not a holder of this account"
							<< endl;
					cout << "Choose a customer: ";
					clearbuffer();
					cin >> a;
				} while (!isnumeric(a));
				idcustomer = atoi(a.c_str());
				flag = false;
				for (unsigned int j = 0; j < tempaccount->getHolders().size();
						j++) {
					if (tempaccount->getHolders()[j] == idcustomer)
						flag = true;
				}

			}
			tempaccount->reHolder(idcustomer);
			break;

		}
	}
}

void Bank::removeEmployee() {

	int opt2;

	nif novo_nif;
	int id;
	string a;
	stringstream text, st;
	bool flag = false;
	do {

		id = readIDEmployee("Delete Employee");
		if (id == -1)
			return;

		clearscreen();
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << "Delete Employee" << endl;
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
		cout << text.str();
		showEmployee(getEmployeebyID(id));
		vector<account*> temp = getAccountsByEmployeeID(id);
		if (employees.size() == 1) {
			text
					<< "If you delete this employee, the bank employees will be without!\nWhile not hire more employees will not open accounts.\n";
		}

		do {

			clearscreen();
			cout << text.str();
			showEmployee(getEmployeebyID(id));
			cout << "You really want to delete this employee?\n";
			cout << "1) Yes\n2) No\n";
			cin >> a;
		} while (a != "1" && a != "2");
		opt2 = atoi(a.c_str());
		if (opt2 == 2) {
			cout << "Press ENTER to continue\n";
			clearbuffer();
			cin.get();
			flag = true;

		} else {

			deleteByID(id, employees);

			temp = getAccountsByEmployeeID(id);
			for (unsigned int i = 0; i < temp.size(); i++) {
				int managerID;
				if (employees.size() == 0)
					temp[i]->setManagerID(-1);
				else if (employees.size() == 1)
					temp[i]->setManagerID(employees[0]->getID());
				else {
					clearscreen();
					text.str("");
					text
							<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
					text << "Delete Employee" << endl;
					text
							<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
					cout << text.str();
					cout
							<< "\nThis employee was responsible for the account with the nib:\n"
							<< temp[i]->getNIB()
							<< "\nChoose a new responsible!\n";
					cout << "Press ENTER to continue\n";
					clearbuffer();
					cin.get();
					/*readEmployees();
					 cout << "Manager ID: ";
					 managerID = readint("Manager ID: ");
					 while (!existEmployeeID(managerID)) {
					 cout << "This Employee ID does not exist." << endl;
					 readEmployees();
					 managerID = readint("Manager ID: ");
					 }*/
					st.str("");
					st << "Choose a new employee for this account: "
							<< temp[i]->getNIB();
					managerID = readIDEmployee(st.str());

					temp[i]->setManagerID(managerID);
				}
			}
			clearscreen();
			text.str("");
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "Delete Employee" << endl;
			text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
			cout << text.str();
			cout << endl << "The employee has been deleted" << endl;
			cout << "Press ENTER to continue\n";
			clearbuffer();
			cin.get();
		}
	} while (flag);
}

void Bank::removeCustomer() {

	string a;
	int id, opt2;
	stringstream text;

	vector<account*> temp;
	bool flag2 = false;
	do {
		id = readIDCustomer("Remove Customer");
		if (id == -1)
			return;
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << "Delete Employee" << endl;
		text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
		do {
			clearscreen();

			cout << text.str();
			showCustomer(getCustomerbyID(id));
			cout
					<< "Want to remove this customer?\nThe account in which he is the sole proprietor will be deleted.\n";

			cout << "1) Yes\n2) No\n";
			cin >> a;
		} while (a != "1" && a != "2");
		opt2 = atoi(a.c_str());

		vector<int> vecID;
		if (opt2 == 1) {
			temp = getAccountsByCustomerID(id);
			for (unsigned int i = 0; i < temp.size(); i++) {
				if (temp[i]->getHolders().size() > 1)
					temp[i]->reHolder(id);
				else if (temp[i]->getHolders().size() == 1)
					vecID.push_back(temp[i]->getID());
			}
			for (unsigned int i = 0; i < vecID.size(); i++) {
				try {
					deleteByID(vecID[i], accounts);
				} catch (idDoesntExist &e) {
				};
			}
			deleteByID(id, customers);
			cout << endl << "The employee has been deleted" << endl;
		} else
			flag2 = true;
		cout << "Press ENTER to continue\n";
		clearbuffer();
		cin.get();
	} while (flag2);
}

void Bank::removeAccount() {
	string a;
	int id, opt2;
	stringstream text;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	text << "Delete Account" << endl;
	text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	bool flag2 = false;
	do {
		id = readIDAccount("Remove Account");
		if (id == -1)
			return;
		do {
			clearscreen();
			cout << text.str();
			showAccount(getAccountByID(id));
			cout << "\nWant to remove this account? " << endl;
			cout << "1) Yes\n2) No\n";
			cin >> a;

		} while (a != "1" && a != "2");
		opt2 = atoi(a.c_str());
		if (opt2 == 1) {
			deleteByID(id, accounts);
			cout << "The account was deleted\n";
		} else
			flag2 = true;

		cout << "Press ENTER to continue\n";
		clearbuffer();
		cin.get();
	} while (flag2);
}

void Bank::viewOperation() {
	int id;
	vector<operation*> temp;
	id = readIDAccount("Choose account: ");
	if (id == -1)
		return;
	temp = GetOperationByAccountID(id);
	clearscreen();
	cout
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
	cout << "List operations\n" << endl;
	cout
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
	showOperation(temp);
	cout << "Press ENTER to continue\n";
	clearbuffer();
	cin.get();
}
