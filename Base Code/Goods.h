#include <string>
#include "Date.h"
using namespace std;
class Import
{
    protected: 
        string Batch;
        int Import_amount;
        float Import_cost;
        Date Import_date;
    public:
        Import();
        Import(string, int, float, Date);
        void Import_in();
        void Import_out();
        void Set_batch(string);
        void Set_import_cost(float);
        void Set_import_date(string);
        string Get_Batch();
        float Get_cost();
        int Get_import_amount();
        string Get_Impdate_str();
        Date Get_import_date();
        ~Import();
};
class Export
{
    protected:
        int Export_amount;
        float Export_cost;
        Date Export_date;
    public:
        Export();
        Export(int, float, Date);
        Date& Get_export_date();
        float Get_export_cost();
        int Get_export_amount();
        int Set_goods_amount_again(const int&);
        void Export_in(string, const float ogrCost, float shipCost);
        void Export_out();
        ~Export();
};
class Goods : public Import, public Export
{
    private:
        string ID;
        string Goods_name;
        string Type;
        string Origin;
        Date EXP;
        int Status;
        // if Status > 0 then this goods exited in the depot
        // if Status == 0 then this goods has just been imported
        // if Status < 0 then this goods has just been exported
    public:
        Goods();
        Goods(string, string, string, Date, int);
        void Input(string);
        void Input_from_file(fstream &file_in);
        void Output(string);
        void Set_id();
        void Set_goods_name(string);
        void Set_type(string);
        void Set_origin(string);
        void Set_EXP(string);
        void Set_amount(int);
        void Set_status(int);
        string Get_id();
        string Get_good_name();
        string Get_type();
        string Get_origin();
        string Get_EXP_str();
        Date Get_EXP();
        int Get_status();
        void Set_amount_after_export(const int&);
        const Goods& operator= (const Goods&);
        ~Goods();
};
void Standardized(string&);