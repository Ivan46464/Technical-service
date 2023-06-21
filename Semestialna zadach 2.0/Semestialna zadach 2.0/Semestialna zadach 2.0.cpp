#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include<limits>
using namespace std;
const int Max_orders = 100;
struct Order
{
    unsigned int  Order_number = 0;
    unsigned int  Order_dayofmonth = 0;
    char Order_client[20];
    char Order_typeofdevice[20];
    char Order_id[20];
    char Order_problem[50];
    char Order_nameoftechnik[20];
    char Order_what_order[20];
    char Order_repair_done[50];
   double Order_price = 0;
    int index = 0;
    int index2 = 0;
    char Order_days_of_downtime[20];
    char Order_status[20] = { "" };
};
void Output_updated_info(Order orders[], int& Number_of_made_orders)//Output on the screen all orders, which are updated. 
{
    for (int i = 0; i < Number_of_made_orders; i++) {
        if (orders[i].index ==2) {
            cout << "Order number:" << orders[i].Order_number << endl;
            cout << "Day of the month:" << orders[i].Order_dayofmonth << endl;
            cout << "Client's name:" << orders[i].Order_client << endl;
            cout << "Type of the device:" << orders[i].Order_typeofdevice << endl;
            cout << "Orders id:" << orders[i].Order_id << endl;
            cout << "What problem do you have:" << orders[i].Order_problem << endl;
            cout << "Status of order:" << orders[i].Order_status << endl;
            cout << "Orders type:" << orders[i].Order_what_order << endl;
            cout << "The name of the technik:" << orders[i].Order_nameoftechnik << endl;
            cout << "Repair done:" << orders[i].Order_repair_done << endl;          
            cout << "Days of downtime:" << orders[i].Order_days_of_downtime << endl;           
            cout << "Order price:" << orders[i].Order_price << endl;
            cout << "---------------------------------\n";

        }
    }
    cout << endl;
} 
int Cstring_compare1(char str1[], string str2) //This function compares char array and string and returs 1 if they are equal. 
{
    int index = 0;
    int res = str2.compare(str1);
    if (res == 0)
        index++;
    return index;
}
void Done_orders_by_one_technik(Order orders[], int& Number_of_made_orders)//Sorts orders done by the same tecknik by the day of month, which they are requested.
{                   
            bool issorted;
            for (int i = 0; i < Number_of_made_orders - 1; i++)
            {
                if ((string)orders[i].Order_nameoftechnik == (string)orders[i+1].Order_nameoftechnik)
                {
                    if (orders[i].Order_status == string("Finished order"))
                    {

                        issorted = true;
                        for (int j = 0; j < Number_of_made_orders - i - 1; j++)
                        {


                            if (orders[j].Order_dayofmonth > orders[j + 1].Order_dayofmonth)
                            {
                                swap(orders[j], orders[j + 1]);
                                issorted = false;
                            }


                        }
                        if (issorted)
                            break;
                    }
                }

            }
        
    
}
double What_order_price(Order orders[], int& Number_of_made_orders,double price,double price1,double price2)//This function is foè calculating the price for an order. 
{
    for (int i = 0; i < Number_of_made_orders; i++) 
    {
        int number = Cstring_compare1(orders[i].Order_what_order, "10 days-normal");
        if (number == 1 && orders[i].index2 == 1)
        {
                    
            price2 = price * 1;
        }
        int number1 = Cstring_compare1(orders[i].Order_what_order, "5 days-fast");
        if (number1 ==1  && orders[i].index2 == 2)
        {
            price1 = (price * 0.2);
            price2 = price + price1;
        }
        
       
        int number2 = Cstring_compare1(orders[i].Order_what_order, "2 days-express");
        if (number2 == 1 && orders[i].index2 == 3)
        {
            price1 = price * 0.5;
            price2 = price + price1;
        }
    }
        return price2;
 }
