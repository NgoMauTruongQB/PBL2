#include "Manage.h"
#include <iomanip>
using namespace std;
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
bool GoodsManagement::Check_empty()
{
    return (this->All_goods.empty());
}
int GoodsManagement::Find_id(string id)
{
    for (int i = 0; i < this->All_goods.size(); i++)
    {
        if ((*this)[i].Get_id().compare(id) == 0)
        return 0;
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
void GoodsManagement::Input(string distance)
{
    int n;
    cout << distance << "The number of goods which you want to import: "; cin >> n;
    this->Import_length = n;
    for(int i = 0; i < this->Import_length; i++)
    {
        cout << distance << i + 1 << ". " << endl;
        Goods s;
        cin.ignore();
        s.Input(distance);
        s.Set_id();
        this->All_goods.push_back(s);
    } 
}

//chua viet 
void GoodsManagement::Output(string distance)
{
    // int n;
    // cout << " ===== GOODS EXPORT ===== " << endl;
    // cout << " Enter imtem number: "; cin >> n;
    // this->Export_length = n;
    // for(int i = 0; i < this->Export_length; i++)
    // {
    //     cout << " " << i + 1 << ". " << endl;
    //     Goods s;
    //     cout << "Enter name item: ";
    //     // Nhap vao ten loai hang hoa 
    //     // Nhap vao so luong
    //     // Nhap vao gia ban 
    // }

    int n;
    cout << distance << "The number of goods which you want to export: "; cin >> n;
    this->Export_length = n;
    for(int i = 0; i < this->Export_length; i++)
    {
        cout << distance << i + 1 << ". " << endl;
        map<int, string> mapping;
        int select, exp_amount, index;
        string goods_name;
        cout << distance << "Enter the goods of name which you want to export: "; cin.ignore(); getline(cin, goods_name);
        this->Show_information(distance, mapping, goods_name);
        cout << distance << "Enter the number you want to export: "; cin >> select;
        index = this->Find_id(mapping.at(select));
        if (index == -1) throw string ("ID is not found");
        cout << distance << "Amount: "; cin >> exp_amount;
        try
        {
            (*this)[index].Set_amount_after_export(exp_amount);
        }
        catch(string e)
        {
            cout << distance << e << endl;
        }
        Get_real_time((*this)[index].Get_export_date());


    } 
}
void GoodsManagement::Print_bill(string fileName, bool isImportBill)
{
    ofstream out;
    out.open(fileName, ios::trunc);
    double totalBill = 0;
    Date localDate;
    Get_real_time(localDate);
    cin.ignore();
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
                    << setw(14) << (*this)[i].Get_origin() << "     |" << setw(9) << (*this)[i].Get_import_amount() << " |"  
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
                    << setw(18) << setprecision(18) << (*this)[i].Get_export_cost() * (*this)[i].Get_export_amount() << "    |" << endl;
                out << " ____________________________________________________________________________________ ";    
                if ((*this)[i].Get_import_amount() > 0) ((*this)[i].Set_status(1));
                else this->Delete((*this)[i].Get_id());
                totalBill += (*this)[i].Get_export_cost() * (*this)[i].Get_export_amount();
            }
        }
        out << endl << " -------------------------------------------------------------------------------------" << endl;
        out << "Total: " << setprecision(20) << totalBill << endl;
    }
    out.close();
}
void GoodsManagement::Show_information(string distance, map<int,string>& mapping, string Goods_name)
{
    if (this->All_goods.empty() == true || (Goods_name.compare("") != 0 && this->Find_name_goods(Goods_name) == false)) 
    {
        cout << distance << "Don't have this goods in the depot!" << endl;
    }
    else if (Goods_name.compare("") == 0)
    {
        cout << distance << " ___________________________________________________________________________________________________________________________ " << endl
             << distance << "                                                    ALL GOODS INFORMATION                                                    " << endl
             << distance << " --------------------------------------------------------------------------------------------------------------------------- " << endl
             << distance << "| STT | Lo |      Ten san pham      |     Nguon goc     |   Loai   |  Ngay het han  | So Luong |  Ngay nhap  |    Don gia   |" << endl
             << distance << " ____________________________________________________________________________________________________________________________" << endl;
        for (int i = 0; i < this->All_goods.size(); i++) 
        {
            mapping.insert({i+1, (*this)[i].Get_id()});
            cout << distance << "|" << setw(4) << i + 1 << " |";
            (*this)[i].Output(distance);
            cout << distance << " ___________________________________________________________________________________________________________________________ " << endl;
        }
        cout << distance << " ----------------------------------------------------------- END ----------------------------------------------------------- " << endl;
    }
    else
    {
        int count = 0;
        cout << distance << " ___________________________________________________________________________________________________________________________ " << endl
             << distance << "                                                    ALL GOODS INFORMATION                                                    " << endl
             << distance << " --------------------------------------------------------------------------------------------------------------------------- " << endl
             << distance << "| STT | Lo |      Ten san pham      |     Nguon goc     |   Loai   |  Ngay het han  | So Luong |  Ngay nhap  |    Don gia   |" << endl
             << distance << " ____________________________________________________________________________________________________________________________" << endl;
        for (int i = 0; i < this->All_goods.size(); i++)
        {
            if ((*this)[i].Get_good_name().compare(Goods_name) == 0)
            {
                count++;
                mapping.insert({count, (*this)[i].Get_id()});
                cout << distance << "|" << setw(4) << count << " |";
                (*this)[i].Output(distance);
                cout << distance << " ___________________________________________________________________________________________________________________________ " << endl;
            }
        }    
        cout << distance << " ----------------------------------------------------------- END ----------------------------------------------------------- " << endl;    
    }
}
// chua biet 
// void GoodsManagement::Export_bill(ofstream& out)
// {
//     //In ra file hoa don xuat hang
//     // cout ngay thuc te hoa don duoc tao
//     //Tinh trang thanh toan
//     // Ten khach hang 
//     // Dia chi khách hàng 
//     // số điện thoại của khách hàng 
//     // Tổng số tiền cần thanh toán
//     // Tên người xuất
//     // Ten khách hàng 
// }
void GoodsManagement::Update_file_database(string filename)
{
    fstream out;
    out.open(filename, ios::out | ios::trunc);
    for (int i = 0; i < this->All_goods.size(); i++)
    {
        out << (*this)[i].Get_Batch() << "," << (*this)[i].Get_good_name() << ","
            << (*this)[i].Get_origin() << "," << (*this)[i].Get_type() << ","
            << (*this)[i].Get_EXP_str() << "," << (*this)[i].Get_import_amount() << ","
            << setprecision(18) << (*this)[i].Get_cost() << "," << (*this)[i].Get_Impdate_str();
        if (i < this->All_goods.size() - 1) out << endl;
    }
    out.ignore();
}
Goods& GoodsManagement::operator[](int index)
{
    static Goods data;
    return (index < 0 || index > this->All_goods.size()) ? data : this->All_goods[index];
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
        string type;
        getline(cin, type);
        Standardized(type);
        (*this)[index].Set_type(type);
        break;
    }
    case 4:
    {
        string origin;
        getline(cin, origin);
        Standardized(origin);
        (*this)[index].Set_origin(origin);
        break;
    }
    case 5:
    {
        string date;
        getline(cin, date);
        Standardized(date);
        (*this)[index].Set_EXP(date);
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
        (*this)[index].Set_import_cost(import_cost);
        break;
    }
    case 8:
    {
        string import_date;
        getline(cin, import_date);
        Standardized(import_date);
        (*this)[index].Set_import_date(import_date);
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

//friend function
void Swap(Goods& a, Goods& b)
{
    Goods temp;
    temp = a;
    a = b;
    b = temp;
}
void Information_of_customer()
{
    string name, address, phoneNumber;
    cout << " ===== ENTER IFORMATION OF CUSTOMER ===== " << endl;
    cout << " Full name: "; getline(cin, name);
    cout << " Address: "; getline(cin, address);
    cout << " Phone number: "; getline(cin, phoneNumber);
}
void Get_real_time(Date& localDate)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << "Time: " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << " Date:"
         << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
    localDate.Set_day(ltm->tm_mday);
    localDate.Set_month(ltm->tm_mon + 1);
    localDate.Set_year(ltm->tm_year + 1900);
}

