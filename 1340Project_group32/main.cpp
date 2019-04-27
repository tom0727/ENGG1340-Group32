#include "headerfile.h"
using namespace std;

int main()
{ string login_user="",user_password="";
 // income , expense,budget: the total income /expense/budget regardless of date
  float budget,income,expense;
 // RecordList: a list which stores record loaded form file
  vector<Record> recordList;
 // typeList: Key: the name of differnet usage of money
 //         value: the number of record of that type of usage of money
 //methodList: Key: the name of differnet payment method
 //         value: the number of record of that category of payment of method
  map <string,int> typeList;
  map <string,int> methodList;
 // Login to the system
  login(login_user,user_password,budget,income,expense);
 // load the data stores in username_record.txt file to different list and variable
  load_userdata(login_user,recordList,typeList,methodList);
  // The overall menu of function avaliable for execution after login
  string choice;
 // the main menu avaliable to perform different function
  while (true)
  {
    print_menu2();
    getline(cin,choice);
    if (choice=="1"){add(recordList,typeList,methodList,income,expense,budget);}
    else if (choice=="2"){show(income,expense,budget,recordList,methodList,typeList);}
    else if (choice=="3"){financial_report(recordList,typeList,methodList,income,expense,budget);}
    else if (choice=="4"){change_password(login_user,user_password);}
    else if (choice==""){write_data(login_user,user_password,recordList,budget,income,expense);break;}
    else {cout<<"Invalid input, please enter again: ";}
  }
  return 0;
}
