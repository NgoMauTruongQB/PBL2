#include <iostream>
#include <string>
using namespace std;

class Order_Status
{
    protected:
        bool Delivery;
        bool Payment;
        // int tinh trang gioa hang;
        // bool trinh trang thanh toan;
        // bool gioa hang khong thanh cong - tra hang - giao lai
    public:
        Order_Status(bool = true, bool = true);
        void Set_Delivery(bool);
        void Set_Payment(bool);
        bool Get_Delivery();
        bool Get_Payment();
        bool Check_Delivery(int);
        bool Check_Payment(int);
        bool Check_Order_Status(int);
        ~Order_Status();
};

class Customer : public Order_Status
{
    private:
        string Customer_name;
        string Address;
        string Phone_number;
        Order_Status Check;
    public:
        Customer(string = "", string = "", string = "");
        void Customer_in();
        void Customer_out();
        void Customer_update();
        ~Customer();
};