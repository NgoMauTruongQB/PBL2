#pragma once
#include <string>
#include <vector>
#include "Goods.h"
#include "Bill.h"
using namespace std;
class ListBill;
class Customer
{
private:
	string ID;
	string Name;
	string Address;
	string PhoneNumber;
    string Bill_ID;
public:
	Customer(string = "", string = "", string = "", string = "", string = "");
	~Customer();
	//void Customer_out();
	void Set_Name(string);
	void Set_Address(string);
	void Set_PhoneNumber(string);
	void Set_Bill_ID(string);
	string Get_ID();
	string Get_name();
	string Get_address();
	string Get_PhoneNumber();
	string Get_Bill_ID();
	friend istream& operator>>(istream&, Customer&);
	friend ostream& operator<<(ostream&, const Customer&);
};

class ListCustomer
{
private:
	vector<Customer> List;
public:
	~ListCustomer();
	bool Check_valid_ID(string);
	Customer& operator[](int);
	int Find_id(string);
	Customer& Get_customer(string);
	void Add(const Customer&);
	void Update(string);
	void Delete(string);
	void Find();
	void Show_information(ListBill&, string = "");
};