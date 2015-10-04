#include "bank.h"
using namespace std;

int main() {
	int opt=0, opt2;
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
			text << "2) Add new customer" << endl;
			text << "3) Edit customer" << endl;
			text << "4) Remove customer" << endl;
			text << "0) Return to Menu" << endl;
			do {
				opt2 = readint(text.str());
				switch (opt2) {
				case 1:
					clearscreen()
						;
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
					bank.createCustomer();
					break;
				case 3:
					bank.updateCustomer();
					break;
				case 4:
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
					clearscreen()
						;
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
			text << "2) Add new Account" << endl;
			text << "3) Edit Account" << endl;
			text << "4) List operations of an account" << endl;
			text << "5) Remove account" << endl;
			text << "0) Return to Menu" << endl;
			do {
				opt2 = readint(text.str());
				switch (opt2) {
				case 1:
					clearscreen()
						;
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
					bank.createAccount();
					break;
				case 3:
					bank.updateAccount();
					break;
				case 4:
					bank.viewOperation();
					break;
				case 5:
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
					clearscreen()
						;
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

		}
	} while (opt != 0);
}
