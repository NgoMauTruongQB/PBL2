#include "Bill.h"

//========================================= Class Bill ============================================

Bill::Bill() : ID(""), Payment_status(false)
{}
Bill::Bill(string id, vector<Goods *> g, bool status) : ID(id), g(g), Payment_status(status)
{}
Bill::~Bill()
{
}
void Bill::Set_ID(Date Real_time)
{
    string str = "";
    str += to_string(Real_time.Get_hour());
    str += to_string(Real_time.Get_minute());
    str += to_string(Real_time.Get_second());
    str += to_string(Real_time.Get_day());
    str += to_string(Real_time.Get_month());
    str += to_string(Real_time.Get_year());
    this->ID = str;
}
void Bill::Set_PayStatus(bool status)
{
    this->Payment_status = status;
}
string Bill::Get_ID()
{
    return this->ID;
}
bool Bill::Get_PayStatus()
{
    return this->Payment_status;
}
void Bill::Add_goods(Goods * g)
{
    this->g.push_back(g);
}
void Bill::Print(string fileName, ListCustomer& lc)
{
    ofstream out;
    out.open(fileName, ios::trunc);
    double totalBill = 0;
    Date localTime;
    localTime.Set_full_real_time();
    localTime.Output_to_file(out);
    Customer c = lc.Get_customer(this->ID);
    out         << "Khach hang: " << c.Get_name() << "         SDT: " << c.Get_PhoneNumber()
        << endl << "                               BILL                               "
        << endl << " ---------------------------------------------------------------- "
        << endl << "| STT |      Ten san pham      | So Luong |      Thanh tien      |"
        << endl << " ________________________________________________________________ ";
    int count = 0;
    for (int i = 0; i < this->g.size(); i++)
    {
        count++;
        out << endl << "|" << setw(4) << count << " |" << setw(18) << (*this)[i]->Get_good_name() 
            << "      |" << setw(9) << (*this)[i]->Get_export_amount() << " |"  
            << setw(18) << setprecision(18) << (*this)[i]->Get_sale_cost() * (*this)[i]->Get_export_amount() << "    |" << endl;
        out << " ________________________________________________________________ ";    
        totalBill += (*this)[i]->Get_sale_cost() * (*this)[i]->Get_export_amount();
    }
    out << endl << " ---------------------------------------------------------------- " << endl;
    out << "Total: " << setprecision(20) << totalBill << endl;
    // this->Payment_status = true;
}
void Bill::Show(ListCustomer& lc)
{
    double totalBill = 0;
    Date localTime;
    localTime.Set_full_real_time();
    cout << distance(); localTime.Output();
    Customer c = lc.Get_customer(this->ID);
    cout         << " " << c.Get_name() << "         " << c.Get_PhoneNumber()
        << endl << "                               BILL                               "
        << endl << " ---------------------------------------------------------------- "
        << endl << "| STT |      Ten san pham      | So Luong |      Thanh tien      |"
        << endl << " ________________________________________________________________ ";
    // int count = 0;
    for (int i = 0; i < this->g.size(); i++)
    {
        // count++;
        cout << endl << "|" << setw(4) << i+1 << " |" << setw(18) << (*this)[i]->Get_good_name() 
            << "     |" << setw(9) << (*this)[i]->Get_export_amount() << " |"  
            << setw(18) << setprecision(18) << (*this)[i]->Get_sale_cost() * (*this)[i]->Get_export_amount() << "    |" << endl;
        cout << " ________________________________________________________________ ";    
        totalBill += (*this)[i]->Get_sale_cost() * (*this)[i]->Get_export_amount();
    }
    cout << endl << " ---------------------------------------------------------------- " << endl;
    cout << "Total: " << setprecision(20) << totalBill << endl;
    // this->Payment_status = true;    
}
Goods*& Bill::operator[](int index)
{
    if (index > this->g.size() || index < 0)
    {
        static Goods * g = new Goods;
        return g;
    }
    else return this->g.at(index);

}

//========================================= Class ListBill ============================================

ListBill::~ListBill() {}
int ListBill::Find_id(string id)
{
    for (int i = 0; i < this->bill.size(); i++)
    {
        if ((*this)[i].Get_ID().compare(id) == 0)
        {
            return i;
        }
    }
    return -1;
}
void ListBill::Add(const Bill& b)
{
    this->bill.push_back(b);
}
vector<Bill>& ListBill::Get_vector()
{
    return this->bill;
}
Bill& ListBill::operator[](int index)
{
    if (index > this->bill.size() || index < 0)
    {
        static Bill temp;
        return temp;
    }
    else return this->bill.at(index);
}
Bill& ListBill::Get_bill(string id)
{
    int index = this->Find_id(id);
    if (index == -1)
    {
        static Bill temp;
        return temp;
    }
    else return (*this)[index];
}

