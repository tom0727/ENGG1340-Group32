//user.cpp is used for registeration, login, loading, writing data, changing password and
//other specific user-relevant functions
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <map>
#include "headerfile.h"
using namespace std;
// print the Login menu
void print_menu1(){
  cout<<"********************************************************************************************************"<<endl;
  cout<<"Welcome to private accounting system"<<endl;
  cout<<"1.Sign up"<<endl;
  cout<<"2.Login"<<endl;
  cout<<"Please select the menu by entering corresponding number(Press Enter to Exit): ";
}

// print the main menu after login
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
// users.txt stores the login username and password of each user also each user's relevant informtion (total income/expense and allowed budget)
// each line in the users.txt store information of one user in the following format:
//username#password#budget#income#expense
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

//helper function
// check whether the password contain the seperator '#' in users.txt file 
bool password_check(string &password){
  for (int i=0;i<password.size();i++){
    if (password[i]=='#'){return 0;}
  }
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
    cout<<"Please settle your username (Press Enter to Exit): ";
    getline(cin,username);
    if (username==""){return;}
    // username_check would check whether the username proposed is already registered by someone else or whether the user name is in the correct format
    // i.e. only contain number and alphabet character
    if (username_check(username)==true){
      // prompt user to set his password
      cout<<"please settle your password: ";
      getline(cin,password);
      if (!password_check(password)){
        cout<<"Password should not contain #"<<endl;
        continue;
      }
      ofstream File ("users.txt",ofstream::app);
      ofstream RecordFile ((username+"_record.txt").c_str());
      if (File.fail()){
        exit(1);
      }
      // write newly deined username and password to the users.txt and initialize the income/budget /expense to 0
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
// if there is such username in the file return true
// OUTPUT: whether the inputed username is in the file
// INPUT: the user prompted usename 
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
  cout<<"Please enter your username (Press Enter to Exit): ";
  while (true){
    getline(cin,username);
    // To check whether inputed username exist in the users.txt file
    //and extract that specific line in the users.txt for use
    if (username_find(userrecord,username)){
      cout<<"Please enter the password (Press Enter to Exit): ";
      getline(cin,password);
      int extract_length=username.size()+password.size()+1;
      if ((userrecord.find(username+"#"+password)==0) and (userrecord.substr(extract_length,1)=="#")){
        cout<<"Login successful"<<endl;
        // load initial data for login user
        // load the login username
        login_user=username;
        // load the login password
        user_password=password;
        // manupulate the recordline extract from the users.txt /find value seperator "#" to initialize different information
        userrecord=userrecord.substr(extract_length+1,userrecord.size()-extract_length);
        // load the budget of that logined user
        extract_length=userrecord.find("#");
        budget=stof(userrecord.substr(0,extract_length));
        // load the budget of that logined user
        userrecord=userrecord.substr(extract_length+1,userrecord.size()-extract_length);
        extract_length=userrecord.find("#");
        income=stof(userrecord.substr(0,extract_length));
        // load the expense of that logined user
        userrecord=userrecord.substr(extract_length+1,userrecord.size()-extract_length);
        expense=stof(userrecord.substr(0,userrecord.find("#")));
        return 1;
      }
      else if (username==""){return 0;}
      else{cout<<"Incorrect password,please enter username again(press Enter to return to main menu): ";}
    }
    // press Enter to return to previous menu
    else if (username==""){return 0;}
    else{cout<<"User name not found,please enter username again(press Enter to return to main menu): ";}
  }
}

//                          END of Login function
//********************************************************************************/
// main function for part I(Login and sign up section )
void login(string &login_user,string &user_password,float &budget,float &income,float &expense){
  string choice;
  create_usertxt();
  // print the login and sign up menu
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
    // press ENTER to exit the program
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

//extract information from user_record.txt and fill in recordList, typeList, methodList
// recordList: store each record including: amount /date/usage of money /method of payment /remark
// typeList: key: the name of the usage of money 
//         value: the number of records having that particular usage of money
// methodList: key: the name of the mehtod of payment 
//         value: the number of records having that particular method of payment
// The data storage format in the user_record function is :
// amount|date|usage of money|method of payment|remark
void load_userdata(string login_user,  vector<Record> &recordList,  map <string,int> &typeList, map <string,int> &methodList){
   string record_line;
   ifstream record((login_user+"_record.txt").c_str());
   if (record.fail()){
     cout<<"This user does not exist"<<endl;
     exit(1);
   }
   // read each line of the users_record.txt to load each record to the program
   while (getline(record,record_line)){
     // temp: a Record object which stores currently loading record and transfer to the recordList
     Record temp;
     //current_type,current_method: the usage of money and method of payment of current reading line record
     string current_type;
     string current_method;
     int seperator_position [4];
     // find the seperator in the user_records.txt to extract different data, seperator: |
     for (int i=0;i<4;i++){
       seperator_position[i]=record_line.find("|");
       record_line.replace(seperator_position[i],1,"~");
     }
     // according to the seperator position of each recordline to load corresponding data
     // load amount
     temp.set_amount(stof((record_line.substr(0,seperator_position[0])).c_str()));
     //load date
     temp.set_time(record_line.substr(seperator_position[0]+1,seperator_position[1]-seperator_position[0]-1));
     current_type=record_line.substr(seperator_position[1]+1,seperator_position[2]-seperator_position[1]-1);
     // load the usage of money
     temp.set_type(current_type);
     current_method=record_line.substr(seperator_position[2]+1,seperator_position[3]-seperator_position[2]-1);
     // load the payment method
     temp.set_method(current_method);
     // load remark
     temp.set_remark(record_line.substr(seperator_position[3]+1,record_line.size()-seperator_position[3]-1));
     recordList.push_back(temp);
     // update typeList and mehtod list according to the the usage of money and method of payment of current loading  record
     List_fill(typeList,current_type);
     List_fill(methodList,current_method);
   }
   record.close();
}


// It is the ending function which would update the change in record to the user_record.txt and users.txt file 
// It is always the last function to execute before end
void write_data(string &login_user, string &user_password,vector <Record> &recordList,float &budget, float &income, float &expense){
  //write to update user_record.txt
  //Rewrite the entire file to update the changes
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
  // Create the temp file and copy all the original lines in users.txt file to it 
  // Except the line with record relted to the login user
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
  // delete the original users.txt file and rename the temp.txt file to the user.txt file
  char user_file_char []="users.txt";
  remove(user_file_char);
  rename("temp.txt", user_file_char);
  cout<<"Logout successfully"<<endl;
}

// Execute the fourth function of the print_menu2 after login 
// users could use this funcition to change their password
void change_password(string &login_user,string &user_password){
   string username,password;
   cout<<"**********************************************************************"<<endl;
   cout<<"You are changing your password"<<endl;
   cout<<"Please enter your username(Press Enter to Exit): ";
   // Authetification process to allow user to retype username and password to verify its identity
   while (true){
    getline(cin,username);
    if (username==login_user){
      cout<<"Please enter the old password: ";
      getline(cin,password);
      if (password==user_password){break;}
      else{cout<<"Incorrect password, please enter the username again(Press Enter to Exit):";}
    }
    else if (username==""){return;}
    else{cout<<"Incorrect username, please enter the username again(Press Enter to Exit):";}
  }
  // set new password 
  string password_1,password_2;
  while (true){
    cout<<"Please enter your new password: ";
    getline(cin,password_1);
    if (!password_check(password)){
        cout<<"Password should not contain #"<<endl;
        continue;
      }
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
