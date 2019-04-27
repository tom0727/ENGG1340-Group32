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
//print the menu of the financial report function
void print_menu3(){
  cout << endl;
  cout<<"1.Set budget"<<endl;
  cout<<"2.View the type report"<<endl;
  cout<<"3.View the method report"<<endl;
  cout<<"4.View overall expense and income by date"<<endl;
  cout<<"5.View monthly income and expense"<<endl;
  cout<<"Please enter your choice(press Enter to Exit): ";
}

// execute the first function of financial financial_report： set the budget
//input : the original budget user defined and the user total expense
void set_budget(float &budget, float &expense){
  string s_budget;
  cout<<"Please enter your expected budget: ";
  getline(cin,s_budget);
  //check whether the amount user input is in the right format
  while (!amount_check(s_budget)||s_budget[0]=='-'){
    cout<<"Invalid input, please enter again: ";
    getline(cin,s_budget);
  }
  budget=stof(s_budget);
  cout<<"Budget set successfully"<<endl;
  if (expense>=budget) {cout<<"The current expense is: "<<expense<< " ,You have exceeded the budget of "<<budget;}
}

// helper function to format the output
//change the decimal number to the persentage number
float to_percentage (float amount){
  if (amount==0){return 0;}
  else{return (amount*100);}
}

// helper function the print the bar chart with
//X-axis: the record payment method or the record payment type(category)
//Y-axis: the persentage each category occupy the total income / Expense
// x_header: the header of the x axis
//datamap: A map with key: the income/expense of certain categoty or payment methodmap
//                  value: the name of that category/ payment method
void print_graph (map <float,string> &datamap,float &income,float &expense,string x_header){
    // print the bar chart of different category's income
    cout<<"Income Percentage"<<endl;
    cout<<"A"<<endl;
    for (int j=22;j>=0;j--){
      cout<<"I";
      if (j%4==3){
        cout<<setw(3)<<(j+1)*5<<"%     ";
      }
      else{
        cout<<"         ";
      }
      // print the bar
      for (map <float,string >::iterator itr=datamap.begin();itr!=datamap.end();itr++){
        if (itr->first<0){continue;}
        if ((itr->first/income)>=j*0.05){
          cout<<"**";
          cout<<"        ";
        }
        // print number in the top of the bar to show the persentagen of that type with respect to total income
        // and the absolute value of that type of income
        else if ((j*0.05-(itr->first/income))<0.05){cout<<fixed<<setprecision(1)<<to_percentage((itr->first)/income)<<"%     ";}
        else if (j*0.05-(itr->first/income)<0.10 && j*0.05-(itr->first/income)>0.05){cout<<fixed<<left<<setprecision(1)<<setw(10)<<itr->first;}
        else{cout<<"          ";};
      }
      cout<<endl;
    }
    // print the X-axis and the X-axis header
   cout<<"-------------------------------------------------------------------->"<<x_header<<endl;
   cout<<"   ";
   // print the name of each category along X-axis
   for (map <float,string >::iterator itr=datamap.begin();itr!=datamap.end();itr++){
      if (itr->first<0){continue;}
      cout<<setw(10)<<right<<itr->second;
   }
   cout<<endl;
   cout<<endl;

   // repeat the similar process for expense
   // print the graph of different category's expense
   cout<<"Expense Percentage"<<endl;
   cout<<"A"<<endl;
   cout<<"I"<<endl;
   for (int j=22;j>=0;j--){
     cout<<"I";
     if (j%4==3){
       cout<<setw(3)<<(j+1)*5<<"%     ";
     }
     else{
       cout<<"         ";
     }
     // print the bar
     for (map <float,string >::iterator itr=datamap.begin();itr!=datamap.end();itr++){
       if (itr->first>0){continue;}
       if ((itr->first/expense)<=(j*-0.05)){
         cout<<"**";
         cout<<"        ";
       }
       // print number in the top of the bar to show the persentagen of that type with respect to total income
       // and the absolute value of that type of income
       else if ((itr->first/expense)+j*0.05<0.05){cout<<fixed<<setprecision(1)<<to_percentage(-(itr->first)/expense)<<"%     ";}
       else if ((itr->first/expense)+j*0.05<0.10 && (itr->first/expense)+j*0.05>0.05){cout<<fixed<<left<<setprecision(1)<<setw(10)<<-itr->first;}
       else{cout<<"          ";};
     }
     cout<<endl;
   }
   // print the X-axis and the X-axis header
  cout<<"-------------------------------------------------------------------->"<<x_header<<endl;
  cout<<"   ";
  // print the name of each category along X-axis
  for (map <float,string >::iterator itr=datamap.begin();itr!=datamap.end();itr++){
     if (itr->first>0){continue;}
     cout<<setw(10)<<right<<itr->second;
  }
  cout<<endl;
  cout<<endl;
}



