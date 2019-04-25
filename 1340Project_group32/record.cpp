//get the record from user input/ input promotion
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
void Record::set_amount(float newamount)
{
  amount = newamount;
}
void Record::set_time(string newtime)
{
  time = newtime;
}
void Record::set_type(string newtype)
{
  type = newtype;
}
void Record::set_method(string newmethod)
{
  method = newmethod;
}
void Record::set_remark(string newremark)
{
  remark = newremark;
}
float Record::get_amount()
{
  return amount;
}
string Record::get_time()
{
  return time;
}
string Record::get_type()
{
  return type;
}
string Record::get_method()
{
  return method;
}
string Record::get_remark()
{
  return remark;
}

void prompt_add_input(float &amount,string &time,string &type,string &method,string &remark){
  string s_amount;
  cout<<"Please indicate the amount,positive number means income and negative number means expense: ";
  while (true)
  {
    getline(cin,s_amount);
    if (s_amount=="") {cout << "Amount cannot be empty, please enter again: "; continue;}
    else if (amount_check(s_amount))
    {
      amount=stof(s_amount);
      if (amount==0) {cout<<"Amount cannot start with 0, please enter again: "; continue;}
      break;
    }
    else {cout<<"Invalid amount,please enter again: ";}
  }
  //get the time
  cout<<"Please enter the date(format:YYYYMMDD): ";
  while (true)
  {
    getline(cin,time);
    if (time=="") {cout << "Time cannot be empty, please enter again: "; continue;}
    else if (time_check(time)) {break;}
    else {cout<<"Invalid amount,please enter again: ";}
  }
  time=time.substr(0,4)+"-"+time.substr(4,2)+"-"+time.substr(6,2);  
  //The format of date is YYYY-MM-DD when stored in recordList
  transform_lower(time);

  cout<<"Please enter the type of expense/income: ";
  while (true)
  {
    getline(cin,type);
    if (type=="") {cout<<"Type can not be empty, please enter again: ";}
    else {break;}
  }
  transform_lower(type);


  cout<<"Please enter the payment method of expense/income: ";
  while(true)
  {
    getline(cin,method);
    if (method=="") {cout<<"Method can not be empty, please enter again: ";}
    else {break;}
  }
  transform_lower(method);

  cout<<"Please add some remark to the record: ";
  getline(cin,remark); 
  //Remark can be empty
  transform_lower(remark);
}

// add record from user
void add(vector<Record> &recordList, map <string,int> &typeList, map<string,int> &methodList, float &income, float &expense, float &budget){
  string time,type,method,remark;
  float amount;
  prompt_add_input(amount,time,type,method,remark);
  if (amount>0){
    income+=amount;
  }
  else{
    expense-=amount;  //expense is positive, the amount here is negative
    if (expense>=budget) {cout<<endl;cout<<"The current expense is: "<<expense<< " ,You have exceeded the budget of "<<budget<<endl;}
  }
  Record temp;
  temp.set_amount(amount);
  temp.set_time(time);
  temp.set_type(type);
  temp.set_method(method);
  temp.set_remark(remark);
  recordList.push_back(temp);
  List_fill(typeList,type);  //update the typeList
  List_fill(methodList,method);  //update the methodList
  cout<<"Record successfully added"<<endl;
}
//************************End of addition function*****************************************
//********************************************************************************************
//**********************The start of the show function***************************************


void show_menu()
{
  cout << endl;
  cout << "***********************************************************************************************" << endl;
  cout << "You are now asking to show Records" << endl;
  cout << "1.show by Date" << endl;
  cout << "2.show by Amount" << endl;
  cout << "3.show by Method" << endl;
  cout << "4.show by Type" << endl;
  cout << "5.search by Date" << endl;
  cout << "6.search by Amount" << endl;
  cout << "7.search by Method" << endl;
  cout << "8.search by Type" << endl;
  cout << "d.delete records" << endl;
  cout << "e.edit records" << endl;
  cout << "Please enter an integer to select, press Enter to exit: ";
}

