#include "atm.h"
bool ATM::deposit(double ammount){
	if((money+ammount)>capacity) return 0;
	else {
		if(!active) active=1;
		money+=ammount;
	}
	return 1;
};

bool ATM::withdraw(double ammount){
	if((money-ammount)<0) return 0;
	else {
		money-=ammount;
		if(money==0) active=0;
	}
	return 1;
}

bool ATM::operator<(const ATM& b) const{
	if(!active && b.active) return 1; // The not actives need to be put in the bottom of the queue
	if(active && !b.active) return 0;
	double d1=Localization::distance(target,localization);
	double d2=Localization::distance(target,b.localization);
	// Need to be like this
	return d1>d2;
}

int ATM::lastId=-1;
Localization ATM::target=Localization(0,0);