// execute the second function of financial financial_report： show the financial report according to the usage of money
//input: the user record, the map with key: the name of each expense/income type
//                                with value :  the numnber of record which have that specific type
void Show_Income_Expense_ByType(vector <Record> &recordList,map <string,int> &typeList,float &income,float &expense){
  // generate a map with key: the total expense/income of a particular usage of income/expense
  //                with value : the name of that type usage of income/expense
  map <float,string> typemap;
  for (map <string,int>::iterator itr=typeList.begin();itr!=typeList.end();itr++){
    float Category_income=0, Category_expense=0;
    for (int i=0;i<recordList.size();i++){
      if (itr->first==recordList[i].get_type() && recordList[i].get_amount()>0){
        Category_income+=recordList[i].get_amount();
      }
      if (itr->first==recordList[i].get_type() && recordList[i].get_amount()<0){
        Category_expense+=recordList[i].get_amount();
      }
    }
    if (Category_income!=0){typemap[Category_income]=itr->first;}
    if (Category_expense!=0){typemap[Category_expense]=itr->first;}
  }

  cout << endl;
  string choice;
  // print the menu to give user choice about the format to display
  cout<<"1.View by graph"<<endl;
  cout<<"2.View by Text"<<endl;
  cout<<"Please input your choice (Press Enter to exit) :";
  getline(cin,choice);
  while (true){
    // show by graph
    if (choice=="1"){print_graph(typemap,income,expense,"Type");return;}
    // show by text
    else if (choice=="2"){
      for (map <float,string>::iterator itr=typemap.begin();itr!=typemap.end();itr++){
        if ((itr->first)>0){
          cout<<"The "<<left<<setw(10)<<itr->second<<"income  is +"<<fixed<<setprecision(1)<<setw(9)<<itr->first<<" occupying "<<setw(5)<<to_percentage(itr->first/income)<< "% "<<"of total income"<<endl;
        }
        if ((itr->first)<0){
          cout<<"The "<<left<<setw(10)<<itr->second<<"expense is "<<fixed<<setprecision(1)<<setw(10)<<itr->first<<" occupying "<<setw(5)<<to_percentage(-(itr->first/expense))<<"% "<<"of total expense"<<endl;
        }
      }
      return;
    }
    else if (choice==""){return;}
    else {cout<<"Invalid input, please enter again :";getline(cin,choice);}
  }
}



