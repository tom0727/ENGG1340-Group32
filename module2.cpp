#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <fstream>
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

 private:
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
//function to use user record to fill in both typelist and record list
void List_fill(RecordCategory *&List, int &List_length, string value){
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
  }
}

//extract information from user_record.txt and fill in recordList
void load_userdata(string login_user, Record *&recordList, RecordCategory *&typeList ,RecordCategory *&methodList,int &length_recordList, int &length_typeList,int &length_methodList){
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
     List_fill(typeList,length_typeList,current_type);
     List_fill(methodList,length_methodList,current_method);
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

int main()
{
  Record *recordList = new Record[100];  //recordList is a pointer,type is Record
  RecordCategory *typeList = new RecordCategory[100];
  RecordCategory *methodList = new RecordCategory[100];
  int length_recordList=0;
  int length_typeList=0;
  int length_methodList=0;
  load_userdata(login_user,recordList,typeList,methodList,length_recordList,length_typeList,length_methodList);
  delete [] recordList; //These 3 delete are used only for testing
  delete [] typeList;  //They may be put somewhere else in the complete program.
  delete [] methodList;
  return 0;
}
