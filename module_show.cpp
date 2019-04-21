bool int_check(string amount){
  for (int i=0;i<amount.length();i++){
    if (!isdigit(amount[i])){
      return 0;
    }
  }
  return 1;
}

void show_menu()
{
  cout << "*****************" << endl;
  cout << "You are now asking to show Records" << endl;
  cout << "Please enter an integer or char to select" << endl;
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
  cout << "9.Exit" << endl;
}

void show_record(vector<Record> &recordList,int &i)
{
  cout<<i<<" "<<(recordList[i]).get_amount()<<" "<<(recordList[i]).get_time()<<" "<<(recordList[i]).get_type()<<" "<<(recordList[i]).get_method()<<" "<<(recordList[i]).get_remark()<<" "<<endl;
}

bool compareTime(Record &r1,Record &r2)
{ return (r1.get_time() > r2.get_time()); }  //From new to old time

bool compareAmount(Record &r1,Record &r2)
{ return (r1.get_amount() > r2.get_amount()); }  //From big to small amount

bool compareMethod(Record &r1,Record &r2)
{ return (r1.get_method() < r2.get_method()); }

bool compareType(Record &r1,Record &r2)
{ return (r1.get_type() < r2.get_type()); }

void sort_time(vector<Record> &recordList)
{
  sort(recordList.begin(),recordList.end(),compareTime);
  for (int i=0;i<recordList.size();i++) {show_record(recordList,i);}
}

void sort_amount(vector<Record> &recordList)
{
  sort(recordList.begin(),recordList.end(),compareAmount);
  for (int i=0;i<recordList.size();i++) {show_record(recordList,i);}
}

void sort_method(vector<Record> &recordList)
{
  sort(recordList.begin(),recordList.end(),compareMethod);
  for (int i=0;i<recordList.size();i++) {show_record(recordList,i);}
}

void sort_type(vector<Record> &recordList)
{
  sort(recordList.begin(),recordList.end(),compareType);
  for (int i=0;i<recordList.size();i++) {show_record(recordList,i);}
}

void search_time(vector<Record> &recordList)
{
  cout << "Please enter a time interval you want to search for:(The format is YYYYMMDD)" << endl;
  cout << "Start time: ";
  string starttime,endtime;
  getline(cin,starttime);
  while (!time_check(starttime))  //time_check function is in another file
  {
    cout << "Invalid input" << endl;
    getline (cin,starttime);
  }

  cout << "End time: ";
  getline(cin,endtime);
  while (!time_check(endtime))  //time_check function is in another file
  {
    cout << "Invalid input" << endl;
    getline (cin,endtime);
  }

  for (int i=0;i<recordList.size();i++)  //assume it is a vector
  {
    if (recordList[i].get_time()>=starttime && recordList[i].get_time()<=endtime)
    {
      show_record(recordList,i);
    }
  }
}

void search_amount(vector<Record> &recordList)  //search according to an amount interval
{
  cout << "Please enter an amount interval you want to search for:" << endl;
  string low,high;
  cout << "Lower amount: ";
  getline(cin,low);
  while (!amount_check(low))
  {
    cout << "Invalid input" << endl;
    getline (cin,low);
  }

  cout << "Higher amount: ";
  getline(cin,high);
  while (!amount_check(high))
  {
    cout << "Invalid input" << endl;
    getline (cin,high);
  }

  float l=stof(low),h=stof(high);

  for (int i=0;i<recordList.size();i++)  //assume it is a vector
  {
    if (fabs(recordList[i].get_amount()) >= l && fabs(recordList[i].get_amount()) <= h)  //using absolute value
    {show_record(recordList,i);}
  }
}

void search_method(vector<Record> &recordList,vector<RecordCategory> &methodList)
{
  cout << "Please enter a method you want to search for:" << endl;
  cout << "These are the existing method:" << endl;
  for (int i=0;i<methodList.size();i++)
  {
    cout << methodList[i].category << " ";  //showing existing method
  }
  cout << endl;
  string method;
  getline(cin,method);
  transform(method.begin(),method.end(),method.begin(),tolower);  //transform "method" into lower case
  for (int i=0;i<recordList.size();i++)  //assume it is a vector
  {
    if (recordList[i].get_method() == method)
    {
      show_record(recordList,i);
    }
  }
}

void search_type(vector<Record> &recordList,vector<RecordCategory> &typeList)
{
  cout << "Please enter a type you want to search for:" << endl;
  cout << "These are the existing type:" << endl;
  for (int i=0;i<typeList.size();i++)
  {
    cout << typeList[i].category << " ";  //showing existing type
  }
  cout << endl;
  string type;
  getline(cin,type);
  transform(type.begin(),type.end(),type.begin(),tolower);  //transform "type" into lower case
  for (int i=0;i<recordList.size();i++)  //assume it is a vector
  {
    if (recordList[i].get_type() == type)
    {show_record(recordList,i);}
  }
}

void edit_mode(float &income,float &expense,float &budget,vector<Record> &recordList,vector<Record> &methodList, vector<Record> &typeList)
{
  void sort_time(recordList);
  cout << "You are now in the edit mode,please enter the corresponding integer to edit record" << endl;
  string input;
  getline(cin,input);
  while (!int_check(input)) 
  {
    cout << "Invalid input, please enter again" << endl;
    getline(cin,input);
  }
  index


}

void edit_mode(float &income,float &expense,float &budget,vector<Record> &recordList,vector<RecordCategory> &methodList, vector<RecordCategory> &typeList)
{
  void sort_time(recordList);
  cout << "You are now in the edit mode,please enter the corresponding integer to edit record" << endl;
  string input;
  getline(cin,input);
  while (!int_check(input)) 
  {
    cout << "Invalid input, please enter again" << endl;
    getline(cin,input);
  }
  int i = stoi(input);
  show_record(recordList,i);
  cout << "Please edit the record, if you want to keep the origin data, please press Enter" << endl;

  cout << "Please enter the Amount(positive means income,negative means expense):";
  getline(cin,input);
  while (!amount_check(input))
  {
    cout << "Invalid input, please enter again" << endl;
    getline(cin,input);
  }
  if (input.size()==0);
  else 
  {
    float oldamount = recordList[i].get_amount();
    float newamount = stof(input);
    if (oldamount<0) {expense-=oldamount;}
    else if (oldamount>0) {income-=oldamount;}
    if (newamount<0) {expense+=newamount;}
    else if (newamount>0) {income+=newamount;}
    recordList[i].set_amount(newamount);
  }

  cout << "Please enter the Date:(Format:YYYYMMDD)";
  getline(cin,input);
  while (!time_check(input))
  {
    cout << "Invalid input, please enter again" << endl;
    getline(cin,input);
  }
  if (input.size()==0);
  else {recordList[i].set_time(input);}

  cout << "Please enter the Method:";
  getline(cin,input);
  if (input.size()==0);
  else {recordList[i].set_method(input); List_fill(methodList,input);}

  cout << "Please enter the Type:";
  getline(cin,input);
  if (input.size()==0);
  else {recordList[i].set_type(input); List_fill(typeList,input);}

  cout << "Please enter the Remark:";
  getline(cin,input);
  if (input.size()==0);
  else {recordList[i].set_remark(input);}

}




void show(float &income,float &expense,float &budget,vector<Record> &recordList,vector<Record> &methodList, vector<Record> &typeList)
{
  string choice;
  bool stop = false;
  while (!stop)
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
    else if(choice=="9") {stop = true;}
    else if(choice=="d") {delete_mode();}
    else if(choice=="e") {edit_mode();}
    else {cout << "Invalid option,please enter again" << endl;}
  }
}


