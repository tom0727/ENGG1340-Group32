void print_menu3(){
  cout << endl;
  cout<<"1.Set budget"<<endl;
  cout<<"2.View the type report"<<endl;
  cout<<"3.View the method report"<<endl;
  cout<<"4.View overall expense and income by date"<<endl;
  cout<<"5.View monthly income and expense"<<endl;
  cout<<"Please enter your choice(press Enter to Exit): ";
}
void set_budget(float &budget, float &expense){
  string s_budget;
  cout<<"Please enter your expected budget: ";
  getline(cin,s_budget);
  while (!amount_check(s_budget)||s_budget[0]=='-'){
    cout<<"Invalid input, please enter again: ";
    getline(cin,s_budget);
  }
  budget=stof(s_budget);
  cout<<"Budget set successfully"<<endl;
  if (expense>=budget) {cout<<"The current expense is: "<<expense<< " ,You have exceeded the budget of "<<budget;}
}

float to_percentage (float amount){
  if (amount==0){return 0;}
  else{return (amount*100);}
}

void print_graph (map <float,string> &datamap,float &income,float &expense,string x_header){
    cout<<"Income Percentage"<<endl;
    cout<<"A"<<endl;
    for (int j=21;j>=0;j--){
      cout<<"I";
      if (j%4==3){
        cout<<setw(3)<<(j+1)*5<<"%     ";
      }
      else{
        cout<<"         ";
      }
      for (map <float,string >::iterator itr=datamap.begin();itr!=datamap.end();itr++){
        if (itr->first<0){continue;}
        if ((itr->first/income)>=j*0.05){
          cout<<"**";
          cout<<"        ";
        }
        else if ((j*0.05-(itr->first/income))<0.05){cout<<fixed<<setprecision(1)<<to_percentage((itr->first)/income)<<"%     ";}
        else if (j*0.05-(itr->first/income)<0.10 && j*0.05-(itr->first/income)>0.05){cout<<fixed<<left<<setprecision(1)<<setw(10)<<itr->first;}
        else{cout<<"          ";};
      }
      cout<<endl;
    }
   cout<<"-------------------------------------------------------------------->"<<x_header<<endl;
   cout<<"   ";
   for (map <float,string >::iterator itr=datamap.begin();itr!=datamap.end();itr++){
      if (itr->first<0){continue;}
      cout<<setw(10)<<right<<itr->second;
   }
   cout<<endl;
   cout<<endl;



   cout<<"Expense Percentage"<<endl;
   cout<<"A"<<endl;
   cout<<"I"<<endl;
   for (int j=21;j>=0;j--){
     cout<<"I";
     if (j%4==3){
       cout<<setw(3)<<(j+1)*5<<"%     ";
     }
     else{
       cout<<"         ";
     }
     for (map <float,string >::iterator itr=datamap.begin();itr!=datamap.end();itr++){
       if (itr->first>0){continue;}
       if ((itr->first/expense)<=(j*-0.05)){
         cout<<"**";
         cout<<"        ";
       }
       else if ((itr->first/expense)+j*0.05<0.05){cout<<fixed<<setprecision(1)<<to_percentage(-(itr->first)/expense)<<"%     ";}
       else if ((itr->first/expense)+j*0.05<0.10 && (itr->first/expense)+j*0.05>0.05){cout<<fixed<<left<<setprecision(1)<<setw(10)<<-itr->first;}
       else{cout<<"          ";};
     }
     cout<<endl;
   }
  cout<<"-------------------------------------------------------------------->"<<x_header<<endl;
  cout<<"   ";
  for (map <float,string >::iterator itr=datamap.begin();itr!=datamap.end();itr++){
     if (itr->first>0){continue;}
     cout<<setw(10)<<right<<itr->second;
  }
  cout<<endl;
  cout<<endl;
}




void Show_Income_Expense_ByType(vector <Record> &recordList,map <string,int> &typeList,float &income,float &expense){
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
  cout<<"1.View by graph"<<endl;
  cout<<"2.View by Text"<<endl;
  cout<<"Please input your choice (Press Enter to exit)";
  getline(cin,choice);
  while (true){
    if (choice=="1"){print_graph(typemap,income,expense,"Type");return;}
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
    else {cout<<"Invalid input, please enter again: ";getline(cin,choice);}
  }
}




