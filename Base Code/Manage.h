#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <ctime>
#include "Goods.h"
class GoodsManagement
{
    private:
        vector<Goods> All_goods;
        int Import_length;
        int Export_length;
    public:
        GoodsManagement();
        GoodsManagement(int, int);
        bool Check_empty();
        int Find_id(string);
        bool Find_name_goods(string);
        void Input(string);
        void Input_from_file(string filename);
        // void Export_bill(ofstream& out);
        void Output(string);
        void Print_bill(string, bool);
        // void Export_print();
        void Update(int, int);
        void Delete(string);
        void Sort(int, int);
        void Show_information(string, map<int,string>&, string = "");
        void Update_file_database(string = "Database.txt");
        Goods& operator[](int);
        int Get_import_length();
        int Get_export_length();
        void Print_list_ID();
        ~GoodsManagement();
};
template<class T> bool Asc(T a, T b)
{
    return (a < b);
}
template<class T> bool Desc(T a, T b)
{
    return (a > b);
}
template<class T> bool Compare(bool(*func) (T, T), T a, T b)
{
    return func(a, b);
}
void Swap(Goods&, Goods&);
void Information_of_customer();
void Get_real_time(Date&);
