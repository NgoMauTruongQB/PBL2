#include "Customer.h"
#include "Date.h"
#include <string>
#include <iostream>
// #include "NumberDuck.h"
// #include <sstream>
// #include <stdio.h>

// using namespace NumberDuck;
using namespace std;

//========================================= Class Customer ============================================

Customer::Customer(string id, string name, string address, string phone, string bill_id)
{
	this->ID = id;
    this->Name = name;
    this->Address = address;
    this->PhoneNumber = phone;
	this->Bill_ID = bill_id;
}
Customer::~Customer()
{
}
// void Customer::Customer_in()
// {
// 	cout << "Name's customer: "; getline(cin, this->Name);
// 	cout << "Address: "; getline(cin, this->Address);
// 	cout << "Phone Number: "; getline(cin, this->PhoneNumber);
// 	cout << "Condition: "; cin >> this->Condition;
// }
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
void Customer::Set_Bill_ID(string billID)
{
	this->Bill_ID = billID;
}
string Customer::Get_ID()
{
	return this->ID;
}
string Customer::Get_name()
{
	return this->Name;
}
string Customer::Get_address()
{
	return this->Address;
}
string Customer::Get_PhoneNumber()
{
	return this->PhoneNumber;
}
string Customer::Get_Bill_ID()
{
	return this->Bill_ID;
}
istream& operator>>(istream& in, Customer& c)
{
	cout << distance() << "--------- Customer Information --------" << endl;
	cout << distance() << "ID: "; getline(in, c.ID);
	cout << distance() << "Name's customer: "; getline(in, c.Name); Standardized(c.Name);
	cout << distance() << "Address: "; getline(in, c.Address);
	cout << distance() << "Phone Number: "; getline(in, c.PhoneNumber);
	cout << distance() << "----------------- END -----------------" << endl;
	return in;
}
ostream& operator<<(ostream& out, const Customer& c)
{
	out << " " << setw(12) << c.ID << " |" << " " << setw(24) << c.Name << " |"
	    << " " << setw(25) << c.Address << " |" << "  " << setw(10) << c.PhoneNumber << "  |"
		<< " " << setw(12) << c.Bill_ID << " |";
	return out;
}