// execute the third function of financial financial_report： show the financial report according to type of method of payment
//input: the user record, the map with key: the name of each expense/income type
//
void Show_Income_Expense_ByMethod(vector <Record> &recordList,map <string,int> &methodList,float &income,float &expense)
{
  map <float,string> methodmap;
  // generate a map with key: the total expense/income of a particular method of payment
  //                with value : the name of that method of payment
  for (map <string,int>::iterator itr=methodList.begin();itr!=methodList.end();itr++){
    float Category_income=0, Category_expense=0;
    for (int i=0;i<recordList.size();i++){
      if (itr->first==recordList[i].get_method() && recordList[i].get_amount()>0){
        Category_income+=recordList[i].get_amount();
      }
      if (itr->first==recordList[i].get_method() && recordList[i].get_amount()<0){
        Category_expense+=recordList[i].get_amount();
      }
    }
    if (Category_income!=0){methodmap[Category_income]=itr->first;}
    if (Category_expense!=0){methodmap[Category_expense]=itr->first;}
  }
  cout << endl;
  string choice;
  // the user would choice to view by graph and text
  cout<<"1.View by graph"<<endl;
  cout<<"2.View by Text"<<endl;
  cout<<"Please input your choice (Press Enter to exit) :";
  getline(cin,choice);
  while (true){
    // to show in graph format
    if (choice=="1"){print_graph(methodmap,income,expense,"Method");return;}
    // to show in text format
    else if (choice=="2"){
      for (map <float,string>::iterator itr=methodmap.begin();itr!=methodmap.end();itr++){
        if ((itr->first)>0){
          cout<<"The income  via "<<left<<setw(10)<<itr->second<<" is +"<<fixed<<setprecision(1)<<setw(9)<<itr->first<<" occupying "<<setw(5)<<to_percentage(itr->first/income)<<"% "<<"of total income"<<endl;
        }
        if ((itr->first)<0){
          cout<<"The expense via "<<left<<setw(10)<<itr->second<<" is "<<fixed<<setprecision(1)<<setw(10)<<itr->first<<" occupying "<<setw(5)<<to_percentage(-(itr->first/expense))<<"% "<<"of total expense"<<endl;
        }
      }
      return;
    }
    else if (choice==""){return;}
    else {cout<<"Invalid input, please enter again: ";getline(cin,choice);}
  }
}

// View the total income /expense in a user defined interval (specific to day)
void Show_Income_Expense_ByDate(vector <Record> &recordList){
  cout << endl;
  cout << "Please enter a time interval you want to search for" << endl;
  cout << "The format is YYYYMMDD, press Enter to exit" << endl;
  cout << "Enter 0 to show from the earliest/latest time" << endl;
  // prompt to input the starting date
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
  // to include the earlist possible date
  if (starttime=="0") {starttime = "00000000";}
  starttime=starttime.substr(0,4)+"-"+starttime.substr(4,2)+"-"+starttime.substr(6,2);

  // prompt to the endding date
  cout << "End time: ";
  getline(cin,endtime);
  if (endtime=="") {return;}
  while (!time_check(endtime) && endtime!="0")  //time_check function is in another file
  {
    cout << "Invalid input,please enter again: " ;
    getline (cin,endtime);
    if (endtime=="") {return;}
  }
  // to include the latest possible date
  if (endtime=="0") {endtime = "99999999";}
  endtime=endtime.substr(0,4)+"-"+endtime.substr(4,2)+"-"+endtime.substr(6,2);

  // interval_income,interval_expense: the total income /expense of the given defined interval
  float interval_expense=0,interval_income=0;
  for (int i=0;i<recordList.size();i++){  //assume it is a vector
    if (recordList[i].get_time()>=starttime && recordList[i].get_time()<=endtime){
      if (recordList[i].get_amount()>0){interval_income+=recordList[i].get_amount();}
      if (recordList[i].get_amount()<0){interval_expense+=recordList[i].get_amount();}
    }
  }
  cout << endl;
  cout<<"The total income  in this interval is: +"<<interval_income<<endl;
  cout<<"The total expense in this interval is: "<<interval_expense<<endl;
}


// helper function which help the iteration of data Format
// to increase the date by one moneth
// used in the fifth function: view monthly income /expenditure
void date_increment(string &date){
  if (date.substr(5,2)=="12"){
    date[5]='0';
    date[6]='1';
    if (date[3]=='9'){
      date[2]+=1;
      date[3]='0';
    }
    else{date[3]+=1;}
  }
  else if (date[6]=='9'){
    date[6]='0';
    date[5]='1';
  }
  else{date[6]+=1;}
}

