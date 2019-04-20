#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstdlib>
using namespace std;

//class and struct names are captialized,variable names are not.

class Record
{
  public:
    void set_amount(float);
    void set_time(string);
    void set_type(string);
    void set_method(string);
    void set_remark(string);
    float get_amount();
    string get_time();
    string get_type();
    string get_method();
    string get_remark();

 //private:
    float amount;
    string time;  //time format is: "YYYY-MM-DD"
    string type; //such as "food"
    string method; //such as "cash"
    string remark;

};


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


struct RecordCategory //RecordCategory is struct,contains type and corresponding count.
{
  int count;
  string category;
};
//***************************************************************************
// function to extend the dynamic array of recordList and delete the old one
void extend_array(RecordCategory *&List,int &List_length,int &max_List){
  RecordCategory *newList= new RecordCategory[max_List*2];
  max_List*=2;
  for (int i=0;i<List_length;i++){
    newList[i]=List[i];
  }
  delete List;
  List=newList;
}
// argument overload function to entend the dynamic array of typeList and methodList and delete the old one
void extend_array(Record *&List,int &length_recordList,int &max_recordList){
  Record *newList= new Record[max_recordList*2];
  max_recordList*=2;
  for (int i=0;i<length_recordList;i++){
    newList[i]=List[i];
  }
  delete List;
  List=newList;
}
//function to use user record to fill in both typelist and method list
void List_fill(RecordCategory *&List, int &List_length, string value,int &max_List){
  bool newtype=1;
  for (int i=0;i<List_length;i++){
    if (List[i].category==value){
      List[i].count+=1;
      newtype=0;
      break;
    }
  }
  if (newtype==1){
    List[List_length]={1,value};
    List_length+=1;
    if (List_length>=max_List){
      extend_array(List,List_length,max_List);
    }
  }
}

//extract information from user_record.txt and fill in recordList
void load_userdata(string login_user, Record *&recordList, RecordCategory *&typeList ,RecordCategory *&methodList,int &length_recordList, int &length_typeList,int &length_methodList,int &max_recordList,int &max_typeList,int &max_methodList){
   string record_line;
   ifstream record((login_user+"_record.txt").c_str());
   if (record.fail()){
     cout<<"This user does not exist"<<endl;
     exit(1);
   }
   while (getline(record,record_line)){
     Record temp;
     string current_type;
     string current_method;
     int seperator_position [4];
     for (int i=0;i<4;i++){
       seperator_position[i]=record_line.find("|");
       record_line.replace(seperator_position[i],1,"~");
     }
     temp.set_amount(stof((record_line.substr(0,seperator_position[0])).c_str()));
     temp.set_time(record_line.substr(seperator_position[0]+1,seperator_position[1]-seperator_position[0]-1));
     current_type=record_line.substr(seperator_position[1]+1,seperator_position[2]-seperator_position[1]-1);
     temp.set_type(current_type);
     current_method=record_line.substr(seperator_position[2]+1,seperator_position[3]-seperator_position[2]-1);
     temp.set_method(current_method);
     temp.set_remark(record_line.substr(seperator_position[3]+1,record_line.size()-seperator_position[3]-1));
     recordList[length_recordList]=temp;
     length_recordList+=1;
     if (length_recordList>=max_recordList){
       extend_array(recordList,length_recordList,max_recordList);
     }
     List_fill(typeList,length_typeList,current_type,max_typeList);
     List_fill(methodList,length_methodList,current_method,max_methodList);
   }
  /*  Testing code leave with that
 for (int i=0;i<length_recordList;i++){
       cout<<(recordList[i]).amount<<" "<<(recordList[i]).time<<" "<<(recordList[i]).type<<" "<<(recordList[i]).method<<" "<<(recordList[i]).remark<<" "<<endl;
     }
     for (int i=0;i<length_typeList;i++){
       cout<<(typeList[i]).category<<" "<<(typeList[i]).count<<endl;
     }
     for (int i=0;i<length_methodList;i++){
       cout<<(methodList[i]).category<<" "<<(methodList[i]).count<<endl;
     }    */
   record.close();
}
//*************************************************************************************
//print the second menu about the function avaliable for execution
void print_menu2(){
  cout<<"*************************************"<<endl;
  cout<<"Function needed to be choose"<<endl;
  cout<<"1.Add"<<endl;
  cout<<"2.Exit"<<endl;
  cout<<"Please select the menu by entering corresponding number"<<endl;
}
//************************************************************************************
//check whether the user input function are valid
bool amount_check(string amount){
  for (int i=0;i<amount.length();i++){
    if (!isdigit(amount[i])){
      return 0;
    }
  }
  return 1;
}

//check whether the user input time fit the format
bool time_check(string time){
  if (time.length()!=8){ return 0;}
  for (int i=0;i<time.length();i++){
    if (!isdigit(time[i])){
      return 0;
    }
  }
  if (time.substr(4,2)>"12" or time.substr(4,2)<"01"){ return 0;}
  if (time.substr(6,2)>"31" or time.substr(6,2)<"01"){ return 0;}
  return 1;
}

