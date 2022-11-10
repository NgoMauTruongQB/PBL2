#include "Customer.h"


// class Order_Status
Order_Status::Order_Status(bool d, bool p)
{
    this->Delivery = d;
    this->Payment = p;
}
void Order_Status::Set_Delivery(bool check)
{
    if(check == 1)
        this->Delivery = 1;
    else 
        this->Delivery = 0;
}
void Order_Status::Set_Payment(bool check)
{
    if(check == 1)
        this->Payment = 1;
    else 
        this->Payment = 0;
}
bool Order_Status::Get_Delivery()
{
    return this->Delivery;
}
bool Order_Status::Get_Payment()
{
    return this->Payment;
}
Order_Status::~Order_Status(){

}

// class Customer

Customer::Customer(string name, string add, string phone)
{
    this->Customer_name = name;
    this->Address = add;
    this->Phone_number = phone;
}
void Customer::Customer_in()
{
    cout << "Customer's name: ";
    getline(cin, this->Customer_name);
    cout << "Address: "; 
    getline(cin, this->Address);
    cout << "Phone number: "; 
    cin >> this->Phone_number;
}

// void Customer::Customer_in(int x, int y)
// {
//     system("cls");
//     gotoXY(x, y);
//     cout << (char) 218;
//     for(int i = 0; i < 60; i++)
//         cout << (char) 196;
//     cout << (char) 191;
//     gotoXY(x, y + 1);
//     cout << (char) 179;
//     gotoXY(x + 61, y + 1);
//     cout << (char) 179;
//     gotoXY(x, y + 2);
//     cout << (char) 192;
//     for(int i = 0; i < 60; i++)
//         cout << (char) 196;
//     cout << (char) 217;
//     cout << "Customer's name: ";
//     getline(cin, this->Customer_name);
//     cout << "Address: "; 
//     getline(cin, this->Address);
//     cout << "Phone number: "; 
//     cin >> this->Phone_number;
// } 
void Customer::Customer_out()
{
    cout << "Name: " << this->Customer_name 
         << " ,Address: " << this->Address
         << " ,Phone number: " << this->Phone_number << endl;

}
void Customer::Customer_update()
{
    int n;
    do
    {
        cout << "1. Update Delivery: " << endl;
        cout << "2. Update Payment: " << endl;
        cin >> n;
        switch (n)
        {
        case 1:
            int k;
            do
            {
                cout << "1.Successful delivery..." << endl;
                cout << "2.Unsuccessful delivery... " << endl;
                cin >> k;
                if(k == 1)
                    Set_Delivery(true);
                else
                    Set_Delivery(false);
            } while (k =! 1 && k != 2);
            break;
        case 2:
            int h;
            do
            {
                cout << "1.Payment completed..." << endl;
                cout << "2.Payment not completed..." << endl;
                cin >> h;
                if(h == 1)
                    Set_Payment(true);
                else 
                    Set_Payment(false);
            } while (h != 1 && h != 2);
            break;
        default:
            break;
    }
    } while (n != 1 && n != 2);
}
Customer::~Customer(){
}