void show_record(vector<Record> &recordList,int &i)
{
  ios init(NULL);  
  init.copyfmt(cout);  //store the default output format
  cout<<"  "<<left<<setw(6)<<i;
  cout<<setw(1)<<" "<<setw(8)<<(recordList[i]).get_amount();
  cout<<setw(10)<<(recordList[i]).get_time();
  cout<<setw(6)<<"      "<<setw(18)<<(recordList[i]).get_type();
  cout<<setw(2)<<"  "<<setw(20)<<(recordList[i]).get_method()<<setw(2)<<"  ";
  cout.copyfmt(init);  //restore the default output format
  cout<<left<<(recordList[i]).get_remark()<<endl;
}

void show_header()  //show the header when showing Records
{
  cout << endl;
  cout<<left<<setw(5)<<"Index"<<setw(3)<<"   "<<setw(6)<<"Amount"<<setw(6)<<"      "<<setw(8)<<"Date"<<setw(5)<<"   "<<setw(20)<<"Type"<<setw(22)<<"Method"<<setw(6)<<"Remark"<<endl;
}


void sort_time(vector<Record> &recordList)  //show by time
{
  sort(recordList.begin(),recordList.end(),compareTime);  //sort the vector according to time
  show_header();
  int i=0,count=0;
  string option;
  while (i<recordList.size())
  {
    show_record(recordList,i);
    i++; count++;
    if (count==5&& i!=recordList.size())  //each page has 5 records at most
    {
      cout << endl;
      cout << "Please Enter n to view next page, press Enter to Exit: ";
      while (true)
      {
        getline(cin,option);
        if (option.size()==0) {return;}
        else if (option=="n") {count=0; cout<<endl; break;}
        else {cout << "Invalid input,please Enter again: ";}
      }
    }
  }
}


void sort_amount(vector<Record> &recordList)  //show by amount
{
  sort(recordList.begin(),recordList.end(),compareAmount);
  int negative_index=recordList.size();  //The index of the first negative number
  show_header();
  int i=0,count=0;
  string option;
  while (i<recordList.size())
  {
    show_record(recordList,i);
    i++,count++;
    if (count==5&& i!=recordList.size()) //if i==recordList.size(),this means the last record has been shown, no need to view next page
    {
      cout<<endl;
      cout << "Please Enter n to view next page, press Enter to Exit: ";
      while (true)
      {
        getline(cin,option);
        if (option=="") {return;}
        else if (option=="n") {count=0; cout<<endl; break;}
        else {cout << "Invalid input,please Enter again: ";}
      }
    }
    if (recordList[i].get_amount()<0) {negative_index=i; i=recordList.size()-1; break;}
  }
  // show from the +(biggest) to +(smallest)
  
  // then show from the -(biggest) to -(smallest)
  while (i>=negative_index)
  {
    show_record(recordList,i);
    i--;count++;
    if (count==5&& i!=negative_index-1)  // if i==negative_index-1, this means the last record has been shown, no need to view next page
    {
      cout<<endl;
      cout << "Please Enter n to view next page, press Enter to Exit: ";
      while (true)
      {
        getline(cin,option);
        if (option=="") {return;}
        else if (option=="n") {count=0;cout<<endl; break;}
        else {cout << "Invalid input,please Enter again: ";}
      }
    }
  }
}

void sort_method(vector<Record> &recordList)  //show by method,Lexicographical order
{
  sort(recordList.begin(),recordList.end(),compareMethod);
  show_header();
  int i=0,count=0;
  string option;
  while (i<recordList.size())
  {
    show_record(recordList,i);
    i++; count++;
    if (count==5&& i!=recordList.size())
    {
      cout<<endl;
      cout << "Please Enter n to view next page, press Enter to Exit: ";
      while (true)
      {
        getline(cin,option);
        if (option=="") {return;}
        else if (option=="n") {count=0;cout<<endl; break;}
        else {cout << "Invalid input,please Enter again: ";}
      }
    }
  }
}