void Order_status(Order orders[], int& Number_of_made_orders)//Adds a status to an order.
{
    
    unsigned int write_order_number1;
    cout << "Write the number of the order to update it:\n";   
    while (!(cin >> write_order_number1)) {
        cout << "Enter number please.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (write_order_number1 > orders[Number_of_made_orders - 1].Order_number) {
        cout << "This order does not exist.\n";
    }
    for (int i = 0; i < Number_of_made_orders; i++)
    {
        
        if (write_order_number1 == orders[i].Order_number)
        {
            int number7 = Cstring_compare1(orders[i].Order_status, "");
            int number8 = Cstring_compare1(orders[i].Order_status, "Accepted order");
            int number9 = Cstring_compare1(orders[i].Order_status, "Finished order");
            if (number7 == 0 && number8 == 0 && number9 == 1) {
                cout << "This order is finished, so it's status cannot be changed\n";
            }
            int number4 = Cstring_compare1(orders[i].Order_status, "");
            int number5 = Cstring_compare1(orders[i].Order_status, "Accepted order");
            int number6 = Cstring_compare1(orders[i].Order_status, "Denied order");
            if (number4 == 0 && number5 == 0 && number6 == 1) {
                cout << "This order is denied so it's status cannot be changed.\n";
            }
            int number1 = Cstring_compare1(orders[i].Order_status, "Accepted order");
            if (number1 == 1 && orders[i].index == 1 && orders[i].Order_price == 0) {
                cout << "This order is accepted,but it hadsn't been choosen what type the order will be,so it cannot be finished.\n";
            }
            int number = Cstring_compare1(orders[i].Order_status,"");
            if (number==1)
             
            {
                 
                 orders[i].index += 1;
                 cout << "Pick order status:\n";
                 cout << "1.Accepted order\n";               
                 cout << "2.Denied order\n";
                 int orderstatus;
                 cout << "Pick:\n";
                
                 while (!(cin >> orderstatus) || orderstatus>2) {
                     cout << "Enter number between 1 and 2 please.\n";
                     cin.clear();
                     cin.ignore(numeric_limits<streamsize>::max(), '\n');
                 }
                 switch (orderstatus)
                 {
                   case 1: strcpy_s(orders[i].Order_status , "Accepted order");  break;
                   case 2: strcpy_s(orders[i].Order_status , "Denied order");  break;                                                                      
                 }
                 
            }
           
            int number2 = Cstring_compare1(orders[i].Order_status, "Accepted order");
            if (number2 == 1 && orders[i].index>1 && orders[i].Order_price != 0)
            {
                
                orders[i].index += 1;
                int finishedorder;
                cout << "This order can be only updated to finished\n";
                cout << "Write one if you want it to be finished:\n";              
                while (!(cin >> finishedorder) || finishedorder>1) {
                    cout << "Enter 1 please.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                switch (finishedorder) {
                case 1: strcpy_s(orders[i].Order_status , "Finished order");  break;
                  
                }
                
               

            }
            
            
        }
    }
}
void Add_order(Order orders[], int& Number_of_made_orders)//Adds order/s int the array of structs.
{
    
    int number_of_orders;    
      cout << "Number of orders:";
    cin >> number_of_orders;
    if (number_of_orders > Max_orders)
    {
        cout << "Error - too many orders.\n";
        system("pause");
        system("cls");
       
    }
    else 
    {
       
        if (Number_of_made_orders > Max_orders) {
            cout << "This is the limit of the orders.\n";
        }
        for (int i = Number_of_made_orders; i < Number_of_made_orders + number_of_orders; i++) {

            cout << "Order number:\n";
            //cin >> orders[i].Order_number;
            while (!(cin >> orders[i].Order_number)) {
                cout << "Enter number please.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (orders[0].Order_number > 1 || orders[0].Order_number < 1) {
                cout << "This order must be first.\n";
                cin >> orders[0].Order_number;
            }
            while (orders[i].Order_number-1 > orders[i - 1].Order_number) {
                cout << "The number of the orders must be consecutive. Last order was:" << orders[i - 1].Order_number << endl;
                cin >> orders[i].Order_number;
            }
            bool isOrderNumburValid = (i == 0 ? 0 : orders[i - 1].Order_number) < orders[i].Order_number;
           
            while (!isOrderNumburValid)
            {
                isOrderNumburValid = (i == 0 ? 0 : orders[i - 1].Order_number) < orders[i].Order_number;
                if (isOrderNumburValid) break;
                

                cout << "You cannot input order number which have passed. Last order was:" << orders[i - 1].Order_number << endl;
                cin >> orders[i].Order_number;

            }
            while (orders[i].Order_number > 100) {
                cout << "You cannot input order number which is past the limit of the orders. Last order was:" << orders[i - 1].Order_number << endl;
                cin >> orders[i].Order_number;
            }
            
            cout << "Day of the month:\n";
            //cin >> orders[i].Order_dayofmonth;
            while (!(cin >> orders[i].Order_dayofmonth)) {
                cout << "Enter day of the month please.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            bool isDayOfMonthValid = (i == 0 ? 1 : orders[i - 1].Order_dayofmonth) <= orders[i].Order_dayofmonth;
            if (orders[0].Order_dayofmonth > 31|| orders[0].Order_dayofmonth<1) {
                cout << "You cannot input date which is off the limit of one month. Current date is:" << 1 << endl;
                cin >> orders[0].Order_dayofmonth;
            }
           while (orders[i].Order_dayofmonth > 31) {
                cout << "You cannot input date which is off the limit of one month. Current date is:" << orders[i-1].Order_dayofmonth << endl;
                cin >> orders[i].Order_dayofmonth;
            }
            while (!isDayOfMonthValid)
            {
                isDayOfMonthValid = (i == 0 ? 1 : orders[i - 1].Order_dayofmonth) <= orders[i].Order_dayofmonth;
                if (isDayOfMonthValid) break;

                cout << "You cannot input date which have passed. Current date is:" << orders[i - 1].Order_dayofmonth << endl;
                cin >> orders[i].Order_dayofmonth;

            }
            cout << "Client's name:\n";
            cin.ignore(1000, '\n');
            cin.getline(orders[i].Order_client, 20);
            cout << "Type of the device:\n";
            cin.getline(orders[i].Order_typeofdevice, 20);
            cout << "Orders id:\n";
            cin.getline(orders[i].Order_id, 20);
            cout << "What problem do you have:\n";
            cout << "1.Problem with the screen." << endl;
            cout << "2.Problem with the CPU." << endl;
            cout << "3.Problem with the GPU." << endl;
            cout << "4.Problem with the keyboard." << endl;
            cout << "5.Problem with the videocard." << endl;
            cout << "6.Problem with the software." << endl;
            cout << "7.Problem with the touchpad." << endl;
            cout << "8.Problem with the mouse." << endl;
            cout << "9.Problem with the battery." << endl;
            cout << "10.Poblem with the memory." << endl;
            int ChoiceForProblem;
            cout << "Pick problem:\n";
           
            while (!(cin >> ChoiceForProblem)|| ChoiceForProblem>10) {
                cout << "Try with the problem we can solve.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            switch (ChoiceForProblem)
            {
            case 1: strcpy_s(orders[i].Order_problem, "Problem with the screen."); break;
            case 2: strcpy_s(orders[i].Order_problem, "Problem with the CPU."); break;
            case 3: strcpy_s(orders[i].Order_problem, "Problem with the GPU."); break;
            case 4: strcpy_s(orders[i].Order_problem, "Problem with the keyboard."); break;
            case 5: strcpy_s(orders[i].Order_problem, "Problem with the videocard."); break;
            case 6: strcpy_s(orders[i].Order_problem, "Problem with the software."); break;
            case 7: strcpy_s(orders[i].Order_problem, "Problem with the touchpad."); break;
            case 8: strcpy_s(orders[i].Order_problem, "Problem with the mouse."); break;
            case 9: strcpy_s(orders[i].Order_problem, "Problem with the battery."); break;
            case 10:strcpy_s(orders[i].Order_problem, "Poblem with the memory."); break;                                
            }
           


            cout << "-------------------------------------\n";

        }
        Number_of_made_orders += number_of_orders;
    }
}
void Output_orders(Order orders[], int& Number_of_made_orders)//Outputs orders on the screen, which are not updated or finished.
{
    for (int i = 0; i < Number_of_made_orders; i++) 
    {
        if (orders[i].index < 2)
        {
            cout << "Order number:" << orders[i].Order_number << endl;
            cout << "Day of the month:" << orders[i].Order_dayofmonth << endl;
            cout << "Client's name:" << orders[i].Order_client << endl;
            cout << "Type of the device:" << orders[i].Order_typeofdevice << endl;
            cout << "Orders id:" << orders[i].Order_id << endl;
            cout << "What problem do you have:" << orders[i].Order_problem << endl;
            cout << "Order status:" << orders[i].Order_status<<endl;
            cout << "---------------------------------\n";
        }
    }
    cout << endl;
}
void Search_by_type_of_device(Order orders[], int& Number_of_made_orders)// Searches for orders with the same type of device and outputting them on the screen. 
{
    string target;
    cout << "Type the device that you are looking for:\n";
    cin >> target;
    for (int i = 0; i < Number_of_made_orders; i++) 
    {
        int number = Cstring_compare1(orders[i].Order_typeofdevice, target);
        
        if (number == 1)
        {
            cout << "Order number:" << orders[i].Order_number << endl;
            cout << "Day of the month:" << orders[i].Order_dayofmonth << endl;
            cout << "Client's name:" << orders[i].Order_client << endl;
            cout << "Type of the device:" << orders[i].Order_typeofdevice << endl;
            cout << "Orders id:" << orders[i].Order_id << endl;
            cout << "What problem do you have:" << orders[i].Order_problem << endl;
            cout << "Order status:" << orders[i].Order_status << endl;
            cout << "---------------------------------\n";
        }
    }
}
void Search_by_type_of_device_status(Order orders[], int& Number_of_made_orders)//Searches for orders with the same status and outputting them on the screen.
{
    string target;
    cout << "Choose between Accepter order, Denied order or Finished order.\n";
    cout << "Type the status that you are looking for:\n";
    cin.ignore(1000, '\n');
    getline(cin, target);
    for (int i = 0; i < Number_of_made_orders; i++)
    {
        int number = Cstring_compare1(orders[i].Order_status, target);

        if (number == 1)
        {
            cout << "Order number:" << orders[i].Order_number << endl;
            cout << "Day of the month:" << orders[i].Order_dayofmonth << endl;
            cout << "Client's name:" << orders[i].Order_client << endl;
            cout << "Type of the device:" << orders[i].Order_typeofdevice << endl;
            cout << "Orders id:" << orders[i].Order_id << endl;
            cout << "What problem do you have:" << orders[i].Order_problem << endl;
            cout << "Order status:" << orders[i].Order_status << endl;
            cout << "---------------------------------\n";
        }
        
    }
}
void Sort_by_date(Order orders[], int& Number_of_made_orders)//Sorts the orders by date.
{
    {
        bool issorted;
        for (int i = 0; i < Number_of_made_orders - 1; i++)
        {


            issorted = true;
            for (int j = 0; j < Number_of_made_orders - i - 1; j++)
            {
                if (orders[j].Order_dayofmonth > orders[j + 1].Order_dayofmonth)
                {

                    swap(orders[j], orders[j + 1]);
                    issorted = false;
                }


            }
            if (issorted)
                break;
        }
    }
}
void Update_order_info(Order orders[], int& Number_of_made_orders) //Updates a selected order by the êÿåè with new information like price, days of downtime, the name of the tecknik and more.Ouputing the updated information for the selected order.
{
    unsigned int write_order_number;
    cout << "Write the number of the order to update it:\n";    
    while (!(cin >> write_order_number)) {
        cout << "Enter number please.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (write_order_number > orders[Number_of_made_orders-1].Order_number) {
        cout << "This order does not exist.\n";
    }
    for (int i = 0; i < Number_of_made_orders; i++)
    {
       
        
        if (write_order_number == orders[i].Order_number) 
        {
            if (orders[i].index == 0) {
                cout << "This order does not have status.\n";
            }
            if (orders[i].Order_price != 0) {
                cout << "This order has alredy been updated.\n";
            }
            
             int result;
             string Acceptedorder = "Accepted order";
             result = Cstring_compare1(orders[i].Order_status, Acceptedorder);
             if (result > 0 && orders[i].index==1)
             {
                 orders[i].index += 1;
                cout << "Pick what type of order you want:\n";
                int whatorder;
                cout << "1.10 days-normal\n";
                cout << "2.5 days-fast\n";
                cout << "3.2 days-express\n";
                cout << "Pick number\n";               
                while (!(cin >> whatorder)|| whatorder>3) {
                    cout << "Enter number between 1-3 please.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                switch (whatorder) 
                {
                case 1:strcpy_s(orders[i].Order_what_order,"10 days-normal");
                    orders[i].index2++;
                    break;
                case 2:strcpy_s(orders[i].Order_what_order,"5 days-fast"); 
                    orders[i].index2+=2;
                    break;
                case 3:strcpy_s(orders[i].Order_what_order,"2 days-express");
                    orders[i].index2 +=3;
                    break;
                
                }
                int result1 = Cstring_compare1(orders[i].Order_what_order, (string)"10 days-normal");
                if (result1 > 0) {
                    strcpy_s(orders[i].Order_days_of_downtime , "10 days-normal");
                    
                }
                int result2 = Cstring_compare1(orders[i].Order_what_order, "5 days-fast");
                if (result2 > 0) {
                    strcpy_s(orders[i].Order_days_of_downtime , "5 days-fast");
                    
                }
                int result3 = Cstring_compare1(orders[i].Order_what_order, "2 days-express");
                if (result3 > 0) {
                    strcpy_s(orders[i].Order_days_of_downtime , "2 days-express");
                    
                }
                int result4 = Cstring_compare1(orders[i].Order_problem, "Problem with the screen.");
                if (result4 > 0) {
                    strcpy_s(orders[i].Order_repair_done , "Fixed screen.");
                    
                }
                int result5 = Cstring_compare1(orders[i].Order_problem, "Problem with the CPU.");
                if (result5 > 0) {
                    strcpy_s(orders[i].Order_repair_done , "Fixed CPU.");
                   
                }
                int result6 = Cstring_compare1(orders[i].Order_problem, "Problem with the GPU.");
                if (result6 > 0) {
                    strcpy_s(orders[i].Order_repair_done , "Fixed GPU.");
                    
                }
                int result7 = Cstring_compare1(orders[i].Order_problem, "Problem with the keyboard.");
                if (result7 > 0) {
                    strcpy_s(orders[i].Order_repair_done , "Fixed keyboard.");
                    
                }
                int result8 = Cstring_compare1(orders[i].Order_problem, "Problem with the videocard.");
                if (result8 > 0) {
                    strcpy_s(orders[i].Order_repair_done , "Fixed videocard.");
                    
                }
                int result9 = Cstring_compare1(orders[i].Order_problem, "Problem with the software.");
                if (result9 > 0) {
                    strcpy_s(orders[i].Order_repair_done , "Fixed software.");
                    
                }
                int result10 = Cstring_compare1(orders[i].Order_problem, "Problem with the touchpad.");
                if (result10 > 0) {
                    strcpy_s(orders[i].Order_repair_done , "Fixed touchpad.");
                   
                }
                int result11 = Cstring_compare1(orders[i].Order_problem, "Problem with the mouse.");
                if (result11 > 0) {
                    strcpy_s(orders[i].Order_repair_done , "Fixed mouse.");
                    
                }
                int result12 = Cstring_compare1(orders[i].Order_problem, "Problem with the battery.");
                if (result12 > 0) {
                    strcpy_s(orders[i].Order_repair_done , "Fixed battery.");
                   
                }
                int result13 = Cstring_compare1(orders[i].Order_problem, (string)"Poblem with the memory.");
                if (result13 > 0) {
                    strcpy_s(orders[i].Order_repair_done , "Fixed memory.");
                    
                }
                double result14 = Cstring_compare1(orders[i].Order_problem, (string)"Problem with the screen.");
                if (result14 > 0) {
                    orders[i].Order_price = What_order_price(orders, Number_of_made_orders, (double)100,(double)0,(double)0);
                }
                double result15 = Cstring_compare1(orders[i].Order_problem, (string)"Problem with the CPU.");
                if (result15> 0) {
                    orders[i].Order_price = What_order_price(orders, Number_of_made_orders, (double)200, (double)0, (double)0);

                }
                double result16 = Cstring_compare1(orders[i].Order_problem, (string)"Problem with the GPU.");
                if (result16 > 0) {
                    orders[i].Order_price = What_order_price(orders, Number_of_made_orders, (double)300, (double)0, (double)0);

                }
                double result17 = Cstring_compare1(orders[i].Order_problem, (string)"Problem with the keyboard.");
                if (result17 > 0) {
                    orders[i].Order_price = What_order_price(orders, Number_of_made_orders, (double)50, (double)0, (double)0);

                }
                double result18 = Cstring_compare1(orders[i].Order_problem, (string)"Problem with the videocard.");
                if (result18 > 0) {
                    orders[i].Order_price = What_order_price(orders, Number_of_made_orders, (double)200, (double)0, (double)0);

                }
                double result19 = Cstring_compare1(orders[i].Order_problem, (string)"Problem with the software.");
                if (result19 > 0) {
                    orders[i].Order_price = What_order_price(orders, Number_of_made_orders, (double)100, (double)0, (double)0);

                }
                double result20 = Cstring_compare1(orders[i].Order_problem, (string)"Problem with the touchpad.");
                if (result20 > 0) {
                    orders[i].Order_price = What_order_price(orders, Number_of_made_orders, (double)80, (double)0, (double)0);

                }
                double result21 = Cstring_compare1(orders[i].Order_problem, (string)"Problem with the mouse.");
                if (result21 > 0) {
                    orders[i].Order_price = What_order_price(orders, Number_of_made_orders, (double)50, (double)0, (double)0);

                }
                double result22 = Cstring_compare1(orders[i].Order_problem, (string)"Problem with the battery.");
                if (result22 > 0) {
                    orders[i].Order_price = What_order_price(orders, Number_of_made_orders,(double)20, (double)0, (double)0);

                }
                double result23 = Cstring_compare1(orders[i].Order_problem, (string)"Poblem with the memory.");
                if (result23 > 0) {
                    orders[i].Order_price = What_order_price(orders, Number_of_made_orders, double(120), (double)0, (double)0);

                }

                
                cout << "Enter the name of the technik:\n";
                cin.ignore(1000, '\n');
                cin.getline(orders[i].Order_nameoftechnik,20);
                cout << "Orders type:\n" << orders[i].Order_what_order << endl;
                cout << "Repair done:" << endl;
                cout << orders[i].Order_repair_done<<endl;
                cout << "Days of downtime:\n"<< orders[i].Order_days_of_downtime<<endl; 
                cout << "Order price:\n";
                cout << orders[i].Order_price << endl;
              }
              
              
              
              
            int result24;
            string Acceptedorder1 = string("Finished order");
            result24 = Cstring_compare1(orders[i].Order_status, (string)Acceptedorder1);
            if (result24 > 0) 
            {
                
                cout << "You cannot change finished order.\n";
            }
            int result25;
            string Acceptedorder2 = "Denied order";
            result25 = Cstring_compare1(orders[i].Order_status, (string)Acceptedorder2);
            if (result25 > 0)
            {
               
                cout << "You cannot change denied order\n";
            }
        }
                               
    }
   
   system("pause");
   system("cls");
}
void Sort_by_order_number(Order orders[], int& Number_of_made_orders)//Sorts the orders by their number. 
{
    {
        bool issorted;
        for (int i = 0; i < Number_of_made_orders - 1; i++)
        {


            issorted = true;
            for (int j = 0; j < Number_of_made_orders - i - 1; j++)
            {
                if (orders[j].Order_number > orders[j + 1].Order_number)
                {

                    swap(orders[j], orders[j + 1]);
                    issorted = false;
                }


            }
            if (issorted)
                break;
        }
    }
}
void Ouput_update_order_technik(Order orders[], int& Number_of_made_orders)//Outputs done orders by the same tecknik, which is selected by the user.
{
    string nameOfTechnik;
    cout << "Write the name of the technik:\n";
    cin.ignore(1000, '\n');
    getline(cin, nameOfTechnik);
    for (int i = 0; i < Number_of_made_orders; i++) {
        if (orders[i].index > 2) {
            int number = Cstring_compare1(orders[i].Order_nameoftechnik, nameOfTechnik);
            if (number == 1)
            {


                cout << "Order number:" << orders[i].Order_number << endl;
                cout << "Day of the month:" << orders[i].Order_dayofmonth << endl;
                cout << "Client's name:" << orders[i].Order_client << endl;
                cout << "Type of the device:" << orders[i].Order_typeofdevice << endl;
                cout << "Orders id:" << orders[i].Order_id << endl;
                cout << "What problem do you have:" << orders[i].Order_problem << endl;
                cout << "Status of order:" << orders[i].Order_status << endl;
                cout << "The name of the technik:" << orders[i].Order_nameoftechnik << endl;
                cout << "Repair done:" << orders[i].Order_repair_done << endl;
                cout << "Days of downtime:" << orders[i].Order_days_of_downtime << endl;
                cout << "Order price:" << orders[i].Order_price << endl;
                cout << "---------------------------------\n";
            }
        }
    }
    cout << endl;
}
void Sort_by_type_device_which_is_repaired(Order orders[], int& Number_of_made_orders)//Sorts the orders by the type of the device,which are repaired in descending order.
{
   
    bool issorted;
    for (int i = 0; i < Number_of_made_orders - 1; i++)
    {
        if (orders[i].Order_typeofdevice == orders[i].Order_typeofdevice)
        {
            if (orders[i].Order_price > 0)
            {

                issorted = true;
                for (int j = 0; j < Number_of_made_orders - i - 1; j++)
                {
                    if (orders[j].Order_dayofmonth < orders[j + 1].Order_dayofmonth)
                    {

                        swap(orders[j], orders[j + 1]);
                        issorted = false;
                    }


                }
                if (issorted)
                    break;
            }
        }
    }
}
void Output_sorted_devices_which_are_repaired(Order orders[], int& Number_of_made_orders)//Outputs all devices of the same type,which are repaired.
{
    
    string target5;
    cout << "Write the device you are looking for:";
    cin >> target5;
    for (int i = 0; i < Number_of_made_orders; i++) {
        int number = Cstring_compare1(orders[i].Order_typeofdevice, target5);
        if (number == 1)
        {
            if (orders[i].index > 2) 
            {

               
                    cout << "Order number:" << orders[i].Order_number << endl;
                    cout << "Day of the month:" << orders[i].Order_dayofmonth << endl;
                    cout << "Client's name:" << orders[i].Order_client << endl;
                    cout << "Type of the device:" << orders[i].Order_typeofdevice << endl;
                    cout << "Orders id:" << orders[i].Order_id << endl;
                    cout << "What problem do you have:" << orders[i].Order_problem << endl;
                    cout << "Status of order:" << orders[i].Order_status << endl;
                    cout << "The name of the technik:" << orders[i].Order_nameoftechnik << endl;
                    cout << "Repair done:" << orders[i].Order_repair_done << endl;
                    cout << "Days of downtime:" << orders[i].Order_days_of_downtime << endl;
                    cout << "Order price:" << orders[i].Order_price << endl;
                    cout << "---------------------------------\n";
                
            }
        }
    }
    cout << endl;
}
void Output_finished_order(Order orders[], int& Number_of_made_orders)//Outputs finished orders.
{
    for (int i = 0; i < Number_of_made_orders; i++) {
        if (orders[i].index > 2) {
            
                cout << "Order number:" << orders[i].Order_number << endl;
                cout << "Day of the month:" << orders[i].Order_dayofmonth << endl;
                cout << "Client's name:" << orders[i].Order_client << endl;
                cout << "Type of the device:" << orders[i].Order_typeofdevice << endl;
                cout << "Orders id:" << orders[i].Order_id << endl;
                cout << "What problem do you have:" << orders[i].Order_problem << endl;
                cout << "Status of order:" << orders[i].Order_status << endl;
                cout << "The name of the technik:" << orders[i].Order_nameoftechnik << endl;
                cout << "Repair done:" << orders[i].Order_repair_done << endl;
                cout << "Days of downtime:" << orders[i].Order_days_of_downtime << endl;
                cout << "Order price:" << orders[i].Order_price << endl;
                cout << "---------------------------------\n";
            
        }
    }
    cout << endl;

}
void Output_to_file(Order orders[], int& Number_of_made_orders)//Outputs the information from the program to a file.
{
    fstream outfile("Orders.dat", ios :: out | ios :: binary );
    if (outfile.fail()) {
        cout << "Error";
        return;
    }
    outfile.write((char*)orders, Number_of_made_orders * sizeof(Order));
    outfile.close();

}
void Input_from_file(Order orders[], int& Number_of_made_orders)// Inputs the information from a file to the program.
{
    fstream infile("Orders.dat", ios::in | ios::binary);
    if (infile.fail()) {
        cout << "Error";
        return;
    }
    infile.seekg(0, ios::end);
    long filesize = infile.tellg();
    int ordersinfile = filesize / sizeof(Order);
    infile.seekg(0, ios::beg);
    infile.read((char*)&orders[Number_of_made_orders], filesize);
    Number_of_made_orders += ordersinfile;
    infile.close();


}




    void Menu(Order made_orders[], int& Number_of_made_orders) 
    {
      int Option;


      do {
        cout << "*******************************\n";
        cout << "1. Input new order\n";
        cout << "2. Output devices\n";
        cout << "3. Search and output\n";        
        cout << "4. Sort the devices\n";
        cout << "5. Order status.\n";
        cout << "6. Output to file.\n";
        cout << "7. Update order info\n";
        cout << "8. Exit\n";
        cout << "*******************************\n";
        cout << "Pick option:";       
        while (!(cin >> Option)) {
            cout << "Enter number please.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        system("cls");
        switch (Option) {
       
       
        case 1:Add_order(made_orders, Number_of_made_orders);
            system("pause");
            system("cls"); break;

        case 2:
            cout << "Requested orders:\n";
            Sort_by_order_number(made_orders, Number_of_made_orders);
            Output_orders(made_orders, Number_of_made_orders);                                            
            cout << "Updated orders:\n\n";
            Output_updated_info(made_orders, Number_of_made_orders);
            cout << "Finished orders:\n\n";
            Output_finished_order(made_orders, Number_of_made_orders);
            system("pause"); system("cls"); break;
        case 3: int option3;
            do {
                cout << "1.Search by the type of the device.\n";
                cout << "2.Search by the status of the order.\n";
                cout << "3.Go back.\n";
                cout << "-------------------------------------\n";
                cout << "Enter option:";
                
                while (!(cin >> option3)) {
                    cout << "Enter number between 1-3 please.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                system("cls");
                switch (option3) 
                {
                case 1: Search_by_type_of_device(made_orders, Number_of_made_orders);
                    system("pause"); system("cls"); break;
                case 2: Search_by_type_of_device_status(made_orders, Number_of_made_orders);
                    system("pause"); system("cls"); break;
                case 3: Menu(made_orders, Number_of_made_orders);
               
                }
            } while (option3 <= 3); break;
        case 4:
            int option2;
            do {
                cout << "1.Sort by date.\n";
                cout << "2.Done orders by one technik sorted by date.\n";
                cout << "3.Sort done orders of same type of device by date.\n";
                cout << "4.Go back.\n";
                cout << "-------------------------------------\n";
                cout << "Enter option:";
               
                while (!(cin >> option2)) {
                    cout << "Enter number between 1-4 please.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                system("cls");
                switch (option2) {
                case 1: Sort_by_date(made_orders, Number_of_made_orders);
                    cout << "Sorted by date:\n";
                    Output_orders(made_orders, Number_of_made_orders);
                    cout << "Sorted orders by date, which have been accepted and had started to work on them:\n";
                    Output_updated_info(made_orders, Number_of_made_orders);
                    cout << "Sorted orders by date, which have been finished:\n";
                    Output_finished_order(made_orders, Number_of_made_orders);
                    system("pause"); system("cls"); break;
                case 2:Done_orders_by_one_technik(made_orders, Number_of_made_orders);
                    cout << "Done orders by one technik sorted by date:\n";
                    Ouput_update_order_technik(made_orders, Number_of_made_orders);
                    system("pause"); system("cls"); break;
                case 3:
                    Sort_by_type_device_which_is_repaired(made_orders, Number_of_made_orders);
                    cout << "Sort done orders of same type of device, which have been repaired by date:\n";
                    Output_sorted_devices_which_are_repaired(made_orders, Number_of_made_orders);
                    system("pause"); system("cls"); break;
                case 4: Menu(made_orders, Number_of_made_orders); break;
               

                }
            } while (option2 < 5); break;

        case 5:  Order_status(made_orders, Number_of_made_orders);
            system("pause"); system("cls");  break;
        case 6:Output_to_file(made_orders, Number_of_made_orders); break;
        
        case 7:Update_order_info(made_orders, Number_of_made_orders); break;





        case 8:
            Output_to_file(made_orders, Number_of_made_orders); 
            exit(0); break;
        default: cout << "Invalid option\n"; Menu(made_orders, Number_of_made_orders);
           
         }
       
        } while(Option < 9);
    }
    int main()
    {
        Order made_orders[Max_orders];
        int Number_of_made_orders = 0;
        Input_from_file(made_orders, Number_of_made_orders);
        Menu(made_orders, Number_of_made_orders);
        
    }