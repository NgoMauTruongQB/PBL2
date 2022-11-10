#include "Goods.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
//class Import
Import::Import(){
    this->Batch = "";
    this->Import_amount = 0;
    this->Import_cost = 0;
}
Import::Import(string batch, int amount, float cost, Date date)
{
    this->Batch = batch;
    this->Import_amount = amount;
    this->Import_cost = cost;
    this->Import_date = date;
}
void Import::Import_in()
{
    // cout << " ===== ENTER INFORMATION IMPORT ===== " << endl;
    cout << " Batch: "; cin >> this->Batch;
    cout << " Amount: "; cin >> this->Import_amount;
    cout << " Cost: "; cin >> this->Import_cost;
    this->Import_date.Input();
    cout << endl;
}
void Import::Import_out()
{
    cout << " ===== ALL INFORMATION IMPORT ===== " << endl;
    cout << " Batch: " << this->Batch << ",";
    cout << " Amount: " << this->Import_amount << ", ";
    cout << " Cost: " << this->Import_cost << ", ";
    cout << " Date:"; this->Import_date.Output();
    cout << endl;
}
void Import::Set_batch(string batch)
{
    this->Batch = batch;
}
void Import::Set_import_cost(float cost)
{
    this->Import_cost = cost;
}
void Import::Set_import_date(string date)
{
    (this->Import_date).Input(date);
}
string Import::Get_Batch()
{
    return this->Batch;
}
float Import::Get_cost()
{
    return this->Import_cost;
}
int Import::Get_import_amount()
{
    return this->Import_amount;
}
string Import::Get_Impdate_str()
{
    return this->Import_date.Get_date_str();
}
Date Import::Get_import_date()
{
    return this->Import_date;
}
Import::~Import(){
}

//class Goods
Goods::Goods()
{
    this->ID = "";
    this->Goods_name = "";
    this->Type = "";
    this->Origin = "";
    this->Status = 0;
}
Goods::Goods(string name, string type, string origin, Date exp, int status)
{
    // this->Set_id();
    this->Goods_name = name;
    this->Type = type;
    this->Origin = origin;
    this->EXP = exp;
    this->Status = status;
}
void Goods::Input(string distance)
{
    cout << distance << " ----- ENTER GOODS INFORMATION ----- " << endl;
    cout << distance << " Batch: "; getline(cin, this->Batch); Standardized(this->Batch);
    cout << distance << " Name: "; cin.ignore(); getline(cin,this->Goods_name); Standardized(this->Goods_name);
    cout << distance << " Origin: "; getline(cin,this->Origin); Standardized(this->Origin);
    cout << distance << " Type: "; getline(cin, this->Type); Standardized(this->Type); 
    cout << distance << " EXP"; this->EXP.Input();
    cout << distance << " Import amount: "; cin >> this->Import_amount;
    cout << distance << " Total cost: "; cin >> this->Import_cost;
    cout << distance << " Import date"; this->Import_date.Input();
    cout << distance << " ----------------------------------- " << endl;
}
void Goods::Input_from_file(fstream &file_in)
{
    string date;
    getline(file_in, this->Batch, ',');
    Standardized(this->Batch);
    getline(file_in, this->Goods_name, ',');
    Standardized(this->Goods_name);
    getline(file_in, this->Origin, ',');
    Standardized(this->Origin);
    getline(file_in, this->Type, ',');
    Standardized(this->Type);
    getline(file_in, date, ',');
    this->EXP.Input(date);
    file_in >> this->Import_amount; file_in.ignore();
    file_in >> this->Import_cost; file_in.ignore();
    getline(file_in, date, '\n');
    this->Import_date.Input(date);
}
void Goods::Output(string distance)
{
    cout << setw(3) << this->Batch << " |"
         << setw(18) << this->Goods_name << "      |"
         << setw(14) << this->Origin << "     |"
         << setw(9) << this->Type << " |"
         << "    " << this->EXP.Get_date_str() << "  |";
    cout << setw(9) << this->Import_amount << " |"
         << "  " << this->Import_date.Get_date_str() << " |"
         << setw(10) << this->Import_cost / this->Import_amount << "    |" << endl;
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
    temp = (this->Import_date).Get_date_str();
    temp.erase(2, 1);
    temp.erase(4, 1);
    this->ID += temp;
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
    this->EXP.Input(exp);
}
void Goods::Set_amount(int amount)
{
    this->Import_amount = amount;
}
void Goods::Set_status(int status)
{
    this->Status = status;
}
string Goods::Get_id()
{
    return this->ID;
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
string Goods::Get_EXP_str()
{
    return this->EXP.Get_date_str();
}
Date Goods::Get_EXP()
{
    return this->EXP;
}
int Goods::Get_status()
{
    return this->Status;
}
void Goods::Set_amount_after_export(const int& amount)
{
    if (amount > this->Import_amount) throw string("Amount is out of range");
    else
        this->Import_amount -= amount;
}
const Goods& Goods::operator=(const Goods& other)
{
    this->ID = other.ID;
    this->Batch = other.Batch;
    this->Goods_name = other.Goods_name;
    this->Type = other.Type;
    this->Origin = other.Origin;
    this->EXP = other.EXP;
    this->Status = other.Status;
    this->Import_amount = other.Import_amount;
    this->Import_cost = other.Import_cost;
    this->Import_date = other.Import_date;
    return (*this);
}
Goods::~Goods(){
}

//class Export
Export::Export()
{
    this->Export_amount = 0;
    this->Export_cost = 0;
}
Export::Export(int amount, float cost, Date date)
{
    this->Export_amount = amount;
    this->Export_cost = cost;
    this->Export_date = date;
}
Date& Export::Get_export_date()
{
    return this->Export_date;
}
float Export::Get_export_cost()
{
    return this->Export_cost;
}
int Export::Get_export_amount()
{
    return this->Export_amount;
}
int Export::Set_goods_amount_again(const int& amount)
{
    return (this->Export_amount > amount) ? -1 : (amount - this->Export_amount);
}
void Export::Export_in(string distance, const float ogrCost, float shipCost)
{
    float cost;
    cout << distance << " ===== ENTER EXPORT INFORMATION ===== " << endl;
    cout << "\n Enter amount: "; cin >> this->Export_amount; cout << endl;
    
    this->Export_date.Input();
    float minSellCost = (this->Export_amount) * ogrCost + (this->Export_amount) * ogrCost * 0.05 + shipCost;
    cout << " Minimum selling price: " << minSellCost << endl;
    float listPrice = minSellCost + (minSellCost) * 0.2;
    cout << " List price: " << listPrice << endl;
    cout << " Enter selling price: "; cin >> cost;
    if(cost <= listPrice)
    {
        cout << "\n Are you sure? ";
        cout << "\n 1.Yes.";
        cout << "\n 2.No and change." << endl;
        int select;
        do{
            cin >> select;
            cout << "\n Select again ...." << endl;
        } while (select < 1 || select > 2);
        switch (select)
            {
            case 1:
                this->Export_cost = cost;
                break;
            case 2:
                cout << "\n Enter selling price again: "; 
                cin >> this->Export_cost;
            }
    }
    cout << "\n Selling price: " << this->Export_cost << endl;
}
void Export::Export_out()
{
    cout << "===== EXPORT INFORMATION =====" << endl;
    cout << " Amount: " << this->Export_amount << endl;
    cout << " Cost: " << this->Export_cost << endl;
    cout << " Date: "; this->Export_date.Output();
}
Export::~Export(){
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
