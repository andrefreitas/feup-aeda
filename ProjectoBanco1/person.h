#ifndef PERSON_H_
#define PERSON_H_
// Include of Libraries
#include "types.h"
#include <string>
#include "nif.h"
using namespace std;
//!  Super-Class Person
/*! This class defines an object of type person with the typical data like address, nif, cellphone, etc
 */
class person {
protected:
	//! name of the customer
	string name;
	//! the unique identifier
	unsigned int id;
	//! the Birth Date
	date birthDate;
	//! the address
	string address;
	//! the postal code
	string postalCode;
	//! the NIF
	nif NIF;
	//! the phone number
	long phone;
public:
	// ******************************** Constructors
	//! default constructor
	person() {
	}
	//! Constructor
	/*!
	 \param name the name of the person
	 \param birthDate the birth Date
	 \param address the address string
	 \param postalCode the postal code string
	 \param NIF the nif number
	 \param phone the phone number
	 */
	person(string name, string birthDate, string address, string postalCode,
			nif NIF, long phone);
	// ******************************** Get Methods
	//! get the id
	virtual long getID();
	//! get the name
	virtual string getName();
	//! get the birth date

	virtual string getBirthDate();
	//! get the NIF number
	virtual long getNIF();
	//! get the addres
	virtual string getAddress();
	//! get the postal code
	virtual string getPostalCode();
	//! get the phone number
	virtual long getPhone();
	// ******************************** Set Methods
	//! set the ID
	virtual void setID(long new_id);
	//! set the name
	virtual void setName(string name);
	//! set birth date
	virtual void setBirthDate(date data);
	//! set the Address
	virtual void setAddress(string address);
	//! set the postal code
	virtual void setPostalCode(string pcode);
	//! set the nif number
	virtual void setNIF(nif a);
	//! set the phone number
	virtual void setPhone(long phone);
	//! ovearloading of operator ==
	virtual bool operator==(unsigned int id) {
		return this->id == id;
	}

};

//!  Sub-Class customer
/*! This class defines a customer of the bank
 */
class customer: public person {
public:
	// ******************************** Constructors
	//! empty constructor
	customer() {
	}
	//! Constructor
	/*!
	 \param name the name of the person
	 \param birthDate the birth Date
	 \param address the address string
	 \param postalCode the postal code string
	 \param NIF the nif number
	 \param phone the phone number
	 */
	customer(string name, string birthDate, string address, string postalCode,
			nif NIF, long phone);
	//! overloaded constructor
	/*!
	 \param name the name of the person
	 \param birthDate the birth Date
	 \param address the address string
	 \param postalCode the postal code string
	 \param NIF the nif number
	 \param phone the phone number
	 \param the id of the customer
	 */
	customer(string name, string birthDate, string address, string postalCode,
			nif NIF, long phone, unsigned int ID);
	// ******************************** Get Methods
	//! WARNING: NECESSARY TO BASE POINTERS
	virtual string getType() const {
		return "";
	}
	//! Get the total of customers
	static long getTotalcustomers();
	//! WARNING: NECESSARY TO BASE POINTERS
	virtual double getCapital() {
		return 0;
	}
	//! WARNING: NECESSARY TO BASE POINTERS
	virtual long getBI() {
		return 0;
	}
	// ******************************** Set Methods
	//! Set the BI
	virtual void setBI(long BI) {
	}
	//! the total number of customers to use for id
	static long nextCustomerID;
	//! set capital
	virtual void setCapital(double) {
	}

};

//!  Sub-Class Particular
/*! This class defines a particular customer, know as an individual person
 */

