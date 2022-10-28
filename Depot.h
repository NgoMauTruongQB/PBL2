#include <string>
#include <vector>
#include <fstream>
using namespace std;
class SubArea
{
    private: 
        string SubArea_name;
        string SuperArea;
        int Remaning_amount;
    public:
        SubArea(string = "", string = "", int = 0);
        void SubArea_in(ifstream& );
        void SubArea_out();
        void Set_amount(int = 0);
        string Get_SubArea_name();
        string Get_SuperArea();
        bool Check_empty(int);
        ~SubArea();
};
class SuperArea
{
    private:
        string SuperArea_name;
        vector<SubArea> All_SubArea;
        int SubArea_amount;
        int Max_capacity;
    public:
        SuperArea();
        SuperArea(string, int, int);
        ~SuperArea();   
        void SuperArea_in(ifstream&);
        void SuperArea_out();
        string Get_superArea_name();
        void Empty_postion();
};
class Depot
{
    private:
        vector<SuperArea> All_SuperArea;
        int SuperArea_amount;
    public:
        Depot();
        Depot(int);
        int Find_SuperArea(string); 
        void Depot_in(ifstream& in);
        void Depot_out(string = "");
        void Empty_position(string = "");
        ~Depot();
};