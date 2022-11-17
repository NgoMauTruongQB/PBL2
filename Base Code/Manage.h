#pragma once
#include <iostream>
// #include <vector>
// #include <string>
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
        void Input();
        void Input_from_file(string filename);
        // void Export_bill(ofstream& out);
        void Export(ListCustomer&, ListBill&);
        void Print_bill(string, bool);
        // void Export_print();
        // void Print_bill(ListBill&);
        void Update(int, int);
        void Delete(string);
        void Sort(int, int);
        void Show_information(map<int,string>&, string = "");
        void Update_file_database(string = "Database.txt");
        Goods& operator[](int);
        int Get_import_length();
        int Get_export_length();
        void Print_list_ID();
        ~GoodsManagement();
};