void sort_type(vector<Record> &recordList)  //show by type, Lexicographical order
{
  sort(recordList.begin(),recordList.end(),compareType);
  show_header();
  int i=0,count=0;
  string option;
  while (i<recordList.size())
  {
    show_record(recordList,i);
    i++; count++;
    if (count==5&& i!=recordList.size())
    {
      cout<<endl;
      cout << "Please Enter n to view next page, press Enter to Exit: ";
      while (true)
      {
        getline(cin,option);
        if (option=="") {return;}
        else if (option=="n") {count=0;cout<<endl; break;}
        else {cout << "Invalid input,please Enter again: ";}
      }
    }
  }
}

void search_time(vector<Record> &recordList)  //search by date
{
  cout << endl;
  cout << "Please enter a time interval you want to search for" << endl;
  cout << "The format is YYYYMMDD, press Enter to exit" << endl;
  cout << "Enter 0 to show from the earliest/latest time" << endl;
  cout << "Start time: ";
  string starttime,endtime;
  getline(cin,starttime);
  if (starttime=="") {return;}
  while (!time_check(starttime) && starttime!="0")  //time_check function is in another file
  {
    cout << "Invalid input,please enter again: ";
    getline (cin,starttime);
    if (starttime=="") {return;}
  }
  if (starttime=="0") {starttime = "00000000";}  //starttime will be smaller than any "time"
  starttime=starttime.substr(0,4)+"-"+starttime.substr(4,2)+"-"+starttime.substr(6,2);

  cout << "End time: ";
  getline(cin,endtime);
  if (endtime=="") {return;}
  while (!time_check(endtime) && endtime!="0")  //time_check function is in another file
  {
    cout << "Invalid input,please enter again: " ;
    getline (cin,endtime);
    if (endtime=="") {return;}
  }
  if (endtime=="0") {endtime = "99999999";}  //endtime will be greater than any "time"
  endtime=endtime.substr(0,4)+"-"+endtime.substr(4,2)+"-"+endtime.substr(6,2);

  show_header();
  for (int i=0;i<recordList.size();i++)
  {
    if (recordList[i].get_time()>=starttime && recordList[i].get_time()<=endtime)
    {
      show_record(recordList,i);
    }
  }
}

void search_amount(vector<Record> &recordList)  //search according to an amount interval
{
  cout << endl;
  cout << "Please enter an amount interval you want to search for (press Enter to exit)" << endl;
  cout << "Enter 0 to show from/until the lowest/highest amount" << endl;
  string low,high;
  cout << "Lower amount: ";
  getline(cin,low);
  if (low=="") {return;}
  while (!amount_check(low) && low!="0")
  {
    cout << "Invalid input,please enter again: ";
    getline (cin,low);
    if (low=="") {return;}
  }

  cout << "Higher amount: ";
  getline(cin,high);
  if (high=="") {return;}
  while (!amount_check(high) && high!="0")
  {
    cout << "Invalid input,please enter again: ";
    getline (cin,high);
    if (high=="") {return;}
  }
  float l,h;
  if (low=="0") {l=-99999999;} else {l=stof(low);}  //set l to a very small amount
  if (high=="0") {h=99999999;} else {h=stof(high);}  //set h to a very huge amount

  show_header();
  for (int i=0;i<recordList.size();i++)  //assume it is a vector
  {
    if (recordList[i].get_amount() >= l && recordList[i].get_amount() <= h)
    {show_record(recordList,i);}
  }
}

void search_method(vector<Record> &recordList,map<string,int> &methodList)  //search according to method
{
  cout << endl;
  cout << "These are the existing method:" << endl;  cout<<endl;
  map <string,int>::iterator itr;
  for (itr = methodList.begin();itr!=methodList.end();itr++)
  {cout << itr->first << "  |  ";}  //showing existing method
  cout << endl;
  cout << "Please enter a method you want to search for(press Enter to exit): ";
  string method;
  getline(cin,method);
  transform_lower(method);  //transform "method" into lower case
  show_header();
  for (int i=0;i<recordList.size();i++)
  {
    if (recordList[i].get_method() == method)
    {show_record(recordList,i);}
  }
}

