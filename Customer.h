#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Customer
{
private:
	string Name;
	string Address;
	string PhoneNumber;
	bool Condition;
public:
	Customer(string = "", string = "", string = "", bool = false);
	~Customer();
	void Customer_in();
	//void Customer_out();
	string Get_name();
	string Get_address();
	string Get_PhoneNumber();
	string Get_Condition();
	void Set_Name(string);
	void Set_Address(string);
	void Set_PhoneNumber(string);
	void Set_Condition(bool);
};

class ListCustomer : public Customer
{
private:
	vector<Customer> list;
	int AmountCustomer;
public:
	ListCustomer(int amount = 0);
	~ListCustomer();
	void ListCustomer_in(int n);
	void List_out();
	int Get_AmountCustomer();
};