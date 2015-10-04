// Include of Librarys
#include "person.h"

// Constructor
person::person(string name, string birthDate, string address, string postalCode,
		nif NIF, long phone) {
	this->name = name;
	date auxDate(birthDate);
	this->birthDate = auxDate;
	this->address = address;
	this->postalCode = postalCode;
	nif aux(NIF);
	this->NIF = aux;
	this->phone = phone;
}

// get the id Number
long person::getID() {
	return id;
}

// get the name
string person::getName() {
	return name;
}

// get the birth date
string person::getBirthDate() {
	return birthDate.print();
}

// get the NIF number
long person::getNIF() {
	return NIF.getNumber();
}

// get the address
string person::getAddress() {
	return address;
}

// get the postal code
string person::getPostalCode() {
	return postalCode;
}

// get the phone number
long person::getPhone() {
	return phone;
}

// Set the id Number
void person::setID(long new_id) {
	id = new_id;
}

// set the name
void person::setName(string name) {
	this->name = name;
}

// set birth date
void person::setBirthDate(date data) {
	this->birthDate = data;
}

// set the Address
void person::setAddress(string address) {
	this->address = address;
}

// set the postal code
void person::setPostalCode(string pcode) {
	this->postalCode = pcode;
}

// set the nif number
void person::setNIF(nif a) {
	this->NIF = a;
}

// set the phone number
void person::setPhone(long phone) {
	this->phone = phone;
}

// Initializing the static variable "total"
long customer::nextCustomerID = 0;

// Constructor
customer::customer(string name, string birthDate, string address,
		string postalCode, nif NIF, long phone) :
		person(name, birthDate, address, postalCode, NIF, phone) {
	this->id = nextCustomerID;
	nextCustomerID++;
}

// Overloaded constructor - for use with loadFile
customer::customer(string name, string birthDate, string address,
		string postalCode, nif NIF, long phone, unsigned int ID) :
		person(name, birthDate, address, postalCode, NIF, phone) {
	this->id = ID;
}

// Constructor
particular::particular(string name, string birthDate, string address,
		string postalCode, nif NIF, long BI, long phone) :
		customer(name, birthDate, address, postalCode, NIF, phone) {
	this->BI = BI;
}

// Overloaded constructor
particular::particular(string name, string birthDate, string address,
		string postalCode, nif NIF, long BI, long phone, unsigned int ID) :
		customer(name, birthDate, address, postalCode, NIF, phone, ID) {
	this->BI = BI;
}

// Get the type of customer. This would be very useful in reading and saving data
string particular::getType() const {
	return "particular";
}

// Constructor
company::company(string name, string birthDate, string address,
		string postalCode, nif NIF, long phone, double capital) :
		customer(name, birthDate, address, postalCode, NIF, phone) {
	this->capital = capital;
}

// overloaded constructor
company::company(string name, string birthDate, string address,
		string postalCode, nif NIF, long phone, double capital, unsigned int ID) :
		customer(name, birthDate, address, postalCode, NIF, phone, ID) {
	this->capital = capital;
}

// set the capital
void company::setCapital(double new_capital) {
	capital = new_capital;
}

// get the capital
double company::getCapital() {
	return capital;
}

// Get the type of customer, that is "company"
string company::getType() const {
	return "company";
}

// Static variable initialization
long employee::nextEmployeeID = 0;

// Constructor
employee::employee(string name, string birthDate, string address,
		string postalCode, nif NIF, long BI, long phone, double salary,
		string post, string qualifications) :
		person(name, birthDate, address, postalCode, NIF, phone) {
	this->BI = BI;
	this->salary = salary;
	this->post = post;
	this->qualifications = qualifications;
	this->id = nextEmployeeID; // ID starts in 0
	nextEmployeeID++;
}
// Overloaded Constructor
employee::employee(string name, string birthDate, string address,
		string postalCode, nif NIF, long BI, long phone, double salary,
		string post, string qualifications, unsigned int ID) :
		person(name, birthDate, address, postalCode, NIF, phone) {
	this->BI = BI;
	this->salary = salary;
	this->post = post;
	this->qualifications = qualifications;
	this->id = ID;
}

// Get the salary
double employee::getSalary() {
	return salary;
}

// Get the post
string employee::getPost() {
	return post;
}

// Get the qualifications
string employee::getQualifications() {
	return qualifications;
}

// Set the post
void employee::setPost(string new_post) {
	this->post = new_post;
}

// Set the qualifications
void employee::setQualifications(string q) {
	this->qualifications = q;
}

// Set the salary
void employee::setSalary(double s) {
	this->salary = s;
}
