// #pragma once
#include "Manage.h"
using namespace std;
void Check_valid_option(string distance, string checkValidOption, int &select, int maxValue)
{
    bool valid = true;
    do
    {
        if (valid == false) cout << distance << "Your option is not valid... Please choose again: ";
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
            select = stoi(checkValidOption);
            if (select < 1 || select > maxValue)
            {
                valid = false;
            }
        }
    }while (!valid);
}
void checkValidFileName(string distance, string &fileName)
{
    bool checkValid = true;
    do
    {
        if (checkValid == false) cout << distance << "File of name is not valid... Please enter again: ";
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
void Import(string distance, GoodsManagement &g)
{
    int select;
    do
    {
        string checkValidOption;
        system("cls");
        cout << distance << " ------ List Option Of Import ------ " << endl
             << distance << "|       1. From file                |" << endl
             << distance << "|       2. From user                |" << endl
             << distance << "|       3. Print bill               |" << endl
             << distance << "|       4. Back                     |" << endl
             << distance << " ----------------------------------- " << endl
             << distance << "Choose option: ";
        Check_valid_option(distance, checkValidOption, select, 4);
        switch (select)
        {
        case 1:
        {
            string file_name;
            cout << distance << "File name: "; checkValidFileName(distance, file_name);
            try 
            {
                g.Input_from_file(file_name);
                cout << distance << "Import goods from " << file_name << " file successfully..." << endl;
            }
            catch (string e)
            {
                cout << distance << e << endl;
            }
            cout << distance; system("pause");  
            break;
        }
        case 2:
        {
            g.Input(distance);
            cout << distance << "Import goods successfully..." << endl;
            cout << distance; system("pause");
            break;
        }
        case 3:
        {
            string file_name;
            cout << distance << "File name: "; checkValidFileName(distance, file_name);
            g.Print_bill(file_name, true);
            cout << distance; system("pause");
            break;
        }
        }
    }while ( select < 4);
}
void Export(string distance, GoodsManagement &g)
{
    int select;
    do
    {
        string checkValidOption;
        system("cls");
        cout << distance << " ------ List Option Of Export ------ " << endl
             << distance << "|       1. By package               |" << endl
             << distance << "|       2. By user                  |" << endl
             << distance << "|       3. Print bill               |" << endl
             << distance << "|       4. Back                     |" << endl
             << distance << " ----------------------------------- " << endl
             << distance << " Choose option: ";
        Check_valid_option(distance, checkValidOption, select, 4);        
        switch (select)
        {
        case 1:
            cout << distance << "This function is not available yet..." << endl;   
            system("pause");
            break;
        case 2:
        {
            g.Output(distance);
            system("pause");
            break;
        }
        case 3:
        {
            string file_name;
            cout << distance << "File name: "; 
            checkValidFileName(distance, file_name);
            g.Print_bill(file_name, false);
            system("pause");
            break;
        }
        }
    }while(select < 4);
}
void Update(string distance, GoodsManagement &g)
{
    string Goods_name;
    cout << distance << "Enter the name of goods which you want to update: "; getline(cin, Goods_name);
    if (g.Find_name_goods(Goods_name) == false) cout<< distance << "Don't have this goods in your depot." << endl;
    else
    {
        map<int, string> mapping;
        g.Show_information(distance, mapping, Goods_name);
        int select, index_of_id;
        cout << distance << "What do you want to update: "; cin >> index_of_id; cin.ignore();
        int index = g.Find_id(mapping.at(index_of_id));
        if (index == -1)
        {
            cout << distance << "Can't find this id." << endl;
            return;
        }
        try
        {
            do
            {
                string checkValidOption;
                system("cls");
                cout << distance << " ------ List Option Of Update ------ " << endl
                    << distance << "|       1. Batch                    |" << endl
                    << distance << "|       2. Name                     |" << endl
                    << distance << "|       3. Type                     |" << endl
                    << distance << "|       4. Origin                   |" << endl
                    << distance << "|       5. Expiry date              |" << endl
                    << distance << "|       6. Amount                   |" << endl
                    << distance << "|       7. Import cost              |" << endl
                    << distance << "|       8. Import date              |" << endl
                    << distance << "|       9. Back                     |" << endl
                    << distance << " ----------------------------------- " << endl
                    << distance << " Choose option: ";
                Check_valid_option(distance, checkValidOption, select, 9);                    
                switch (select)
                {
                    case 1:
                        cout << distance << "Batch: ";
                        g.Update(index, select);
                        cout << distance << "Update batch successfully..." << endl;
                        break;
                    case 2:
                        cout << distance << "Name: ";
                        g.Update(index, select);
                        cout << distance << "Update name successfully..." << endl;
                        break;
                    case 3:
                        cout << distance << "Type: ";
                        g.Update(index, select);
                        cout << distance << "Update type successfully..." << endl;
                        break;
                    case 4:
                        cout << distance << "Origin: ";
                        g.Update(index, select);
                        cout << distance << "Update origin successfully..." << endl;
                        break;
                    case 5:
                        cout << distance << "Expiry date: ";
                        try
                        {
                            g.Update(index, select);
                            cout << distance << "Update expiry date successfully..." << endl;
                        }
                        catch(string e)
                        {
                            cout << distance << e << endl;
                        }
                        break;
                    case 6:
                        cout << distance << "Amount: ";
                        g.Update(index, select);
                        cout << distance << "Update amount successfully..." << endl;
                        break;
                    case 7:
                        cout << distance << "Import cost: ";
                        g.Update(index, select);
                        cout << distance << "Update import cost successfully..." << endl;
                        break;
                    case 8:
                        cout << distance << "Import date: ";
                        try
                        {
                            g.Update(index, select);
                            cout << distance << "Update import date successfully..." << endl;
                        }
                        catch(string e)
                        {
                            cout << distance << e << endl;
                        }
                        break;
                    default:
                        cout << distance << "Goods update successfully..." << endl;     
                }
            } while (select < 9);
        }
        catch(string e)
        {
            cout << distance << e << endl;
        }
    }
}
void Delete(string distance, GoodsManagement &g)
{
    string Goods_name;
    cout << distance << "Enter the name of goods which you want to delete: "; getline(cin, Goods_name);
    if (g.Find_name_goods(Goods_name) == false) cout << distance << "Don't have this goods in your depot." << endl;
    else
    {
        map<int, string> mapping;
        g.Show_information(distance, mapping, Goods_name);
        int select;
        cout << distance << "What do you want to delete: "; cin >> select; cin.ignore();
        try
        {
            g.Delete(mapping.at(select)); 
            cout << distance << "Goods deleted successfully..." << endl;         
        }
        catch(string e)
        {
            cout << distance << e << endl;
        }
    }
}
void Sort(string distance, GoodsManagement &g, map<int, string> mapping)
{
    int select;
    do
    {
        string checkValidOption;
        system("cls");
        g.Show_information(distance, mapping);
        cout << distance << " ------- List Option Of Sort ------ " << endl
             << distance << "|       1. Sort by name            |" << endl
             << distance << "|       2. Sort by expiry date     |" << endl
             << distance << "|       3. Sort by import date     |" << endl
             << distance << "|       4. Sort by type            |" << endl
             << distance << "|       5. Back                    |" << endl
             << distance << " ---------------------------------- " << endl;
        cout << distance << " Choose option: ";
        Check_valid_option(distance, checkValidOption, select, 5);
        if (select < 5)
        {
            int ascORdesc;
            cout << distance << "Ascending[1] or Descending[2]: "; cin >> ascORdesc; cin.ignore();
            g.Sort(select, ascORdesc);
            g.Show_information(distance, mapping);
            cout << distance; system("pause");
        }
    }while(select < 5);
}
void Menu(string distance, GoodsManagement &g)
{
    g.Input_from_file("Database.txt");
    int select;
    do
    {
        string checkValidOption;
        system("cls");
        cout << distance << " ------ List Option Of Goods ------ " << endl
             << distance << "|       1. Import                  |" << endl
             << distance << "|       2. Export                  |" << endl
             << distance << "|       3. Update                  |" << endl
             << distance << "|       4. Delete                  |" << endl
             << distance << "|       5. Sort                    |" << endl
             << distance << "|       6. Search                  |" << endl
             << distance << "|       7. Show information        |" << endl
             << distance << "|       8. Exit                    |" << endl
             << distance << " ---------------------------------- " << endl;
        cout << distance << " Choose option: ";
        Check_valid_option(distance, checkValidOption, select, 8);
        switch (select)
        {
        case 1:
            Import(distance, g);
            break;
        case 2:
            Export(distance, g);
            cout << distance; system("pause");
            break;
        case 3:
            Update(distance, g);
            cout << distance; system("pause");
            break;
        case 4:
            Delete(distance, g);
            cout << distance; system("pause");
            break;
        case 5:
        {
            map<int, string> mapping;
            Sort(distance, g, mapping);
            cout << distance; system("pause");
            break;
        }    
        case 6:
        {
            map<int, string> mapping;
            string goods_name;
            cout << distance << "Enter the goods of name which you want to search: "; getline(cin, goods_name);
            g.Show_information(distance, mapping, goods_name);
            cout << distance; system("pause");
            break;
        }
        case 7:
        {
            map<int,string> mapping;
            g.Show_information(distance, mapping);
            cout << distance; system("pause");
            break;
        }
        default:
            //g.Update_file_database();
            cout << endl << distance << "Thanks for using our software ^_^...  Have a nice day!" << endl << endl;
        }
    }while (select < 8);
}

int main()
{
    string distance = "";
    for (int i = 0; i < 20; i++) distance += " ";
    GoodsManagement g;
    Menu(distance, g);
    // g.Input_from_file("Database");
    // map<int, string> mapping;
    // g.Show_information(distance, mapping);
    // cout << Asc(g[0].Get_good_name(), g[1].Get_good_name()) << endl;
    return 0;
}
