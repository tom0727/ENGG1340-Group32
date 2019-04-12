#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
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


struct RecordType  //RecordType is struct,contains type and corresponding count.
{
  int count;
  string type;
};

struct RecordMethod  //RecordMethod is struct,contains method and corresponding count.
{
  int count;
  string method;
};

int main()
{
  Record *recordList = new Record[100];  //recordList is a pointer,type is Record 
  RecordType *typeList = new RecordType[100];
  RecordMethod *methodList = new RecordMethod[100];

  delete [] recordList; //These 3 delete are used only for testing
  delete [] typeList;  //They may be put somewhere else in the complete program.
  delete [] methodList;
  return 0;
}
