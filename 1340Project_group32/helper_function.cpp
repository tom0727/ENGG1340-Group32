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
bool isalnum(char c) //checking if the char is a Alphabet or number
{
  if ((c>=65 and  c<=90) or (c>=97 and c<=122) or (c<=57 and c>=48))
  {return 1;}
  else {return 0;}
}

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

bool time_check(string time)  //check if this string is a valid date format
{
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

bool int_check(string amount)  //check if this is an integer
{
  for (int i=0;i<amount.length();i++){
    if (!isdigit(amount[i])){
      return 0;
    }
  }
  return 1;
}

bool compareTime(Record &r1,Record &r2)
{ return (r1.get_time() > r2.get_time()); }  //From new to old time

bool compareAmount(Record &r1,Record &r2)
{ return (r1.get_amount() > r2.get_amount()); }  //From big to small amount

bool compareMethod(Record &r1,Record &r2)
{ return (r1.get_method() < r2.get_method()); }

bool compareType(Record &r1,Record &r2)
{ return (r1.get_type() < r2.get_type()); }

bool time_check2(string time)  //only used in financial_report part, the format is YYYYMM
{
  if (time.length()!=6){ return 0;}
  for (int i=0;i<time.length();i++){
    if (!isdigit(time[i])){
      return 0;
    }
  }
  if (time.substr(4,2)>"12" or time.substr(4,2)<"01"){ return 0;} //check if "month" is valid
  return 1;
}