// helper function for the fifth function which would help to print the bar chart
// the X-axis: the date_increment
// the Y-axis: the income/ expenditure of that month(seperately)
void print_graph2 (map <string,float> &timemap_income,map <string,float> &timemap_expense,float &income,float &expense,string x_header){
    // print the bar chart of the monthly income first
    cout<<"Income Percentage"<<endl;
    cout<<"A"<<endl;
    for (int j=22;j>=0;j--){
      cout<<"I";
      if (j%4==3){
        cout<<setw(3)<<(j+1)*5<<"%     ";
      }
      else{cout<<"         ";}
      // print the bar
      for (map <string,float>::iterator itr=timemap_income.begin();itr!=timemap_income.end();itr++){
        if ((itr->second/income)>j*0.05){
          cout<<"**";
          cout<<"        ";
        }
        // print the absolute value of income of each month above each month's bar
        // print the persentage of that month income with respective to total income of the period above each month of the bar
        else if ((j*0.05-(itr->second/income))<0.05){cout<<fixed<<setprecision(1)<<left<<setw(5)<<to_percentage((itr->second)/income)<<"%    ";}
        else if (j*0.05-(itr->second/income)<0.10 && j*0.05-(itr->second/income)>=0.05){cout<<fixed<<left<<setprecision(1)<<setw(10)<<itr->second;}
        else{cout<<"          ";};
      }
      cout<<endl;
    }
    //print the x-axis
   cout<<"-------------------------------------------------------------------->"<<x_header<<endl;
   cout<<"    ";
   // print the month along the x-axis
   for (map <string,float >::iterator itr=timemap_income.begin();itr!=timemap_income.end();itr++){
      cout<<setw(10)<<right<<itr->first;
   }
   cout<<endl;
   cout<<endl;

  // print the bar chart of the monthly expense
   cout<<"Expense Percentage"<<endl;
   cout<<"A"<<endl;
   cout<<"I"<<endl;
   for (int j=22;j>=0;j--){
     cout<<"I";
     if (j%4==3){
       cout<<setw(3)<<(j+1)*5<<"%     ";
     }
     else{
       cout<<"         ";
     }
     // print the bar
     for (map <string,float >::iterator itr=timemap_expense.begin();itr!=timemap_expense.end();itr++){
       if ((itr->second/expense)<(j*-0.05)){
         cout<<"**";
         cout<<"        ";
       }
       // print the absolute value of expense of each month above each month's bar
       // print the persentage of that month expense with respective to total expense of the period above each month of the bar
       else if ((itr->second/expense)+j*0.05<0.05){cout<<fixed<<setprecision(1)<<left<<setw(5)<<to_percentage(-(itr->second/expense))<<"%    ";}
       else if ((itr->second/expense)+j*0.05<0.10 && (itr->second/expense)+j*0.05>=0.05){cout<<fixed<<left<<setprecision(1)<<setw(10)<<((itr->second==0)? (itr->second):(-itr->second));}
       else{cout<<"          ";};
     }
     cout<<endl;
   }
  // print the X-axis
  cout<<"-------------------------------------------------------------------->"<<x_header<<endl;
  cout<<"    ";
  // print the month along x-axis
  for (map <string,float >::iterator itr=timemap_expense.begin();itr!=timemap_expense.end();itr++){
     cout<<setw(10)<<right<<itr->first;
  }
  cout<<endl;
  cout<<endl;
}