class particular: public customer {
private:
	//! BI Number
	long BI;
public:
	// ******************************** Constructors
	//! empty constructor
	particular() {
	}
	//! Constructor
	/*!
	 \param name the name of the person
	 \param birthDate the birth Date
	 \param address the address string
	 \param postalCode the postal code string
	 \param NIF the nif number
	 \param phone the phone number
	 */
	particular(string name, string birthDate, string address, string postalCode,
			nif NIF, long BI, long phone);
	//! overloaded constructor
	/*!
	 \param name the name of the person
	 \param birthDate the birth Date
	 \param address the address string
	 \param postalCode the postal code string
	 \param NIF the nif number
	 \param phone the phone number
	 \param ID the id of the particular
	 */
	particular(string name, string birthDate, string address, string postalCode,
			nif NIF, long BI, long phone, unsigned int ID);
	// ******************************** Get Methods
	//! Get the type of customer, that is "particular"
	string getType() const;
	//! Get the BI Number
	long getBI() {
		return BI;
	}
	// ******************************** Set Methods
	//! Set the BI
	void setBI(long BI) {
		this->BI = BI;
	}
};

//!  Sub-Class Company
/*! This class defines a customer of type company. Note: the birthdate is the date of the company creation
 */
class company: public customer {
	double capital;
public:
	// ******************************** Constructors
	//! empty constructor
	company() {
	}
	//! Constructor
	/*!
	 \param name the name of the person
	 \param birthDate the birth Date
	 \param address the address string
	 \param postalCode the postal code string
	 \param NIF the nif number
	 \param phone the phone number
	 \param capital the capital of the company
	 */
	company(string name, string birthDate, string address, string postalCode,
			nif NIF, long phone, double capital);
	//! overloaded constructor
	/*!
	 \param name the name of the person
	 \param birthDate the birth Date
	 \param address the address string
	 \param postalCode the postal code string
	 \param NIF the nif number
	 \param phone the phone number
	 \param capital the capital of the company
	 \param the id of the company
	 */
	company(string name, string birthDate, string address, string postalCode,
			nif NIF, long phone, double capital, unsigned int ID);
	// ******************************** Set Methods
	//! set the capital
	void setCapital(double new_capital);
	// ******************************** Get Methods
	//! get the capital
	double getCapital();
	//! Get the type of customer, that is "company"
	string getType() const;
};

//!  Sub-Class Employee
/*! This class defines an employee of the bank that have the access to the bank management
 */
class employee: public person {
	//! Monthly salary of the employee
	double salary;
	//! Post in company
	string post;
	//! Employee qualifications
	string qualifications;
	//! BI Number
	long BI;
public:
	// ******************************** Constructors
	//! Empty constructor
	employee() {
	}
	//! Constructor
	/*!
	 \param name the name of the person
	 \param birthDate the birth Date
	 \param address the address string
	 \param postalCode the postal code string
	 \param NIF the nif number
	 \param phone the phone number
	 \param salary the monthly salary of the person
	 \param post the post in the company
	 \param qualifications the qualifications of the employee
	 */
	employee(string name, string birthDate, string address, string postalCode,
			nif NIF, long BI, long phone, double salary, string post,
			string qualifications);
	//! overloaded constructor
	/*!
	 \param name the name of the person
	 \param birthDate the birth Date
	 \param address the address string
	 \param postalCode the postal code string
	 \param NIF the nif number
	 \param phone the phone number
	 \param salary the monthly salary of the person
	 \param post the post in the company
	 \param qualifications the qualifications of the employee
	 \param the id of the employee
	 */
	employee(string name, string birthDate, string address, string postalCode,
			nif NIF, long BI, long phone, double salary, string post,
			string qualifications, unsigned int ID);
	// ******************************** Get Methods
	//! Get the salary
	double getSalary();
	//! Get the post
	string getPost();
	//! Get the qualifications
	string getQualifications();
	//! Get the total of employees
	static long getTotalEmployees();
	//! Get the BI
	long getBI() {
		return BI;
	}
	// ******************************** Set Methods
	//! Set the post
	void setPost(string new_post);
	//! Set the qualifications
	void setQualifications(string q);
	//! Set the salary
	void setSalary(double s);
	//! Set the BI
	void setBI(long BI) {
		this->BI = BI;
	}
	//! Total number of employees
	static long nextEmployeeID;
};

#endif /* PERSON_H_ */
