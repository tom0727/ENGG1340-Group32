#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;

//class and struct names are captialized,variable names are not.
// the start of definition of data structure
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


//                    The End of definition of data structure
//*******************************************************************************

//  The start of definition of Helper Function
bool isalnum(char c) //checking if the char is a Alphabet or number
{
  if ((c>=65 and  c<=90) or (c>=97 and c<=122) or (c<=57 and c>=48))
  {return 1;}
  else {return 0;}
}

// The end of definition of Helper Function

//printing the login menu
/* print the starting menu*/
void printmenu(){
  cout<<"********************************************************************************************************"<<endl;
  cout<<"Welcome to private accounting system"<<endl;
  cout<<"1.Sign up"<<endl;
  cout<<"2.Login"<<endl;
  cout<<"Please select the menu by entering corresponding number(press Enter to Exit): ";
}

//***********************************************************************
//******************** Start of the login program***************************************
// Initialization function to create users.txt if it does not exist
void create_usertxt(){
  ifstream F_test ("users.txt");
  if (!F_test.good()){
    F_test.close();
    ofstream File("users.txt");
    File.close();
  }
  else{
    F_test.close();
  }
}
// End of the initializaiton function
// To be MODIFY
//Registration function

/* check whether username_input is in the correct format
1. It should be alphabet and number character only
2. It should not be already registered by others*/
bool username_check (string username){
  // Perform selection 1
  for (int i=0;i<username.size();i++){
    if (!isalnum(username[i])){
      cout<<"Username could only consist of digit and Alphabet"<<endl;
      return 0;
    }
  }
  // perform selection 2
  ifstream fin ("users.txt");
  if (fin.fail()){
    cout<<"Failed to open users.txt"<<endl;
  }
  string file_line;
  while (getline(fin,file_line)){
    if ((file_line.find(username)==0) and (file_line.substr(username.size(),1)=="#")){
      cout<<"This username has been registered by someone else,please try another one: ";
      return 0;
    }
  }
  fin.close();
  return 1;
}


/* register account and record it in to the file*/
void registeraccount(){
  string username;
  string password;
  cout<<"*****************************************************************************************************"<<endl;
  cout<<"Registration:"<<endl;
  while (true){
    cout<<"Username should only contain Alphabet or digit"<<endl;
    cout<<"Please settle your username: ";
    getline(cin,username);
    if (username_check(username)==true){
      cout<<"please settle your password: ";
      getline(cin,password);
      ofstream File ("users.txt",ofstream::app);
      ofstream RecordFile ((username+"_record.txt").c_str());
      if (File.fail()){
        cout<<"Fail to open users.txt"<<endl;
        exit(1);
      }
      File<<username<<"#"<<password<<"#"<<0<<"#"<<0<<"#"<<0<<endl;
      File.close();
      RecordFile.close();
      cout<<"Registeration successful"<<endl;
      break;
    }
}
}
// ***********************      END OF REGISTRATION function***********************88
//******************************************************************************
//                      start of the login function*******************************

// Find the user name in correct format and serach corresponding line in the user.txt
bool username_find(string &userrecord, string username){
  for (int i=0;i<username.size();i++){
    if (!isalnum(username[i])){
        cout<<"Invalid username.Username could only consist of digit and Alphabet"<<endl;
      return 0;
    }
  }
  ifstream fin ("users.txt");
  if (fin.fail()){
    cout<<"failed to open users.txt"<<endl;
  }
  string file_line;
  while (getline(fin,file_line)){
    if ((file_line.find(username)==0) and (file_line.substr(username.size(),1)=="#")){
      userrecord=file_line;
      return 1;
    }
  }
  fin.close();
  return 0;
}

//To check whether the username and password match. Prompt username and password input
bool authentification(string &login_user,string &user_password,float &budget,float &income,float &expense){
  string userrecord;
  string password;
  string username;
  string userdata;
  cout<<"********************************************************************************************************"<<endl;
  cout<<"Login:"<<endl;
  cout<<"Please enter your username: ";
  while (true){
    getline(cin,username);
    if (username_find(userrecord,username)){
      cout<<"Please enter the password: ";
      getline(cin,password);
      int extract_length=username.size()+password.size()+1;
      if ((userrecord.find(username+"#"+password)==0) and (userrecord.substr(extract_length,1)=="#")){
        cout<<"Login successful"<<endl;
        // load initial data for login user
        login_user=username;
        user_password=password;
        userrecord=userrecord.substr(extract_length+1,userrecord.size()-extract_length);
        extract_length=userrecord.find("#");
        budget=stof(userrecord.substr(0,extract_length));
        userrecord=userrecord.substr(extract_length+1,userrecord.size()-extract_length);
        extract_length=userrecord.find("#");
        income=stof(userrecord.substr(0,extract_length));
        userrecord=userrecord.substr(extract_length+1,userrecord.size()-extract_length);
        expense=stof(userrecord.substr(0,userrecord.find("#")));
        return 1;
      }
      else{
        cout<<"Incorrect password,please enter username again(press Enter to return to main menu): ";
      }
    }
    else if (username.size()==0){return 0;}
    else{cout<<"User name not found,please enter username again(press Enter to return to main menu): ";}
  }
}

