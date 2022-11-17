#include "Manage.h"
// using namespace std;
//class GoodsManagement
GoodsManagement::GoodsManagement()
{
    this->Import_length = 0;
    this->Export_length = 0;
}
GoodsManagement::GoodsManagement(int importL, int exportL)
{
    this->Import_length = importL;
    this->Export_length = exportL;
}
int GoodsManagement::Get_import_length()
{
    return this->Import_length;
}
int GoodsManagement::Get_export_length()
{
    return this->Export_length;
}
int GoodsManagement::Find_id(string id)
{
    for (int i = 0; i < this->All_goods.size(); i++)
    {
        if ((*this)[i].Get_id().compare(id) == 0)
        return i;
    } 
    return -1;
}
bool GoodsManagement::Find_name_goods(string Goods_name)
{
    for (int i = 0; i < this->All_goods.size(); i++)
    {
        if ((*this)[i].Get_good_name().compare(Goods_name) == 0)
        return true;
    }
    return false;
}
void GoodsManagement::Input_from_file(string filename)
{
    fstream file_in;
    file_in.open(filename, ios::in);
    if(!file_in.good())
    {
        throw string("File not found!");
    }
    while (!file_in.eof())
    {
        Goods s;
        s.Input_from_file(file_in);
        (filename == "Database.txt") ? s.Set_status(1) : s.Set_status(0);
        s.Set_id();
        this->All_goods.push_back(s);
    }
    file_in.close();
}
void GoodsManagement::Input()
{
    int n;
    cout << distance() << "The number of goods which you want to import: "; cin >> n; cin.ignore();
    this->Import_length = n;
    for(int i = 0; i < this->Import_length; i++)
    {
        cout << distance() << i + 1 << ". " << endl;
        Goods s;
        cin.ignore();
        s.Input();
        s.Set_id();
        this->All_goods.push_back(s);
    } 
}

