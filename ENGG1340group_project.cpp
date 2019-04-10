#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/* print the starting menu*/
void printmenu(){
  int choice;
  cout<<"******************************"<<endl;
  cout<<"Welcome to private accounting system"<<endl;
  cout<<"1.Sign up"<<endl;
  cout<<"2.Login in"<<endl;
  cout<<"3.Exit"<<endl;
  cout<<"Please select the menu by entering corresponding number"<<endl;
}

//***********************************************************************
//Registration function

/* check whether username_input is in the correct format
1. It should be alphabet and number character only
2. It should not be already registered by others*/
bool username_check (string username){
  // Perform selection 1
  for (int i=0;i<username.size();i++){
    if (!((username[i]>=65 and  username[i]<=90) or (username[i]>=97 and  username[i]<=122) or (username[i]<=57 and username[i]>=48))){
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
  while (true){
    cout<<"******************************"<<endl;
    cout<<"Registration:"<<endl;
    cout<<"please settle your username, username should only contain Alphabet or digit"<<endl;
    getline(cin,username);
    if (username_check(username)==true){
      cout<<"please settle your password"<<endl;
      getline(cin,password);
      ofstream File ("users.txt",ofstream::app);
      if (File.fail()){
        cout<<"Fail to open users.txt"<<endl;
        exit(1);
      }
      File<<username<<"#"<<password<<endl;
      File.close();
      cout<<"Registeration successful"<<endl;
      break;
    }
}
}
/*                            END OF REGISTRATION function
******************************************************************************
Login function*/

// Find the user name in correct format and serach corresponding line in the user.txt//
bool username_find(string &userrecord, string username){
  for (int i=0;i<username.size();i++){
    if (!((username[i]>=65 and  username[i]<=90) or (username[i]>=97 and  username[i]<=122) or (username[i]<=57 and username[i]>=48))){
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
bool authentification(string &login_user){
  string userrecord;
  string password;
  string username;
  cout<<"*********************************"<<endl;
  cout<<"Login:"<<endl;
  cout<<"Please input your username"<<endl;
  while (true){
    getline(cin,username);
    if (username_find(userrecord,username)){
      cout<<"Please input the password"<<endl;
      getline(cin,password);
      if (username+"#"+password==userrecord){
        cout<<"Login successful"<<endl;
        login_user=username;
        return 1;
      }
      else{
        cout<<"Incorrect password,please input username again, Input 000 to return to main menu"<<endl;
      }
    }
    else if (username=="000"){
      break;
    }
    else{
      cout<<"User name not found,please input username again,Input 000 to return to main menu"<<endl;
    }
  }
  return 0;
}
/*                          END of Login program
********************************************************************************/
/* main function for part I */
string login(){
  string login_user="";
  string choice;
  printmenu();
  while (login_user==""){
    getline(cin,choice);
    if (choice=="1"){
        registeraccount();
        printmenu();
      }
    else if (choice=="2"){
      if (authentification(login_user)){
        break;
      }
      printmenu();
    }
    else if (choice=="3"){
        exit(1);
      }
    else{
        cout<<"please input valid choice"<<endl;
    }
  }
  return login_user;
}

//main function for overall execution
int main(){
   cout<<login()<<endl;
}