void search_type(vector<Record> &recordList,map<string,int> &typeList)
{
  cout << "These are the existing type:" << endl;
  map <string,int>::iterator itr;
  for (itr=typeList.begin();itr!=typeList.end();itr++)
  {cout << (*itr).first << "  |  ";}  //showing existing type, use "|" as a delimiter
  cout << endl;
  cout << "Please enter a type you want to search for(press Enter to exit): ";
  string type;
  getline(cin,type);
  transform_lower(type);  //transform "type" into lower case
  show_header();
  for (int i=0;i<recordList.size();i++)
  {
    if (recordList[i].get_type() == type)
    {show_record(recordList,i);}
  }
}

void update_map(map<string,int> &m,string key,int change)  //used to update methodList and typeList
// methodList and typeList are map<string,int>, used to store a method/type and its corresponding count
{
  if (change==1)  //if a record of this method/type is added
  {
    if (m.count(key)==0) {m[key]=1;}
    else {m[key]+=1;}
  }
  else if (change==-1)  //if a record of this method/type is deleted
  {
    if (m[key]==1) {m.erase(key);}
    else {m[key]-=1;}
  }
}

void edit_record(float &income,float &expense,float &budget,vector<Record> &recordList,map<string,int> &methodList, map<string,int> &typeList,int i)
{
  string option;
  cout << endl;
  show_record(recordList,i); cout<<endl;
  cout << "Please edit the record, if you want to keep the origin data, please Enter 0 (press Enter to Exit)" << endl<<endl;
  cout << "Please enter the Amount(positive number means income, negative number means expense): ";
  while (true)
  {
    getline(cin,option);
    if (option=="") {return;}
    else if (option=="0") {break;}
    else if (amount_check(option))
    {
      float oldamount = recordList[i].get_amount();
      float newamount = stof(option);
      if (oldamount<0) {expense+=oldamount;}  //because the expense here is positive, oldamount is a negative number, here is to decrease expense
      else if (oldamount>0) {income-=oldamount;}
      if (newamount<0)
      {
        expense-=newamount; //because the expense here is positive, oldamount is a negative number, here is to increase expense
        if (expense>=budget) {cout<<"The current expense is: "<<expense<< " ,You have exceeded the budget of "<<budget<<endl;}
      }
      else if (newamount>0) {income+=newamount;}
      recordList[i].set_amount(newamount);
      break;
    }
    else {cout << "Invalid input, please enter again: ";}
  }


  cout << "Please enter the Date(Format:YYYYMMDD): ";
  while (true)
  {
    getline(cin,option);
    if (option=="") {return;}
    else if (option=="0") {break;}
    else if (time_check(option))
    {recordList[i].set_time(option.substr(0,4)+"-"+option.substr(4,2)+"-"+option.substr(6,2)); break;}
    else {cout << "Invalid option, please enter again: ";}
  }

  cout << "Please enter the Type: ";
  while (true)
  {
    getline(cin,option);
    if (option=="") {return;}
    else if (option=="0") {break;}
    else
    {
      string oldtype = recordList[i].get_type();
      string newtype = option;
      update_map(typeList,oldtype,-1);
      update_map(typeList,newtype,1);
      recordList[i].set_type(option);
      break;
    }
  }


  cout << "Please enter the Method: ";
  while (true)
  {
    getline(cin,option);
    if (option=="") {return;}
    else if (option=="0") {break;}
    else
    {
      string oldmethod = recordList[i].get_method();
      string newmethod = option;
      update_map(methodList,oldmethod,-1);
      update_map(methodList,newmethod,1);
      recordList[i].set_method(option);
      break;
    }
  }

  cout << "Please enter the Remark: ";
  while (true)
  {
    getline(cin,option);
    if (option=="") {return;}
    else if (option=="0") {break;}
    else {recordList[i].set_remark(option); break;}
  }
}


