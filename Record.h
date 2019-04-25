
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
void Record::set_amount(float );
void Record::set_time(string);
void Record::set_type(string);
void Record::set_method(string);
void Record::set_remark(string);
float Record::get_amount();
string Record::get_time();
string Record::get_type();
string Record::get_method();
string Record::get_remark();
bool isalnum(char );
void print_menu1();
void create_usertxt();
bool username_check (string);
void registeraccount();
bool username_find(string &, string );
bool authentification(string &,string &,float &,float &,float &);
void login(string &,string &,float &,float &,float &);
void List_fill(map <string,int> &,string );
void load_userdata(string,  vector<Record> &,  map <string,int> &, map <string,int> &);
void print_menu2();
bool amount_check(string );
bool time_check(string);
void transform_lower (string &);
void prompt_add_input(float &,string &,string &,string &,string &);
void add(vector<Record> &, map <string,int> &, map<string,int> &, float &, float &, float &);
bool int_check(string );
void show_menu();
void show_record(vector<Record> &,int &);
void show_header();
bool compareTime(Record &,Record &);
bool compareAmount(Record &,Record &);
bool compareMethod(Record &,Record &);
bool compareType(Record &,Record &);
void sort_time(vector<Record> &);
void sort_amount(vector<Record> &);
void sort_method(vector<Record> &);
void sort_type(vector<Record> &);
void search_time(vector<Record> &);
void search_amount(vector<Record> &);
void search_method(vector<Record> &,map<string,int> &);
void search_type(vector<Record> &,map<string,int> &);
void update_map(map<string,int> &,string,int );
void edit_record(float &,float &,float &,vector<Record> &,map<string,int> &, map<string,int> &,int );
void edit_mode(float &,float &,float &,vector<Record> &,map<string,int> &, map<string,int> &);
void delete_record(float &,float &,float &,vector<Record> &,map<string,int> &, map<string,int> &,int );
void delete_mode(float &,float &,float &,vector<Record> &,map<string,int> &, map<string,int> &);
void show(float &,float &,float &,vector<Record> &,map<string,int> &, map<string,int> &);
void write_data(string &, string &,vector <Record> &,float &, float &, float &);
void print_menu3();
void set_budget(float &, float &);
float to_percentage (float );
void print_graph (map <float,string> &,float &,float &,string);
void Show_Income_Expense_ByType(vector <Record> &,map <string,int> &,float &,float &);
void Show_Income_Expense_ByMethod(vector <Record> &,map <string,int> &,float &,float &);
void date_increment(string &date);
void print_graph2 (map <string,float> &,map <string,float> &,float &,float &,string);
bool time_check2(string );
void Show_Income_Expense_ByMonth(vector <Record> &);
void Show_Income_Expense_ByDate(vector <Record> &);
void financial_report(vector <Record> &,map <string,int> &, map <string,int> &,float &,float &,float &);
void change_password(string &,string &);