// =================================== Class ListCustomer ==========================================
ListCustomer::~ListCustomer()
{
}
bool ListCustomer::Check_valid_ID(string id)
{
	for (int i = 0; i < this->List.size(); i++)
	{
		if ((*this)[i].Get_ID().compare(id) == 0)
			return false;
	}
	return true;
}
Customer& ListCustomer::operator[](int index)
{
	if (index > this->List.size() || index < 0)
	{
		static Customer c;
		return c;
	}
	else return this->List[index];
}
int ListCustomer::Find_id(string id)
{
	for (int i = 0; i < this->List.size(); i++)
	{
		if ((*this)[i].Get_ID().compare(id) == 0)
		{
			return i;
		}
	}
	return -1;
}
Customer& ListCustomer::Get_customer(string billID)
{
	for (int i = 0; i < this->List.size(); i++)
	{
		if ((*this)[i].Get_Bill_ID().compare(billID) == 0)
		{
			return (*this)[i];
		}
	}
	static Customer temp;
	return temp;
}
void ListCustomer::Add(const Customer& _new_customer)
{
	if (this->Check_valid_ID(const_cast<Customer&>(_new_customer).Get_ID())) this->List.push_back(_new_customer);
	else
		throw string("Customer of ID is not valid...");
}
void ListCustomer::Delete(string id)
{
	int index = this->Find_id(id);
    if (index == -1)
    {
        throw string("ID is not found...");
    }
	else
	{
		this->List.erase(this->List.begin() + index);
	}	
}
void ListCustomer::Show_information(ListBill& lb, string id)
{
	if (this->List.empty() == true || (id.compare("") != 0 && this->Find_id(id) == -1)) 
    {
        cout << distance() << "Don't have this customer!" << endl;
    }
	else if (id.compare("") == 0)
	{
		cout <<    distance() << " ______________________________________________________________________________________________________________________________________ " << endl
				<< distance() << "                                                       ALL CUSTOMER INFORMATION                                                         " << endl
				<< distance() << " -------------------------------------------------------------------------------------------------------------------------------------- " << endl
				<< distance() << "| STT |      ID      |      Ten khach hang      |          Dia chi          |      SDT     |    Ma hoa don    | Trinh trang thanh toan |" << endl
				<< distance() << " ______________________________________________________________________________________________________________________________________ " << endl;
		for (int i = 0; i < this->List.size(); i++) 
		{
			cout << distance() << "|" << setw(4) << i + 1 << " |";
			cout << (*this)[i];
			cout << "    " << setw(16);
			(lb[lb.Find_id((*this)[i].Get_Bill_ID())].Get_PayStatus()) ? cout << "Da thanh toan" : cout << "Chua thanh toan";
			cout << "    |" << endl;
			cout << distance() << " ______________________________________________________________________________________________________________________________________ " << endl;
		}
		cout << distance() << " ----------------------------------------------------------------- END ---------------------------------------------------------------- " << endl;
	}
	else
	{
		cout <<    distance() << " ______________________________________________________________________________________________________________________________________ " << endl
				<< distance() << "                                                          CUSTOMER INFORMATION                                                          " << endl
				<< distance() << " -------------------------------------------------------------------------------------------------------------------------------------- " << endl
				<< distance() << "| STT |      ID      |      Ten khach hang      |          Dia chi          |      SDT     |    Ma hoa don    | Trinh trang thanh toan |" << endl
				<< distance() << " ______________________________________________________________________________________________________________________________________ " << endl;
		int i = this->Find_id(id);
		cout << distance() << "|" << setw(4) << 1 << " |";
		cout << (*this)[i];
		cout << "    " << setw(16);
		(lb[lb.Find_id((*this)[i].Get_Bill_ID())].Get_PayStatus()) ? cout << "Da thanh toan" : cout << "Chua thanh toan";
		cout << "    |" << endl;
		cout << distance() << " ______________________________________________________________________________________________________________________________________ " << endl;
		cout << distance() << " ----------------------------------------------------------------- END ---------------------------------------------------------------- " << endl;
	}
	
}
// void ListCustomer::List_out()
// {
// 	ListCustomer a;
// 	Workbook workbook("");
// 	Worksheet* pWorksheet = workbook.GetWorksheetByIndex(0);

// 	for (uint16_t i = 0; i < this->Get_AmountCustomer(); i++)
// 	{
// 		Cell* pCell = pWorksheet->GetCell(0, i);
// 		pCell->SetFloat(i + 1);
// 		//pCell->SetFloat(i * 2.34f);
// 	}
// 	int j = 0;
// 	for (Customer i : this->list)
// 	{
// 		string s;
// 		s = i.Get_name();

// 		char* g = const_cast<char*>(s.c_str());
// 		pWorksheet->GetCell(1, j)->SetString(g);
// 		s = i.Get_address();
// 		g = const_cast<char*>(s.c_str());
// 		pWorksheet->GetCell(2, j)->SetString(g);
// 		s = i.Get_PhoneNumber();
// 		g = const_cast<char*>(s.c_str());
// 		pWorksheet->GetCell(3, j)->SetString(g);
// 		s = i.Get_Condition();
// 		g = const_cast<char*>(s.c_str());
// 		pWorksheet->GetCell(4, j)->SetString(g);
		
// 	}
// 	workbook.Save("ListCustomer.xls");

// 	Workbook* pWorkbookIn = new Workbook("");
// 	if (pWorkbookIn->Load("ListCustomer.xls"))
// 	{
// 		Worksheet* pWorksheetIn = pWorkbookIn->GetWorksheetByIndex(0);
// 		Cell* pCellIn = pWorksheetIn->GetCell(2, 1);
// 		printf("Formula: %s\n", pCellIn->GetFormula());
// 	}
// }