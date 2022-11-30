#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include "Goods.h"
#include "Bill.h"
#include "Customer.h"
class ListBill;
class ListCustomer;
class GoodsManagement
{
    private:
        vector<Goods> All_goods;
        int Import_length;
        int Export_length;
    public:
        GoodsManagement();
        GoodsManagement(int, int);
        int Find_id(string);
        bool Find_name_goods(string);
        bool Find_type_goods(string);
        bool Find_batch_goods(string);
        void Input();
        void Input_from_file(string filename);
        void Export(ListCustomer&, ListBill&);
        void Update(int, int);
        void Delete(string);
        void Sort(int, int);
        void Search(map<int,string>&, string, int);
        void Show_information();
        Goods& operator[](int);
        int Get_import_length();
        int Get_export_length();
        int Get_length();
        void Print_list_ID();
        ~GoodsManagement();
};
