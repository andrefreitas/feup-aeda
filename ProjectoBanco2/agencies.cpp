#include "agencies.h"
#include <iostream>
using namespace std;

int agency::nextAgencyNum =1;
ostream & operator <<(ostream & out, agency & a) {
	out << a.getNumber() << "   " << a.getLocation() << "   "
			<< a.getNumClients() << endl;
	return out;
}

agency::agency(string location, string address, string postalCode,
		long contact) :
		number(nextAgencyNum), location(location), address(address), postalCode(
				postalCode), contact(contact) {
	numClients=0;
	nextAgencyNum++;
}

void  agency::setnextNumber(int a)
{
	nextAgencyNum=a;
}
