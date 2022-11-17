#pragma once
#include "Date.h"
#include <vector>
class Goods
{
    private:
        string ID;
        string Batch;
        string Goods_name;
        string Type;
        string Origin;
        Date EXP;
        int Amount;
        Date Import_date;
        float Cost;
        float Sale_cost;
        int Export_amount;
        Date Export_date;
        int Status;
        /*{
            if Status > 0 then this goods exited in the depot
            if Status == 0 then this goods has just been imported
            if Status < 0 then this goods has just been exported
        }*/
    public:
        Goods();
        Goods(string, string, string, string, string, Date, int, Date, float, float, Date, int);
        void Input();
        void Input_from_file(fstream &file_in);
        void Output();
        void Set_id();
        void Set_batch(string);
        void Set_goods_name(string);
        void Set_type(string);
        void Set_origin(string);
        void Set_EXP(string);
        void Set_amount(int);
        void Set_import_date(string);
        void Set_cost(float);
        void Set_sale_cost();
        void Set_export_amount(int);
        void Set_export_date(string);
        void Set_status(int);
        string Get_id();
        string Get_batch();
        string Get_good_name();
        string Get_type();
        string Get_origin();
        Date& Get_EXP();
        int Get_amount();
        Date& Get_import_date();
        float Get_cost();
        float Get_sale_cost();
        int Get_export_amount();
        Date& Get_export_date();
        int Get_status();
        // void Set_amount_after_export(const int&);
        const Goods& operator= (const Goods&);
        ~Goods();
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
void Standardized(string&);
void Swap(Goods&, Goods&);