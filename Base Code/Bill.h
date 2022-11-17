#pragma once
#include "Manage.h"
using namespace std;
class ListCustomer;
class Bill
{
private:
    string ID;
    vector<Goods *> g;
    bool Payment_status;
public:
    Bill();
    Bill(string, vector<Goods *>, bool);
    ~Bill();
    void Set_ID(Date);
    void Set_PayStatus(bool);
    string Get_ID();
    bool Get_PayStatus();
    void Add_goods(Goods *);
    void Print(string, ListCustomer&);
    void Show(ListCustomer&);
    Goods*& operator[](int);
};

class ListBill
{
private:
    vector<Bill> bill;
public:
    ~ListBill();
    int Find_id(string);
    void Add(const Bill&);
    vector<Bill>& Get_vector();
    Bill& operator[](int);
    Bill& Get_bill(string);
};

