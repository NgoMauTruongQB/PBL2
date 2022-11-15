#pragma once
#include "Customer.h"
#include "NumberDuck.h"
#include <sstream>
#include <string>
#include <stdio.h>

using namespace NumberDuck;
using namespace std;

//========================================= Class Customer ============================================

Customer::Customer(string name, string add, string phone, bool condition)
{
	this->Name = name;
	this->Address = add;
	this->PhoneNumber = phone;
	this->Condition = condition;
}

Customer::~Customer()
{
}

string Customer::Get_name()
{
	return this->Name;
}

void Customer::Customer_in()
{
	cout << "Name's customer: "; getline(cin, this->Name);
	cout << "Address: "; getline(cin, this->Address);
	cout << "Phone Number: "; getline(cin, this->PhoneNumber);
	cout << "Condition: "; cin >> this->Condition;
}

string Customer::Get_address()
{
	return this->Address;
}

string Customer::Get_PhoneNumber()
{
	return this->PhoneNumber;
}

string Customer::Get_Condition()
{
	if (this->Condition == 1)
		return "Hoan thanh";
	return "Chua hoan thanh";
}

void Customer::Set_Name(string name)
{
	this->Name = name;
}

void Customer::Set_Address(string add)
{
	this->Address = add;
}

void Customer::Set_PhoneNumber(string phone)
{
	this->PhoneNumber = phone;
}

void Customer::Set_Condition(bool check)
{
	this->Condition = check;
}

// =================================== Class ListCustomer ==========================================

ListCustomer::ListCustomer(int amount )
{
	this->AmountCustomer = amount;
}

ListCustomer::~ListCustomer()
{
}

void ListCustomer::ListCustomer_in(int n)
{
	Customer a;
	this->AmountCustomer = n;
	for (int i = 0; i < n; i++)
	{
		a.Customer_in();
		cin.ignore();
		this->list.push_back(a);
	}
}

void ListCustomer::List_out()
{
	ListCustomer a;
	Workbook workbook("");
	Worksheet* pWorksheet = workbook.GetWorksheetByIndex(0);

	for (uint16_t i = 0; i < this->Get_AmountCustomer(); i++)
	{
		Cell* pCell = pWorksheet->GetCell(0, i);
		pCell->SetFloat(i + 1);
		//pCell->SetFloat(i * 2.34f);
	}
	int j = 0;
	for (Customer i : this->list)
	{
		string s;
		s = i.Get_name();

		char* g = const_cast<char*>(s.c_str());
		pWorksheet->GetCell(1, j)->SetString(g);
		s = i.Get_address();
		g = const_cast<char*>(s.c_str());
		pWorksheet->GetCell(2, j)->SetString(g);
		s = i.Get_PhoneNumber();
		g = const_cast<char*>(s.c_str());
		pWorksheet->GetCell(3, j)->SetString(g);
		s = i.Get_Condition();
		g = const_cast<char*>(s.c_str());
		pWorksheet->GetCell(4, j)->SetString(g);
		
	}
	workbook.Save("ListCustomer.xls");

	Workbook* pWorkbookIn = new Workbook("");
	if (pWorkbookIn->Load("ListCustomer.xls"))
	{
		Worksheet* pWorksheetIn = pWorkbookIn->GetWorksheetByIndex(0);
		Cell* pCellIn = pWorksheetIn->GetCell(2, 1);
		printf("Formula: %s\n", pCellIn->GetFormula());
	}
}
int ListCustomer::Get_AmountCustomer()
{
	return this->AmountCustomer;
}
