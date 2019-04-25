//user.cpp is used for registeration, login, loading, writing data, changing password and
//other user-relevant functions
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <map>
#include "headerfile.h"
using namespace std;
void print_menu1(){
  cout<<"********************************************************************************************************"<<endl;
  cout<<"Welcome to private accounting system"<<endl;
  cout<<"1.Sign up"<<endl;
  cout<<"2.Login"<<endl;
  cout<<"Please select the menu by entering corresponding number(Press Enter to Exit): ";
}
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
//Registration function

/* register account and record it in to the file*/
void registeraccount(){
  string username;
  string password;
  cout<<"*****************************************************************************************************"<<endl;
  cout<<"Registration:"<<endl;
  while (true){
    cout<<"Username should only contain Alphabet or digit"<<endl;
    cout<<"Please settle your username (Press Enter to Exit): ";
    getline(cin,username);
    if (username==""){return;}
    if (username_check(username)==true){
      cout<<"please settle your password: ";
      getline(cin,password);
      ofstream File ("users.txt",ofstream::app);
      ofstream RecordFile ((username+"_record.txt").c_str());
      if (File.fail()){
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
  print_menu1();
  while (login_user==""){
    getline(cin,choice);
    if (choice=="1"){
        registeraccount();
        print_menu1();
      }
    else if (choice=="2"){
      if (authentification(login_user,user_password,budget,income,expense)){break;}
      print_menu1();
    }
    else if (choice.size()==0){
        exit(1);
      }
    else{
        cout<<"Invalid input, please enter again: (press Enter to exit)";
    }
  }
}

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

void change_password(string &login_user,string &user_password){
   string username,password;
   cout<<"**********************************************************************"<<endl;
   cout<<"You are changing your password"<<endl;
   cout<<"Please enter your username(Press Enter to Exit): ";
   while (true){
    getline(cin,username);
    if (username==""){return;}
    if (username==login_user){
      cout<<"Please enter the old password: ";
      getline(cin,password);
      if (password==user_password){
        break;
      }
      else{cout<<"Incorrect password, please enter the username again(Press Enter to Exit):";}
    }
    else{cout<<"Incorrect password, please enter the username again(Press Enter to Exit):";}
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
