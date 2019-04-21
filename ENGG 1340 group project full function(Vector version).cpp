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


struct RecordCategory //RecordCategory is struct,contains type and corresponding count.
{
  int count;
  string category;
};


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
  cout<<"******************************"<<endl;
  cout<<"Welcome to private accounting system"<<endl;
  cout<<"1.Sign up"<<endl;
  cout<<"2.Login in"<<endl;
  cout<<"3.Exit"<<endl;
  cout<<"Please select the menu by entering corresponding number"<<endl;
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
      cout<<"This username has been registered by someone else,please try another one"<<endl;
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
  cout<<"******************************"<<endl;
  cout<<"Registration:"<<endl;
  while (true){
    cout<<"please settle your username, username should only contain Alphabet or digit"<<endl;
    getline(cin,username);
    if (username_check(username)==true){
      cout<<"please settle your password"<<endl;
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
bool authentification(string &login_user,float &user_budget,float &user_income,float &user_expenditure){
  string userrecord;
  string password;
  string username;
  string userdata;
  cout<<"*********************************"<<endl;
  cout<<"Login:"<<endl;
  cout<<"Please input your username"<<endl;
  while (true){
    getline(cin,username);
    if (username_find(userrecord,username)){
      cout<<"Please input the password"<<endl;
      getline(cin,password);
      int extract_length=username.size()+password.size()+1;
      if ((userrecord.find(username+"#"+password)==0) and (userrecord.substr(extract_length,1)=="#")){
        cout<<"Login successful"<<endl;
        // load initial data for login user
        login_user=username;
        userrecord=userrecord.substr(extract_length+1,userrecord.size()-extract_length);
        extract_length=userrecord.find("#");
        user_budget=stof(userrecord.substr(0,extract_length));
        userrecord=userrecord.substr(extract_length+1,userrecord.size()-extract_length);
        extract_length=userrecord.find("#");
        user_income=stof(userrecord.substr(0,extract_length));
        userrecord=userrecord.substr(extract_length+1,userrecord.size()-extract_length);
        user_expenditure=stof(userrecord.substr(0,userrecord.find("#")));
        return 1;
      }
      else{
        cout<<"Incorrect password,please input username again, Input 000 to return to main menu"<<endl;
      }
    }
    else if (username=="000"){return 0;}
    else{cout<<"User name not found,please input username again,Input 000 to return to main menu"<<endl;}
  }
}

//                          END of Login function
//********************************************************************************/
// main function for part I
void login(string &login_user,float &user_budget,float &user_income,float &user_expenditure){
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
      if (authentification(login_user,user_budget,user_income,user_expenditure)){break;}
      printmenu();
    }
    else if (choice=="3"){
        exit(1);
      }
    else{
        cout<<"please input valid choice"<<endl;
    }
  }
}
//                    End of the login program
//***************************************************************************
// *************************start of the load data from file section(load function)  ******************
//function to use user record to fill in both typelist and method list
void List_fill(vector <RecordCategory> &List,string value){
  bool newtype=1;
  for (int i=0;i<List.size();i++){
    if (List[i].category==value){
      List[i].count+=1;
      newtype=0;
      break;
    }
  }
  if (newtype==1){
    RecordCategory temp={1,value};
    List.push_back(temp);
  }
}

