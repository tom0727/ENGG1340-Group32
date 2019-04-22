void print_menu3(){
  cout<<"1.Set budget"<<endl;
  cout<<"2.View the type report"<<endl;
  cout<<"3.View the method report"<<endl;
  cout<<"4.View overall expenditure and income by date"<<endl;
  cout<<"5.Exit"<<endl;
  cout<<"Please input your choice"<<endl;
}
void set_budget(float &budget){
  string s_budget;
  cout<<"please input your expected budget"<<endl;
  getline(cin,s_budget);
  while (!amount_check(s_budget) || s_budget[0]=='-'){
    cout<<"Invalid input, please input again"<<endl;
    getline(cin,s_budget);
  }
  budget=stof(s_budget);
}

float to_persentage (float amount){
  return 1LL*(amount*100)*10;
}

void Show_Income_Expense_ByType(vector <Record> &recordList,map <string,int> &typeList,float &income,float &expense){
  map <float,string> typemap;
  for (map <string,int>::iterator itr=typeList.begin();itr!=typeList.end();itr++){
    float Category_income=0, Category_expense=0;
    for (int i=0;i<recordList.size() && recordList.get_amount()>0;i++){
      if (itr->first==recordList[i].get_type() && recordList[i].get_amount()>0){
        Category_income+=recordList[i].get_amount();
      }
      if (itr->first==recordList[i].get_type() && recordList[i].get_amount()<0){
        Category_expense+=recordList[i].get_amount();
      }
    }
    typemap[Category_income]=itr->first;
    typemap[Category_expense]=itr->first;
  }
  for (map <float,string>::iterator itr=typemap.begin();itr!=typemap.end();itr++){
    if ((itr->first)>0){
      cout<<"The "<<left<<setw(10)<<itr->second<<"income is"<<Category_income<<"occupying"<<to_persentage(itr->first/income)<<"% of total income"<<endl;
    }
    if ((itr->first)<0){
      cout<<"The "<<left<<setw(10)<<itr->second<<"expenditure is"<<Category_income<<"occupying"<<to_persentage(itr->first/expense)<<"% of total expenditure"<<endl;
    }
  }
}




void Show_Income_Expense_ByMethod(vector <Record> &recordList,map <string,int> &methodList,float &income,float &expense){
  map <float,string> methodmap;
  for (map <string,int>::iterator itr=typeList.begin();itr!=typeList.end();itr++){
    float Category_income=0, Category_expense=0;
    for (int i=0;i<recordList.size() && recordList.get_amount()>0;i++){
      if (itr->first==recordList[i].get_method() && recordList[i].get_amount()>0){
        Category_income+=recordList[i].get_amount();
      }
      if (itr->first==recordList[i].get_method() && recordList[i].get_amount()<0){
        Category_expense+=recordList[i].get_amount();
      }
    }
    methodmap[Category_income]=itr->first;
    methodmap[Category_expense]=itr->first;
  }
  for (map <float,string>::iterator itr=methodmap.begin();itr!=methodmap.end();itr++){
    if ((itr->first)>0){
      cout<<"The income via "<<left<<setw(10)<<itr->second<<"is "<<Category_income<<"occupying "<<to_persentage(Category_income/income)<<"% of total income"<<endl;
    }
    if ((itr->first)<0){
      cout<<"The income via "<<left<<setw(10)<<itr->second<<"is "<<Category_expense<<"occupying"<<to_persentage(Category_expense/expense)<<"% of total expense"<<endl;
    }
  }
}

void Show_Income_Expense_ByDate(vector <Record> &recordList){
  cout << "Please enter a time interval you want to search for:(The format is YYYYMMDD)" << endl;
  cout << "Start time: "<<endl;
  string starttime,endtime;
  getline(cin,starttime);
  while (!time_check(starttime))  //time_check function is in another file
  {
    cout << "Invalid input" << endl;
    getline (cin,starttime);
  }

  cout << "End time: "<<endl;
  getline(cin,endtime);
  while (!time_check(endtime))  //time_check function is in another file
  {
    cout << "Invalid input" << endl;
    getline (cin,endtime);
  }

  float interval_expense=0,interval_income=0;
  for (int i=0;i<recordList.size();i++){  //assume it is a vector
    if (recordList[i].get_time()>=starttime && recordList[i].get_time()<=endtime){
      if (recordList[i].get_amount()>0){interval_income+=recordList[i].get_amount();}
      if (recordList[i].get_amount()<0){interval_expense+=recordList[i].get_amount();}
    }
  }
  cout<<"The total income in this interval is:"<<interval_income<<endl;
  cout<<"The total expenditure in this interval is:"<<interval_expense<<endl;
}


void financial_report(vector <Record> &recordList,map <string,int> &typeList, map <string,int> &methodList,float &income,float &expense,float &budget){
  cout<<"You have enter the financial report mode"<<endl;
  while (true)
  {
    string choice;
    print_menu3();
    getline(cin,choice);
    if (choice=="1"){set_budget(budget)}
    else if (choice=="2"){Show_Income_Expense_ByType(recordList,typeList,income,expense)}
    else if (choice=="3"){Show_Income_Expense_ByMethod(recordList,typeList,income,expense)}
    else if (choice=="4"){Show_Income_Expense_ByDate(recordList)}
    else if (choice=="5"){break;}
    else{cout<<"Invalid input"<<endl;}
  }
}
