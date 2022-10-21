#include <iostream>
#include <fstream>
#include <string>
#include "Depot.h"
using namespace std;

//--------------------------------------------------------------------------------------------- class Shelf

Shelf::Shelf(string name, string area, int amount)
{
    this->Shelf_Name = name;
    this->Area = area;
    this->RemainingAmount = amount;
}
string Shelf::getShelfName()
{
    return this->Shelf_Name;
};
string Shelf::getArea()
{
    return this->Area;
}
void Shelf::Input(ifstream &in)
{
    //in >> this->Shelf_Name;
    getline(in,this->Shelf_Name, '-');
    //in.ignore(); 
    getline(in, this->Area, '-');
    in >> this->RemainingAmount;
}
void Shelf::Output(int Space_Amount)
{
    string space = "";
    for (int i = 1; i <= Space_Amount; i++) space += " ";
    cout << space << "Shelf of name: " << this->Shelf_Name << endl
         << space << "Area: " << this->Area << endl
         << space << "Remaining Amount: " << this->RemainingAmount << endl;
}
bool Shelf::CheckEmpty()
{
    return (this->RemainingAmount < MAX_OF_AMOUNT_ON_SHELF) ? true :  false;
}

//--------------------------------------------------------------------------------------------------------------- class Depot

Depot::Depot()
{
    this->The_Number_Of_Shelf_In_Depot = 0;
}
Depot::Depot(vector<Shelf> s, int theNumberOfShelfInDepot)
{
    this->All_Of_Shelf = s;
    this->The_Number_Of_Shelf_In_Depot = theNumberOfShelfInDepot;
}
bool Depot::FindArea(string area)
{
    for (string i : this->All_Of_Area)
    {
        if (i.compare(area) == 0) return true;
    }
    return false;
}
void Depot::SortArea()
{
    for (int i = 0; i < this->All_Of_Area.size()-1; i++)
    {
        for (int j = i+1; j < this->All_Of_Area.size(); j++)
        {
            if (this->All_Of_Area[i] > this->All_Of_Area[j])
            {
                string temp = this->All_Of_Area[i];
                this->All_Of_Area[i] = this->All_Of_Area[j];
                this->All_Of_Area[j] = temp;
            }
        }
    }
}
// void Depot::SortShelf()
// {
//     for (int i = 0; i < this->All_Of_Area.size(); i++)
//     {
//         for (int j = 0; i < this->All_Of_Shelf.size()-1; j++)
//         {
//             for (int k = j + 1; k < this->All_Of_Shelf.size(); k++)
//             {
//                 if (this->All_Of_Shelf[j].getShelfName() > this->All_Of_Shelf[k].getShelfName() && (this->All_Of_Shelf[j].getArea()))
//                 {

