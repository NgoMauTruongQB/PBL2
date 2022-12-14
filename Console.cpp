#include <windows.h>
#include <ctype.h>
#include <string>
#include <conio.h>
#include "Manage.h"
#pragma GCC diagnostic ignored "-Wwrite-strings"
using namespace std;

string dis = distance();

void Check_valid_option(string checkValidOption, int &select, int maxValue)
{
    bool valid = true;
    do
    {
        if (valid == false) cout << dis << "Lua chon cua ban khong hop le... Hay chon lai: ";
        valid = true;
        getline(cin, checkValidOption);
        if (checkValidOption.empty() == false)
        {
            for (int i = 0; i < checkValidOption.length(); i++)
            {
                if (checkValidOption[i] < 48 || checkValidOption[i] > 57)
                {
                    valid = false;
                    break;
                }
            }
        }
        else valid = false;
        if (valid)
        {
            if (checkValidOption.length() >= 9)
            {
                valid = false;
            }
            else
            {
                select = stoi(checkValidOption);
                if (select < 1 || select > maxValue)
                {
                    valid = false;
                }
            }
        }
    }while (!valid);
}

void checkValidFileName(string &fileName)
{
    bool checkValid = true;
    do
    {
        if (checkValid == false) cout << dis << "Ten cua tep khong hop lai... Hay nhap lai: ";
        checkValid = true;
        getline(cin, fileName);
        for (int i = 0; i < fileName.length(); i++)
        {
            if (fileName[i] == ' ')
            {
                checkValid = false;
                break;
            }
        }
    }while(!checkValid);
}
void Update_file_database(GoodsManagement& g, ListCustomer& lc, ListBill& lb ,string File_goods_database = "Database.txt", string File_cus_database = "Customer_database.txt", string File_bill_database = "Bill_database.txt")
{
    fstream goods_out, cus_out, bill_out;
    goods_out.open(File_goods_database, ios::out | ios::trunc);
    for (int i = 0; i < g.Get_length(); i++)
    {
        goods_out << g[i].Get_batch() << "," << g[i].Get_good_name() << ","
            << g[i].Get_origin() << "," << g[i].Get_type() << ","
            << g[i].Get_EXP().to_String() << "," << g[i].Get_amount() << ","
            << setprecision(18) << g[i].Get_cost() * g[i].Get_amount() << "," << g[i].Get_import_date().to_String();
        if (i < g.Get_length() - 1) goods_out << endl;
    }
    goods_out.ignore();
    goods_out.close();

    cus_out.open(File_cus_database, ios::out | ios::trunc);
    for (int i = 0; i < lc.Get_length(); i++) 
    {
        cus_out << lc[i].Get_ID() << "," << lc[i].Get_name() << ","
                << lc[i].Get_address() << "," << lc[i].Get_PhoneNumber();
        if (i < lc.Get_length() - 1) cus_out << endl;
    }
    cus_out.ignore();
    cus_out.close();

    bill_out.open(File_bill_database, ios::out | ios::trunc);
    for (int i = 0; i < lb.Get_vector().size(); i++)
    {
        bill_out << lb[i].Get_ID() << "," << lb[i].Get_PayStatus() << "," << lb[i].Get_date_of_bill().to_String() << "," << lb[i].Get_vector().size() << ",";
        for (int j = 0 ; j < lb[i].Get_vector().size(); j++)
        {
            bill_out << lb[i].Get_vector().at(j)->Get_id() << "-" << lb[i].Get_vector_expAmount().at(j);
            (j < lb[i].Get_vector().size() - 1) ? bill_out << " " : bill_out << ",";
        }
        bill_out << lb[i].Get_customer()->Get_ID();
        if (i < lb.Get_vector().size() - 1) bill_out << endl;
    }
    bill_out.ignore();
    bill_out.close();
}

void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}

void gotoxy(int x, int y)
{
  static HANDLE h=NULL;
  if(!h)
    h=GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c={x,y};
  SetConsoleCursorPosition(h,c);
}

void viet(int x, int y, int z)
{
	gotoxy(x,y);
	cout << (char)z;
}