// execute the fifth function of financial financial_report： show the financial report of monthly income/expense
//input: the user record
void Show_Income_Expense_ByMonth(vector <Record> &recordList){
  cout << endl;
  cout << "Please enter a monthly time interval you want to search for" << endl;
  cout << "The format is YYYYMM, press Enter to exit" << endl;

  // prompt user to input the starting month
  cout << "Start time: ";
  string starttime,endtime;
  getline(cin,starttime);
  if (starttime=="") {return;}
  while (!time_check2(starttime))  //time_check function is in another file
  {
    cout << "Invalid input,please enter again, press Enter to exit" << endl;
    getline (cin,starttime);
    if (starttime=="") {return;}
  }
  starttime=starttime.substr(0,4)+"-"+starttime.substr(4,2);

  // prompt user to input the ending month
  cout << "End time: ";
  getline(cin,endtime);
  if (endtime=="") {return;}
  while (!time_check2(endtime))  //time_check function is in another file
  {
    cout << "Invalid input,please enter again, press Enter to exit" << endl;
    getline (cin,endtime);
    if (endtime=="") {return;}
  }
  endtime=endtime.substr(0,4)+"-"+endtime.substr(4,2);

  // total_income/total_expense: the total income /expense in the interval
  float total_income=0,total_expense=0;
  //gernerate two map with key:each month
  //                     value:the income/ expense of each month
  map <string,float> timemap_income,timemap_expense;
  for (string  i=starttime;i<=endtime;date_increment(i)){  //assume it is a vector
    // interval_income,interval_expense: the monthly income /expense
    float interval_expense=0,interval_income=0;
    for (int j=0;j<recordList.size();j++){
      if (recordList[j].get_time().substr(0,7)==i){
        if (recordList[j].get_amount()>0){interval_income+=recordList[j].get_amount();}
        if (recordList[j].get_amount()<0){interval_expense+=recordList[j].get_amount();}
      }
    }
    timemap_income[i]=interval_income;
    timemap_expense[i]=interval_expense;
    total_income+=interval_income;
    total_expense-=interval_expense;
  }
  cout << endl;
  // give user choice to view by graph or text
  string choice;
  cout<<"1.View by Graph"<<endl;
  cout<<"2.View by Text"<<endl;
  cout<<"Please input your choice (Press Enter to exit): ";
  getline(cin,choice);
  while (true){
    //view by graph
    if (choice=="1"){print_graph2(timemap_income,timemap_expense,total_income,total_expense,"Time");return;}
    // view by text
    else if (choice=="2"){
      for (map <string,float>::iterator itr=timemap_income.begin();itr!=timemap_income.end();itr++){
        cout<<"The montly income in "<<itr->first<<" is "<<fixed<<setprecision(1)<<itr->second<<endl;
      }
      cout<<endl;
      for (map <string,float>::iterator itr=timemap_expense.begin();itr!=timemap_expense.end();itr++){
        cout<<"The montly expense in "<<itr->first<<" is "<<fixed<<setprecision(1)<<itr->second<<endl;
      }
      return;
    }
    else if (choice==""){return;}
    else {cout<<"Invalid input, please enter again: ";getline(cin,choice);}
  }
}

// the main funciton for financial report, which links to individual sub-function
void financial_report(vector <Record> &recordList,map <string,int> &typeList, map <string,int> &methodList,float &income,float &expense,float &budget){
  cout << endl;
  cout<<"You have entered the financial report mode"<<endl;
  while (true)
  {
    string choice;
    // print the menu for financial report
    print_menu3();
    getline(cin,choice);
    // based on user's choice to enter different subfucntion
    if (choice=="1"){set_budget(budget,expense);}
    else if (choice=="2"){Show_Income_Expense_ByType(recordList,typeList,income,expense);}
    else if (choice=="3"){Show_Income_Expense_ByMethod(recordList,methodList,income,expense);}
    else if (choice=="4"){Show_Income_Expense_ByDate(recordList);}
    else if (choice=="5"){Show_Income_Expense_ByMonth(recordList);}
    else if (choice==""){break;}
    else{cout<<"Invalid input,please enter again: ";}
  }
}