//                 }
//             }
//         }
//     }
// }
void Depot::Input(ifstream & in)
{
    int count = 0;
    map<string, int> dpp;
    while (!in.eof())
    {
        Shelf s;
        s.Input(in); in.ignore();
        this->All_Of_Shelf.push_back(s);
        dpp[s.getArea()]++;
        if (dpp[s.getArea()] == 1) this->All_Of_Area.push_back(s.getArea());
        count++;
    }
    SortArea();
    this->The_Number_Of_Shelf_In_Depot = count;
}
void Depot::Output(string area, int Space_Amount)
{
    string space = "";
    for (int i = 1; i <= Space_Amount; i++) space += " ";
    if (area.compare("") == 0)
    {
        
        cout << space << "-------- ALL OF SHELVES IN DEPOT --------" << endl;
        for (int i = 0; i < this->All_Of_Area.size(); i++)
        {
            int count = 0;
            cout << space << "- Area: " <<  this->All_Of_Area[i] << endl << endl;
            for (Shelf j : this->All_Of_Shelf)
            {
                if (j.getArea().compare(this->All_Of_Area[i]) == 0)
                {
                    count++;
                    if (count > 1) cout << space << "     ------------------------" << endl;
                    j.Output(Space_Amount + 5);
                }
            }
            cout << endl;
        }
        cout << space << "================= END =================" << endl;
    }
    else if (FindArea(area) == true)
    {
        int count = 0;
        cout << space << "-------- ALL OF SHELVES IN " << area << " AREA ---------" << endl;
        for (Shelf i : this->All_Of_Shelf)
        {
            if (i.getArea().compare(area) == 0)
            {
                count++;
                if (count > 1) cout << space << "          ------------------------" << endl;
                i.Output(Space_Amount + 10);
            }
        }
        cout << space << "================= END =================" << endl;
    }
    else cout << space << "Don't have any shelf '"<< area << "' in depot!" << endl; 
}
void Depot::EmptyPosition(string area, int Space_Amount)
{
    string space = "";
    for (int i = 1; i <= Space_Amount; i++) space += " ";    
    if (area.compare("") == 0)
    {
        cout << space << "-------- ALL EMPTY SHELVES IN DEPOT --------" << endl;
        for (int i = 0; i < this->All_Of_Area.size(); i++)
        {
            int count = 0;
            cout << space << "- Area: " <<  this->All_Of_Area[i] << endl << endl;
            for (Shelf j : this->All_Of_Shelf)
            {
                if (j.getArea().compare(this->All_Of_Area[i]) == 0 && j.CheckEmpty() == true)
                {
                    count++;
                    if (count > 1) cout << space << "     ------------------------" << endl;
                    j.Output(Space_Amount + 5);
                }
            }
            if (count == 0) cout << space << "Don't have any empty shelf in " << this->All_Of_Area[i] << " area!";
            cout << endl;
        }
        cout << space << "================= END =================" << endl;
    }
    else if (FindArea(area) == true)
    {
        int count = 0;
        cout << space << "-------- ALL EMPTY SHELVES IN " << area << " AREA ---------" << endl;
        for (Shelf i : this->All_Of_Shelf)
        {
            if (i.getArea().compare(area) == 0 && i.CheckEmpty() == true)
            {
                count++;
                if (count > 1) cout << space << "          ------------------------" << endl;
                i.Output(Space_Amount + 10);
            }
        }
        if (count == 0) cout << space << "Don't have any empty shelf in this area!";
        cout << space << "================= END =================" << endl;
    }
    else cout << space << "Don't have any shelf '"<< area << "' in depot!" << endl; 
}

//-------------------------------------------------------------------------------------------------------------- class Date

Date::Date(int day, int month, int year)
{
    this->Day = day;
    this->Month = month;
    this->Year = year;
}
void Date::InputDate()
{
    bool true_Date = true;
    do
    {
        if (true_Date == false) cout << "The date is invalid!" << endl;
        string str_date; 
        int count = 0;
        do
        {   
            count++;
            if (count > 1) cout << "ERROR Form!" << endl;
            cin >> str_date;
        }while (str_date[2] != '/' || str_date[5] != '/' || str_date.length() <= 6); // check Date's Form
        this->Day = stoi(str_date.substr(0,2));
        this->Month = stoi(str_date.substr(3, 2));
        this->Year = stoi(str_date.substr(6, str_date.length()));
        true_Date = (this->Year < 1 || this->Month < 1 || this->Month > 12) ? false : true; // check year and month
        if (true_Date == true)
        {
            bool check_Leap_Year = false;
            if (this->Year % 100 == 0 && this->Year % 400 == 0) check_Leap_Year = true; // check leap year
            else if (this->Year % 4 == 0) check_Leap_Year = true;
            switch (this->Month) // check day
            {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    true_Date = (this->Day < 1 || this->Day > 31) ? false : true;
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    true_Date = (this->Day < 1 || this->Day > 30) ? false : true;
                    break;
                default:
                    if (check_Leap_Year == true) true_Date = (this->Day < 1 || this->Day > 29) ? false : true; 
                    else true_Date = (this->Day < 1 || this->Day > 28) ? false : true;
            }
        }
    }while(true_Date == false);
}
void Date::OutputDate()
{
    if (this->Day < 10) cout << "0" << this->Day << "/"; else cout << this->Day << "/";
    if (this->Month < 10) cout << "0" << this->Month << "/"; else cout << this->Month << "/";
    cout << this->Year << endl;;
}

