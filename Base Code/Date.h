#include <string>
using namespace std;
class Date
{
    private:
        int Day;
        int Month;
        int Year;
    public:
        Date(int = 1, int = 1, int = 2022);
        void Input();
        void Input_from_file(fstream&);
        void Input(string);
        void Output();
        bool Check_Leap_Year();
        int Month_Day();
        void Check_Valid();
        const Date& operator= (const Date&);
        bool operator< (const Date&);
        bool operator> (const Date&);
        void Set_day(const int&);
        void Set_month(const int&);
        void Set_year(const int&);
        int Get_day();
        int Get_month();
        int Get_year();
        string Get_date_str();
        ~Date();
};