//                          END of Login function
//********************************************************************************/
// main function for part I
void login(string &login_user,string &user_password,float &budget,float &income,float &expense){
  string choice;
  create_usertxt();
  printmenu();
  while (login_user==""){
    getline(cin,choice);
    if (choice=="1"){
        registeraccount();
        printmenu();
      }
    else if (choice=="2"){
      if (authentification(login_user,user_password,budget,income,expense)){break;}
      printmenu();
    }
    else if (choice.size()==0){
        exit(1);
      }
    else{
        cout<<"Invalid input, please enter again: (press Enter to exit)";
    }
  }
}
//                    End of the login program
//***************************************************************************
// *************************start of the load data from file section(load function)  ******************
//function to use user record to fill in both typelist and method list
void List_fill(map <string,int> &List,string value){
  bool newtype=1;
  if (List.count(value)){List[value]+=1;}
  else { List[value]=1;}
}

//extract information from user_record.txt and fill in recordList
void load_userdata(string login_user,  vector<Record> &recordList,  map <string,int> &typeList, map <string,int> &methodList){
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
     recordList.push_back(temp);
     List_fill(typeList,current_type);
     List_fill(methodList,current_method);
   }
   record.close();
}
//                        End of the load data from file function
//*************************************************************************************
//print the second menu about the function avaliable for execution
void print_menu2(){
  cout << endl;
  cout<<"********************************************************************************************************"<<endl;
  cout<<"Function needed to be choose"<<endl;
  cout<<"1.Add"<<endl;
  cout<<"2.Show"<<endl;
  cout<<"3.Financial Report"<<endl;
  cout<<"4.Change password"<<endl;
  cout<<"Please select the menu by entering corresponding number(press Enter to exit): ";
}
//************************************************************************************
// *****************************The start of the addition section***********************88
//check whether the user input function are valid
bool amount_check(string s_amount){
  if (!isdigit(s_amount[0]) && (s_amount[0]!='-' && s_amount[0]!='+')){return 0;}
  int dot_count=0;
  for (int i=1;i<s_amount.length();i++){
    if (!isdigit(s_amount[i]) && s_amount[i]!='.'){
      return 0;
    }
    if (s_amount[i]=='.'){
      dot_count+=1;
    }
    if (dot_count>=2){
      return 0;
    }
  }
  float amount=stof(s_amount);
  if (amount==0){return 0;}
  return 1;
}

//check whether the user input time fit the format
bool time_check(string time){
  if (time.length()==0) {return 1;}
  if (time.length()!=8){ return 0;}
  for (int i=0;i<time.length();i++){
    if (!isdigit(time[i])){
      return 0;
    }
  }
  if (time.substr(4,2)>"12" or time.substr(4,2)<"01"){ return 0;} //check if "month" is valid
  if (time.substr(6,2)>"31" or time.substr(6,2)<"01"){ return 0;} //check if "day" is valid
  return 1;
}
//transform all the user input data to lower case
void transform_lower (string &content){
  for (unsigned i=0;i<content.size();i++){
    content[i]=tolower(content[i]);
  }
}
//get the record from user input/ input promotion
void prompt_add_input(float &amount,string &time,string &type,string &method,string &remark){
  string s_amount;
  string choice_ei;
  // get the amount
  cout<<"Please indicate the amount,positive number means income and negative number means expense: ";
  getline(cin,s_amount);
  while (!amount_check(s_amount)){
    cout<<"Invalid amount,please enter again: ";
    getline(cin,s_amount);
  }
  //manuipulate the amount check
  if (s_amount.size()==0) {amount=0;}
  else {amount=stof(s_amount);}
  //get the time
  cout<<"Please enter the date(format:YYYYMMDD): ";
  getline(cin,time);
  while (!time_check(time)||time.size()==0){
    cout<<"Invalid input,please enter again: ";
    getline(cin,time);
  }
  time=time.substr(0,4)+"-"+time.substr(4,2)+"-"+time.substr(6,2);
  transform_lower(time);
  //get type/method/remark
  cout<<"Please enter the type of expense/income: ";
  getline(cin,type);
  transform_lower(type);
  cout<<"Please enter the payment method of expense/income: ";
  getline(cin,method);
  transform_lower(method);
  cout<<"Please add some remark to the record: ";
  getline(cin,remark);
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
  List_fill(typeList,type);
  List_fill(methodList,method);
}
//************************End of addition function*****************************************
//********************************************************************************************
//**********************The start of the show function***************************************
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
  init.copyfmt(cout);
  cout<<"  "<<left<<setw(6)<<i;
  cout<<setw(1)<<" "<<setw(8)<<(recordList[i]).get_amount();
  cout<<setw(10)<<(recordList[i]).get_time();
  cout<<setw(6)<<"      "<<setw(18)<<(recordList[i]).get_type();
  cout<<setw(2)<<"  "<<setw(20)<<(recordList[i]).get_method()<<setw(2)<<"  ";
  cout.copyfmt(init);
  cout<<left<<(recordList[i]).get_remark()<<endl;
}