//get the record from user input/ input promotion
void prompt_add_input(float &amount,string &time,string &type,string &method,string &remark){
  string s_amount;
  string choice_ei;
  //get the type: expenditure or income
  cout<<"Please indicate type of record"<<endl;
  cout<<"1.Expenditure"<<endl;
  cout<<"2.Income"<<endl;
  getline(cin,choice_ei);
  while (choice_ei!="1" && choice_ei!="2"){
      cout<<"Invalid option"<<endl;
      getline(cin,choice_ei);
  }
  // get the amount
  cout<<"Please indicate the amount"<<endl;
  getline(cin,s_amount);
  while (!amount_check(s_amount)){
    getline(cin,s_amount);
    cout<<"Invalid amount"<<endl;
  }
  //precess the amount
  if (choice_ei=="1"){amount=stof("-"+s_amount);}
  else{amount=stof("+"+s_amount);}
  //get the time
  cout<<"Please enter the year month date by following exactly format: YYYYDDMM"<<endl;
  getline(cin,time);
  while (!time_check(time)){
    getline(cin,time);
    cout<<"Invalid input"<<endl;
  }
  time=time.substr(0,4)+"-"+time.substr(4,2)+"-"+time.substr(6,2);
  //get type/method/remark
  cout<<"Please input the type of expenditure/income"<<endl;
  getline(cin,type);
  cout<<"Please input the payment method of expenditure/income"<<endl;
  getline(cin,method);
  cout<<"Please add some remark to the record"<<endl;
  getline(cin,remark);
}

// add record from user
void add(Record *&recordList, RecordCategory *&typeList ,RecordCategory *&methodList,int &length_recordList, int &length_typeList,int &length_methodList,int &max_recordList,int &max_typeList,int &max_methodList){
  string time,type,method,remark;
  float amount;
  prompt_add_input(amount,time,type,method,remark);
  Record temp;
  temp.set_amount(amount);
  temp.set_time(time);
  temp.set_type(type);
  temp.set_method(method);
  temp.set_remark(remark);
  recordList[length_recordList]=temp;
  length_recordList+=1;
  if (length_recordList>=max_recordList){
    extend_array(recordList,length_recordList,max_recordList);
  }
  List_fill(typeList,length_typeList,type,max_typeList);
  List_fill(methodList,length_methodList,method,max_methodList);
}
//********************************************************************************************
//write data in to the
void write_data(string login_user, Record *&recordList, RecordCategory *&typeList ,RecordCategory *&methodList,int &length_recordList, int &length_typeList,int &length_methodList,int &max_recordList,int &max_typeList,int &max_methodList){
  ofstream fin((login_user+"_record.txt").c_str());
  if (fin.fail()){
    cout<<"fail to open "<<login_user<<"_record.txt"<<endl;
    exit(1);
  }
  for (int i=0;i<length_recordList;i++){
     string line;
     line=to_string(recordList[i].get_amount())+"|"+recordList[i].get_time()+"|"+recordList[i].get_type()+"|"+recordList[i].get_method()+"|"+recordList[i].get_remark();
     fin<<line<<endl;
  }
}

//*********************************************************************************************
int main()
{ string login_user="Tom";
  Record *recordList = new Record[100];  //recordList is a pointer,type is Record
  RecordCategory *typeList = new RecordCategory[100];
  RecordCategory *methodList = new RecordCategory[100];
  int max_recordList=100;
  int max_typeList=100;
  int max_methodList=100;
  int length_recordList=0;
  int length_typeList=0;
  int length_methodList=0;
  load_userdata(login_user,recordList,typeList,methodList,length_recordList,length_typeList,length_methodList,max_recordList,max_typeList,max_methodList);
  // The overall menu of function avaliable for execution after login
  string choice;
  print_menu2();
  while (true){
    getline(cin,choice);
    if (choice=="1"){
      add(recordList,typeList,methodList,length_recordList,length_typeList,length_methodList,max_recordList,max_typeList,max_methodList);
      print_menu2();
      }
    else if (choice=="2"){
      write_data(login_user,recordList,typeList,methodList,length_recordList,length_typeList,length_methodList,max_recordList,max_typeList,max_methodList);
      break;
      }
    else {
      cout<<"please input valid choice"<<endl;
    }
  }
  for (int i=0;i<length_recordList;i++){
        cout<<(recordList[i]).amount<<" "<<(recordList[i]).time<<" "<<(recordList[i]).type<<" "<<(recordList[i]).method<<" "<<(recordList[i]).remark<<" "<<endl;
      }
  for (int i=0;i<length_typeList;i++){
        cout<<(typeList[i]).category<<" "<<(typeList[i]).count<<endl;
      }
  for (int i=0;i<length_methodList;i++){
        cout<<(methodList[i]).category<<" "<<(methodList[i]).count<<endl;
      }




/*  delete [] recordList; //These 3 delete are used only for testing
  delete [] typeList;  //They may be put somewhere else in the complete program.
  delete [] methodList;*/
  return 0;
}