void vietchuoi(int x, int y, char s[], int mau)
{
	gotoxy(x,y);
	textcolor(mau);
	puts(s);
}

int bangmenu(int x, int y, int m, int n, int mau)
{
	int i, j;
	textcolor(mau);
	for(i=x;i<=x+m;i++)
		for(j=y;j<=y+n;j++)
		{
			if(i==x || i==x+m)
			{
				if(j==y && i!=x+m)
					viet(i,j,218);
				else if(j==y && i!=x)
					viet(i,j,191);
				else if(j==y+n && i!=x+m)
					viet(i,j,192);
				else if(j==y+n && i!=x)
					viet(i,j,217);
				else viet(i,j,179);
			}
			else if(j==y || j==y+n)
					viet(i,j,196);
		}
}

void Import(GoodsManagement &g)
{
    int select;
    do
    {
        string checkValidOption;
        system("cls");
         bangmenu(65,1,30,5,6);
        vietchuoi(70,2,"TINH NANG NHAP HANG",11);
        vietchuoi(68,3,"1. Tu file",11);
        vietchuoi(68,4,"2. Tu nguoi su dung",11);
        vietchuoi(68,5,"3. Quay lai",11);
        gotoxy(68,7); cout << "Lua chon:";
        Check_valid_option(checkValidOption, select, 3);
        switch (select)
        {
        case 1:
        {
            string file_name;
            cout << dis << "Ten file: "; checkValidFileName(file_name);
            try 
            {
                g.Input_from_file(file_name);
                cout << dis << "Nhap hang tu file " << file_name << " thanh cong..." << endl;
            }
            catch (string e)
            {
                cout << dis << e << endl;
            }
            cout << dis; system("pause");  
            break;
        }
        case 2:
        {
            g.Input();
            cout << dis << "Nhap hang thanh cong..." << endl;
            cout << dis; system("pause");
            break;
        }
        }
    }while ( select < 3);
}
void Export(GoodsManagement &g, ListCustomer &lc, ListBill &lb)
{
    int select;
    bool check_export =  false, checkk_print_bill = true;
    do
    {
        string checkValidOption;
        system("cls");
        bangmenu(65,1,30,6,6);
        vietchuoi(70,2,"TINH NANG XUAT HANG",11);
        vietchuoi(68,3,"1. Theo goi",11);
        vietchuoi(68,4,"2. Theo nguoi su dung",11);
        vietchuoi(68,5,"3. In hoa don",11);
        vietchuoi(68,6,"4. Quay lai",11);
        gotoxy(68,8); cout << "Lua chon:";
        Check_valid_option(checkValidOption, select, 4);        
        switch (select)
        {
        case 1:
            cout << dis << "Chuc nang nay se duoc cap nhat som..." << endl;   
            cout << dis; system("pause");
            break;
        case 2:
        {
            try
            {
                if (!checkk_print_bill) cout << dis << "Ban phai in hoa don moi nhat truoc khi thuc hien cho lan tiep theo!" << endl;
                else
                {
                    g.Export(lc, lb);
                    cout << dis << "Xuat hang thanh cong!..." << endl;
                    check_export = true;
                    checkk_print_bill = false;
                }
                cout << dis; system("pause");
                break;
            }
            catch (string e)
            {
                check_export = false;
                cout << dis << e << endl;
                cout << dis; system("pause");
                break;
            }
        }
        case 3:
        {
            if (check_export)
            {
                string file_name = "Bill.txt";
                // cout << dis << "Ten tep: "; 
                // checkValidFileName(file_name);
                lb[lb.Get_vector().size()-1].Print(file_name);
                cout << dis << "In hoa don thanh cong!..." << endl;
                check_export = false;
                checkk_print_bill = true;
            }
            else cout << dis << "Ban khong co hoa don nao de in..." << endl;
            cout << dis; system("pause");
            break;
        }
        default:
        {
            if (!checkk_print_bill) 
            {
                cout << dis << "Ban phai in hoa don moi nhat truoc khi thoat tinh nang nay!" << endl;
                cout << dis; system("pause");
                select = 0;
            }
        }
        }
    }while(select < 4);
}
void Update(GoodsManagement &g)
{
    string Goods_name;
    cout << dis << "Nhap ten hang hoa ma ban muon cap nhat: "; getline(cin, Goods_name);
    if (g.Find_name_goods(Goods_name) == false) cout<< dis << "Khong co hang hoa nay trong kho!" << endl;
    else
    {
        map<int, string> mapping;
        g.Search(mapping, Goods_name, 1);
        int select, index_of_id;
        cout << dis << "Lua chon hang hoa de cap nhat: "; cin >> index_of_id; cin.ignore();
        int index = g.Find_id(mapping[index_of_id]);
        if (index == -1)
        {
            cout << dis << "Khong tim thay hang hoa nay." << endl;
            return;
        }
        try
        {
            do
            {
                string checkValidOption;
                system("cls");
                g.Search(mapping, Goods_name, 1);
                bangmenu(65,1,60,12,6);
                vietchuoi(70,2,"TINH NANG CAP NHAT",11);
                vietchuoi(68,3,"1. Lo",11);
                vietchuoi(68,4,"2. Ten ",11);
                vietchuoi(68,5,"3. Nguon goc",11);
                vietchuoi(68,6,"4. Loai ",11);
                vietchuoi(68,7,"5. Han su dung ",11);
                vietchuoi(68,8,"6. So luong ",11);
                vietchuoi(68,9,"7. Gia nhap",11);
                vietchuoi(68,10,"8. Ngay nhap",11);
                vietchuoi(68,11,"9. Quay lai",11);
                gotoxy(68,13); cout << "Lua chon:";
                Check_valid_option(checkValidOption, select, 9);                    
                switch (select)
                {
                    case 1:
                        cout << dis << "Lo: ";
                        g.Update(index, select);
                        cout << dis << "Cap nhat lo thanh cong..." << endl;
                        cout << dis; system("pause");
                        break;
                    case 2:
                        cout << dis << "Ten: ";
                        g.Update(index, select);
                        cout << dis << "Cap nhat ten thanh cong..." << endl;
                        cout << dis; system("pause");
                        break;
                    case 3:
                        cout << dis << "Nguon goc: ";
                        g.Update(index, select);
                        cout << dis << "Cap nhat nguon goc thanh cong..." << endl;
                        cout << dis; system("pause");
                        break;
                    case 4:
                        cout << dis << "Loai: ";
                        g.Update(index, select);
                        cout << dis << "Cap nhat loai thanh cong..." << endl;
                        cout << dis; system("pause");
                        break;
                    case 5:
                        try
                        {
                            cout << dis << "Han su dung";
                            g.Update(index, select);
                            cout << dis << "Cap nhat han su dung thanh cong..." << endl;
                            cout << dis; system("pause");
                            break;
                        }
                        catch(string e)
                        {
                            cout << dis << e << endl;
                            cout << dis; system("pause");
                            break;
                        }
                    case 6:
                        cout << dis << "So luong: ";
                        g.Update(index, select);
                        cout << dis << "Cap nhat so luong thanh cong..." << endl;
                        cout << dis; system("pause");
                        cin.ignore();
                        break;
                    case 7:
                        cout << dis << "Gia nhap: ";
                        g.Update(index, select);
                        cout << dis << "Cap nhat gia nhap thanh cong..." << endl;
                        cout << dis; system("pause");
                        cin.ignore();
                        break;
                    case 8:
                        try
                        {
                            cout << dis << "Ngay nhap";
                            g.Update(index, select);
                            cout << dis << "Cap nhat ngay nhap thanh cong..." << endl;
                            cout << dis; system("pause");
                            break;
                        }
                        catch(string e)
                        {
                            cout << dis << e << endl;
                            cout << dis; system("pause");
                            break;
                        }
                    default:
                        cout << dis << "Cap nhat hang hoa thanh cong..." << endl;     
                }
            } while (select < 9);
        }
        catch(string e)
        {
            cout << dis << e << endl;
        }
    }
}
void Delete(GoodsManagement &g)
{
    string Goods_name;
    cout << dis << "Nhap ten hang hoa ma ban muon xoa: "; getline(cin, Goods_name);
    if (g.Find_name_goods(Goods_name) == false) cout << dis << "Khong co hang hoa nay trong kho." << endl;
    else
    {
        map<int, string> mapping;
        g.Search(mapping, Goods_name, 1);
        int select;
        cout << dis << "Lua chon hang hoa de xoa: "; cin >> select; cin.ignore();
        try
        {
            g.Delete(mapping.at(select)); 
            cout << dis << "Xoa hang hoa thanh cong..." << endl;         
        }
        catch(string e)
        {
            cout << dis << e << endl;
        } 
    }
}
void Sort(GoodsManagement &g, map<int, string> mapping)
{
    int select;
    do
    {
        string checkValidOption;
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n\n";
        g.Show_information();
        bangmenu(65,1,30,7,6);
        vietchuoi(70,2,"TINH NANG SAP XEP",11);
        vietchuoi(68,3,"1. Theo ten san pham",11);
        vietchuoi(68,4,"2. Theo han su dung",11);
        vietchuoi(68,5,"3. Theo ngay nhap",11);
        vietchuoi(68,6,"4. Theo loai ",11);
        vietchuoi(68,7,"5. Quay lai ",11);
        gotoxy(68,9); cout << "Lua chon:";
        Check_valid_option(checkValidOption, select, 5);
        if (select < 5)
        {
            int ascORdesc;
            cout << dis << "Tang dan[1] hay Giam dan[2]: "; cin >> ascORdesc; cin.ignore();
            g.Sort(select, ascORdesc);
            cout << "\n\n\n\n\n\n\n\n\n\n\n";
            g.Show_information();
            cout << dis; system("pause");
        }
    }while(select < 5);
}
void Search(GoodsManagement &g)
{
    int select;
    do
    {
        string checkValidOption;
        system("cls");
        bangmenu(65,1,30,6,6);
        vietchuoi(70,2,"TINH NANG TIM KIEM",11);
        vietchuoi(68,3,"1. Theo ten san pham",11);
        vietchuoi(68,4,"2. Theo loai san pham",11);
        vietchuoi(68,5,"3. Theo lo hang",11);
        vietchuoi(68,6,"4. Quay lai ",11);
        gotoxy(68,8); cout << "Lua chon:";
        Check_valid_option(checkValidOption, select, 4);
        map<int, string> mapping;
        switch (select)
        {
        case 1:
        {
            string goods_name;
            cout << dis << "Nhap ten hang hoa ma ban muon tim kiem: "; getline(cin, goods_name);
            g.Search(mapping, goods_name, 1);
            break;
        }
        case 2:
        {
            string goods_type;
            cout << dis << "Nhap loai hang hoa ma ban muon tim kiem: "; getline(cin, goods_type);
            g.Search(mapping, goods_type, 2);
            break;
        }
        case 3:
        {
            string goods_batch;
            cout << dis << "Nhap Lo hang ma ban muon tim kiem: "; getline(cin, goods_batch);
            g.Search(mapping, goods_batch, 3);
            break;
        }
        }
        if (select < 4) { cout << dis; system("pause"); }
    }while (select < 4);
    
}
void Goods_Object(GoodsManagement &g, ListCustomer &lc, ListBill &lb)
{
    int select;
    do
    {
        string checkValidOption;
        system("cls");
        bangmenu(65,1,60,10,6);
        vietchuoi(77,2,"DANH SACH LUA CHON CHO HANG HOA",11);
        vietchuoi(68,3,"1. Nhap hang",11);
        vietchuoi(68,4,"2. Xuat hang ",11);
        vietchuoi(68,5,"3. Cap nhat",11);
        vietchuoi(68,6,"4. Xoa",11);
        vietchuoi(68,7,"5. Sap xep",11);
        vietchuoi(68,8,"6. Tim kiem",11);
        vietchuoi(68,9,"7. Hien thi thong tin",11);
        vietchuoi(68,10,"8. Quay lai ",11);
        gotoxy(68,12); cout << "Lua chon:";
        Check_valid_option(checkValidOption, select, 8);
        switch (select)
        {
        case 1:
            Import(g);
            break;
        case 2:
            Export(g, lc, lb);
            break;
        case 3:
            Update(g);
            cout << dis; system("pause");
            break;
        case 4:
            Delete(g);
            cout << dis; system("pause");
            break;
        case 5:
        {
            map<int, string> mapping;
            Sort(g, mapping);
            cout << dis; system("pause");
            break;
        }    
        case 6:
        {
            Search(g);
            break;
        }
        case 7:
        {
            g.Show_information();
            cout << dis; system("pause");
            break;
        }
    }
    }while (select < 8);
}
void Customer_Object(GoodsManagement &g, ListCustomer &lc, ListBill &lb)
{
    int select;
    do
    {
        string checkValidOption;
        system("cls");
        bangmenu(65,1,45,10,6);
        vietchuoi(70,2,"DANH SACH LUA CHON CHO KHACH HANG",11);
        vietchuoi(68,3,"1. Them khach hang moi",11);
        vietchuoi(68,4,"2. Cap nhat ",11);
        vietchuoi(68,5,"3. Xoa  ",11);
        vietchuoi(68,6,"4. Tim kiem ",11);
        vietchuoi(68,7,"5. Hien thi thong tin  ",11);
        vietchuoi(68,8,"6. Thanh toan hoa don  ",11);
        vietchuoi(68,9,"7. Lich su thanh toan  ",11);
        vietchuoi(68,10,"8. Quay lai ",11);
        gotoxy(68,12); cout << "Lua chon:";
        Check_valid_option(checkValidOption, select, 8);
        switch (select)
        {
            case 1:
            {
                try
                {
                    Customer c;
                    cin >> c;
                    lc.Add(c);
                    cout << dis << "Them khach hang moi thanh cong..." << endl;  
                    cout << dis; system("pause");
                    break;
                }
                catch(string e)
                {
                    cout << dis << e << endl;
                    cout << dis; system("pause");
                }
            }            
            case 2:
            {
                string id;
                cout << dis << "Nhap ID cua khach hang ma ban muon cap nhat: "; getline(cin, id);
                int index = lc.Find_id(id);
                if (index == -1) 
                {
                    cout << dis << "Khong tim thay ID nay..." << endl;
                    cout << dis; system("pause");
                }
                else
                {
                    int select;
                    do
                    {
                        //system("cls");
                        lc.Show_information(id);
                        string checkValidOption;
                        system("cls");
                        bangmenu(65,1,33,6,6);
                        vietchuoi(72,2,"TINH NANG CAP NHAT",11);
                        vietchuoi(68,3,"1. Ten",11);
                        vietchuoi(68,4,"2. Dia chi",11);
                        vietchuoi(68,5,"3. So dien thoai",11);
                        vietchuoi(68,6,"4. Quay lai",11);
                        gotoxy(68,8); cout << "Lua chon:";
                        Check_valid_option(checkValidOption, select, 4);
                        lc.Update(index, select);
                        if (select < 4) { cout << dis; system("pause"); }
                    } while(select < 4);
                }
                break;
            }
            case 3:
            {
                try
                {
                    string id;
                    cout << dis << "Nhap ID cua khach hang ma ban muon xoa: "; getline(cin, id);
                    lc.Delete(id);
                    cout << dis << "Xoa khach hang co ID: " << id << " thanh cong..." << endl;
                    cout << dis; system("pause");
                    break;
                }
                catch(string e)
                {
                    cout << dis << e << endl;
                    cout << dis; system("pause");
                    break;
                }
            }
            case 4:
            {
                try
                {
                    string id;
                    cout << dis << "Nhap ID cua khach hang ma ban muon tim kiem: "; getline(cin, id);
                    lc.Show_information(id);   
                    cout << dis; system("pause");
                    break;
                }
                catch(string e)
                {
                    cout << dis << e << endl;
                    cout << dis; system("pause");
                }
            }
            case 5:
                lc.Show_information();   
                cout << dis; system("pause");
                break;
            case 6:
            {
                try
                {
                    string id;
                    int indexOfListBill;
                    cout << dis << "Nhap ID khach hang muon thanh toan hoa don tra sau: "; getline(cin, id);
                    int indexOfListCustomer = lc.Find_id(id);
                    if (indexOfListCustomer != -1)
                    {
                        lc.Show_information(id);
                        if (lc[indexOfListCustomer].Get_vector().size() == 0)
                        {
                            cout << dis << "Khach hang nay chua mua hang hoa nao!" << endl;
                        }
                        else indexOfListBill = lb.Find_id(lc[indexOfListCustomer].Get_vector().at(lc[indexOfListCustomer].Get_vector().size() - 1).Get_ID());


                        if (lb[indexOfListBill].Get_PayStatus())
                        {
                            cout << dis << "Khach hang nay da thanh toan hoa don!" << endl;
                        }
                        else
                        {
                            cout << dis << "Xac nhan thanh toan: Co[1] | Khong [2]: "; 
                            char ch;
                            do
                            {
                                ch = getchar(); cin.ignore();
                                if (ch == '1') lb[indexOfListBill].Set_PayStatus(true);
                                else if (ch != '2') 
                                {
                                    ch = '0';
                                    cout << dis << "Xac nhan khong chinh xac ... Lua chon lai: ";
                                }
                            }while(ch == '0');
                            cout << dis << "Xac nhan thanh toan hoa don thanh cong" << endl;
                            lc[indexOfListCustomer].Update_bill(lb[indexOfListBill]);
                        }
                    }
                    else cout << dis << "Khong tim thay khach hang nay!" << endl;
                    cout << dis; system("pause");
                    break;  
                }
                catch(string e)
                {
                    cout << dis << e << endl;
                    cout << dis; system("pause");
                    break;
                }
            }
            case 7:
            {
                string id;
                cout << dis << "Nhap ID khach hang ma ban muon xem lich su thanh toan: "; getline(cin, id);
                int index = lc.Find_id(id);
                if(index != -1)
                {
                    string dis_temp = dis;
                    dis_temp.erase(0, 4);
                    cout << dis_temp << "-------------------------------------- LICH SU THANH TOAN --------------------------------------" << endl << endl;
                    for (int i = 0; i < lc[index].Get_vector().size(); i++)
                    {
                        lc[index].Get_vector()[i].Show();
                        cout << dis_temp << "________________________________________________________________________________________________" << endl << endl;
                    }
                    cout << dis_temp << "------------------------------------------- KET THUC -------------------------------------------" << endl;
                }
                else
                {
                    cout << dis << "Khong tim thay khach hang nay!" << endl;
                }
                cout << dis; system("pause");
            }
        }
    }while (select < 8);
}