//chua viet 
void GoodsManagement::Export(ListCustomer& _list_customer, ListBill& _list_bill)
{
    int n;
    Bill b;
    cout << distance() << "The number of goods which you want to export: "; cin >> n;
    this->Export_length = n;
    for(int i = 0; i < this->Export_length; i++)
    {
        map<int, string> mapping;
        int select, exp_amount, index;
        bool _check_amount = false;
        cout << distance() << i + 1 << ". " << endl;
        string goods_name;
        cout << distance() << "Enter the goods of name which you want to export: "; cin.ignore(); getline(cin, goods_name);
        if (this->Find_name_goods(goods_name) == false) 
            throw string("Don't have this goods in the depot!");
        this->Show_information(mapping, goods_name);
        cout << distance() << "Enter the number you want to export: "; cin >> select;
        index = this->Find_id(mapping[select]);
        if (index == -1) throw string ("ID is not found");
        cout << distance() << "Amount: "; cin >> exp_amount;
        _check_amount = (exp_amount > (*this)[index].Get_amount());
        while (_check_amount == true)
        {
            cout << distance() << "Amount is not valid... Enter again: "; cin >> exp_amount;
            _check_amount = (exp_amount > (*this)[index].Get_amount());
        }
        (*this)[index].Set_export_amount(exp_amount);
        (*this)[index].Get_export_date().Set_day_real_time();
        (*this)[index].Set_sale_cost();
        (*this)[index].Set_status(-1);
        Goods *g = new Goods;
        g = &(*this)[index];
        b.Add_goods(g);
    }
    Date _local_time;
    _local_time.Set_full_real_time();
    b.Set_ID(_local_time);
    _list_bill.Add(b);
    Customer c;
    cin.ignore(); cin >> c;
    c.Set_Bill_ID(b.Get_ID());
    _list_customer.Add(c);
    cout << distance(); system("pause");
}
void GoodsManagement::Print_bill(string fileName, bool isImportBill)
{
    ofstream out;
    out.open(fileName, ios::trunc);
    double totalBill = 0;
    Date localTime;
    localTime.Set_full_real_time();
    localTime.Output_to_file(out);
    if (isImportBill == true)
    {
        out         << "                                     IMPORT BILL                                      "
            << endl << " ------------------------------------------------------------------------------------ "
            << endl << "| STT |      Ten san pham      |     Nguon goc     | So Luong |      Thanh tien      |"
            << endl << " ____________________________________________________________________________________ ";
        int count = 0;
        for (int i = 0; i < this->All_goods.size(); i++)
        {
            if ((*this)[i].Get_status() == 0)
            {
                count++;
                out << endl << "|" << setw(4) << count << " |" << setw(18) << (*this)[i].Get_good_name() << "      |" 
                    << setw(14) << (*this)[i].Get_origin() << "     |" << setw(9) << (*this)[i].Get_amount() << " |"  
                    << setw(18) << setprecision(18) << (*this)[i].Get_cost() << "    |" << endl;
                out << " ____________________________________________________________________________________ ";    
                (*this)[i].Set_status(1);
                totalBill += (*this)[i].Get_cost();
            }
        }
        out << endl << " -------------------------------------------------------------------------------------" << endl;
        out << "Total: " << setprecision(20) << totalBill << endl;
    }
    else
    {
        out         << "                                     EXPORT BILL                                      "
            << endl << " ------------------------------------------------------------------------------------ "
            << endl << "| STT |      Ten san pham      |     Nguon goc     | So Luong |      Thanh tien      |"
            << endl << " ____________________________________________________________________________________ ";
        int count = 0;
        for (int i = 0; i < this->All_goods.size(); i++)
        {
            if ((*this)[i].Get_status() < 0)
            {
                count++;
                out << endl << "|" << setw(4) << count << " |" << setw(18) << (*this)[i].Get_good_name() << "      |" 
                    << setw(14) << (*this)[i].Get_origin() << "     |" << setw(9) << (*this)[i].Get_export_amount() << " |"  
                    << setw(18) << setprecision(18) << (*this)[i].Get_sale_cost() * (*this)[i].Get_export_amount() << "    |" << endl;
                out << " ____________________________________________________________________________________ ";    
                if ((*this)[i].Get_amount() > 0) ((*this)[i].Set_status(1));
                else this->Delete((*this)[i].Get_id());
                totalBill += (*this)[i].Get_sale_cost() * (*this)[i].Get_export_amount();
            }
        }
        out << endl << " -------------------------------------------------------------------------------------" << endl;
        out << "Total: " << setprecision(20) << totalBill << endl;
    }
    map<string, int> mapping; 
    int i = 0;
    while (i < this->All_goods.size())
    {
        mapping[(*this)[i].Get_id()]++;
        if (mapping[(*this)[i].Get_id()] > 1) 
        {
            int temp = this->Find_id((*this)[i].Get_id());
            (*this)[temp].Set_amount((*this)[temp].Get_amount() + (*this)[i].Get_amount());
            (*this)[temp].Set_cost((*this)[temp].Get_cost() + (*this)[i].Get_cost());
            mapping[(*this)[i].Get_id()]--;
            this->All_goods.erase(this->All_goods.begin() + i);
        }
        else i++;
    }
    out.close();
}
void GoodsManagement::Show_information(map<int,string>& mapping, string Goods_name)
{
    if (this->All_goods.empty() == true || (Goods_name.compare("") != 0 && this->Find_name_goods(Goods_name) == false)) 
    {
        cout << distance() << "Don't have this goods in the depot!" << endl;
    }
    else if (Goods_name.compare("") == 0)
    {
        cout << distance() << " ___________________________________________________________________________________________________________________________ " << endl
             << distance() << "                                                    ALL GOODS INFORMATION                                                    " << endl
             << distance() << " --------------------------------------------------------------------------------------------------------------------------- " << endl
             << distance() << "| STT | Lo |      Ten san pham      |     Nguon goc     |   Loai   |  Ngay het han  | So Luong |  Ngay nhap  |    Don gia   |" << endl
             << distance() << " ____________________________________________________________________________________________________________________________" << endl;
        for (int i = 0; i < this->All_goods.size(); i++) 
        {
            mapping.insert({i+1, (*this)[i].Get_id()});
            cout << distance() << "|" << setw(4) << i + 1 << " |";
            (*this)[i].Output();
            cout << distance() << " ___________________________________________________________________________________________________________________________ " << endl;
        }
        cout << distance() << " ----------------------------------------------------------- END ----------------------------------------------------------- " << endl;
    }
    else
    {
        int count = 0;
        cout << distance() << " ___________________________________________________________________________________________________________________________ " << endl
             << distance() << "                                                    ALL GOODS INFORMATION                                                    " << endl
             << distance() << " --------------------------------------------------------------------------------------------------------------------------- " << endl
             << distance() << "| STT | Lo |      Ten san pham      |     Nguon goc     |   Loai   |  Ngay het han  | So Luong |  Ngay nhap  |    Don gia   |" << endl
             << distance() << " ____________________________________________________________________________________________________________________________" << endl;
        for (int i = 0; i < this->All_goods.size(); i++)
        {
            if ((*this)[i].Get_good_name().compare(Goods_name) == 0)
            {
                count++;
                mapping.insert({count, (*this)[i].Get_id()});
                cout << distance() << "|" << setw(4) << count << " |";
                (*this)[i].Output();
                cout << distance() << " ___________________________________________________________________________________________________________________________ " << endl;
            }
        }    
        cout << distance() << " ----------------------------------------------------------- END ----------------------------------------------------------- " << endl;    
    }
}
void GoodsManagement::Update_file_database(string filename)
{
    fstream out;
    out.open(filename, ios::out | ios::trunc);
    for (int i = 0; i < this->All_goods.size(); i++)
    {
        out << (*this)[i].Get_batch() << "," << (*this)[i].Get_good_name() << ","
            << (*this)[i].Get_origin() << "," << (*this)[i].Get_type() << ","
            << (*this)[i].Get_EXP().to_String() << "," << (*this)[i].Get_amount() << ","
            << setprecision(18) << (*this)[i].Get_cost() << "," << (*this)[i].Get_import_date().to_String();
        if (i < this->All_goods.size() - 1) out << endl;
    }
    out.ignore();
}
Goods& GoodsManagement::operator[](int index)
{
    if (index < 0 || index > this->All_goods.size())
    {
        static Goods data;
        return data;
    }
    else return this->All_goods[index];
}
void GoodsManagement::Update(int index, int select)
{
    switch(select)
    {
    case 1:
    {
        string batch;
        getline(cin, batch);
        Standardized(batch);
        (*this)[index].Set_batch(batch);
        break;
    }
    case 2:
    {
        string name;
        getline(cin,name);
        Standardized(name);
        (*this)[index].Set_goods_name(name);
        break;
    }
    case 3:
    {
        string origin;
        getline(cin, origin);
        Standardized(origin);
        (*this)[index].Set_origin(origin);
        break;
    }
    case 4:
    {
        string type;
        getline(cin, type);
        Standardized(type);
        (*this)[index].Set_type(type);
        break;
    }
    case 5:
    {
        (*this)[index].Get_EXP().Input();
        break;
    }
    case 6:
    {
        int amount;
        cin >> amount;
        (*this)[index].Set_amount(amount);
        break;
    }
    case 7:
    {
        float import_cost;
        cin >> import_cost;
        (*this)[index].Set_cost(import_cost);
        break;
    }
    case 8:
    {
        (*this)[index].Get_import_date().Input();
        break;
    }
    }
}
void GoodsManagement::Delete(string id)
{
    if (this->Find_id(id) == -1)
    {
        throw string("ID is not found...");
    }
    for (int i = 0; i < (this->All_goods).size(); i++)
    {
        if ((*this)[i].Get_id().compare(id) == 0)
        {
            (this->All_goods).erase((this->All_goods).begin() + i);        
            break;
        }
    }
}
void GoodsManagement::Sort(int select, int ascORdesc)
{   
    switch(select)
    {
        case 1:
        {
            if (ascORdesc == 1)
            {
                for (int i = 0; i < (this->All_goods).size() - 1; i++)
                for (int j = i + 1; j < (this->All_goods).size(); j++)
                {
                    if (Compare<string>(Asc, (*this)[i].Get_good_name(), (*this)[j].Get_good_name()) == false)
                        Swap((*this)[i], (*this)[j]);
                }
            }
            else
            {
                for (int i = 0; i < (this->All_goods).size() - 1; i++)
                for (int j = i + 1; j < (this->All_goods).size(); j++)
                {
                    if (Compare<string>(Desc, (*this)[i].Get_good_name(), (*this)[j].Get_good_name()) == false)
                        Swap((*this)[i], (*this)[j]);
                }
            }    
            break;
        }
        case 2:
        {
            if (ascORdesc == 1)
            {
                for (int i = 0; i < (this->All_goods).size() - 1; i++)
                for (int j = i + 1; j < (this->All_goods).size(); j++)
                {
                    if (Compare<Date>(Asc, (*this)[i].Get_EXP(), (*this)[j].Get_EXP()) == false)
                        Swap((*this)[i], (*this)[j]);
                }
            }
            else
            {
                for (int i = 0; i < (this->All_goods).size() - 1; i++)
                for (int j = i + 1; j < (this->All_goods).size(); j++)
                {
                    if (Compare<Date>(Desc, (*this)[i].Get_EXP(), (*this)[j].Get_EXP()) == false)
                        Swap((*this)[i], (*this)[j]);
                }
            }    
            break;
        }
        case 3:
        {
            if (ascORdesc == 1)
            {
                for (int i = 0; i < (this->All_goods).size() - 1; i++)
                for (int j = i + 1; j < (this->All_goods).size(); j++)
                {
                    if (Compare<Date>(Asc, (*this)[i].Get_import_date(), (*this)[j].Get_import_date()) == false)
                        Swap((*this)[i], (*this)[j]);
                }
            }
            else
            {
                for (int i = 0; i < (this->All_goods).size() - 1; i++)
                for (int j = i + 1; j < (this->All_goods).size(); j++)
                {
                    if (Compare<Date>(Desc, (*this)[i].Get_import_date(), (*this)[j].Get_import_date()) == false)
                        Swap((*this)[i], (*this)[j]);
                }
            }    
            break;
        }
        default:
        {
            if (ascORdesc == 1)
            {
                for (int i = 0; i < (this->All_goods).size() - 1; i++)
                for (int j = i + 1; j < (this->All_goods).size(); j++)
                {
                    if (Compare<string>(Asc, (*this)[i].Get_type(), (*this)[j].Get_type()) == false)
                        Swap((*this)[i], (*this)[j]);
                }
            }
            else
            {
                for (int i = 0; i < (this->All_goods).size() - 1; i++)
                for (int j = i + 1; j < (this->All_goods).size(); j++)
                {
                    if (Compare<string>(Desc, (*this)[i].Get_type(), (*this)[j].Get_type()) == false)
                        Swap((*this)[i], (*this)[j]);
                }
            }    
        }
    }
}
void GoodsManagement::Print_list_ID()
{
    for (int i = 0; i < (this->All_goods).size(); i++) 
    {
        cout << (*this)[i].Get_id() << " " << (*this)[i].Get_good_name() << endl;
    }
}
GoodsManagement::~GoodsManagement(){

}