void Show_Income_Expense_ByMethod(vector <Record> &recordList,map <string,int> &methodList,float &income,float &expense)
{
  map <float,string> methodmap;
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
  cout<<"1.View by graph"<<endl;
  cout<<"2.View by Text"<<endl;
  cout<<"Please input your choice (Press Enter to exit)";
  getline(cin,choice);
  while (true){
    if (choice=="1"){print_graph(methodmap,income,expense,"Method");return;}
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

void print_graph2 (map <string,float> &timemap_income,map <string,float> &timemap_expense,float &income,float &expense,string x_header){
    cout<<"Income Percentage"<<endl;
    cout<<"A"<<endl;
    for (int j=21;j>=0;j--){
      cout<<"I";
      if (j%4==3){
        cout<<setw(3)<<(j+1)*5<<"%     ";
      }
      else{cout<<"         ";}
      for (map <string,float>::iterator itr=timemap_income.begin();itr!=timemap_income.end();itr++){
        if ((itr->second/income)>j*0.05){
          cout<<"**";
          cout<<"        ";
        }
        else if ((j*0.05-(itr->second/income))<0.05){cout<<fixed<<setprecision(1)<<left<<setw(5)<<to_percentage((itr->second)/income)<<"%    ";}
        else if (j*0.05-(itr->second/income)<0.10 && j*0.05-(itr->second/income)>=0.05){cout<<fixed<<left<<setprecision(1)<<setw(10)<<itr->second;}
        else{cout<<"          ";};
      }
      cout<<endl;
    }
   cout<<"-------------------------------------------------------------------->"<<x_header<<endl;
   cout<<"    ";
   for (map <string,float >::iterator itr=timemap_income.begin();itr!=timemap_income.end();itr++){
      cout<<setw(10)<<right<<itr->first;
   }
   cout<<endl;
   cout<<endl;


   cout<<"Expense Percentage"<<endl;
   cout<<"A"<<endl;
   cout<<"I"<<endl;
   for (int j=21;j>=0;j--){
     cout<<"I";
     if (j%4==3){
       cout<<setw(3)<<(j+1)*5<<"%     ";
     }
     else{
       cout<<"         ";
     }
     for (map <string,float >::iterator itr=timemap_expense.begin();itr!=timemap_expense.end();itr++){
       if ((itr->second/expense)<(j*-0.05)){
         cout<<"**";
         cout<<"        ";
       }
       else if ((itr->second/expense)+j*0.05<0.05){cout<<fixed<<setprecision(1)<<left<<setw(5)<<to_percentage(-(itr->second/expense))<<"%    ";}
       else if ((itr->second/expense)+j*0.05<0.10 && (itr->second/expense)+j*0.05>=0.05){cout<<fixed<<left<<setprecision(1)<<setw(10)<<(itr->second);}
       else{cout<<"          ";};
     }
     cout<<endl;
   }
  cout<<"-------------------------------------------------------------------->"<<x_header<<endl;
  cout<<"    ";
  for (map <string,float >::iterator itr=timemap_expense.begin();itr!=timemap_expense.end();itr++){
     cout<<setw(10)<<right<<itr->first;
  }
  cout<<endl;
  cout<<endl;
}

bool time_check2(string time){
  if (time.length()!=6){ return 0;}
  for (int i=0;i<time.length();i++){
    if (!isdigit(time[i])){
      return 0;
    }
  }
  if (time.substr(4,2)>"12" or time.substr(4,2)<"01"){ return 0;} //check if "month" is valid
  return 1;
}

void Show_Income_Expense_ByMonth(vector <Record> &recordList){
  cout << endl;
  cout << "Please enter a monthly time interval you want to search for" << endl;
  cout << "The format is YYYYMM, press Enter to exit" << endl;


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


  float total_income=0,total_expense=0;
  map <string,float> timemap_income,timemap_expense;
  for (string  i=starttime;i<=endtime;date_increment(i)){  //assume it is a vector
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
  string choice;
  cout<<"1.View by Graph"<<endl;
  cout<<"2.View by Text"<<endl;
  cout<<"Please input your choice (Press Enter to exit)";
  getline(cin,choice);
  while (true){
    if (choice=="1"){print_graph2(timemap_income,timemap_expense,total_income,total_expense,"Time");return;}
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

void Show_Income_Expense_ByDate(vector <Record> &recordList){
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
    cout << "Invalid input,please enter again" << endl;
    getline (cin,starttime);
    if (starttime=="") {return;}
  }
  if (starttime=="0") {starttime = "00000000";}
  starttime=starttime.substr(0,4)+"-"+starttime.substr(4,2)+"-"+starttime.substr(6,2);

  cout << "End time: ";
  getline(cin,endtime);
  if (endtime=="") {return;}
  while (!time_check(endtime) && endtime!="0")  //time_check function is in another file
  {
    cout << "Invalid input,please enter again" << endl;
    getline (cin,endtime);
    if (endtime=="") {return;}
  }
  if (endtime=="0") {endtime = "99999999";}
  endtime=endtime.substr(0,4)+"-"+endtime.substr(4,2)+"-"+endtime.substr(6,2);

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



void financial_report(vector <Record> &recordList,map <string,int> &typeList, map <string,int> &methodList,float &income,float &expense,float &budget){
  cout << endl;
  cout<<"You have entered the financial report mode"<<endl;
  while (true)
  {
    string choice;
    print_menu3();
    getline(cin,choice);
    if (choice=="1"){set_budget(budget,expense);}
    else if (choice=="2"){Show_Income_Expense_ByType(recordList,typeList,income,expense);}
    else if (choice=="3"){Show_Income_Expense_ByMethod(recordList,methodList,income,expense);}
    else if (choice=="4"){Show_Income_Expense_ByDate(recordList);}
    else if (choice=="5"){Show_Income_Expense_ByMonth(recordList);}
    else if (choice==""){break;}
    else{cout<<"Invalid input,please enter again: ";}
  }
}