//---------------------------------------------------------------------------------------------------------- class Import
Import::Import(int batch, int amount, float cost)
{
    this->Batch = batch;
    this->Import_Amount = amount;
    this->Import_Cost = cost;
}
float Import::GetImportCost()
{
    return this->Import_Cost;
}
void Import::Input(int Space_Amount)
{
    string space = "";
    for (int i = 1; i <= Space_Amount; i++) space += " ";
    cout << space << "Batch: "; cin >> this->Batch;
    cout << space << "The number of import(package): "; cin >> this->Import_Amount;
    cout << space << "Import cost(VND/package): "; cin >> this->Import_Cost;
    cout << space << "Import date(dd/mm/yyyy): "; this->Import_Date.InputDate();
}
void Import::Output(int Space_Amount)
{
    string space = "";
    for (int i = 1 ; i <= Space_Amount; i++) space += " ";
    cout << space << "Batch: " << this->Batch << endl
         << space << "The number of import(package): " << this->Import_Amount << endl
         << space << "Import cost(VND/package): " << this->Import_Cost << endl
         << space << "Import date: "; this->Import_Date.OutputDate();
}

//------------------------------------------------------------------------------------------------------------ class Goods
Goods::Goods(string sku_code, string name, string type, string origin)
{
    this->SKU = sku_code;
    this->Name = name;
    this->Type = type;
    this->Origin = origin;
}
string Goods::GetSKU()
{
    return this->SKU;
}
void Goods::ImportGoods(int Space_Amount)
{
    string space = "";
    for (int i = 1; i <= Space_Amount; i++) space += " ";
    cout << space << "---------- GOODS IMPORT ----------" << endl;
    cout << space << "SKU code: "; getline(cin, this->SKU);
    cout << space << "Goods of name: "; getline(cin, this->Name);
    cout << space << "Type: "; getline(cin, this->Type);
    cout << space << "Expiry date(dd/mm/yyyy): "; this->Expiry_Date.InputDate(); cin.ignore();
    cout << space << "Origin: "; getline(cin, this->Origin);
    Import::Input(Space_Amount);
    cout << space << "-------------- END --------------" << endl;
}
// void Goods::ExportGoods(int Space_Amount)
// {
//     string space = "";
//     for (int i = 1; i <= Space_Amount; i++) space += " ";
//     cout << "---------- GOODS EXPORT ----------" << endl;
//     cout << space << "SKU: "; cin >> this->SKU;
//     Export::Input(Space_Amount);
//     Export::SetExportCost(Import::GetImportCost());
//     cout << "---------- END ----------" << endl;

// }
void Goods::ShowInformation(int Space_Amount)
{
    string space = "";
    for (int i = 1; i <= Space_Amount; i++) space += " ";
    cout << space << "---------- GOODS'S INFORMATION ----------" << endl
         << space << "SKU: " << this->SKU << endl
         << space << "Goods of name: " << this->Name << endl
         << space << "Type: " << this->Type << endl
         << space << "Expiry date: "; this->Expiry_Date.OutputDate();
    cout << space << "Origin: " << this->Origin << endl;
    Import::Output(Space_Amount);
    cout << space << "------------------ END ------------------" << endl;
}

//------------------------------------------------------------------------------------------------------------ class Export
Export::Export(int amount, float cost)
{
    this->Export_Amount = amount;
    this->Export_Cost = cost;
}
void Export::SetExportCost(float import_cost)
{
    this->Export_Cost = import_cost + import_cost*20/100;
}
bool Export::checkSKU(vector<Goods> g, string sku, int *position)
{
    for (int i = 0; i < g.size(); i++)
    {
        if (sku.compare(g[i].GetSKU()) == 0) 
        {
            return true;
            *position = i;
        }
    }
    return false;
} 
void Export::ExportGoods(int Space_Amount, vector<Goods> g)
{
    string space = "";
    for (int i = 1 ; i <= Space_Amount; i++) space += " ";
    string sku;
    cout << space << "---------- GOODS EXPORT ----------" << endl;
    int isRun, postion ;
    do
    {
        isRun = 0;
        cout << space << "SKU: "; cin >> sku;
        if (checkSKU(g, sku, &postion) == false) 
        {
            cout << space << "This goods dose not exist!";
            isRun = 1;
        }
    }while(isRun == 1);
    cout << space << "The number of export(package): "; cin >> this->Export_Amount;
    cout << space << "Export date(dd/mm/yyyy): "; this->Export_Date.InputDate();
    SetExportCost(g[postion].GetImportCost());
    cout << space << "---------- END ----------" << endl;
} 

