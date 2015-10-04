#ifndef ATM_H_
#define ATM_H_
#include <string>
#include "types.h"
//!  ATM Terminal (Multibanco)
/*! This class defines an ATM with all the typical attributes
 */
class ATM{
	//! The id of the ATM
	int id;
	//! The GPS localization
	Localization localization;
	//! The capacity fo money
	double capacity;
	//! The money that the atm have
	double money;
	//! True if the ATM is active
	bool active;
	//! True if the ATM have a problem
	bool issue;
	//! The name of the localization
	string localName;
	//! Static that is usefull to increment the ids (the ids start with 0 so this statics must start with -1)
	static int lastId;
	//! This is the target for the operator <
	static Localization target;
	public:
	//!Empty consctructor
	ATM(){};
	//! Constructor for loading files
	ATM(int i, bool a, bool is, Localization l, double c, double m,string ln):id(i),localization(l),capacity(c),money(m),active(a),issue(is),localName(ln){};
	//! Simpler constructor
	ATM(Localization l, double c, double m, string ln):id(++lastId),localization(l),capacity(c),money(m),active(1),issue(0),localName(ln){};
	// Set Methods
	//! Sets the ID of the ATM to the one given
	/*!
	 \param i the new id of the ATM
	 */
	void setId(int i){id=i;};
	//! Sets the active state of the ATM to the one given
	/*!
	 \param a the new active state of the ATM
	 */
	void setActive(bool a){active=a;};
	//! Sets the issue state of the ATM to the one given
	/*!
	 \param is the new issue state of the ATM
	 */
	void setIssue(bool is){issue=is;};
	//! Sets the local name of the ATM to the one given
	/*!
	 \param ln the new local name of the ATM
	 */
	void setLocal(string ln){ localName=ln; };
	//! Sets the localization of the ATM to the one given
	/*!
	 \param l the new localization of the ATM
	 */
	void setLocalization(Localization l){localization=l;};
	//! Sets the capacity of the ATM to the one given
	/*!
	 \param c the new capacity of the ATM
	 */
	void setCapacity(double c){capacity=c;};
	//! Sets the money of the ATM to the one given
	/*!
	 \param m the new ammount of money in the ATM
	 */
	void setMoney(double m){money=m;};
	//! Sets the last ID of any ATM to the one given
	/*!
	 \param i the new last id of any ATM
	 */
	static void setLastId(int i){lastId=i;};
	//! Sets the target of any ATM to the one given
	/*!
	 \param t the new target of any ATM
	 */
	static void setTarget(Localization t){target=t;};
	// Get Methods
	//! Returns the id of the ATM
	/*!
	 \return returns the ATM's ID
	 */
	int getId(){ return id;};
	//! Returns active state of the ATM
	/*!
	 \return returns true if ATM is active, false otherwise
	 */
	bool getActive(){ return active;};
	//! Returns issue state of the ATM
	/*!
	 \return returns true if there is an issue with the ATM, false otherwise
	 */
	bool getIssue(){ return issue;};
	//! Returns the localization of the ATM
	/*!
	 \return returns the localization (latitude, longitude) of the ATM
	 */
	Localization getLocalization(){ return localization;};
	//! Returns the local name of the ATM
	/*!
	 \return returns the ATM's local name
	 */
	string getLocal(){ return localName;};
	//! Returns the capacity of the ATM
	/*!
	 \return returns the ATM's capacity
	 */
	double getCapacity(){return capacity;};
	//! Returns the ammount of money in the ATM
	/*!
	 \return returns the ATM's balance
	 */
	double getMoney() {return money;};
	//! Returns the id of the last ATM
	/*!
	 \return returns the ATM's last ID
	 */
	static int getLastId(){ return lastId;};
	//! Returns the target of the ATM
	/*!
	 \return returns the ATM's target
	 */
	static Localization getTarget(){ return target; };
	// Operations Methods
	//! Deposit money in the atm
	/*!
	  \param ammount the ammount of money
	  \return true upon success
	 */
	bool deposit(double ammount);
	//! Withdraw money in the atm
		/*!
		  \param ammount the ammount of money
		  \return true upon success
		 */
	bool withdraw(double ammount);
	//! < Operator
	/*!
	 \param b the second ATM to be compared
	 \return returns true if the first atm has money and is nearest to the target, false otherwise
	*/
	bool operator<(const ATM& b) const;
};


#endif