void Menu(GoodsManagement &g, ListCustomer &lc, ListBill &lb)
{
    try
    {
        g.Input_from_file("Database.txt");
        lc.Input_from_file("Customer_database.txt");
        lb.Input_from_file("Bill_database.txt", g, lc);
    }
    catch(string e)
    {
        cout << dis << e << endl;
        cout << dis; system("pause");
        return;
    }
    int select;
    do
    {
        string checkValidOption;
        system("cls");
        bangmenu(65,1,33,5,6);
        vietchuoi(74,2,"LUA CHON DOI TUONG",11);
        vietchuoi(68,3,"1. Khach hang",11);
        vietchuoi(68,4,"2. Hang hoa",11);
        vietchuoi(68,5,"3. Thoat",11);
        gotoxy(68,8); cout << "Lua chon:";
        Check_valid_option(checkValidOption, select, 3);
        switch (select)
        {
        case 1:
            Customer_Object(g, lc, lb);
            break;
        case 2:
            Goods_Object(g, lc, lb);
            break;
        default:
            Update_file_database(g, lc, lb, "test1.txt", "test2.txt", "test3.txt");
            cout << endl << dis << "Cam on ban da su dung dich vu cua chung toi ^_^...  Chuc ban mot ngay tot lanh!" << endl << endl;
        }   
    } while (select < 3);
}

int main()
{
  GoodsManagement g;
  ListCustomer lc;
  ListBill lb;
  Menu(g, lc, lb);
  return 0;
}