//extract information from user_record.txt and fill in recordList
void load_userdata(string login_user,   vector<Record> &recordList,  vector<RecordCategory> &typeList, vector<RecordCategory> &methodList){
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
  cout<<"*************************************"<<endl;
  cout<<"Function needed to be choose"<<endl;
  cout<<"1.Add"<<endl;
  cout<<"2.Exit"<<endl;
  cout<<"Please select the menu by entering corresponding number"<<endl;
}
//************************************************************************************
// *****************************The start of the addition section***********************88
//check whether the user input function are valid
bool amount_check(string amount){
  int dot_count=0;
  for (int i=0;i<amount.length();i++){
    if (!isdigit(amount[i]) && amount[i]!='.'){
      return 0;
    }
    if (amount[i]=='.'){
      dot_count+=1;
    }
    if (dot_count>=2){
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
  //get the type: expense or income
  cout<<"Please indicate type of record"<<endl;
  cout<<"1.Expense"<<endl;
  cout<<"2.Income"<<endl;
  getline(cin,choice_ei);
  while (choice_ei!="1" && choice_ei!="2"){
      cout<<"Invalid option please input again"<<endl;
      getline(cin,choice_ei);
  }
  // get the amount
  cout<<"Please indicate the amount"<<endl;
  getline(cin,s_amount);
  while (!amount_check(s_amount)){
    cout<<"Invalid amount please input again"<<endl;
    getline(cin,s_amount);
  }
  //precess the amount
  if (choice_ei=="1"){amount=stof("-"+s_amount);}
  else{amount=stof("+"+s_amount);}
  //get the time
  cout<<"Please enter the year month date by following exactly format: YYYYMMDD"<<endl;
  getline(cin,time);
  while (!time_check(time)){
    cout<<"Invalid input please input again"<<endl;
    getline(cin,time);
  }
  time=time.substr(0,4)+"-"+time.substr(4,2)+"-"+time.substr(6,2);
  transform_lower(time);
  //get type/method/remark
  cout<<"Please input the type of expense/income"<<endl;
  getline(cin,type);
  transform_lower(type);
  cout<<"Please input the payment method of expense/income"<<endl;
  getline(cin,method);
  transform_lower(method);
  cout<<"Please add some remark to the record"<<endl;
  getline(cin,remark);
  transform_lower(remark);
}

// add record from user
void add(vector<Record> &recordList,vector<RecordCategory> &typeList, vector<RecordCategory> &methodList, float &user_income, float &user_expenditure){
  string time,type,method,remark;
  float amount;
  prompt_add_input(amount,time,type,method,remark);
  if (amount>0){
    user_income+=amount;
  }
  else{
    user_expenditure-=amount;
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
// ************************The start of the write data in to user_record function(Ending funtion)***********
//write data in to the user's individual record
void write_data(string login_user, vector <Record> &recordList,float &user_budget, float &user_income, float &user_expenditure){
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
      int username_length,password_length;
      username_length=copy_line.find("#");
      password_length=copy_line.find("#",username_length+1);
      temp<<copy_line.substr(0,password_length+1)<<user_budget<<"#"<<user_income<<"#"<<user_expenditure<<endl;
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
//*********************************************************************************************
//               main execution function
int main()
{ string login_user="";
  float user_budget,user_income,user_expenditure;
  vector<Record> recordList;
  vector<RecordCategory> typeList;
  vector<RecordCategory> methodList;
  login(login_user,user_budget,user_income,user_expenditure);
  load_userdata(login_user,recordList,typeList,methodList);
  // The overall menu of function avaliable for execution after login
  string choice;
  print_menu2();
  while (true){
    getline(cin,choice);
    if (choice=="1"){
      add(recordList,typeList,methodList,user_income,user_expenditure);
      print_menu2();
      }
    else if (choice=="2"){
      write_data(login_user,recordList,user_budget,user_income,user_expenditure);
      break;
      }
    else {
      cout<<"please input valid choice"<<endl;
    }
  }
  for (int i=0;i<recordList.size();i++){
    cout<<(recordList[i]).get_amount()<<" "<<(recordList[i]).get_time()<<" "<<(recordList[i]).get_type()<<" "<<(recordList[i]).get_method()<<" "<<(recordList[i]).get_remark()<<" "<<endl;
  }
  for (int i=0;i<typeList.size();i++){
    cout<<(typeList[i]).category<<" "<<(typeList[i]).count<<endl;
  }
  for (int i=0;i<methodList.size();i++){
    cout<<(methodList[i]).category<<" "<<(methodList[i]).count<<endl;
  }


  return 0;
}
