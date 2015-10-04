#include "bank.h"
using namespace std;

int main() {
	int opt = 0, opt2;
	Bank bank;
	stringstream text;
	do {
		clearscreen();
		text.str("");
		text
		<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << bank.getName() << " - Administration Panel\n";
		text
		<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		text << "\nChoose one of the following options:\n";
		text << "1 - Customers\n";
		text << "2 - Employees\n";
		text << "3 - Accounts\n";
		text << "4 - Operations\n";
		text << "5 - Inactive Customer\n";
		text << "6 - Agencies\n";
		text << "7 - ATM Management\n";
		text << "0 - Exit\n";
		opt = readint(text.str());

		switch (opt) {
		case 1:
			text.str("");
			text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "Customer\n";
			text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "\nChoose one of the following options:\n";
			text << "1) List all Customer" << endl;
			text << "2) Edit customer" << endl;
			text << "3) Remove customer" << endl;
			text << "0) Return to Menu" << endl;
			do {
				opt2 = readint(text.str());
				switch (opt2) {
				case 1:
					clearscreen();
					cout
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
					cout << "List Customer\n" << endl;
					cout
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
					bank.readCustomers();
					cout << "Press ENTER to continue\n";
					clearbuffer();
					cin.get();
					break;
				case 2:
					bank.updateCustomer();
					break;
				case 3:
					bank.removeCustomer();
					break;

				}
			} while (opt2 != 0);
			break;
		case 2:
			text.str("");
			text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "Employee\n";
			text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "\nChoose one of the following options:\n";
			text << "1) List all Employee" << endl;
			text << "2) Add new Employee" << endl;
			text << "3) Edit Employee" << endl;
			text << "4) Remove Employee" << endl;
			text << "0) Return to Menu" << endl;
			do {
				opt2 = readint(text.str());
				switch (opt2) {
				case 1:
					clearscreen();
					cout
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
					cout << "List Employees\n" << endl;
					cout
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
					bank.readEmployees();
					cout << "Press ENTER to continue\n";
					clearbuffer();
					cin.get();
					break;
				case 2:
					bank.createEmployee();
					break;
				case 3:
					bank.updateEmployee();
					break;
				case 4:
					bank.removeEmployee();
					break;

				}
			} while (opt2 != 0);
			break;
		case 3:

			text.str("");
			text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "Account\n";
			text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "\nChoose one of the following options:\n";
			text << "1) List all Accounts" << endl;
			text << "2) Edit Account" << endl;
			text << "3) List operations of an account" << endl;
			text << "4) Remove account" << endl;
			text << "0) Return to Menu" << endl;
			do {
				opt2 = readint(text.str());
				switch (opt2) {
				case 1:
					clearscreen();
					cout
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
					cout << "List Accounts\n" << endl;
					cout
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
					bank.readAccounts();
					cout << "Press ENTER to continue\n";
					clearbuffer();
					cin.get();
					break;

				case 2:
					bank.updateAccount();
					break;
				case 3:
					bank.viewOperation();
					break;
				case 4:
					bank.removeAccount();
					break;
				}
			} while (opt2 != 0);
			break;
		case 4:

			text.str("");
			text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "Operations\n";
			text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "\nChoose one of the following options:\n";
			text << "1) Choose Operation" << endl;
			text << "2) Historical List of operations" << endl;
			text << "0) Return to Menu" << endl;

			do {
				opt2 = readint(text.str());
				switch (opt2) {
				case 1:
					bank.createOperation();
					break;
				case 2:
					clearscreen();
					cout
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
					cout << "List Operations\n" << endl;
					cout
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
					bank.readOperations();
					cout << "Press ENTER to continue\n";
					clearbuffer();
					cin.get();
					break;
				}

			} while (opt2 != 0);
			break;
		case 5:
			text.str("");
			text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "Inactive Customers\n";
			text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "\nChoose one of the following options:\n";
			text << "1) Add new Inactive Customer" << endl;
			text << "2) List All Inactive Customers" << endl;
			text << "3) Remove Inactive Customer" << endl;
			text << "4) Edit Inactive Customer" << endl;
			text << "5) Enable Customer" << endl;
			text << "0) Return to Menu" << endl;
			do {
				opt2 = readint(text.str());
				switch (opt2) {
				case 1:
					bank.createInative_customer();
					break;
				case 2:
					clearscreen();
					cout
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
					cout << "List Inactive Customers\n" << endl;
					cout
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
					bank.readInactiveCustomers();
					cout << "Press ENTER to continue\n";
					clearbuffer();
					cin.get();
					break;
				case 3:
					bank.removeInactiveCustomer();
					break;
				case 4:
					bank.updateInactiveCustomer();
					break;
				case 5:
					bank.activeCustomer();
					break;
				}

			} while (opt2 != 0);
			break;
		case 6:

			text.str("");
			text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "Agencies\n";
			text
			<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
			text << "\nChoose one of the following options:\n";
			text << "1) List all Agencies" << endl;
			text << "2) Add new Agency" << endl;
			text << "3) Edit Agency" << endl;
			text << "4) Account/Customers" << endl;
			text << "5) Remove Agency" << endl;
			text << "0) Return to Menu" << endl;
			do {
				opt2 = readint(text.str());
				switch (opt2) {
				case 1:
					clearscreen();
					cout
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
					cout << "List Agencies\n" << endl;
					cout
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
					bank.readAgencies();
					cout << "Press ENTER to continue\n";
					clearbuffer();
					cin.get();
					break;
				case 2:
					bank.createAgency();
					break;
				case 3:
					bank.updateAgency();
					break;
				case 4:
					clearscreen();

					bank.setAgencyNumber(bank.readIDAgency("Create account"));
					text.str("");
					text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
					text << "Accounts by Agency\n";
					text
					<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
					text << "\nChoose one of the following options:\n";
					text << "1) List all Accounts this Agency" << endl;
					text << "2) Create new accounts" << endl;
					text << "3) Create new costumer" << endl;
					text << "0) Return to Menu" << endl;
					do {
						opt2 = readint(text.str());
						switch (opt2) {
						case 1:
							bank.listAccountsByAgency();
							cout << "Press ENTER to continue\n";
							clearbuffer();
							cin.get();
							break;
							break;
						case 2:
							bank.createAccount();
							cout << "Press ENTER to continue\n";
							clearbuffer();
							cin.get();
							break;
						case 3:
							bank.createCustomer();
							cout << "Press ENTER to continue\n";
							clearbuffer();
							cin.get();
							break;
						}
					} while (opt2 != 0);
					opt2 = 1;

					break;
				case 5:
					bank.removeAgency();
					break;
				}
				text.str("");
				text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << "Agencies\n";
				text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << "\nChoose one of the following options:\n";
				text << "1) List all Agencies" << endl;
				text << "2) Add new Agency" << endl;
				text << "3) Edit Agency" << endl;
				text << "4) Account/Customers" << endl;
				text << "5) Remove Agency" << endl;
				text << "0) Return to Menu" << endl;
			} while (opt2 != 0);
			break;
		case 7:
			do {
				text.str("");
				text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << "ATM Management\n";
				text
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
				text << "\nChoose one of the following options:\n";
				text << "1) List all ATMs" << endl;
				text << "2) Add new ATM" << endl;
				text << "3) Edit ATM" << endl;
				text << "4) Remove ATM" << endl;
				text << "5) Find Nearest" << endl;
				text << "6) Deposit" << endl;
				text << "7) Withdraw" << endl;
				text << "0) Return to Menu" << endl;
				opt2 = readint(text.str());
				switch (opt2) {
				case 1:
					clearscreen();
					bank.readAtms();
					cout << "\nPress ENTER to continue\n";
					clearbuffer();
					cin.get();
					break;
				case 2:
					clearscreen();
					bank.createAtm();
					break;
				case 3:
					clearscreen();
					bank.updateAtm();
					break;
				case 4:
					clearscreen();
					bank.removeAtm();
					break;
				case 5:
					clearscreen();
					bank.nearestAtm();
					break;
				case 6:
					clearscreen();
					bank.depositAtm();
					break;
				case 7:
					clearscreen();
					bank.withdrawAtm();
					break;
				}

			} while (opt2 != 0);
			break;
		}
	} while (opt != 0);
}
