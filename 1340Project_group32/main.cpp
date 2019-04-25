#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include "headerfile.h"
using namespace std;

int main()
{ string login_user="",user_password="";
  float budget=9999999999,income,expense;
  vector<Record> recordList;
  map <string,int> typeList;
  map <string,int> methodList;
  login(login_user,user_password,budget,income,expense);
  load_userdata(login_user,recordList,typeList,methodList);
  // The overall menu of function avaliable for execution after login
  string choice;
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
