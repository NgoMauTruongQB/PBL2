#include "Goods.h"
#include <iostream>
#include <fstream>
#include <iomanip>
Goods::Goods()
{
    this->ID = "";
    this->Batch = "";
    this->Goods_name = "";
    this->Type = "";
    this->Origin = "";
    this->Amount = 0;
    this->Cost = 0;
    this->Sale_cost = 0;
    this->Status = 0;
}
Goods::Goods(string ID, string batch, string name, string type, string origin, Date exp, int amount, Date imp_date, float cost, float sale_cost, Date exp_date, int status)
{
    this->ID = ID;
    this->Batch = batch;
    this->Goods_name = name;
    this->Type = type;
    this->Origin = origin;
    this->EXP = exp;
    this->Amount = amount;
    this->Import_date = imp_date;
    this->Cost = cost;
    this->Sale_cost = sale_cost;
    this->Export_date = exp_date;
    this->Status = status;
}
void Goods::Input()
{
    cout << distance() << " ----- ENTER GOODS INFORMATION ----- " << endl;
    cout << distance() << " Batch: "; getline(cin, this->Batch); Standardized(this->Batch);
    cout << distance() << " Name: "; getline(cin,this->Goods_name); Standardized(this->Goods_name);
    cout << distance() << " Origin: "; getline(cin,this->Origin); Standardized(this->Origin);
    cout << distance() << " Type: "; getline(cin, this->Type); Standardized(this->Type); 
    cout << distance() << " EXP"; this->EXP.Input();
    cout << distance() << " Import amount: "; cin >> this->Amount;
    cout << distance() << " Total cost: "; cin >> this->Cost; cin.ignore();
    cout << distance() << " Import date"; this->Import_date.Input();
    cout << distance() << " ----------------------------------- " << endl;
}
void Goods::Input_from_file(fstream &file_in)
{
    string date; 
    float cost;
    getline(file_in, this->Batch, ',');
    Standardized(this->Batch);
    getline(file_in, this->Goods_name, ',');
    Standardized(this->Goods_name);
    getline(file_in, this->Origin, ',');
    Standardized(this->Origin);
    getline(file_in, this->Type, ',');
    Standardized(this->Type);
    getline(file_in, date, ',');
    this->EXP.str_to_Date(date);
    file_in >> this->Amount; file_in.ignore();
    file_in >> cost;
    this->Set_cost(cost/this->Amount);
    file_in.ignore();
    getline(file_in, date, '\n');
    this->Import_date.str_to_Date(date);
}
void Goods::Output()
{
    cout << setw(3) << this->Batch << " |"
         << setw(18) << this->Goods_name << "      |"
         << setw(14) << this->Origin << "     |"
         << setw(9) << this->Type << " |"
         << "    " << this->EXP.to_String() << "  |";
    cout << setw(9) << this->Amount << " |"
         << "  " << this->Import_date.to_String() << " |"
         << setw(10) << this->Cost << "    |" << endl;
}
void Goods::Set_id()
{
    string temp = "";
    this->ID = "";
    this->ID += this->Batch;
    temp += (this->Goods_name)[0];
    for (int i = 1; i < (this->Goods_name).length(); i++) 
    {
        if ((this->Goods_name)[i] == ' ')
            temp += (this->Goods_name)[i+1];
    }
    this->ID += temp;
    temp = (this->EXP).to_String();
    temp.erase(2, 1);
    temp.erase(4, 1);
    this->ID += temp;
}
void Goods::Set_batch(string batch)
{
    this->Batch = batch;
}
void Goods::Set_goods_name(string name)
{
    this->Goods_name = name;
}
void Goods::Set_type(string type)
{
    this->Type = type;
}
void Goods::Set_origin(string origin)
{
    this->Origin = origin;
}
void Goods::Set_EXP(string exp)
{
    this->EXP.str_to_Date(exp);
}
void Goods::Set_amount(int amount)
{
    this->Amount = amount;
}
void Goods::Set_import_date(string impDate)
{
    this->Import_date.str_to_Date(impDate);
}
void Goods::Set_cost(float cost)
{
    this->Cost = cost;
}
void Goods::Set_sale_cost()
{
    this->Sale_cost = (this->Cost + this->Cost*5/100);
}
void Goods::Set_export_amount(int expAmount)
{
    this->Export_amount = expAmount;
}
void Goods::Set_export_date(string expDate)
{
    this->Export_date.str_to_Date(expDate);
}
void Goods::Set_status(int status)
{
    this->Status = status;
}
string Goods::Get_id()
{
    return this->ID;
}
string Goods::Get_batch()
{
    return this->Batch;
}
string Goods::Get_good_name()
{
    return this->Goods_name;
}
string Goods::Get_type()
{
    return this->Type;
}
string Goods::Get_origin()
{
    return this->Origin;
}
Date& Goods::Get_EXP()
{
    return this->EXP;
}
int Goods::Get_amount()
{
    return this->Amount;
}
Date& Goods::Get_import_date()
{
    return this->Import_date;
}
float Goods::Get_cost()
{
    return this->Cost;
}
float Goods::Get_sale_cost()
{
    return this->Sale_cost;
}
int Goods::Get_export_amount()
{
    return this->Export_amount;
}
Date& Goods::Get_export_date()
{
    return this->Export_date;
}
int Goods::Get_status()
{
    return this->Status;
}
// void Goods::Set_amount_after_export(const int& amount)
// {
//     if (amount > this->Import_amount) throw string("Amount is out of range");
//     else
//         this->Import_amount -= amount;
// }
const Goods& Goods::operator=(const Goods& other)
{
    this->ID = other.ID;
    this->Batch = other.Batch;
    this->Goods_name = other.Goods_name;
    this->Type = other.Type;
    this->Origin = other.Origin;
    this->EXP = other.EXP;
    this->Amount = other.Amount;
    this->Import_date = other.Import_date;
    this->Cost = other.Cost;
    this->Sale_cost = other.Sale_cost;
    this->Export_date = other.Export_date;
    this->Status = other.Status;
    return (*this);
}
Goods::~Goods(){
}
void Standardized(string &s)
{
    while (!(s.empty()) && s[0] == ' ') s.erase(0, 1);
    while (!(s.empty()) && s[s.length() - 1] == ' ') s.erase(s.length() - 1, 1);
    int i = 1;
    while (!(s.empty()) && i < s.length())
    {
        if (s[i] == ' ' && s[i + 1] == ' ') s.erase(i+1, 1);
        else i++;
    }
    s[0] = toupper(s[0]);
    for (int i = 1; i < s.length(); i++)
    {
        if (s[i] == ' ') 
        {
            s[i+1] = toupper(s[i+1]);
        }
        else if (s[i-1] != ' ') s[i] = tolower(s[i]);
    }
}
void Swap(Goods& a, Goods& b)
{
    Goods temp;
    temp = a;
    a = b;
    b = temp;
}