void edit_mode(float &income,float &expense,float &budget,vector<Record> &recordList,map<string,int> &methodList, map<string,int> &typeList)
{
  string option;
  sort(recordList.begin(),recordList.end(),compareTime);
  cout << "You are now in the edit mode" << endl << endl;
  show_header();
  int i=0,count=0;

  while (i<recordList.size())
  {
    show_record(recordList,i);
    i++; count++;
    if (count==5&& i!=recordList.size())  //edit_mode also has "view next page" function
    {
      cout << endl;
      cout << "Please enter the corresponding index to edit record, enter n to view next page(press Enter to Exit): ";
      while (true)
      {
        getline(cin,option);
        if (option=="") {return;}
        else if (option=="n") {count=0; cout<<endl; break;}
        else if (int_check(option))
        {
          int i= stoi(option);
          if (i>=recordList.size()) {cout << "Index does not exist, please enter again: ";}
          else {edit_record(income,expense,budget,recordList,methodList,typeList,i);return;}
        }
        else {cout << "Invalid input,please Enter again: ";}
      }
    }
  }
  cout<<endl<< "Please enter the corresponding index to edit record(press Enter to Exit): ";
  while (true)
  {
    getline(cin,option);
    if (option=="") {return;}
    else if (int_check(option))
    {
      int i= stoi(option);
      if (i>=recordList.size()) {cout << "Index does not exist, please enter again: ";}
      else {edit_record(income,expense,budget,recordList,methodList,typeList,i);return;}
    }
    else {cout << "Invalid input,please Enter again: ";}
  }
}

void delete_record(float &income,float &expense,float &budget,vector<Record> &recordList,map<string,int> &methodList, map<string,int> &typeList,int i)
{
  float oldamount = recordList[i].get_amount();
  if (oldamount<0) {expense-=oldamount;}
  else if (oldamount>0) {income-=oldamount;}
  string oldmethod = recordList[i].get_method();
  update_map(methodList,oldmethod,-1);  //update the methodList
  string oldtype = recordList[i].get_type();
  update_map(typeList,oldtype,-1);  //update the typeList
  recordList.erase(recordList.begin()+i);  //use iterator to erase this record
}


void delete_mode(float &income,float &expense,float &budget,vector<Record> &recordList,map<string,int> &methodList, map<string,int> &typeList)
{
  string option;
  sort(recordList.begin(),recordList.end(),compareTime);
  cout << "You are now in the delete mode" << endl << endl;
  show_header();
  int i=0,count=0;

  //sort_time(recordList); cout<<endl;
  while (i<recordList.size())
  {
    show_record(recordList,i);
    i++; count++;
    if (count==5 && i!=recordList.size())
    {
      cout << endl;
      cout << "Please enter the corresponding index to delete record, enter n to view next page(press Enter to Exit): ";
      while (true)
      {
        getline(cin,option);
        if (option=="") {return;}
        else if (option=="n") {count=0; cout<<endl; break;}
        else if (int_check(option))
        {
          int i= stoi(option);
          if (i>=recordList.size()) {cout << "Index does not exist, please enter again: ";}
          else {delete_record(income,expense,budget,recordList,methodList,typeList,i);return;}
        }
        else {cout << "Invalid input,please Enter again: ";}
      }
    }
  }
  cout<<endl<< "Please enter the corresponding index to delete record(press Enter to Exit): ";
  while (true)
  {
    getline(cin,option);
    if (option=="") {return;}
    else if (int_check(option))
    {
      int i= stoi(option);
      if (i>=recordList.size()) {cout << "Index does not exist, please enter again: ";}
      else {delete_record(income,expense,budget,recordList,methodList,typeList,i); cout<<"Record deleted successfully"<<endl;return;}
    }
    else {cout << "Invalid input,please Enter again: ";}
  }
}


void show(float &income,float &expense,float &budget,vector<Record> &recordList,map<string,int> &methodList, map<string,int> &typeList)
{
  string choice;
  while (true)
  {
    show_menu();
    getline(cin,choice);
    if(choice=="1") {sort_time(recordList);}
    else if(choice=="2") {sort_amount(recordList);}
    else if(choice=="3") {sort_method(recordList);}
    else if(choice=="4") {sort_type(recordList);}
    else if(choice=="5") {search_time(recordList);}
    else if(choice=="6") {search_amount(recordList);}
    else if(choice=="7") {search_method(recordList,methodList);}
    else if(choice=="8") {search_type(recordList,typeList);}
    else if(choice=="") {break;}
    else if(choice=="d") {delete_mode(income,expense,budget,recordList,methodList,typeList);}
    else if(choice=="e") {edit_mode(income,expense,budget,recordList,methodList,typeList);}
    else {cout << "Invalid option,please enter again: ";}
  }
}

