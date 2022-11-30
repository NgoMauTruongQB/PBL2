#include "Manage.h"

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
int GoodsManagement::Get_length()
{
    return this->All_goods.size();
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
bool GoodsManagement::Find_type_goods(string Goods_type)
{
    for (int i = 0; i < this->All_goods.size(); i++)
    {
        if ((*this)[i].Get_type().compare(Goods_type) == 0)
        return true;
    }
    return false;
}
bool GoodsManagement::Find_batch_goods(string Goods_batch)
{
    for (int i = 0; i < this->All_goods.size(); i++)
    {
        if ((*this)[i].Get_batch().compare(Goods_batch) == 0)
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
        s.Set_id();
        s.Set_sale_cost();
        this->All_goods.push_back(s);
    }
    file_in.close();
}
void GoodsManagement::Input()
{
    int n;
    cout << distance() << "So luong hang hoa ma ban muon nhap vao kho: "; cin >> n; cin.ignore();
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

void GoodsManagement::Export(ListCustomer& _list_customer, ListBill& _list_bill)
{
    string str;
    bool valid = true;
    Bill b;
    cout << distance() << "So luong hang hoa ma ban muon xuat kho: "; getline(cin, str);
    if (str.length() > 0 && str.length() < 100)
    {
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] < 48 || str[i] > 57)
            {
                valid = false;
                break;
            }
        }
    }
    else valid = false;
    if (valid) this->Export_length = stoi(str);  
    else throw string("Da co Loi!");

    int index;
    for(int i = 0; i < this->Export_length; i++)
    {
        map<int, string> mapping;
        int select, exp_amount;
        bool _check_amount = false;
        cout << distance() << i + 1 << ". " << endl;
        string goods_name;
        cout << distance() << "Nhap ten hang hoa ma ban muon xuat kho: "; getline(cin, goods_name);
        if (this->Find_name_goods(goods_name) == false) 
            throw string("Khong tim thay hang hoa nay trong kho!");
        this->Search(mapping, goods_name, 1);
        cout << distance() << "Lua chon: "; cin >> select; cin.ignore();
        index = this->Find_id(mapping[select]);
        if (index == -1) throw string ("Khong tim thay hang hoa nay trong kho!");

        if ((*this)[index].Get_amount() != 0)
        {
            cout << distance() << "So luong: "; cin >> exp_amount; cin.ignore();
            _check_amount = (exp_amount > (*this)[index].Get_amount());
            while (_check_amount)
            {
                cout << distance() << "So luong khong hop le...Nhap lai: "; cin >> exp_amount;
                _check_amount = (exp_amount > (*this)[index].Get_amount());
            }
        }
        else throw string("San pham nay da het hang!");
        
        b.Add_goods(&(*this)[index]);
        b.Add_expAmount(exp_amount);
    }
    Date _local_time;
    _local_time.Set_full_real_time();
    b.Set_ID(_local_time);
    b.Set_date_of_bill(_local_time);
    
    bool check_Finish = false;
    int select; 
    do
    {
        cout << distance() << " ------- THONG TIN KHACH HANG ------- " << endl
             << distance() << "|        1. Khach hang moi           |" << endl
             << distance() << "|        2. Khach hang cu            |" << endl
             << distance() << "|        3. Ket thuc                 |" << endl
             << distance() << " ------------------------------------ " << endl;
        cout << distance() << "Lua chon: "; cin >> select; cin.ignore();
        switch (select) 
        {
        case 1:
        {
            Customer c;
            cin >> c;
            cout << distance() << "Loai hinh thanh toan: " << endl
                 << distance() << "Tra truoc[1] hay tra sau[2]: ";
            char ch;
            do
            {
                ch = getchar(); cin.ignore();
                if (ch == '1') b.Set_PayStatus(true);
                else if(ch == '2') b.Set_PayStatus(false);
                else 
                {
                    ch = '0';
                    cout << distance() << "Loai hinh thanh toan nay khong co ... Lua chon lai: ";
                }
            }while(ch == '0');
            _list_customer.Add(c);
            _list_customer[_list_customer.Get_length() - 1].Add_bill(b);
            _list_bill.Add(b); 
            check_Finish = true;
            break;
        }
        case 2:
        {
            string id;
            cout << distance() << "ID: "; getline(cin, id);
            int index = _list_customer.Find_id(id);
            if (index != -1)
            {
                if (_list_customer[index].Get_vector().size() != 0)
                {
                    if (_list_customer[index].Get_vector().at(_list_customer[index].Get_vector().size() - 1).Get_PayStatus())
                    {
                        cout << distance() << "Loai hinh thanh toan: " << endl
                            << distance() << "Tra truoc[1] hay tra sau[2]: ";
                        char ch;
                        do
                        {
                            ch = getchar(); cin.ignore();
                            if (ch == '1') b.Set_PayStatus(true);
                            else if(ch == '2') b.Set_PayStatus(false);
                            else 
                            {
                                ch = '0';
                                cout << distance() << "Loai hinh thanh toan nay khong co ... Lua chon lai: ";
                            }
                        }while(ch == '0');
                        _list_customer[index].Add_bill(b);
                        _list_bill.Add(b);
                        check_Finish = true;
                    }
                    else
                    {
                        cout << distance() << "Khach hang phai thanh toan hoa don truoc do!" << endl;
                        check_Finish = false;
                    }   
                }
                else
                {
                    cout << distance() << "Loai hinh thanh toan: " << endl
                        << distance() << "Tra truoc[1] hay tra sau[2]: ";
                    char ch;
                    do
                    {
                        ch = getchar(); cin.ignore();
                        if (ch == '1') b.Set_PayStatus(true);
                        else if(ch == '2') b.Set_PayStatus(false);
                        else 
                        {
                            ch = '0';
                            cout << distance() << "Loai hinh thanh toan nay khong co ... Lua chon lai: ";
                        }
                    }while(ch == '0');
                    _list_customer[index].Add_bill(b);
                    _list_bill.Add(b);
                    check_Finish = true;
                }
            }
            else
            {
                cout << distance() << "Khong tim thay ID tren ... " << endl;
                check_Finish = false;
            } 
            break;
        }
        }
        if (check_Finish == true) break;
    }while(select < 3);
    if (check_Finish == false) throw string("Khong co thong tin khach hang");
    for (int i = 0; i < b.Get_vector().size(); i++)
    {
        b.Get_vector()[i]->Set_amount(b.Get_vector()[i]->Get_amount() - b.Get_vector_expAmount()[i]);
    }
}
void GoodsManagement::Search(map<int,string>& mapping, string search_by, int option)
{
    string dis = distance();
    switch (option)
    {
    case 1:
    {
        if (this->All_goods.empty() == true || (this->Find_name_goods(search_by) == false)) 
            cout << dis << "Khong co mat hang nay trong kho!" << endl;
        else
        {
            int count = 0;
            dis = distance(20);
            cout << dis << " _______________________________________________________________________________________________________________________________________________________ " << endl
                << dis << "                                                                   THONG TIN HANG HOA                                                                    " << endl
                << dis << " ------------------------------------------------------------------------------------------------------------------------------------------------------- " << endl
                << dis << "| STT |   Lo   |                 Ten san pham                |  Nguon goc  |       Loai        |  Ngay het han  | So Luong |  Ngay nhap  |    Don gia   |" << endl
                << dis << " _______________________________________________________________________________________________________________________________________________________ " << endl;
            for (int i = 0; i < this->All_goods.size(); i++)
            {
                if ((*this)[i].Get_good_name().compare(search_by) == 0)
                {
                    count++;
                    mapping.insert({count, (*this)[i].Get_id()});
                    cout << dis << "|" << setw(4) << count << " |";
                    (*this)[i].Output();
                    cout << dis << " _______________________________________________________________________________________________________________________________________________________ " << endl;
                }
            }    
            cout << dis << " ---------------------------------------------------------------------- KET THUC ----------------------------------------------------------------------- " << endl;
        }
        break;
    }
    case 2:
    {
        if (this->All_goods.empty() == true || (this->Find_type_goods(search_by) == false)) 
            cout << dis << "Khong co mat hang nay trong kho!" << endl;
        else
        {
            int count = 0;
            dis = distance(20);
            cout << dis << " _______________________________________________________________________________________________________________________________________________________ " << endl
                << dis << "                                                                   THONG TIN HANG HOA                                                                    " << endl
                << dis << " ------------------------------------------------------------------------------------------------------------------------------------------------------- " << endl
                << dis << "| STT |   Lo   |                 Ten san pham                |  Nguon goc  |       Loai        |  Ngay het han  | So Luong |  Ngay nhap  |    Don gia   |" << endl
                << dis << " _______________________________________________________________________________________________________________________________________________________ " << endl;
            for (int i = 0; i < this->All_goods.size(); i++)
            {
                if ((*this)[i].Get_type().compare(search_by) == 0)
                {
                    count++;
                    mapping.insert({count, (*this)[i].Get_id()});
                    cout << dis << "|" << setw(4) << count << " |";
                    (*this)[i].Output();
                    cout << dis << " _______________________________________________________________________________________________________________________________________________________ " << endl;
                }
            }    
            cout << dis << " ---------------------------------------------------------------------- KET THUC ----------------------------------------------------------------------- " << endl;
        }
        break;
    }
    default:
    {
        if (this->All_goods.empty() == true || (this->Find_batch_goods(search_by) == false)) 
            cout << dis << "Khong co mat hang nay trong kho!" << endl;
        else
        {
            int count = 0;
            dis = distance(20);
            cout << dis << " _______________________________________________________________________________________________________________________________________________________ " << endl
                << dis << "                                                                   THONG TIN HANG HOA                                                                    " << endl
                << dis << " ------------------------------------------------------------------------------------------------------------------------------------------------------- " << endl
                << dis << "| STT |   Lo   |                 Ten san pham                |  Nguon goc  |       Loai        |  Ngay het han  | So Luong |  Ngay nhap  |    Don gia   |" << endl
                << dis << " _______________________________________________________________________________________________________________________________________________________ " << endl;
            for (int i = 0; i < this->All_goods.size(); i++)
            {
                if ((*this)[i].Get_batch().compare(search_by) == 0)
                {
                    count++;
                    mapping.insert({count, (*this)[i].Get_id()});
                    cout << dis << "|" << setw(4) << count << " |";
                    (*this)[i].Output();
                    cout << dis << " _______________________________________________________________________________________________________________________________________________________ " << endl;
                }
            }    
            cout << dis << " ---------------------------------------------------------------------- KET THUC ----------------------------------------------------------------------- " << endl;
        }
    }
    }
}
void GoodsManagement::Show_information()
{
    string dis = distance();
    if (this->All_goods.empty())
        cout << dis << "Kho trong..." << endl;
    else
    {
        dis = distance(20);
        cout << dis << " _______________________________________________________________________________________________________________________________________________________ " << endl
             << dis << "                                                                   THONG TIN HANG HOA                                                                    " << endl
             << dis << " ------------------------------------------------------------------------------------------------------------------------------------------------------- " << endl
             << dis << "| STT |   Lo   |                 Ten san pham                |  Nguon goc  |       Loai        |  Ngay het han  | So Luong |  Ngay nhap  |    Don gia   |" << endl
             << dis << " _______________________________________________________________________________________________________________________________________________________ " << endl;
        for (int i = 0; i < this->All_goods.size(); i++) 
        {
            cout << dis << "|" << setw(4) << i + 1 << " |";
            (*this)[i].Output();
            cout << dis << " _______________________________________________________________________________________________________________________________________________________ " << endl;
        }
        cout << dis << " ---------------------------------------------------------------------- KET THUC ----------------------------------------------------------------------- " << endl;
    }
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
        throw string("Khong tim thay mat hang nay...");
    }
    for (int i = 0; i < (this->All_goods).size(); i++)
    {
        if ((*this)[i].Get_id().compare(id) == 0)
        {
            (this->All_goods).erase(i);        
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
