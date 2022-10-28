#include "Depot.h"
#include <iostream>
using namespace std;

//class SubArea
SubArea::SubArea(string name, string area, int amount)
{
    this->SubArea_name = name;
    this->SuperArea = area;
    this->Remaning_amount = amount; 
}
void SubArea::SubArea_in(ifstream& in)
{
    getline(in, this->SubArea_name, '-');
    getline(in, this->SuperArea, '-');
    in >> this->Remaning_amount;
}
void SubArea::SubArea_out()
{
    cout << " " << "SubArea of name: " << this->SubArea_name << endl;
    cout << " " << "Super Area: " << this->SuperArea << endl;
    cout << " " << "Remaning amount: " << this->Remaning_amount << endl;
}
string SubArea::Get_SubArea_name()
{
    return this->SubArea_name;
}
string SubArea::Get_SuperArea()
{
    return this->SuperArea;
}
void SubArea::Set_amount(int amount)
{
    //Xây dựng hàm trả về số lượng hàng hoá còn lại trên subArea
    //Tuỳ vào loại hàng thì sức chứa của subArea sẽ khác nhau
    // => làm sao để biết sức chứa của từng subArea 
}
bool SubArea::Check_empty(int capacity)
{
    return (this->Remaning_amount < capacity);
}
SubArea::~SubArea(){
}

//class SuperArea
SuperArea::SuperArea()
{
    this->SuperArea_name = "";
    this->SubArea_amount = 0;
    this->Max_capacity = 0;
}
SuperArea::SuperArea(string name, int length, int maxCapacity)
{
    this->SuperArea_name = name;
    this->SubArea_amount = length;
    this->Max_capacity = maxCapacity;
}
SuperArea::~SuperArea()
{
}
void SuperArea::SuperArea_in(ifstream& in)
{
    getline(in,this->SuperArea_name, '-');
    in >> this->SubArea_amount;
    in >> this->Max_capacity;
    in.ignore();
    for (int i = 0; i < this->SubArea_amount; i++)
    {
        SubArea s;
        s.SubArea_in(in); 
        in.ignore();
        this->All_SubArea.push_back(s);
    }
}
void SuperArea::SuperArea_out()
{
    int count = 0;
    cout << "- Super Area: " << this->SuperArea_name << endl;
    for (SubArea i : this->All_SubArea)
    {
        count++;
        i.SubArea_out();
        if (count != this->SubArea_amount) cout << "---------------------------\n";
    }
}   
string SuperArea::Get_superArea_name()
{
    return this->SuperArea_name;
} 
void SuperArea::Empty_postion()
{
    int count = 0;
    cout << "- Super Area: " << this->SuperArea_name << endl;
    for (SubArea i : this->All_SubArea)
    {
        if (i.Check_empty(this->Max_capacity) == true)
        {
            count++;
            if (count > 1) cout << "----------------------------" << endl;
            i.SubArea_out();
        }
    }
    if (count == 0) cout << "Don't have any empty subArea in this super area!\n";
}


//class Depot
Depot::Depot()
{
    this->SuperArea_amount = 0;
}
Depot::Depot(int length)
{
    this->SuperArea_amount = length;
}
int Depot ::Find_SuperArea(string area)
{
    for (int i = 0; i < this->SuperArea_amount; i++)
    {
        if (this->All_SuperArea[i].Get_superArea_name().compare(area) == 0) return i;
    }
    return -1;
}
void Depot::Depot_in(ifstream& in)
{
    int i = 0;
    while(!in.eof())
    {   
        i++;
        SuperArea s;
        s.SuperArea_in(in); 
        this->All_SuperArea.push_back(s);
    }
    this->SuperArea_amount = i;

    
}
void Depot::Depot_out(string area)
{
    if (area.compare("") == 0)
    {
        cout << "-------- ALL OF SUBAREA IN DEPOT --------" << endl;
        for (SuperArea i : this->All_SuperArea)
        {
            i.SuperArea_out();
        }
        cout << "================= END =================" << endl;
    }
    else if (Find_SuperArea(area) != -1)
    {
        cout << "-------- ALL OF SUBAREA IN '" << area << "' SuperArea ---------" << endl;
        this->All_SuperArea[Find_SuperArea(area)].SuperArea_out();
        cout << "================= END =================" << endl;    
    }
    else cout << "Don't have any subArea '" << area << "' in depot!" << endl;
}
void Depot::Empty_position(string area)
{
    if (area.compare("") == 0)
    {
        cout << "-------- ALL EMPTY SUBAREA IN DEPOT --------" << endl;
        for (SuperArea i : this->All_SuperArea)
        {
            i.Empty_postion();
        }
        cout << "================= END =================" << endl;
    }
    else if (Find_SuperArea(area) != -1)
    {
        int count = 0;
        cout << "-------- ALL OF SUBAREA IN " << area << " SuperArea ---------" << endl;
        this->All_SuperArea[Find_SuperArea(area)].SuperArea_out();
        cout << "================= END =================" << endl;    
    }
    else cout << "Don't have any subArea '" << area << "' in depot!" << endl;
}

Depot::~Depot(){

}
