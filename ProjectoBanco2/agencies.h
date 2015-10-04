#ifndef AGENCIES_H_
#define AGENCIES_H_

#include <string>
#include <iostream>
using namespace std;


//!  Class Agencies
/*! This class defines an agency with all the needed parameters
 */
class agency {
private:
	//! Agency's 4 digit Number
	int number;
	//! Agency's location (town)
	string location;
	//! Agency's complete address
	string address;
	//! Agency's postal code
	string postalCode;
	//! Agency's telephone number
	long contact;
	//! Agency's number of clients
	int numClients;

public:
	//! The number of the next agency to be created
	int static nextAgencyNum;
	//! Default constructor
	agency() {
	}
	//! Constructor
	/*!
	 \param location
	 \param address
	 \param postalCode
	 \param contact
	 */
	agency(string location, string address, string postalCode,
			long contact);
	//! Return the agency number
	/*!
	 \return returns the agency number
	 */
	int getNumber() {
		return number;
	}
	//! Return the location
	/*!
	 \return returns the agency location
	 */
	string getLocation() {
		return location;
	}
	//! Return the address
	/*!
	 \return returns the agency address
	 */
	string getAddress() {
		return address;
	}
	//! Return the postal code
	/*!
	 \return returns the agency postal code
	 */
	string getPostalCode() {
		return postalCode;
	}
	//! Return the contact
	/*!
	 \return returns the agency contact
	 */
	long getContact() {
		return contact;
	}
	//! Return the number of clients
	/*!
	 \return returns the agency number of clients
	 */
	int getNumClients() {
		return numClients;
	}
	//! Set the agency number
	/*!
	 \param number agency number
	 */
	void setNumber(int number) {
		this->number = number;
	}
	//! Set the agency location
	/*!
	 \param location agency location
	 */
	void setLocation(string location) {
		this->location = location;
	}
	//! Set the agency address
	/*!
	 \param address agency address
	 */
	void setAddress(string address) {
		this->address = address;

	}
	//! Set the agency postal code
	/*!
	 \param postalCode agency postal code
	 */
	void setPostalCode(string postalCode) {
		this->postalCode = postalCode;

	}
	//! Set the agency contact
	/*!
	 \param contact agency contact
	 */
	void setContact(long contact) {
		this->contact = contact;

	}
	//! Set the agency number of clients
	/*!
	 \param numClients agency number of clients
	 */
	void setNumClients(int numClients) {
		this->numClients = numClients;
	}
	//! Operator < (needed for the BST)
	/*!
	 \param a2 second agency to be compared
	 \return returns true if a1<a2 and false otherwise
	 */
	bool operator<(agency a2) const {
		if (this->location == a2.location)
			return this->numClients > a2.numClients;
		return this->location < a2.location;
	}
	
	//! Set the next agency number
	void   setnextNumber(int a);

}
;

//! Operator <z (needed for the BST's print tree function)
/*!
 \param out output stream
 \param a agency to print
 \return returns the output stream
*/
ostream & operator <<(ostream & out, agency & a);

#endif