void show_header()
{
  cout << endl;
  cout<<left<<setw(5)<<"Index"<<setw(3)<<"   "<<setw(6)<<"Amount"<<setw(6)<<"      "<<setw(8)<<"Date"<<setw(5)<<"   "<<setw(20)<<"Type"<<setw(22)<<"Method"<<setw(6)<<"Remark"<<endl;
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
  show_header();
  int i=0,count=0;
  string option;
  while (i<recordList.size())
  {
    show_record(recordList,i);
    i++; count++;
    if (count==5)
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


void sort_amount(vector<Record> &recordList)
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
    if (count==5)
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

  while (i>=negative_index)
  {
    show_record(recordList,i);
    i--;count++;
    if (count==5)
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

void sort_method(vector<Record> &recordList)
{
  sort(recordList.begin(),recordList.end(),compareMethod);
  show_header();
  int i=0,count=0;
  string option;
  while (i<recordList.size())
  {
    show_record(recordList,i);
    i++; count++;
    if (count==5)
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

void sort_type(vector<Record> &recordList)
{
  sort(recordList.begin(),recordList.end(),compareType);
  show_header();
  int i=0,count=0;
  string option;
  while (i<recordList.size())
  {
    show_record(recordList,i);
    i++; count++;
    if (count==5)
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

void search_time(vector<Record> &recordList)
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

  show_header();
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
  if (low=="0") {l=-99999999;} else{l=stof(low);}
  if (high=="0") {h=99999999;} else {h=stof(high);}

  show_header();
  for (int i=0;i<recordList.size();i++)  //assume it is a vector
  {
    if (recordList[i].get_amount() >= l && recordList[i].get_amount() <= h)
    {show_record(recordList,i);}
  }
}

void search_method(vector<Record> &recordList,map<string,int> &methodList)
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
  for (int i=0;i<recordList.size();i++)  //assume it is a vector
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
  {cout << (*itr).first << "  |  ";}  //showing existing type
  cout << endl;
  cout << "Please enter a type you want to search for(press Enter to exit): ";
  string type;
  getline(cin,type);
  transform_lower(type);  //transform "type" into lower case
  show_header();
  for (int i=0;i<recordList.size();i++)  //assume it is a vector
  {
    if (recordList[i].get_type() == type)
    {show_record(recordList,i);}
  }
}

void update_map(map<string,int> &m,string key,int change)
{
  if (change==1)
  {
    if (m.count(key)==0) {m[key]=1;}
    else {m[key]+=1;}
  }
  else if (change==-1)
  {
    if (m[key]==1) {m.erase(key);}
    else {m[key]-=1;}
  }
}

void edit_mode(float &income,float &expense,float &budget,vector<Record> &recordList,map<string,int> &methodList, map<string,int> &typeList)
{
  sort_time(recordList); cout<<endl;
  cout << "You are now in the edit mode,please enter the corresponding index to edit record(press Enter to Exit): ";
  string input;
  getline(cin,input);
  if (input.size()==0) {return;}
  while (!int_check(input))
  {
    cout << "Invalid input, please enter again: ";
    getline(cin,input);
    if (input.size()==0) {return;}
  }
  int i = stoi(input);
  show_record(recordList,i);
  cout << "Please edit the record, if you want to keep the origin data, please Enter 0" << endl;
  cout << "Please enter the Amount(positive number means income, negative number means expense): ";
  getline(cin,input);
  while (!amount_check(input) && input!="0")
  {
    cout << "Invalid input, please enter again: ";
    getline(cin,input);
  }
  if (input=="0");
  else
  {
    float oldamount = recordList[i].get_amount();
    float newamount = stof(input);
    if (oldamount<0) {expense+=oldamount;}  //because the expense here is positive
    else if (oldamount>0) {income-=oldamount;}
    if (newamount<0) 
    {
      expense-=newamount;
      if (expense>=budget) {cout<<"The current expense is: "<<expense<< " ,You have exceeded the budget of "<<budget<<endl;}  //because the expense here is positive
    }
    else if (newamount>0) {income+=newamount;}
    recordList[i].set_amount(newamount);
  }

  cout << "Please enter the Date(Format:YYYYMMDD): ";
  getline(cin,input);
  while (!time_check(input))
  {
    cout << "Invalid input, please enter again: ";
    getline(cin,input);
  }
  if (input.size()==0);
  else {recordList[i].set_time(input.substr(0,4)+"-"+input.substr(4,2)+"-"+input.substr(6,2));}

  cout << "Please enter the Method: ";
  getline(cin,input);
  if (input.size()==0);
  else
  {
    string oldmethod = recordList[i].get_method();
    string newmethod = input;
    update_map(methodList,oldmethod,-1);
    update_map(methodList,newmethod,1);
    recordList[i].set_method(input);
  }

  cout << "Please enter the Type: ";
  getline(cin,input);
  if (input.size()==0);
  else
  {
    string oldtype = recordList[i].get_type();
    string newtype = input;
    update_map(typeList,oldtype,-1);
    update_map(typeList,newtype,1);
    recordList[i].set_type(input);
  }

  cout << "Please enter the Remark: ";
  getline(cin,input);
  if (input.size()==0);
  else {recordList[i].set_remark(input);}
}

void delete_mode(float &income,float &expense,float &budget,vector<Record> &recordList,map<string,int> &methodList, map<string,int> &typeList)
{
  sort_time(recordList); cout<<endl;
  cout << "You are now in the delete mode,please enter the corresponding integer to delete record(press Enter to Exit): ";
  string input;
  getline(cin,input);
  if (input.size()==0) {return;}
  while (!int_check(input))
  {
    cout << "Invalid input, please enter again: ";
    getline(cin,input);
    if (input.size()==0) {return;}
  }
  int i = stoi(input);
  float oldamount = recordList[i].get_amount();
  if (oldamount<0) {expense-=oldamount;}
  else if (oldamount>0) {income-=oldamount;}
  string oldmethod = recordList[i].get_method();
  update_map(methodList,oldmethod,-1);
  string oldtype = recordList[i].get_type();
  update_map(typeList,oldtype,-1);
  recordList.erase(recordList.begin()+i);
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


//********************************************************************************************
// ************************The start of the write data in to user_record function(Ending funtion)***********
//write data in to the user's individual record
void write_data(string &login_user, string &user_password,vector <Record> &recordList,float &budget, float &income, float &expense){
  //write to update user_record.txt
  ofstream fin((login_user+"_record.txt").c_str());
  if (fin.fail()){
    cout<<"fail to open "<<login_user<<"_record.txt"<<endl;
    exit(1);
  }
  for (int i=0;i<recordList.size();i++){
    string line;
    line=to_string(recordList[i].get_amount())+"|"+recordList[i].get_time()+"|"+recordList[i].get_type()+"|"+recordList[i].get_method()+"|"+recordList[i].get_remark();
    fin<<line<<endl;
  }
  fin.close();
  // write to update users.txt
  ofstream temp("temp.txt");
  ifstream user_file("users.txt");
  string copy_line;
  while (getline(user_file,copy_line)){
    if (copy_line.find(login_user+"#")==0){
      temp<<login_user<<"#"<<user_password<<"#"<<budget<<"#"<<income<<"#"<<expense<<endl;
    }
    else{
      temp<<copy_line<<endl;
    }
  }
  temp.close();
  user_file.close();
  char user_file_char []="users.txt";
  remove(user_file_char);
  rename("temp.txt", user_file_char);
  cout<<"Logout successfully"<<endl;
}
// The End of the write data in to user_record function(Ending funtion)
//************************************************************************************************
// ************************The start of the financial report function*****************************
void print_menu3(){
  cout << endl;
  cout<<"1.Set budget"<<endl;
  cout<<"2.View the type report"<<endl;
  cout<<"3.View the method report"<<endl;
  cout<<"4.View overall expense and income by date"<<endl;
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
  return (amount*100);
}

void print_graph (map <float,string> &datamap,float &income,float &expense,string x_header){
    cout<<"Income Percentage"<<endl;
    cout<<"A"<<endl;
    cout<<"I"<<endl;
    for (int j=19;j>=0;j--){
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
        else if ((j*0.05-((itr->first)/income))<0.05){cout<<fixed<<setprecision(1)<<to_percentage((itr->first)/income)<<"%     ";}
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
   for (int j=19;j>=0;j--){
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
       else if ((((itr->first)/expense)+j*0.05)<0.05){cout<<fixed<<setprecision(1)<<to_percentage(-(itr->first)/expense)<<"%     ";}
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
    typemap[Category_income]=itr->first;
    typemap[Category_expense]=itr->first;
  }
  cout << endl;
  print_graph(typemap,income,expense,"Type");
  for (map <float,string>::iterator itr=typemap.begin();itr!=typemap.end();itr++){
    if ((itr->first)>0){
      cout<<"The "<<left<<setw(10)<<itr->second<<"income  is +"<<fixed<<setprecision(1)<<setw(9)<<itr->first<<" occupying "<<setw(5)<<to_percentage(itr->first/income)<< "% "<<"of total income"<<endl;
    }
    if ((itr->first)<0){
      cout<<"The "<<left<<setw(10)<<itr->second<<"expense is "<<fixed<<setprecision(1)<<setw(10)<<itr->first<<" occupying "<<setw(5)<<to_percentage(-(itr->first/expense))<<"% "<<"of total expense"<<endl;
    }
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
    methodmap[Category_income]=itr->first;
    methodmap[Category_expense]=itr->first;
  }
  cout << endl;
  print_graph(methodmap,income,expense,"Method");
  for (map <float,string>::iterator itr=methodmap.begin();itr!=methodmap.end();itr++){
    if ((itr->first)>0){
      cout<<"The income  via "<<left<<setw(10)<<itr->second<<" is +"<<fixed<<setprecision(1)<<setw(9)<<itr->first<<" occupying "<<setw(5)<<to_percentage(itr->first/income)<<"% "<<"of total income"<<endl;
    }
    if ((itr->first)<0){
      cout<<"The expense via "<<left<<setw(10)<<itr->second<<" is "<<fixed<<setprecision(1)<<setw(10)<<itr->first<<" occupying "<<setw(5)<<to_percentage(-(itr->first/expense))<<"% "<<"of total expense"<<endl;
    }
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
  cout<<"The total income      in this interval is: +"<<interval_income<<endl;
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
    else if (choice==""){break;}
    else{cout<<"Invalid input,please enter again: ";}
  }
}




//*************************The end of the financial report function*************************
//****************************The start of the password change function***********************
void change_password(string &login_user,string &user_password){
   string username,password;
   cout<<"**********************************************************************"<<endl;
   cout<<"You have enter the password changing mode"<<endl;
   cout<<"Please enter your username: ";
   while (true){
    getline(cin,username);
    if (username==login_user){
      cout<<"Please enter the password: ";
      getline(cin,password);
      if (password==user_password){
        break;
      }
      else{cout<<"Incorrect password, please enter the username again: ";}
    }
    else{cout<<"Incorrect username, please enter the username again: ";}
  }
  string password_1,password_2;
  while (true){
    cout<<"Please enter your new password: ";
    getline(cin,password_1);
    cout<<"Please enter your new password again: ";
    getline(cin,password_2);
    if (password_1==password_2){
      user_password=password_1;
      cout<<"New password will be in effect after log out"<<endl;
      return;
    }
    else{
      cout<<"Please enter the identical password"<<endl;
      cout<<endl;
    }
 }
}
//*****************************The end of the password change function**********************
//**************************************************************************************************8
//               main execution function
int main()
{ string login_user="",user_password="";
  float budget=99999999,income,expense;
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
  /*for (int i=0;i<recordList.size();i++){
    cout<<(recordList[i]).get_amount()<<" "<<(recordList[i]).get_time()<<" "<<(recordList[i]).get_type()<<" "<<(recordList[i]).get_method()<<" "<<(recordList[i]).get_remark()<<" "<<endl;
  }
  for (map <string,int>::iterator itr=typeList.begin();itr!=typeList.end();itr++){
    cout<<itr->first<<" "<<itr->second<<endl;
  }
  for (map <string,int>::iterator itr=methodList.begin();itr!=methodList.end();itr++){
    cout<<itr->first<<" "<<itr->second<<endl;
  }
  return 0;*/
}
